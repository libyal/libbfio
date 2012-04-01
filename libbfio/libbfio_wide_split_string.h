/*
 * Split wide string functions
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBBFIO_WIDE_SPLIT_STRING_H )
#define _LIBBFIO_WIDE_SPLIT_STRING_H

#include <common.h>
#include <types.h>

#include "libbfio_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if defined( HAVE_WIDE_CHARACTER_TYPE )

typedef struct libbfio_wide_split_string libbfio_wide_split_string_t;

struct libbfio_wide_split_string
{
	/* The number of string segments
	 */
	int number_of_segments;

	/* The string
	 */
	wchar_t *string;

	/* The string size
	 */
	size_t string_size;

	/* The segments
	 */
	wchar_t **segments;

	/* The segment sizes
	 */
	size_t *segment_sizes;
};

int libbfio_wide_split_string_initialize(
     libbfio_wide_split_string_t **split_string,
     const wchar_t *string,
     size_t string_size,
     int number_of_segments,
     libcerror_error_t **error );

int libbfio_wide_split_string_free(
     libbfio_wide_split_string_t **split_string,
     libcerror_error_t **error );

int libbfio_wide_split_string_get_string(
     libbfio_wide_split_string_t *split_string,
     wchar_t **string,
     size_t *string_size,
     libcerror_error_t **error );

int libbfio_wide_split_string_get_number_of_segments(
     libbfio_wide_split_string_t *split_string,
     int *number_of_segments,
     libcerror_error_t **error );

int libbfio_wide_split_string_get_segment_by_index(
     libbfio_wide_split_string_t *split_string,
     int segment_index,
     wchar_t **string_segment,
     size_t *string_segment_size,
     libcerror_error_t **error );

int libbfio_wide_split_string_set_segment_by_index(
     libbfio_wide_split_string_t *split_string,
     int segment_index,
     wchar_t *string_segment,
     size_t string_segment_size,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif

