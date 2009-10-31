/*
 * Error string functions
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

#include <common.h>
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "libbfio_error_string.h"
#include "libbfio_libuna.h"

/* Retrieves a descriptive string of the error number
 * Returns 1 if successful or -1 on error
 */
int libbfio_error_string_copy_from_error_number(
     libbfio_system_character_t *string,
     size_t string_size,
     int error_number,
     liberror_error_t **error )
{
	static char *function              = "libbfio_error_string_copy_from_error_number";

#if ( defined( HAVE_STRERROR ) && !defined( HAVE_STRERROR_R ) ) || ( defined( WINAPI ) && defined( USE_CRT_FUNCTIONS ) && !defined( _MSC_VER ) )
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *static_error_string = NULL;
#else
	const char *static_error_string    = NULL;
#endif
	size_t static_error_string_length  = 0;
#endif

	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
/* Use the WINAPI error string function
 */
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( FormatMessageW(
	     FORMAT_MESSAGE_FROM_SYSTEM,
	     NULL,
	     (DWORD) error_number,
	     MAKELANGID(
	      LANG_NEUTRAL,
	      SUBLANG_DEFAULT ),
	     string,
	     string_size,
	     NULL ) != 0 )
#else
	if( FormatMessageA(
	     FORMAT_MESSAGE_FROM_SYSTEM,
	     NULL,
	     (DWORD) error_number,
	     MAKELANGID(
	      LANG_NEUTRAL,
	     SUBLANG_DEFAULT ),
	     string,
	     string_size,
	     NULL ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}

/* Use MSVSC++ specific CRT error string functions
 */
#elif defined( USE_CRT_FUNCTIONS ) && defined( _MSC_VER )
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( _wcserror_s(
	     string,
	     string_size,
	     error_number ) != 0 )
#else
	if( strerror_s(
	     string,
	     string_size,
	     error_number ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}

/* Use POSIX specific error string functions
 */
#elif defined( HAVE_STRERROR_R )
/* Sanity check
 */
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
#error Missing wide character strerror_r function
#endif

#if defined( STRERROR_R_CHAR_P )
	if( strerror_r(
	     error_number,
	     string,
	     string_size ) == NULL )
#else
	if( strerror_r(
	     error_number,
	     string,
	     string_size ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}

/* Use the static error string function
 */
#elif defined( HAVE_STRERROR ) || defined( WINAPI )

/* Sanity check
 */
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER ) && !defined( WINAPI )
#error Missing wide character strerror function
#endif

#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	static_error_string = _wcserror(
	                       error_number );
#else
	static_error_string = strerror(
	                       error_number );
#endif

	if( static_error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to create static error string.",
		 function );

		return( -1 );
	}
	static_error_string_length = libbfio_system_string_length(
	                              static_error_string );

	if( libbfio_system_string_copy(
	     string,
	     static_error_string,
	     static_error_string_length ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	string[ static_error_string_length ] = 0;

#else
#error Missing strerror function
#endif

	return( 1 );
}

