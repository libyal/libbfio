/*
 * Offset list
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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

#include <liberror.h>

#include "libbfio_list_type.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libbfio_offset_list_values libbfio_offset_list_values_t;

struct libbfio_offset_list_values
{
	/* The offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;
};

int libbfio_offset_list_values_free(
     intptr_t *values,
     liberror_error_t **error );

int libbfio_offset_list_values_compare(
     intptr_t *first,
     intptr_t *second,
     liberror_error_t **error );

int libbfio_offset_list_add_offset(
     libbfio_list_t *offset_list,
     off64_t offset,
     size64_t size,
     liberror_error_t **error );

int libbfio_offset_list_get_offset(
     libbfio_list_t *offset_list,
     int index,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error );

int libbfio_offset_list_get_offset_by_value(
     libbfio_list_t *offset_list,
     off64_t offset_value,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error );

int libbfio_offset_list_range_is_present(
     libbfio_list_t *offset_list,
     off64_t offset,
     size64_t size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

