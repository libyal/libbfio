/*
 * The internal handle functions
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

#if !defined( _LIBBFIO_INTERNAL_HANDLE_H )
#define _LIBBFIO_INTERNAL_HANDLE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libbfio_extern.h"
#include "libbfio_list_type.h"
#include "libbfio_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libbfio_internal_handle libbfio_internal_handle_t;

struct libbfio_internal_handle
{
	/* The io handle
	 */
	intptr_t *io_handle;

	/* The flags
	 */
	int flags;

	/* The current offset
	 */
	off64_t offset;

	/* The size
	 */
	size64_t size;

	/* Value to indicate the size was set
	 */
	uint8_t size_set;

	/* Value to indicate to open and close
	 * the systems file descriptor or handle on demand
	 */
	uint8_t open_on_demand;

	/* Reference to the pool last used list element
	 */
	libbfio_list_element_t *pool_last_used_list_element;

	/* Value to indicate to track offsets read
	 */
	uint8_t track_offsets_read;

	/* The offset ranges that were read
	 */
	libbfio_list_t *offsets_read;

	/* The free io handle function
	 */
	int (*free_io_handle)(
	       intptr_t *io_handle,
	       liberror_error_t **error );

	/* The clone (duplicate) io handle function
	 */
	int (*clone_io_handle)(
	       intptr_t **destination_io_handle,
	       intptr_t *source_io_handle,
	       liberror_error_t **error );

	/* The open function
	 */
	int (*open)(
	       intptr_t *io_handle,
	       int flags,
	       liberror_error_t **error );

	/* The close function
	 */
	int (*close)(
	       intptr_t *io_handle,
	       liberror_error_t **error );

	/* The read function
	 */
	ssize_t (*read)(
	           intptr_t *io_handle,
	           uint8_t *buffer,
	           size_t size,
	           liberror_error_t **error );

	/* The write function
	 */
	ssize_t (*write)(
	           intptr_t *io_handle,
	           uint8_t *buffer,
	           size_t size,
	           liberror_error_t **error );

	/* The seek offset function
	 */
	off64_t (*seek_offset)(
	           intptr_t *io_handle,
	           off64_t offset,
	           int whence,
	           liberror_error_t **error );

	/* The exists function
	 */
	int (*exists)(
	       intptr_t *io_handle,
	       liberror_error_t **error );

	/* The is open function
	 */
	int (*is_open)(
	       intptr_t *io_handle,
	       liberror_error_t **error );

	/* The get size function
	 */
	int (*get_size)(
	       intptr_t *io_handle,
	       size64_t *size,
	       liberror_error_t **error );

};

LIBBFIO_EXTERN int libbfio_handle_initialize(
                    libbfio_handle_t **handle,
                    intptr_t *io_handle,
                    int (*free_io_handle)( intptr_t *io_handle, liberror_error_t **error ),
                    int (*clone_io_handle)( intptr_t **destination_io_handle, intptr_t *source_io_handle, liberror_error_t **error ),
                    int (*open)( intptr_t *io_handle, int flags, liberror_error_t **error ),
                    int (*close)( intptr_t *io_handle, liberror_error_t **error ),
                    ssize_t (*read)( intptr_t *io_handle, uint8_t *buffer, size_t size, liberror_error_t **error ),
                    ssize_t (*write)( intptr_t *io_handle, uint8_t *buffer, size_t size, liberror_error_t **error ),
                    off64_t (*seek_offset)( intptr_t *io_handle, off64_t offset, int whence, liberror_error_t **error ),
                    int (*exists)( intptr_t *io_handle, liberror_error_t **error ),
                    int (*is_open)( intptr_t *io_handle, liberror_error_t **error ),
                    int (*get_size)( intptr_t *io_handle, size64_t *size, liberror_error_t **error ),
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_free(
                    libbfio_handle_t **handle,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_clone(
                    libbfio_handle_t **destination_handle,
                    libbfio_handle_t *source_handle,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_open(
                    libbfio_handle_t *handle,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_reopen(
                    libbfio_handle_t *handle,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_close(
                    libbfio_handle_t *handle,
                    liberror_error_t **error );

LIBBFIO_EXTERN ssize_t libbfio_handle_read(
                        libbfio_handle_t *handle,
                        uint8_t *buffer,
                        size_t size,
                        liberror_error_t **error );

LIBBFIO_EXTERN ssize_t libbfio_handle_write(
                        libbfio_handle_t *handle,
                        uint8_t *buffer,
                        size_t size,
                        liberror_error_t **error );

LIBBFIO_EXTERN off64_t libbfio_handle_seek_offset(
                        libbfio_handle_t *handle,
                        off64_t offset,
                        int whence,
                        liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_exists(
                    libbfio_handle_t *handle,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_is_open(
                    libbfio_handle_t *handle,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_get_flags(
                    libbfio_handle_t *handle,
                    int *flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_set_flags(
                    libbfio_handle_t *handle,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_get_size(
                    libbfio_handle_t *handle,
                    size64_t *size,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_get_offset(
                    libbfio_handle_t *handle,
                    off64_t *offset,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_set_open_on_demand(
                    libbfio_handle_t *handle,
                    uint8_t open_on_demand,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_set_track_offsets_read(
                    libbfio_handle_t *handle,
                    uint8_t track_offsets_read,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_get_amount_of_offsets_read(
                    libbfio_handle_t *handle,
                    int *amount_of_read_offsets,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_handle_get_offset_read(
                    libbfio_handle_t *handle,
                    int index,
                    off64_t *offset,
                    size64_t *size,
                    liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

