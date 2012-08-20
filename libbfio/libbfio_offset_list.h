/*
 * Offset list
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

#if !defined( _LIBBFIO_OFFSET_LIST_H )
#define _LIBBFIO_OFFSET_LIST_H

#include <common.h>
#include <types.h>

#include "libbfio_libcerror.h"
#include "libbfio_list_type.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libbfio_offset_list_value libbfio_offset_list_value_t;

struct libbfio_offset_list_value
{
	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;

	/* The last offset
	 */
	off64_t last_offset;
};

typedef struct libbfio_offset_list libbfio_offset_list_t;

struct libbfio_offset_list
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

	/* The current list element
	 */
	libbfio_list_element_t *current_element;

	/* The current list element index
	 */
	int current_element_index;
};

int libbfio_offset_list_value_initialize(
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error );

int libbfio_offset_list_value_free(
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error );

int libbfio_offset_list_value_clone(
     libbfio_offset_list_value_t **destination_offset_list_value,
     libbfio_offset_list_value_t *source_offset_list_value,
     libcerror_error_t **error );

int libbfio_offset_list_initialize(
     libbfio_offset_list_t **offset_list,
     libcerror_error_t **error );

int libbfio_offset_list_free(
     libbfio_offset_list_t **offset_list,
     libcerror_error_t **error );

int libbfio_offset_list_empty(
     libbfio_offset_list_t *offset_list,
     libcerror_error_t **error );

int libbfio_offset_list_clone(
     libbfio_offset_list_t **destination_offset_list,
     libbfio_offset_list_t *source_offset_list,
     libcerror_error_t **error );

int libbfio_offset_list_get_number_of_elements(
     libbfio_offset_list_t *offset_list,
     int *number_of_elements,
     libcerror_error_t **error );

int libbfio_offset_list_append_range(
     libbfio_offset_list_t *offset_list,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error );

int libbfio_offset_list_append_offset_list(
     libbfio_offset_list_t *offset_list,
     libbfio_offset_list_t *source_offset_list,
     libcerror_error_t **error );

int libbfio_offset_list_insert_element(
     libbfio_offset_list_t *offset_list,
     libbfio_list_element_t *offset_list_element,
     libbfio_list_element_t *element,
     libcerror_error_t **error );

int libbfio_offset_list_insert_value(
     libbfio_offset_list_t *offset_list,
     libbfio_list_element_t *offset_list_element,
     libbfio_offset_list_value_t *offset_list_value,
     libcerror_error_t **error );

int libbfio_offset_list_remove_element(
     libbfio_offset_list_t *offset_list,
     libbfio_list_element_t *element,
     libcerror_error_t **error );

int libbfio_offset_list_remove_range(
     libbfio_offset_list_t *offset_list,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error );

int libbfio_offset_list_get_element_by_index(
     libbfio_offset_list_t *offset_list,
     int element_index,
     libbfio_list_element_t **element,
     libcerror_error_t **error );

int libbfio_offset_list_get_element_by_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     libbfio_list_element_t **element,
     libcerror_error_t **error );

int libbfio_offset_list_get_value_by_index(
     libbfio_offset_list_t *offset_list,
     int element_index,
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error );

int libbfio_offset_list_get_value_by_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error );

int libbfio_offset_list_get_range(
     libbfio_offset_list_t *offset_list,
     int element_index,
     off64_t *range_offset,
     size64_t *range_size,
     libcerror_error_t **error );

int libbfio_offset_list_get_range_by_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     off64_t *range_offset,
     size64_t *range_size,
     libcerror_error_t **error );

int libbfio_offset_list_range_is_present(
     libbfio_offset_list_t *offset_list,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

