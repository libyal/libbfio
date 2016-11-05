/*
 * Library pool type testing program
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libcstring.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"

#if SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int bfio_test_pool_get_narrow_source(
     const libcstring_system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "bfio_test_pool_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = libcstring_system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( libcstring_system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int bfio_test_pool_get_wide_source(
     const libcstring_system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "bfio_test_pool_get_wide_source";
	size_t wide_source_size = 0;
	size_t source_length    = 0;

#if !defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = libcstring_system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcstring_system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libbfio_pool_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_initialize(
     void )
{
	libcerror_error_t *error = NULL;
	libbfio_pool_t *pool     = NULL;
	int result               = 0;

	/* Test libbfio_pool_initialize
	 */
	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BFIO_TEST_ASSERT_IS_NOT_NULL(
         "pool",
         pool );

        BFIO_TEST_ASSERT_IS_NULL(
         "error",
         error );

	result = libbfio_pool_free(
	          &pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BFIO_TEST_ASSERT_IS_NULL(
         "pool",
         pool );

        BFIO_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libbfio_pool_initialize(
	          NULL,
	          1,
	          1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BFIO_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	pool = (libbfio_pool_t *) 0x12345678UL;

	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BFIO_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	pool = NULL;

#if defined( HAVE_BFIO_TEST_MEMORY )

	/* Test libbfio_pool_initialize with malloc failing
	 */
	bfio_test_malloc_attempts_before_fail = 0;

	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          1,
	          &error );

	if( bfio_test_malloc_attempts_before_fail != -1 )
	{
		bfio_test_malloc_attempts_before_fail = -1;

		if( pool != NULL )
		{
			libbfio_pool_free(
			 &pool,
			 NULL );
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "pool",
		 pool );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libbfio_pool_initialize with memset failing
	 */
	bfio_test_memset_attempts_before_fail = 0;

	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          1,
	          &error );

	if( bfio_test_memset_attempts_before_fail != -1 )
	{
		bfio_test_memset_attempts_before_fail = -1;

		if( pool != NULL )
		{
			libbfio_pool_free(
			 &pool,
			 NULL );
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "pool",
		 pool );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_BFIO_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_free function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbfio_pool_free(
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BFIO_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_get_number_of_handles functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_get_number_of_handles(
     libbfio_pool_t *pool )
{
	libcerror_error_t *error = NULL;
	int number_of_handles    = 0;
	int result               = 0;

	result = libbfio_pool_get_number_of_handles(
	          pool,
	          &number_of_handles,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

        BFIO_TEST_ASSERT_IS_NULL(
         "error",
         error );

	/* Test error cases
	 */
	result = libbfio_pool_get_number_of_handles(
	          NULL,
	          &number_of_handles,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BFIO_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	result = libbfio_pool_get_number_of_handles(
	          pool,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

        BFIO_TEST_ASSERT_IS_NOT_NULL(
         "error",
         error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libcerror_error_t *error              = NULL;
	libcstring_system_character_t *source = NULL;

	if( argc >= 2 )
	{
		source = argv[ 1 ];
	}
	BFIO_TEST_RUN(
	 "libbfio_pool_initialize",
	 bfio_test_pool_initialize );

	BFIO_TEST_RUN(
	 "libbfio_pool_free",
	 bfio_test_pool_free );

/* TODO
	BFIO_TEST_RUN(
	 "libbfio_pool_get_number_of_handles",
	 bfio_test_pool_get_number_of_handles );
*/

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( EXIT_FAILURE );
}

