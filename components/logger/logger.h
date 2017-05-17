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

#ifndef COMPONENTS_LOGGER_LOGGER_H_
#define COMPONENTS_LOGGER_LOGGER_H_

#include <string.h>
#include "utils/types.h"

//--------------------------------------------------------------------
#ifdef ENABLE_DEBUG
#undef ENABLE_DEBUG
#endif
#define ENABLE_DEBUG 1

enum MsgTypeEnum {
  MSGTYPE_DD = 0,
  MSGTYPE_WW,
  MSGTYPE_EE,
  MSGTYPE_FF,
  MSGTYPE_TR,
  MSGTYPE_INF
};

typedef enum MsgTypeEnum MsgType;

#if ENABLE_DEBUG

#ifdef DBG_MSG
#undef DBG_MSG
#endif
#define DBG_MSG(...) \
  _print(MSGTYPE_DD, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__);

#ifdef DBG_WARNING
#undef DBG_WARNING
#endif
#define DBG_WARNING(...) \
  _print(MSGTYPE_WW, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__);

#ifdef DBG_ERROR
#undef DBG_ERROR
#endif
#define DBG_ERROR(...) \
  _print(MSGTYPE_EE, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__);

#ifdef DBG_FATAL
#undef DBG_FATAL
#endif
#define DBG_FATAL(...) \
  _print(MSGTYPE_FF, __FILENAME__, __LINE__, __FUNCTION__, __VA_ARGS__);

#ifdef DBG_TRACE
#undef DBG_TRACE
#endif
#define DBG_TRACE _trace(__FILENAME__, __LINE__, __FUNCTION__, "");

#ifdef AUTO_TRACE
#undef AUTO_TRACE
#endif
#define AUTO_TRACE AutoTrace trace(__FILENAME__, __FUNCTION__, __LINE__);

void print(const char* file, UInt32 line, const char* method, const char* text);
void _print(MsgType level, const char* file, UInt32 line, const char* method,
            const char* fmt, ...);
void _trace(const char* file, UInt32 line, const char* method, const char* text);
void traceOpen(const char* pTraceFName);
void traceClose();

#ifdef __cplusplus
class AutoTrace {
 private:
  const char* file_name;
  const char* func_name;
  UInt32 line_;

 public:
  AutoTrace(const char* name, const char* func, UInt32 line)
      : file_name(name), func_name(func), line_(line) {
    _trace(file_name, line_, func_name, "ENTER");
  }
  ~AutoTrace() {
    _trace(file_name, line_, func_name, "EXIT");
    file_name = NULL;
    func_name = NULL;
  }
};
#endif

#else  // #if ENABLE_DEBUG

#ifdef DBG_MSG
#undef DBG_MSG
#endif
#define DBG_MSG(...)

#ifdef DBG_WARNING
#undef DBG_WARNING
#endif
#define DBG_WARNING(...)

#ifdef DBG_ERROR
#undef DBG_ERROR
#endif
#define DBG_ERROR(...)

#ifdef DBG_FATAL
#undef DBG_FATAL
#endif
#define DBG_FATAL(...)

#ifdef DBG_MSG
#undef DBG_MSG
#endif
#define DBG_MSG(...)

#ifdef DBG_WARNING
#undef DBG_WARNING
#endif
#define DBG_WARNING(...)

#ifdef DBG_ERROR
#undef DBG_ERROR
#endif
#define DBG_ERROR(...)

#ifdef DBG_FATAL
#undef DBG_FATAL
#endif
#define DBG_FATAL(...)

#ifdef DBG_TRACE
#undef DBG_TRACE
#endif
#define DBG_TRACE

#ifdef AUTO_TRACE
#undef AUTO_TRACE
#endif
#define AUTO_TRACE

#define traceOpen (x)
#define traceClose ()

#endif  // ENABLE_DEBUG

/**
 * The function returns a short file name from its full file name
 * Platform independent
 *
 * @param pFileName The full file name
 *
 * @return The pointer to the string with the short file name
 */
static const char* const getFileName(const char* const pFileName) {
  const char* pRet = 0;

  do {
    if (0 == pFileName) {
      break;
    }

    if (0 == (pRet = strrchr(pFileName, '/')) &&
        0 == (pRet = strrchr(pFileName, '\\'))) {
      break;
    }

    ++pRet;
  } while (0);

  if (0 == pRet) {
    pRet = pFileName;
  }

  return pRet;
}

#undef __FILENAME__
#define __FILENAME__ getFileName(__FILE__)

#endif  // COMPONENTS_LOGGER_LOGGER_H_
