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

#ifndef COMPONENTS_UTILS_TYPES_H_
#define COMPONENTS_UTILS_TYPES_H_

#include <sys/types.h>

/** @typedef Int8
 *  @brief Definition for integral type with 8 bits
 *
 * Type Int8 has a sign. It can contain negative values.
 * Range of Int8: -128..127
 */
typedef signed char Int8;

/** @typedef UInt8
 *  @brief Definition for integral type with 8 bits.
 *
 * Type UInt8 contains only positive values.
 * Range of UInt8: 0..255
 */
typedef unsigned char UInt8;

/** @typedef  Int16
 *  @brief Definition for integral type with 16 bits
 *
 * Type Int16 has a sign. It can contain negative values.
 * Range of Int16: -32,768..32,767
 */
typedef signed short Int16;  // NOLINT

/** @typedef  UInt16
 *  @brief Definition for integral type with 16 bits
 *
 * Type UInt16 contains only positive values.
 * Range of UInt16: 0..65,535
 */
typedef unsigned short UInt16;  // NOLINT

/** @typedef  WChar
 *  @brief Definition for integral type with 32 bits
 *
 * This is a synonym for UInt32.
 */
typedef unsigned int WChar;

/** @typedef  Int32
 *  @brief Definition for integral type with 32 bits
 *
 * Type Int32 has a sign. It can contain negative values.
 * Range of Int32: -2,147,483,648..2,147,483,647
 */
typedef signed int Int32;

/** @typedef  UInt32
 *  @brief Definition for integral type with 32 bits
 *
 * Type UInt32 contains only positive values.
 * Range of UInt32: 0..4,294,967,295
 */
typedef unsigned int UInt32;

/** @typedef  Int64
 *  @brief Definition for integral type with 64 bits
 *
 * Type Int64 has a sign. It can contain negative values.
 * Range of Int64: -9,223,372,036,854,775,808..9,223,372,036,854,775,807
 */
typedef signed long long int Int64;  // NOLINT

/** @typedef  UInt64
 *  @brief Definition for integral type with 64 bits
 *
 * Type UInt64 contains only positive values.
 * Range of UInt64: 0..18,446,744,073,709,551,615
 */
typedef unsigned long long int UInt64;  // NOLINT

#endif  // SRC_FRAMEWORK_UTILS_TYPES_H_
