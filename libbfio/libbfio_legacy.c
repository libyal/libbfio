/*
 * Legacy functions
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include "libbfio_handle.h"
#include "libbfio_legacy.h"
#include "libbfio_pool.h"
#include "libbfio_types.h"

#if !defined( HAVE_LOCAL_LIBBFIO )

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

#endif /* !defined( HAVE_LOCAL_LIBBFIO ) */

