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

#ifndef COMPONENTS_UTILS_MACRO_H_
#define COMPONENTS_UTILS_MACRO_H_

#ifdef DEBUG
#include <assert.h>
#else  // RELEASE
#endif
#include "logger/logger.h"

// A macro to disallow the copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&);               \
  void operator=(const TypeName&)

#define UNUSED(x) (void) x;

#define SKIP_RETURN_VALUE(FUNC) static_cast<void>((FUNC));

#ifdef DEBUG
#define ASSERT(condition) \
  do {                    \
    assert(condition);    \
  } while (false)
#else  // RELEASE
#define ASSERT(condition) DBG_ERROR("Failed condition \"" #condition "\"");
#endif

#define DCHECK(condition)                          \
  if (!(condition)) {                              \
    DBG_ERROR("DCHECK failed \"" #condition "\""); \
    ASSERT((condition));                           \
  }

/*
 * Will cauch assert on debug version,
 * Will return return_value in release build
 */
#define DCHECK_OR_RETURN(condition, return_value)  \
  if (!(condition)) {                              \
    DBG_ERROR("DCHECK failed \"" #condition "\""); \
    ASSERT((condition));                           \
    return (return_value);                         \
  }

/*
 * Will cauch assert on debug version,
 * Will return return_value in release build
 */
#define DCHECK_OR_RETURN_VOID(condition)           \
  if (!(condition)) {                              \
    DBG_ERROR("DCHECK failed \"" #condition "\""); \
    ASSERT((condition));                           \
    return;                                        \
  }

#define NOTREACHED()               \
  do {                             \
    DBG_ERROR("Unreachable code"); \
    ASSERT(false);                 \
  } while (false)

/*
* @brief Calculate size of na array
* @param arr  array, which size need to calculate
*/
#define ARRAYSIZE(arr) sizeof(arr) / sizeof(*arr)

#endif  // SRC_FRAMEWORK_UTILS_MACRO_H_
