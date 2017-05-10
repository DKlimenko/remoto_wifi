/*
 * Copyright (c) 2016, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "utils/file_system.h"
#include <sys/statvfs.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#include <sstream>
// TODO(VS): lint error: Streams are highly discouraged.
#include <fstream>
#include <cstddef>
#include <cstdio>
#include <algorithm>

#include "logger/logger.h"
#include "utils/scope_guard.h"
#include "utils/macro.h"

bool file_system::IsDirectory(const std::string& name) {
  struct stat status = {0};

  if (-1 == stat(name.c_str(), &status)) {
    return false;
  }

  return S_ISDIR(status.st_mode);
}

bool file_system::DirectoryExists(const std::string& name) {
  struct stat status = {0};

  if (-1 == stat(name.c_str(), &status) || !S_ISDIR(status.st_mode)) {
    return false;
  }

  return true;
}

bool file_system::FileExists(const std::string& name) {
  struct stat status = {0};

  if (-1 == stat(name.c_str(), &status)) {
    return false;
  }
  return true;
}

bool file_system::IsAccessible(const std::string& name, int32_t how) {
  return !access(name.c_str(), how);
}

bool file_system::IsWritingAllowed(const std::string& name) {
  return IsAccessible(name, W_OK);
}

bool file_system::IsReadingAllowed(const std::string& name) {
  return IsAccessible(name, R_OK);
}

std::vector<std::string> file_system::ListFiles(
    const std::string& directory_name) {
  std::vector<std::string> listFiles;
  if (!DirectoryExists(directory_name)) {
    return listFiles;
  }

  int32_t return_code = 0;
  DIR* directory = NULL;
#ifndef __QNXNTO__
  struct dirent dir_element_;
  struct dirent* dir_element = &dir_element_;
#else
  char* direntbuffer =
      new char[offsetof(struct dirent, d_name) +
               pathconf(directory_name.c_str(), _PC_NAME_MAX) + 1];
  struct dirent* dir_element = new (direntbuffer) dirent;
#endif
  struct dirent* result = NULL;

  directory = opendir(directory_name.c_str());
  if (NULL != directory) {
    return_code = readdir_r(directory, dir_element, &result);

    for (; NULL != result && 0 == return_code;
         return_code = readdir_r(directory, dir_element, &result)) {
      if (0 == strcmp(result->d_name, "..") ||
          0 == strcmp(result->d_name, ".")) {
        continue;
      }

      listFiles.push_back(std::string(result->d_name));
    }

    closedir(directory);
  }

#ifdef __QNXNTO__
  delete[] direntbuffer;
#endif

  return listFiles;
}

/**
  * @brief Reads from file
  *
  * @param fd file descriptor
  * @param result read data
  * @return returns true if the operation is successfully.
  */
bool file_system::ReadFile(const int fd, std::string* result) {
  struct stat buf;
  int rc = fstat(fd, &buf);
  if (rc == -1) {
    DBG_ERROR("Unable to readfile %d. error \n \t: %s", fd, ::strerror(errno));
    return false;
  }
  ssize_t file_size = buf.st_size;
  char* buffer = new char[file_size];
  utils::ScopeGuard guard =
      utils::MakeGuard(utils::ArrayDeleter<const char*>, buffer);
  UNUSED(guard);
  const ssize_t read_result = read(fd, buffer, file_size);
  if (-1 == read_result) {
    return false;
    DBG_ERROR("Unable to readfile %d. error \n \t: %s", fd, ::strerror(errno));
  }
  *result = std::string(buffer);
  return true;
}

bool file_system::ReadFileChunk(const std::string& file_name, size_t offset,
                                size_t chunk_size, std::string* result) {
  FILE* file = fopen(file_name.c_str(), "rb");
  if (!file) {
    DBG_ERROR("File error '%s'", strerror(errno));
    fclose(file);
    return false;
  }

  struct stat file_info;
  int rc = fstat(fileno(file), &file_info);
  if (rc == -1) {
    DBG_ERROR("Unable to readfile %d. error: '%s'", file, ::strerror(errno));
    fclose(file);
    return false;
  }

  char* buffer = new char[chunk_size];
  utils::ScopeGuard guard =
      utils::MakeGuard(utils::ArrayDeleter<const char*>, buffer);
  UNUSED(guard);

  if (0 != fseek(file, offset, SEEK_SET)) {
    DBG_ERROR("Unable to reposition stream position %d. error '%s'", file,
              ::strerror(errno));
    fclose(file);
    return false;
  }

  const ssize_t read_result = read(fileno(file), buffer, chunk_size);
  if (-1 == read_result) {
    DBG_ERROR("Unable to read file %s. error '%s'", file_name.c_str(),
              ::strerror(errno));
    fclose(file);
    return false;
  }

  *result = std::string(buffer);
  fclose(file);
  return true;
}

ssize_t file_system::ReadFileChunk(const std::string& file_name, size_t offset,
                                   size_t chunk_size, UInt8* result) {
  FILE* file = fopen(file_name.c_str(), "rb");
  ssize_t read_result = 0;
  if (!file) {
    DBG_ERROR("File error '%s'", strerror(errno));
    fclose(file);
    return read_result;
  }

  struct stat file_info;
  int rc = fstat(fileno(file), &file_info);
  if (rc == -1) {
    DBG_ERROR("Unable to readfile %d error: '%s'", file, ::strerror(errno));
    fclose(file);
    return read_result;
  }

  if (0 != fseek(file, offset, SEEK_SET)) {
    DBG_ERROR("Unable to reposition stream position %d. error '%s'", file,
              ::strerror(errno));
    fclose(file);
    return read_result;
  }

  read_result = read(fileno(file), result, chunk_size);
  if (-1 == read_result) {
    DBG_ERROR("Unable to read file %s. error '%s'", file_name.c_str(),
              ::strerror(errno));
    fclose(file);
    return read_result;
  }

  fclose(file);
  return read_result;
}

size_t file_system::GetFileSize(const std::string& file_name) {
  FILE* file = fopen(file_name.c_str(), "rb");
  if (!file) {
    DBG_ERROR("File error '%s'", strerror(errno));
    fclose(file);
    return false;
  }

  struct stat file_info;
  int rc = fstat(fileno(file), &file_info);
  if (rc == -1) {
    DBG_ERROR("Unable to read file %s. error %s", file_name.c_str(),
              strerror(errno));
    fclose(file);
    return false;
  }

  size_t file_size = file_info.st_size;
  fclose(file);
  return file_size;
}
