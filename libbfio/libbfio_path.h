/*
 * Path functions
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

#if !defined( _LIBBFIO_PATH_H )
#define _LIBBFIO_PATH_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "libbfio_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

int libbfio_path_get_current_working_directory(
     char **current_working_directory,
     size_t *current_working_directory_size,
     liberror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_path_get_full_path(
     const char *path,
     size_t path_length,
     char **full_path,
     size_t *full_path_size,
     liberror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

int libbfio_path_get_current_working_directory_wide(
     wchar_t **current_working_directory,
     size_t *current_working_directory_size,
     liberror_error_t **error );

LIBBFIO_EXTERN \
int libbfio_path_get_full_path_wide(
     const wchar_t *path,
     size_t path_length,
     wchar_t **full_path,
     size_t *full_path_size,
     liberror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif

