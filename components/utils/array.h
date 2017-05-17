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

#ifndef COMPONENTS_UTILS_ARRAYLIST_H
#define COMPONENTS_UTILS_ARRAYLIST_H

#include "utils/types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * A value to be stored in an array.
 */

typedef void* ArrayValue;

/**
 * An array structure. New array can be created using the
 * array_new function. See array_new
 */
struct array {
	ArrayValue* data_;
	UInt8       length_;

  // private
	UInt8       data_size_;
};

/**
 * Definition of an array.
 */
typedef struct array Array;

/**
 * Compare two values in an array to determine if they are equal.
 *
 * @return Non-zero if the values are equal, zero if they are not equal.
 */
typedef UInt32 (*ArrayEqualFunc)(ArrayValue value1,
                                 ArrayValue value2);

/**
 * Compare two values in an array. Used by array_sort
 * when sorting values.
 *
 * @param value1              The first value.
 * @param value2              The second value.
 * @return                    A negative number if value1 should be sorted
 *                            before value2, a positive number if value2 should
 *                            be sorted before value1, zero if the two values
 *                            are equal.
 */
typedef UInt32 (*ArrayCompareFunc)(ArrayValue value1,
                                   ArrayValue value2);

/**
 * Allocate a new Array for use.
 *
 * @param length         Hint to the initialise function as to the amount
 *                       of memory to allocate initially to the ArrayList.
 *                       If a value of zero is given, a sensible default
 *                       size is used.
 * @return               A new arraylist, or NULL if it was not possible
 *                       to allocate the memory.
 * @see array_free
 */
Array* array_new(UInt32 length);

/**
 * Destroy an Array and frees memory.
 *
 * @param array  The Array to delete.
 */
void array_free(Array* array);

/**
 * Insert a value at the specified index in an Array. The index is limited by array size
 *
 * @param array          Array object.
 * @param index          Insert index value.
 * @param data           Value to insert.
 * @return               Non-zero on success, otherwise zero
 */
UInt32 array_insert(Array* array, UInt32 index, ArrayValue data);

/**
 * Append a value to the end of an Array.
 *
 * @param array          TArray object.
 * @param data           The value to append.
 * @return               Non-zero on success, otherwise zero
 */
UInt32 array_append(Array* array, ArrayValue data);

/**
 * Prepend a value from the beginning of an Array.
 *
 * @param array          Array object.
 * @param data           The value to prepend.
 * @return               Non-zero on success, otherwise zero
 */
UInt32 array_prepend(Array* array, ArrayValue data);

/**
 * Remove the entry at the specified location in an Array.
 *
 * @param array          Array object.
 * @param index          The index of the entry to remove.
 */
void array_remove(Array* array, UInt32 index);

/**
 * Remove a range of entries at the specified location in an Array.
 *
 * @param array          Array object.
 * @param index          Index of start range position to remove.
 * @param length         The length of the range to remove.
 */
void array_remove_range(Array* array, UInt32 index, UInt32 length);

/**
 * Find value in an Array by index.
 *
 * @param array          Array object.
 * @param callback       Callback function to be invoked to compare values.
 * @param data           The value to search for.
 * @return               The index of the value on success, otherwise -1.
 */
Int32 array_index_of(Array* array,
                     ArrayEqualFunc callback,
                     ArrayValue data);

/**
 * Remove all entries from an Array.
 *
 * @param array          Array object.
 */
void array_clear(Array* array);

/**
 * Sort the values in an Array.
 *
 * @param array          The Array.
 * @param compare_func   Function for comparition during in sorting.
 */
void array_sort(Array* array, ArrayCompareFunc compare_func);

#ifdef __cplusplus
}
#endif

#endif // COMPONENTS_UTILS_ARRAYLIST_H