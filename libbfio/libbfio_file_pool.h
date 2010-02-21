/*
 * File pool functions
 *
 * Copyright (c) 2010, Joachim Metz <jbmetz@users.sourceforge.net>
 * Copyright (c) 2006-2010, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBBFIO_FILE_POOL_H )
#define _LIBBFIO_FILE_POOL_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libbfio_extern.h"
#include "libbfio_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBBFIO_EXTERN int libbfio_file_pool_add_handles_for_names(
                    libbfio_pool_t *pool,
                    char * const names[],
                    int amount_of_names,
                    int flags,
                    liberror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBBFIO_EXTERN int libbfio_file_pool_add_handles_for_names_wide(
                    libbfio_pool_t *pool,
                    wchar_t * const names[],
                    int amount_of_names,
                    int flags,
                    liberror_error_t **error );
#endif

#if defined( __cplusplus )
}
#endif

#endif

