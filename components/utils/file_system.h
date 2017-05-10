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

#ifndef COMPONENTS_UTILS_FILE_SYSTEM_H_
#define COMPONENTS_UTILS_FILE_SYSTEM_H_

#include <string.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <iostream>
#include "utils/types.h"

namespace file_system {

/**
  * @brief Checks the file to see whether the file is a directory
  * @param name path to file
  * @return returns true if file is directory.
  */
bool IsDirectory(const std::string& name);

/**
  * @brief Is directory exist
  * @param name path to directory
  * @return returns true if directory is exists.
  */
bool DirectoryExists(const std::string& name);

/**
  * @brief Is file exist
  * @param name path to file
  * @return returns true if file is exists.
  */
bool FileExists(const std::string& name);

/**
  * @brief Check access rights
  *
  * @param name path to file.
  * @param how Read/write attribute.
  * @return returns true if file has the given mode.
  */
bool IsAccessible(const std::string& name, int32_t how);

/**
  * @brief Check access rights for writing
  *
  * @param name path to file or folder
  * @return returns true if has access rights.
  */
bool IsWritingAllowed(const std::string& name);

/**
  * @brief Check access rights for reading
  *
  * @param name path to file.
  * @return returns true if file has access rights.
  */
bool IsReadingAllowed(const std::string& name);

/**
  * @brief Lists all files in given directory
  *
  * @param name path to directory.
  * @return returns list of files.
  */
std::vector<std::string> ListFiles(const std::string& directory_name);

/**
  * @brief Reads from file
  *
  * @param fd file descriptor
  * @param result read data
  * @return returns true if the operation is successfully.
  */
bool ReadFile(const int fd, std::string* result);

/**
  * @brief Reads from file a chunk of data
  *
  * @param file_name file to read
  * @param offset offset that must be applied
  * @param chunk_size Amount of data
  * @param result Final result stored in string
  * @return returns true if the operation is successfully.
  */
bool ReadFileChunk(const std::string& file_name, size_t offset,
                   size_t chunk_size, std::string* result);

/**
  * @brief Reads from file a chunk of data
  *
  * @param file_name file to read
  * @param offset offset that must be applied
  * @param chunk_size Amount of data
  * @param result Final result stored in pointer
  * @return On success, the number of bytes read is returned , otherwise 0
  *indicating error
  */
ssize_t ReadFileChunk(const std::string& file_name, size_t offset,
                      size_t chunk_size, UInt8* result);

/**
  * @brief Returns file size
  *
  * @param file_name file name
  */
size_t GetFileSize(const std::string& file_name);

}  // namespace file_system

#endif  // SRC_FRAMEWORK_UTILS_FILE_SYSTEM_H_
