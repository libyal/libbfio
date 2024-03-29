/*
 * File range functions
 *
 * Copyright (C) 2009-2024, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBBFIO_FILE_RANGE_H )
#define _LIBBFIO_FILE_RANGE_H

#include <common.h>
#include <types.h>

#include "libbfio_extern.h"
#include "libbfio_libcerror.h"
#include "libbfio_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBBFIO_EXTERN \
int libbfio_file_range_initialize(
     libbfio_handle_t **handle,
     libcerror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_file_range_get_name_size(
     libbfio_handle_t *handle,
     size_t *name_size,
     libcerror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_file_range_get_name(
     libbfio_handle_t *handle,
     char *name,
     size_t name_size,
     libcerror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_file_range_set_name(
     libbfio_handle_t *handle,
     const char *name,
     size_t name_length,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBBFIO_EXTERN \
int libbfio_file_range_get_name_size_wide(
     libbfio_handle_t *handle,
     size_t *name_size,
     libcerror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_file_range_get_name_wide(
     libbfio_handle_t *handle,
     wchar_t *name,
     size_t name_size,
     libcerror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_file_range_set_name_wide(
     libbfio_handle_t *handle,
     const wchar_t *name,
     size_t name_length,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBBFIO_EXTERN \
int libbfio_file_range_get(
     libbfio_handle_t *handle,
     off64_t *range_offset,
     size64_t *range_size,
     libcerror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_file_range_set(
     libbfio_handle_t *handle,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBBFIO_FILE_RANGE_H ) */

