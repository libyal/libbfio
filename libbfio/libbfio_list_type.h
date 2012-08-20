/*
 * List type functions
 *
 * Copyright (c) 2009-2012, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBBFIO_LIST_TYPE_H )
#define _LIBBFIO_LIST_TYPE_H

#include <common.h>
#include <types.h>

#include "libbfio_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* The list comparison definitions
 */
enum LIBBFIO_LIST_COMPARE_DEFINITIONS
{
	/* The first value is less than the second value
	 */
        LIBBFIO_LIST_COMPARE_LESS,

	/* The first and second values are equal
	 */
        LIBBFIO_LIST_COMPARE_EQUAL,

	/* The first value is greater than the second value
	 */
        LIBBFIO_LIST_COMPARE_GREATER
};

/* The list insert flag definitions
 */
enum LIBBFIO_LIST_INSERT_FLAGS
{
	/* Allow duplicate entries
	 */
	LIBBFIO_LIST_INSERT_FLAG_NON_UNIQUE_ENTRIES	= 0x00,

	/* Only allow unique entries, no duplicates
	 */
	LIBBFIO_LIST_INSERT_FLAG_UNIQUE_ENTRIES		= 0x01,
};

typedef struct libbfio_list_element libbfio_list_element_t;

struct libbfio_list_element
{
	/* The previous list element
	 */
	libbfio_list_element_t *previous_element;

	/* The next list element
	 */
	libbfio_list_element_t *next_element;

	/* The value
	 */
	intptr_t *value;
};

typedef struct libbfio_list libbfio_list_t;

struct libbfio_list
{
	/* The number of elements
	 */
	int number_of_elements;

	/* The first element
	 */
	libbfio_list_element_t *first_element;

	/* The last element
	 */
	libbfio_list_element_t *last_element;
};

int libbfio_list_element_initialize(
     libbfio_list_element_t **element,
     libcerror_error_t **error );

int libbfio_list_element_free(
     libbfio_list_element_t **element,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libbfio_list_element_get_value(
     libbfio_list_element_t *element,
     intptr_t **value,
     libcerror_error_t **error );

int libbfio_list_element_set_value(
     libbfio_list_element_t *element,
     intptr_t *value,
     libcerror_error_t **error );

int libbfio_list_initialize(
     libbfio_list_t **list,
     libcerror_error_t **error );

int libbfio_list_free(
     libbfio_list_t **list,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libbfio_list_empty(
     libbfio_list_t *list,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libbfio_list_clone(
     libbfio_list_t **destination_list,
     libbfio_list_t *source_list,
     int (*value_free_function)(
            intptr_t **value,
            libcerror_error_t **error ),
     int (*value_clone_function)(
            intptr_t **destination,
            intptr_t *source,
            libcerror_error_t **error ),
     libcerror_error_t **error );

int libbfio_list_get_number_of_elements(
     libbfio_list_t *list,
     int *number_of_elements,
     libcerror_error_t **error );

int libbfio_list_get_element_by_index(
     libbfio_list_t *list,
     int list_element_index,
     libbfio_list_element_t **element,
     libcerror_error_t **error );

int libbfio_list_get_value_by_index(
     libbfio_list_t *list,
     int list_element_index,
     intptr_t **value,
     libcerror_error_t **error );

int libbfio_list_prepend_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     libcerror_error_t **error );

int libbfio_list_prepend_value(
     libbfio_list_t *list,
     intptr_t *value,
     libcerror_error_t **error );

int libbfio_list_append_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     libcerror_error_t **error );

int libbfio_list_append_value(
     libbfio_list_t *list,
     intptr_t *value,
     libcerror_error_t **error );

int libbfio_list_insert_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     int (*value_compare_function)(
            intptr_t *first,
            intptr_t *second,
            libcerror_error_t **error ),
     uint8_t insert_flags,
     libcerror_error_t **error );

int libbfio_list_insert_value(
     libbfio_list_t *list,
     intptr_t *value,
     int (*value_compare_function)(
            intptr_t *first,
            intptr_t *second,
            libcerror_error_t **error ),
     uint8_t insert_flags,
     libcerror_error_t **error );

int libbfio_list_remove_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

