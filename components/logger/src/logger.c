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

#include <stdarg.h> /* va_list, va_start, va_arg, va_end */
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "logger/logger.h"
#include "utils/mutex_locker.h"

//-------------------------------------------------------------------
#if ENABLE_DEBUG

bool sDebugEnabled = true;
bool sPrintToConsole = true;
static std::string TraceFName;

#define CLOSE_LOG_ALWAYS 0  // 0|1
#if !CLOSE_LOG_ALWAYS
static FILE* sLogfile = 0;
#endif

static char traceStr[2048];
// make logger mutex recursive to avoid deadlock
static sync_primitives::Lock mutex(true);
static MsgType sMsgType = MSGTYPE_DD;

void print(const char* file, UInt32 line, const char* method,
           const char* const text) {
  if (NULL == text) {
    return;
  }

  sync_primitives::AutoLock lock(&mutex);
  bool bEOLTerminated =
      false;  ///< Check whether the string is terminated by EOL
  if ('\0' != *text && '\n' == text[strlen(text) - 1]) {
    bEOLTerminated = true;
  }

// FIXME
// In some reason QNX implementation does not fflushes buffers when
// fflush() function is invoked. The opened file size keeps always zero
// until it is closed.
//
// Therefore, the file is opened every time current function is invoked
#if CLOSE_LOG_ALWAYS
  FILE* pLogfile = fopen(TraceFName.getBuffer(), "a");
#else
  FILE* pLogfile = sLogfile;
#endif

  FILE* pStreams[2] = {
      pLogfile, (false == sPrintToConsole) ? 0 : stdout,
  };

  for (UInt32 i = 0; sizeof pStreams / sizeof(pStreams[0]) > i; ++i) {
    FILE* pStream = pStreams[i];
    if (NULL != pStream) {
      const char* pMsgType = "  ";
      switch (sMsgType) {
        case MSGTYPE_DD: {
          pMsgType = "DD";
          break;
        }
        case MSGTYPE_WW: {
          pMsgType = "WW";
          break;
        }
        case MSGTYPE_EE: {
          pMsgType = "EE";
          break;
        }
        case MSGTYPE_FF: {
          pMsgType = "FF";
          break;
        }
        case MSGTYPE_TR: {
          pMsgType = "TR";
          break;
        }
        default: { break; }
      }

      time_t t = time(0);
      struct tm now;
      if (0 != localtime_r(&t, &now)) {
        fprintf(
            pStream,
            "%s %04d%02d%02d %02d:%02d:%02d [PID %d:TID %02X] %s %d %s() %s%s",
            pMsgType, now.tm_year + 1900, now.tm_mon + 1, now.tm_mday,
            now.tm_hour, now.tm_min, now.tm_sec, getpid(),
            static_cast<unsigned int>(pthread_self()), file, line, method, text,
            (false == bEOLTerminated) ? "\n" : "");

        SKIP_RETURN_VALUE(fflush(pStream));
      }
    }
  }

#if CLOSE_LOG_ALWAYS
  if (NULL != pLogfile) {
    fclose(pLogfile);
    pLogfile = 0;
  }
#endif
}

void _print(MsgType level, const char* file, UInt32 line, const char* method,
            const char* fmt, ...) {
  sync_primitives::AutoLock lock(&mutex);

  if (false == sDebugEnabled) return;

  /*lint -e530*/
  va_list argptr;

  // format the output string
  SKIP_RETURN_VALUE(va_start(argptr, fmt));

  traceStr[0] = 0;

  SKIP_RETURN_VALUE(::vsnprintf(traceStr, sizeof(traceStr), fmt, argptr));

  // write terminating zero
  traceStr[sizeof(traceStr) - 1] =
      0;  // lint !e613 a lint sematic is provided in the header
  //           file. If the caller passes a null pointer,
  //           a lint warning is emitted

  // done
  va_end(argptr);
  // lint -restore

  sMsgType = level;
  print(file, line, method, traceStr);
}

void _trace(const char* file, UInt32 line, const char* method,
            const char* text) {
  sync_primitives::AutoLock lock(&mutex);

  if (false == sDebugEnabled) return;

  sMsgType = MSGTYPE_TR;
  print(file, line, method, text);
}

void traceOpen(const char* pTraceFName) {
  TraceFName = pTraceFName;
  FILE* fp = 0;
  if ((fp = fopen(pTraceFName, "w")) != 0)
    printf("Create trace file %s\n", pTraceFName);
  else
    printf("Error: Can not create trace file %s\n", pTraceFName);

#if CLOSE_LOG_ALWAYS
  fclose(fp);
#else
  sLogfile = fp;
#endif
}

void traceClose() {
#if !CLOSE_LOG_ALWAYS
  if (sLogfile) {
    fflush(sLogfile);
    fclose(sLogfile);
    sLogfile = 0;
  }
#endif
}

#endif  // ENABLE_DEBUG
