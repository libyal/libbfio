/*
 * Error string functions
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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

#if defined( HAVE_STDLIB_H )
#include <stdlib.h>
#endif

#if defined( HAVE_STRING_H )
#include <string.h>
#endif

#include "libbfio_error_string.h"
#include "libbfio_libuna.h"

/* Create a narrow character error string from the error number
 * Returns 1 if successful or -1 on error
 */
int libbfio_error_string_from_error_number(
       char **error_string,
       size_t *error_string_size,
       int error_number,
       liberror_error_t **error )
{
	static char *function     = "libbfio_error_string_from_error_number";

#if defined( HAVE_STRERROR ) && !defined( HAVE_STRERROR_R ) && !defined( WINAPI )
	char *static_error_string = NULL;
#endif

	if( error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid error string.",
		 function );

		return( -1 );
	}
	if( *error_string != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: error string already set.",
		 function );

		return( -1 );
	}
	if( error_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid error string size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_STRERROR ) && !defined( HAVE_STRERROR_R ) && !defined( WINAPI )
	static_error_string = strerror(
	                       error_number );

	if( static_error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve static error string.",
		 function );

		return( -1 );
	}
	*error_string_size = 1 + narrow_string_length(
	                          static_error_string );
#else
	*error_string_size = LIBBFIO_ERROR_STRING_DEFAULT_SIZE;
#endif

	*error_string = (char *) memory_allocate(
	                          sizeof( char ) * *error_string_size );

	if( *error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create error string.",
		 function );

		*error_string_size = 0;

		return( -1 );
	}
#if defined( WINAPI )
#if defined( USE_NATIVE_WINAPI_FUNCTIONS )
	if( FormatMessageA(
	     FORMAT_MESSAGE_FROM_SYSTEM,
	     NULL,
	     (DWORD) error_code,
	     MAKELANGID(
	      LANG_NEUTRAL,
	      SUBLANG_DEFAULT ),
	     *error_string,
	     *error_string_size,
	     NULL ) != 0 )
#else
	if( strerror_s(
	     *error_string,
	     *error_string_size,
	     error_number ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set error string.",
		 function );

		memory_free(
		 *error_string );

		*error_string      = NULL;
		*error_string_size = 0;

		return( -1 );
	}
#elif defined( HAVE_STRERROR_R )
#if defined( STRERROR_R_CHAR_P )
	if( strerror_r(
	     error_number,
	     *error_string,
	     *error_string_size ) != NULL )
#else
	if( strerror_r(
	     error_number,
	     *error_string,
	     *error_string_size ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set error string.",
		 function );

		memory_free(
		 *error_string );

		*error_string      = NULL;
		*error_string_size = 0;

		return( -1 );
	}
#elif defined( HAVE_STRERROR )
	if( memory_copy(
	     *error_string,
	     static_error_string,
	     *error_string_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set error string.",
		 function );

		memory_free(
		 *error_string );

		*error_string      = NULL;
		*error_string_size = 0;

		return( -1 );
	}
#endif
	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Create a wide character error string from the error number
 * Returns 1 if successful or -1 on error
 */
int libbfio_error_string_from_error_number_wide(
       wchar_t **error_string,
       size_t *error_string_size,
       int error_number,
       liberror_error_t **error )
{
	static char *function           = "libbfio_error_string_from_error_number_wide";

#if !defined( WINAPI )
	char *narrow_error_string       = NULL;
	size_t narrow_error_string_size = 0;
#endif

	if( error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid error string.",
		 function );

		return( -1 );
	}
	if( *error_string != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: error string already set.",
		 function );

		return( -1 );
	}
	if( error_string_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid error string size.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
	*error_string_size = LIBBFIO_ERROR_STRING_DEFAULT_SIZE;

	*error_string = (wchar_t *) memory_allocate(
	                             sizeof( wchar_t ) * *error_string_size );

	if( *error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create error string.",
		 function );

		*error_string_size = 0;

		return( -1 );
	}
#if defined( USE_NATIVE_WINAPI_FUNCTIONS )
	if( FormatMessageW(
	     FORMAT_MESSAGE_FROM_SYSTEM,
	     NULL,
	     (DWORD) error_code,
	     MAKELANGID(
	      LANG_NEUTRAL,
	      SUBLANG_DEFAULT ),
	     *error_string,
	     *error_string_size,
	     NULL ) != 0 )
#else
	if( _wcserror_s(
	     *error_string,
	     *error_string_size,
	     error_number ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set error string.",
		 function );

		memory_free(
		 *error_string );

		*error_string      = NULL;
		*error_string_size = 0;

		return( -1 );
	}
#else
#if defined( HAVE_STRERROR ) && !defined( HAVE_STRERROR_R ) && !defined( WINAPI )
	narrow_error_string = strerror(
	                       error_number );

	if( narrow_error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve static narrow error string.",
		 function );

		return( -1 );
	}
	narrow_error_string_size = 1 + narrow_string_length(
	                                narrow_static_error_string );
#elif defined( HAVE_STRERROR_R )
	narrow_error_string_size = LIBBFIO_ERROR_STRING_DEFAULT_SIZE;

	narrow_error_string = (char *) memory_allocate(
	                                sizeof( char ) * narrow_error_string_size );

	if( narrow_error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow error string.",
		 function );

		return( -1 );
	}
#if defined( STRERROR_R_CHAR_P )
	if( strerror_r(
	     error_number,
	     narrow_error_string,
	     narrow_error_string_size ) != NULL )
#else
	if( strerror_r(
	     error_number,
	     narrow_error_string,
	     narrow_error_string_size ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set narrow error string.",
		 function );

		memory_free(
		 narrow_error_string );

		return( -1 );
	}
#endif

	/* Assume the narrow error string is in UTF-8
	 */
	narrow_error_string_size = 1 + narrow_string_length(
	                                narrow_error_string );

#if SIZEOF_WCHAR_T == 4
	if( libuna_utf32_string_size_from_utf8(
	     (libuna_utf8_character_t *) narrow_error_string,
	     narrow_error_string_size,
	     error_string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf16_string_size_from_utf8(
	     (libuna_utf8_character_t *) narrow_error_string,
	     narrow_error_string_size,
	     error_string_size,
	     error ) != 2 )
#else
#error Unsupported size of wchar_t
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine error string size.",
		 function );

#if defined( HAVE_STRERROR_R )
		memory_free(
		 narrow_error_string );
#endif

		return( -1 );
	}
	*error_string = (wchar_t *) memory_allocate(
	                             sizeof( wchar_t ) * *error_string_size );

	if( *error_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create error string.",
		 function );

#if defined( HAVE_STRERROR_R )
		memory_free(
		 narrow_error_string );
#endif

		*error_string_size = 0;

		return( -1 );
	}
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf32_string_copy_from_utf8(
	     (libuna_utf32_character_t *) *error_string,
	     *error_string_size,
	     (libuna_utf8_character_t *) narrow_error_string,
	     narrow_error_string_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf16_string_copy_from_utf8(
	     (libuna_utf16_character_t *) *error_string,
	     *error_string_size,
	     (libuna_utf8_character_t *) narrow_error_string,
	     narrow_error_string_size,
	     error ) != 1 )
#else
#error Unsupported size of wchar_t
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set error string.",
		 function );

#if defined( HAVE_STRERROR_R )
		memory_free(
		 narrow_error_string );
#endif

		memory_free(
		 *error_string );

		*error_string      = NULL;
		*error_string_size = 0;

		return( -1 );
	}
#if defined( HAVE_STRERROR_R )
	memory_free(
	 narrow_error_string );
#endif
#endif
	return( 1 );
}

#endif

