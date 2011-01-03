/*
 * Legacy functions
 *
 * Copyright (c) 2009-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <common.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>

#include "libbfio_file_pool.h"
#include "libbfio_handle.h"
#include "libbfio_legacy.h"
#include "libbfio_pool.h"
#include "libbfio_types.h"

#if !defined( HAVE_LOCAL_LIBBFIO )

/* Retrieves the flags
 * Returns 1 if successful or -1 on error
 */
int libbfio_handle_get_flags(
     libbfio_handle_t *handle,
     int *flags,
     liberror_error_t **error )
{
	return( libbfio_handle_get_access_flags(
	         handle,
	         flags,
	         error ) );
}

/* Sets the flags
 * Returns 1 if successful or -1 on error
 */
int libbfio_handle_set_flags(
     libbfio_handle_t *handle,
     int flags,
     liberror_error_t **error )
{
	return( libbfio_handle_set_access_flags(
	         handle,
	         flags,
	         error ) );
}

/* Retrieves the amount of offsets read
 * Returns 1 if successful or -1 on error
 */
int libbfio_handle_get_amount_of_offsets_read(
     libbfio_handle_t *handle,
     int *amount_of_read_offsets,
     liberror_error_t **error )
{
	return( libbfio_handle_get_number_of_offsets_read(
	         handle,
	         amount_of_read_offsets,
	         error ) );
}

/* Retrieves the amount of handles in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_get_amount_of_handles(
     libbfio_pool_t *pool,
     int *amount_of_handles,
     liberror_error_t **error )
{
	return( libbfio_pool_get_number_of_handles(
	         pool,
	         amount_of_handles,
	         error ) );
}

/* Appends a handle to the pool
 * Sets the entry
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_add_handle(
     libbfio_pool_t *pool,
     int *entry,
     libbfio_handle_t *handle,
     int access_flags,
     liberror_error_t **error )
{
	return( libbfio_pool_append_handle(
	         pool,
	         entry,
	         handle,
	         access_flags,
	         error ) );
}

/* Retrieves the maximum amount of open handles in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_get_maximum_amount_of_open_handles(
     libbfio_pool_t *pool,
     int *maximum_amount_of_open_handles,
     liberror_error_t **error )
{
	return( libbfio_pool_get_maximum_number_of_open_handles(
	         pool,
	         maximum_amount_of_open_handles,
	         error ) );
}

/* Sets the maximum amount of open handles in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_set_maximum_amount_of_open_handles(
     libbfio_pool_t *pool,
     int maximum_amount_of_open_handles,
     liberror_error_t **error )
{
	return( libbfio_pool_set_maximum_number_of_open_handles(
	         pool,
	         maximum_amount_of_open_handles,
	         error ) );
}

/* Adds file handles to the pool for the corresponding filenames
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_pool_add_handles_for_names(
     libbfio_pool_t *pool,
     char * const names[],
     int number_of_names,
     int access_flags,
     liberror_error_t **error )
{
	return( libbfio_file_pool_append_handles_for_names(
	         pool,
	         names,
	         number_of_names,
	         access_flags,
	         error ) );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Adds file handles to the pool for the corresponding filenames
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_pool_add_handles_for_names_wide(
     libbfio_pool_t *pool,
     wchar_t * const names[],
     int number_of_names,
     int access_flags,
     liberror_error_t **error )
{
	return( libbfio_file_pool_append_handles_for_names_wide(
	         pool,
	         names,
	         number_of_names,
	         access_flags,
	         error ) );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* !defined( HAVE_LOCAL_LIBBFIO ) */

