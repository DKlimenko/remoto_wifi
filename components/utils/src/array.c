#include <stdlib.h>
#include <string.h>

#include "utils/array.h"

/* Automatically resizing array */

Array* array_new(UInt32 length) {
  // Use default value in case length is 0
  if (length <= 0) {
    length = 16;
  }
  Array* new_array;
  new_array = (Array*) malloc(sizeof(Array));

  if (NULL == new_array) {
    return NULL;
  }

  /* Allocate the data array */
  new_array->data_ = malloc(length * sizeof(Array));
  if (NULL == new_array->data_) {
    free(new_array);
    return NULL;
  }

  new_array->data_size_ = length;
  new_array->length_ = 0;

  return new_array;
}

void array_free(Array* array) {
	if (NULL != array) {
		free(array->data_);
		free(array);
	}
}

static UInt32 array_enlarge(Array* array) {
	ArrayValue* data;
	UInt32      newsize;

	// Double the allocated size
	newsize = array->data_size_ * 2;
	data = realloc(array->data_, sizeof(ArrayValue) * newsize);

	if (NULL == data) {
		return 0;
	} else {
		array->data_ = data;
		array->data_size_ = newsize;
		return 1;
	}
}

UInt32 array_insert(Array* array, UInt32 index, ArrayValue data) {
  if (index > array->length_) {
    return 0;
	}

	// Increase the size if necessary
	if (array->length_ + 1 > array->data_size_) {
		if (!array_enlarge(array)) {
			return 0;
		}
	}

	// Move the contents of the array forward from the index onwards
	memmove(&array->data_[index + 1],
	        &array->data_[index], 
	        (array->length_ - index) * sizeof(ArrayValue));

	// Insert the new entry at the index
	array->data_[index] = data;
	++array->length_;

	return 1;
}

UInt32 array_append(Array* array, ArrayValue data) {
	return array_insert(array, array->length_, data);
}

UInt32 array_prepend(Array* array, ArrayValue data) {
	return array_insert(array, 0, data);
}

void array_remove_range(Array* array, UInt32 index, UInt32 length) {
	// Check if range is valid
	if (index > array->length_ || index + length > array->length_) {
		return;
	}

	// Move back the entries following the range to be removed

	memmove(&array->data_[index],
	        &array->data_[index + length],
	        (array->length_ - (index + length)) * sizeof(ArrayValue));

	// Decrease length
	array->length_ -= length;
}

void array_remove(Array* array, UInt32 index) {
	array_remove_range(array, index, 1);
}

Int32 array_index_of(Array* array,
                     ArrayEqualFunc callback,
                     ArrayValue data) {
  for (UInt32 i = 0; i<array->length_; ++i) {
    if (callback(array->data_[i], data) != 0)
    return (int) i;
  }

	return -1;
}

void array_clear(Array* array) {
	//Set the length to zero
	array->length_ = 0;
}

static void array_sort_internal(ArrayValue* list_data,
                                UInt32 list_length,
                                ArrayCompareFunc compare_func) {
	// If less than two items, it is always sorted
	if (list_length <= 1) {
		return;
	}

	// Take the last item as the pivot
	ArrayValue pivot = list_data[list_length - 1];

 /* Divide the list into two lists:
  * List 1 contains data less than the pivot.
  * List 2 contains data more than the pivot.
  *
  * As the lists are build up, they are stored sequentially after
  * each other, ie. list_data[list1_length-1] is the last item
  * in list 1, list_data[list1_length] is the first item in
  * list 2.
  */

	UInt32 list1_length;
	for (UInt32 i = 0; i < list_length-1; ++i) {
		if (compare_func(list_data[i], pivot) < 0) {

			/* This should be in list 1.  Therefore it is in the
			 * wrong position. Swap the data immediately following
			 * the last item in list 1 with this data. */

			ArrayValue tmp = list_data[i];
			list_data[i] = list_data[list1_length];
			list_data[list1_length] = tmp;
			++list1_length;
    }
  }
	// The length of list 2 can be calculated
	UInt32 list2_length = list_length - list1_length - 1;

	/* list_data[0..list1_length-1] now contains all items which are
	   before the pivot.
	   list_data[list1_length..list_length-2] contains all items after
       or equal to the pivot. */

	/* Move the pivot into place, by swapping it with the item
	   immediately following the end of list 1.  */

	list_data[list_length-1] = list_data[list1_length];
	list_data[list1_length] = pivot;

	// Recursively sort the sublists
	array_sort_internal(list_data, list1_length, compare_func);
	array_sort_internal(&list_data[list1_length + 1], list2_length, compare_func);
}

void array_sort(Array* array, ArrayCompareFunc compare_func) {
	// Performs recursive sort
	array_sort_internal(array->data_, array->length_, compare_func);
}