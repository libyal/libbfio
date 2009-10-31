/*
 * The internal pool functions
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

#if !defined( _LIBBFIO_POOL_H )
#define _LIBBFIO_POOL_H

#include <common.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>

#include "libbfio_extern.h"
#include "libbfio_list_type.h"
#include "libbfio_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libbfio_internal_pool libbfio_internal_pool_t;

struct libbfio_internal_pool
{
	/* The amount of handles in the pool
	 */
	int amount_of_handles;

	/* The amount of used handles in the pool
	 */
	int amount_of_used_handles;

	/* The amount of open handles in the pool
	 */
	int amount_of_open_handles;

	/* The maximum amount of open handles in the pool
	 */
	int maximum_amount_of_open_handles;

	/* A dynamic array containing the handles
	 */
	libbfio_handle_t **handles;

	/* A list containing the file io handles in order of the last use
	 * it starts with the last used at the beginning of the list
	 * the value of the list element refers to the corresponding file io handle
	 */
	libbfio_list_t *last_used_list;
};

LIBBFIO_EXTERN int libbfio_pool_initialize(
                    libbfio_pool_t **pool,
                    int amount_of_handles,
                    int maximum_amount_of_open_handles,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_free(
                    libbfio_pool_t **pool,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_resize(
                    libbfio_pool_t *pool,
                    int amount_of_handles,
                    liberror_error_t **error );

int libbfio_pool_open_handle(
     libbfio_internal_pool_t *internal_pool,
     libbfio_handle_t *handle,
     int flags,
     liberror_error_t **error );

int libbfio_pool_add_handle_to_last_used_list(
     libbfio_internal_pool_t *internal_pool,
     libbfio_handle_t *handle,
     liberror_error_t **error );

int libbfio_pool_remove_handle_from_last_used_list(
     libbfio_internal_pool_t *internal_pool,
     libbfio_list_element_t *last_used_list_element,
     liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_get_handle(
                    libbfio_pool_t *pool,
                    int entry,
                    libbfio_handle_t **handle,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_add_handle(
                    libbfio_pool_t *pool,
                    int *entry,
                    libbfio_handle_t *handle,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_set_handle(
                    libbfio_pool_t *pool,
                    int entry,
                    libbfio_handle_t *handle,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_open(
                    libbfio_pool_t *pool,
                    int entry,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_reopen(
                    libbfio_pool_t *pool,
                    int entry,
                    int flags,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_close(
                    libbfio_pool_t *pool,
                    int entry,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_close_all(
                    libbfio_pool_t *pool,
                    liberror_error_t **error );

LIBBFIO_EXTERN ssize_t libbfio_pool_read(
                        libbfio_pool_t *pool,
                        int entry,
                        uint8_t *buffer,
                        size_t size,
                        liberror_error_t **error );

LIBBFIO_EXTERN ssize_t libbfio_pool_write(
                        libbfio_pool_t *pool,
                        int entry,
                        uint8_t *buffer,
                        size_t size,
                        liberror_error_t **error );

LIBBFIO_EXTERN off64_t libbfio_pool_seek_offset(
                        libbfio_pool_t *pool,
                        int entry,
                        off64_t offset,
                        int whence,
                        liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_get_size(
                    libbfio_pool_t *pool,
                    int entry,
                    size64_t *size,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_get_offset(
                    libbfio_pool_t *pool,
                    int entry,
                    off64_t *offset,
                    liberror_error_t **error );

LIBBFIO_EXTERN int libbfio_pool_get_amount_of_handles(
                    libbfio_pool_t *pool,
                    int *amount_of_handles,
                    liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

