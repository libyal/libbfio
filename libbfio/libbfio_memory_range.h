/*
 * Memory range functions
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBBFIO_MEMORY_RANGE_H )
#define _LIBBFIO_MEMORY_RANGE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libbfio_extern.h"
#include "libbfio_system_string.h"
#include "libbfio_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libbfio_memory_range_io_handle libbfio_memory_range_io_handle_t;

struct libbfio_memory_range_io_handle
{
	/* The start of the memory range
	 */
	uint8_t *range_start;

	/* The size of the memory range
	 */
	size_t range_size;

	/* The current offset in the memory range
	 */
	size_t range_offset;

	/* Value to indicate the current access flags
	 */
	int access_flags;
};

int libbfio_memory_range_io_handle_initialize(
     libbfio_memory_range_io_handle_t **memory_range_io_handle,
     liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_memory_range_initialize(
                    libbfio_handle_t **handle,
                    liberror_error_t **error );

int libbfio_memory_range_io_handle_free(
     intptr_t *io_handle,
     liberror_error_t **error );

int libbfio_memory_range_io_handle_clone(
     intptr_t **destination_io_handle,
     intptr_t *source_io_handle,
     liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_memory_range_get(
                    libbfio_handle_t *handle,
                    uint8_t **range_start,
                    size_t *range_size,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_memory_range_set(
                    libbfio_handle_t *handle,
                    uint8_t *range_start,
                    size_t range_size,
                    liberror_error_t **error );

int libbfio_memory_range_open(
     intptr_t *io_handle,
     int flags,
     liberror_error_t **error );

int libbfio_memory_range_close(
     intptr_t *io_handle,
     liberror_error_t **error );

ssize_t libbfio_memory_range_read(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error );

ssize_t libbfio_memory_range_write(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error );

off64_t libbfio_memory_range_seek_offset(
         intptr_t *io_handle,
         off64_t offset,
         int whence,
         liberror_error_t **error );

int libbfio_memory_range_exists(
     intptr_t *io_handle,
     liberror_error_t **error );

int libbfio_memory_range_is_open(
     intptr_t *io_handle,
     liberror_error_t **error );

int libbfio_memory_range_get_size(
     intptr_t *io_handle,
     size64_t *size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

