/*
 * Library file_range_io_handle type test program
 *
 * Copyright (C) 2009-2018, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "bfio_test_functions.h"
#include "bfio_test_getopt.h"
#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"

#include "../libbfio/libbfio_file_range_io_handle.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make bfio_test_file generate verbose output
#define BFIO_TEST_FILE_VERBOSE
 */

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_file_range_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_initialize(
     void )
{
	libbfio_file_range_io_handle_t *file_range_io_handle = NULL;
	libcerror_error_t *error                             = NULL;
	int result                                           = 0;

#if defined( HAVE_BFIO_TEST_MEMORY )
	int number_of_malloc_fail_tests                      = 2;
	int number_of_memset_fail_tests                      = 1;
	int test_number                                      = 0;
#endif

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_initialize(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_free(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_file_range_io_handle_initialize(
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

	file_range_io_handle = (libbfio_file_range_io_handle_t *) 0x12345678UL;

	result = libbfio_file_range_io_handle_initialize(
	          &file_range_io_handle,
	          &error );

	file_range_io_handle = NULL;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_BFIO_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libbfio_file_range_io_handle_initialize with malloc failing
		 */
		bfio_test_malloc_attempts_before_fail = test_number;

		result = libbfio_file_range_io_handle_initialize(
		          &file_range_io_handle,
		          &error );

		if( bfio_test_malloc_attempts_before_fail != -1 )
		{
			bfio_test_malloc_attempts_before_fail = -1;

			if( file_range_io_handle != NULL )
			{
				libbfio_file_range_io_handle_free(
				 &file_range_io_handle,
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
			 "file_range_io_handle",
			 file_range_io_handle );

			BFIO_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libbfio_file_range_io_handle_initialize with memset failing
		 */
		bfio_test_memset_attempts_before_fail = test_number;

		result = libbfio_file_range_io_handle_initialize(
		          &file_range_io_handle,
		          &error );

		if( bfio_test_memset_attempts_before_fail != -1 )
		{
			bfio_test_memset_attempts_before_fail = -1;

			if( file_range_io_handle != NULL )
			{
				libbfio_file_range_io_handle_free(
				 &file_range_io_handle,
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
			 "file_range_io_handle",
			 file_range_io_handle );

			BFIO_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_BFIO_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbfio_file_range_io_handle_free(
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

/* Tests the libbfio_file_range_io_handle_clone function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_clone(
     void )
{
	libbfio_file_range_io_handle_t *destination_file_range_io_handle = NULL;
	libbfio_file_range_io_handle_t *source_file_range_io_handle      = NULL;
	libcerror_error_t *error                                         = NULL;
	int result                                                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_initialize(
	          &source_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "source_file_range_io_handle",
	 source_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_clone(
	          &destination_file_range_io_handle,
	          source_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "destination_file_range_io_handle",
	 destination_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_free(
	          &destination_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "destination_file_range_io_handle",
	 destination_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_clone(
	          &destination_file_range_io_handle,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "destination_file_range_io_handle",
	 destination_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_file_range_io_handle_clone(
	          NULL,
	          source_file_range_io_handle,
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

	destination_file_range_io_handle = (libbfio_file_range_io_handle_t *) 0x12345678UL;

	result = libbfio_file_range_io_handle_clone(
	          &destination_file_range_io_handle,
	          source_file_range_io_handle,
	          &error );

	destination_file_range_io_handle = NULL;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_BFIO_TEST_MEMORY )

	/* Test libbfio_file_range_io_handle_clone with malloc failing
	 */
	bfio_test_malloc_attempts_before_fail = 0;

	result = libbfio_file_range_io_handle_clone(
	          &destination_file_range_io_handle,
	          source_file_range_io_handle,
	          &error );

	if( bfio_test_malloc_attempts_before_fail != -1 )
	{
		bfio_test_malloc_attempts_before_fail = -1;

		if( destination_file_range_io_handle != NULL )
		{
			libbfio_file_range_io_handle_free(
			 &destination_file_range_io_handle,
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
		 "destination_file_range_io_handle",
		 destination_file_range_io_handle );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}

	/* Test libbfio_file_range_io_handle_clone with memcpy failing
	 */
	bfio_test_memcpy_attempts_before_fail = 0;

	result = libbfio_file_range_io_handle_clone(
	          &destination_file_range_io_handle,
	          source_file_range_io_handle,
	          &error );

	if( bfio_test_memcpy_attempts_before_fail != -1 )
	{
		bfio_test_memcpy_attempts_before_fail = -1;

		if( destination_file_range_io_handle != NULL )
		{
			libbfio_file_range_io_handle_free(
			 &destination_file_range_io_handle,
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
		 "destination_file_range_io_handle",
		 destination_file_range_io_handle );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_BFIO_TEST_MEMORY ) */

	/* Clean up
	 */
	result = libbfio_file_range_io_handle_free(
	          &source_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "source_file_range_io_handle",
	 source_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( destination_file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &destination_file_range_io_handle,
		 NULL );
	}
	if( source_file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &source_file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_open function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_file_range_io_handle_t *file_range_io_handle = NULL;
	libcerror_error_t *error                             = NULL;
	size_t source_length                                 = 0;
	int result                                           = 0;

	/* Initialize test
	 */
	result = bfio_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_initialize(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_range_io_handle_set_name(
	          file_range_io_handle,
	          narrow_source,
	          source_length,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libbfio_file_range_io_handle_open(
	          file_range_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libbfio_file_range_io_handle_close(
	          file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_free(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_close function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbfio_file_range_io_handle_close(
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

/* Tests the libbfio_file_range_io_handle_open and libbfio_file_range_io_handle_close functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_open_close(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_file_range_io_handle_t *file_range_io_handle = NULL;
	libcerror_error_t *error                             = NULL;
	size_t source_length                                 = 0;
	int result                                           = 0;

	/* Initialize test
	 */
	result = bfio_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_initialize(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_range_io_handle_set_name(
	          file_range_io_handle,
	          narrow_source,
	          source_length,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
	result = libbfio_file_range_io_handle_open(
	          file_range_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_close(
	          file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
	result = libbfio_file_range_io_handle_open(
	          file_range_io_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_range_io_handle_close(
	          file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libbfio_file_range_io_handle_free(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_get_name_size function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_get_name_size(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	libcerror_error_t *error = NULL;
	size_t name_size         = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_get_name_size(
	          file_range_io_handle,
	          &name_size,
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
	result = libbfio_file_range_io_handle_get_name_size(
	          NULL,
	          &name_size,
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

	result = libbfio_file_range_io_handle_get_name_size(
	          file_range_io_handle,
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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libbfio_file_range_io_handle_get_name_size_wide function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_get_name_size_wide(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	libcerror_error_t *error = NULL;
	size_t name_size_wide    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_get_name_size_wide(
	          file_range_io_handle,
	          &name_size_wide,
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
	result = libbfio_file_range_io_handle_get_name_size_wide(
	          NULL,
	          &name_size_wide,
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

	result = libbfio_file_range_io_handle_get_name_size_wide(
	          file_range_io_handle,
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libbfio_file_range_io_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_read_buffer(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	uint8_t buffer[ 32 ];

	libbfio_file_range_io_handle_t *closed_file_range_io_handle = NULL;
	libcerror_error_t *error                                    = NULL;
	size64_t file_size                                          = 0;
	ssize_t read_count                                          = 0;
	off64_t offset                                              = 0;
	int result                                                  = 0;

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_get_size(
	          file_range_io_handle,
	          &file_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( file_size < 32 )
	{
		return( 1 );
	}
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          0,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_count = libbfio_file_range_io_handle_read_buffer(
	              file_range_io_handle,
	              buffer,
	              32,
	              &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) 32 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libbfio_file_range_io_handle_read_buffer(
	              NULL,
	              buffer,
	              0,
	              &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libbfio_file_range_io_handle_read_buffer(
	              file_range_io_handle,
	              NULL,
	              0,
	              &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libbfio_file_range_io_handle_read_buffer(
	              file_range_io_handle,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_initialize(
	          &closed_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file_range_io_handle",
	 closed_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test read buffer with error code on a closed file IO handle
	 */
	read_count = libbfio_file_range_io_handle_read_buffer(
	              closed_file_range_io_handle,
	              buffer,
	              0,
	              &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libbfio_file_range_io_handle_free(
	          &closed_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "closed_file_range_io_handle",
	 closed_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &closed_file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_write_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_write_buffer(
     void )
{
	char narrow_temporary_filename[ 17 ] = {
		'b', 'f', 'i', 'o', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libbfio_file_range_io_handle_t *closed_file_range_io_handle = NULL;
	libbfio_file_range_io_handle_t *file_range_io_handle        = NULL;
	libcerror_error_t *error                                    = NULL;
	ssize_t write_count                                         = 0;
	int result                                                  = 0;
	int with_temporary_file                                     = 0;

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_initialize(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = bfio_test_get_temporary_filename(
	          narrow_temporary_filename,
	          17,
	          &error );

	BFIO_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	with_temporary_file = result;

	if( with_temporary_file != 0 )
	{
		result = libbfio_file_range_io_handle_set_name(
		          file_range_io_handle,
		          narrow_temporary_filename,
		          16,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_file_range_io_handle_open(
		          file_range_io_handle,
		          LIBBFIO_OPEN_WRITE,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Test regular cases
		 */
		write_count = libbfio_file_range_io_handle_write_buffer(
		               file_range_io_handle,
		               buffer,
		               32,
		               &error );

		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) 32 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	write_count = libbfio_file_range_io_handle_write_buffer(
	               NULL,
	               buffer,
	               0,
	               &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libbfio_file_range_io_handle_write_buffer(
	               file_range_io_handle,
	               NULL,
	               0,
	               &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libbfio_file_range_io_handle_write_buffer(
	               file_range_io_handle,
	               buffer,
	               (size_t) SSIZE_MAX + 1,
	               &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_initialize(
	          &closed_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file_range_io_handle",
	 closed_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test write buffer with error code on a closed file IO handle
	 */
	write_count = libbfio_file_range_io_handle_write_buffer(
	               closed_file_range_io_handle,
	               buffer,
	               0,
	               &error );

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libbfio_file_range_io_handle_free(
	          &closed_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "closed_file_range_io_handle",
	 closed_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( with_temporary_file != 0 )
	{
		result = libbfio_file_range_io_handle_close(
		          file_range_io_handle,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = bfio_test_remove_temporary_file(
		          narrow_temporary_filename,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		with_temporary_file = 0;
	}
	result = libbfio_file_range_io_handle_free(
	          &file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "file_range_io_handle",
	 file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &closed_file_range_io_handle,
		 NULL );
	}
	if( with_temporary_file != 0 )
	{
		bfio_test_remove_temporary_file(
		 narrow_temporary_filename,
		 NULL );
	}
	if( file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_seek_offset(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	libbfio_file_range_io_handle_t *closed_file_range_io_handle = NULL;
	libcerror_error_t *error                                    = NULL;
	size64_t file_size                                          = 0;
	off64_t offset                                              = 0;
	off64_t seek_offset                                         = 0;
	int result                                                  = 0;

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_get_size(
	          file_range_io_handle,
	          &file_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 0 and whence: SEEK_SET
	 */
	seek_offset = 0;

	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          seek_offset,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size> and whence: SEEK_SET
	 */
	seek_offset = (off64_t) file_size;

	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          seek_offset,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size / 5> and whence: SEEK_SET
	 */
	seek_offset = (off64_t) ( file_size / 5 );

	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          seek_offset,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size / 5> and whence: SEEK_CUR
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          seek_offset,
	          SEEK_CUR,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset + seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <-1 * (file_size / 5)> and whence: SEEK_CUR
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          -1 * seek_offset,
	          SEEK_CUR,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <file_size + 987> and whence: SEEK_SET
	 */
	seek_offset = (off64_t) ( file_size + 987 );

	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          seek_offset,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 0 and whence: SEEK_CUR
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          0,
	          SEEK_CUR,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 0 and whence: SEEK_END
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          0,
	          SEEK_END,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) file_size );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <-1 * (file_size / 4)> and whence: SEEK_END
	 */
	seek_offset = (off64_t) ( file_size / 4 );

	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          -1 * seek_offset,
	          SEEK_END,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) file_size - seek_offset );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: 542 and whence: SEEK_END
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          542,
	          SEEK_END,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) file_size + 542 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset with offset: <-1 * file_size> and whence: SEEK_END
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          -1 * file_size,
	          SEEK_END,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test seek offset with offset: -987 and whence: SEEK_SET
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          -987,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test seek offset with offset: <1 * (file_size + 542)> and whence: SEEK_END
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          -1 * (file_size + 542),
	          SEEK_END,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test seek offset with offset: 0 and whence: UNKNOWN (88)
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          file_range_io_handle,
	          0,
	          88,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Initialize test
	 */
	result = libbfio_file_range_io_handle_initialize(
	          &closed_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "closed_file_range_io_handle",
	 closed_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset on a closed file IO handle
	 */
	offset = libbfio_file_range_io_handle_seek_offset(
	          closed_file_range_io_handle,
	          0,
	          SEEK_SET,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libbfio_file_range_io_handle_free(
	          &closed_file_range_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "closed_file_range_io_handle",
	 closed_file_range_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( closed_file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &closed_file_range_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_range_io_handle_exists function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_exists(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_exists(
	          file_range_io_handle,
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
	result = libbfio_file_range_io_handle_exists(
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

/* Tests the libbfio_file_range_io_handle_is_open function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_is_open(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_is_open(
	          file_range_io_handle,
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
	result = libbfio_file_range_io_handle_is_open(
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

/* Tests the libbfio_file_range_io_handle_get_size function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_range_io_handle_get_size(
     libbfio_file_range_io_handle_t *file_range_io_handle )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_file_range_io_handle_get_size(
	          file_range_io_handle,
	          &size,
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
	result = libbfio_file_range_io_handle_get_size(
	          NULL,
	          &size,
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

	result = libbfio_file_range_io_handle_get_size(
	          file_range_io_handle,
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

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )
	char narrow_source[ 256 ];

	libbfio_file_range_io_handle_t *file_range_io_handle = NULL;
	size_t source_length                                 = 0;
#endif

	libcerror_error_t *error                             = NULL;
	system_character_t *source                           = NULL;
	system_integer_t option                              = 0;
	int result                                           = 0;

	while( ( option = bfio_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( BFIO_TEST_FILE_VERBOSE )
	libbfio_notify_set_verbose(
	 1 );
	libbfio_notify_set_stream(
	 stderr,
	 NULL );
#endif

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

	BFIO_TEST_RUN(
	 "libbfio_file_range_io_handle_initialize",
	 bfio_test_file_range_io_handle_initialize );

	BFIO_TEST_RUN(
	 "libbfio_file_range_io_handle_free",
	 bfio_test_file_range_io_handle_free );

	BFIO_TEST_RUN(
	 "libbfio_file_range_io_handle_clone",
	 bfio_test_file_range_io_handle_clone );

/* TODO fix test

	BFIO_TEST_RUN(
	 "libbfio_file_range_io_handle_write_buffer",
	 bfio_test_file_range_io_handle_write_buffer );

*/

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_open",
		 bfio_test_file_range_io_handle_open,
		 source );

		BFIO_TEST_RUN(
		 "libbfio_file_range_io_handle_close",
		 bfio_test_file_range_io_handle_close );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_open_close",
		 bfio_test_file_range_io_handle_open_close,
		 source );

		/* Initialize test
		 */
		result = bfio_test_get_narrow_source(
		          source,
		          narrow_source,
		          256,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_file_range_io_handle_initialize(
		          &file_range_io_handle,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "file_range_io_handle",
		 file_range_io_handle );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		source_length = narrow_string_length(
		                 narrow_source );

		result = libbfio_file_range_io_handle_set_name(
		          file_range_io_handle,
		          narrow_source,
		          source_length,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_file_range_io_handle_open(
		          file_range_io_handle,
		          LIBBFIO_OPEN_READ,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_get_name_size",
		 bfio_test_file_range_io_handle_get_name_size,
		 file_range_io_handle );

/* TODO add test for libbfio_file_range_io_handle_get_name */

/* TODO add test for libbfio_file_range_io_handle_set_name */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_get_name_size_wide",
		 bfio_test_file_range_io_handle_get_name_size_wide,
		 file_range_io_handle );

/* TODO add test for libbfio_file_range_io_handle_get_name_wide */

/* TODO add test for libbfio_file_range_io_handle_set_name_wide */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_seek_offset",
		 bfio_test_file_range_io_handle_seek_offset,
		 file_range_io_handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_read_buffer",
		 bfio_test_file_range_io_handle_read_buffer,
		 file_range_io_handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_exists",
		 bfio_test_file_range_io_handle_exists,
		 file_range_io_handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_is_open",
		 bfio_test_file_range_io_handle_is_open,
		 file_range_io_handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_file_range_io_handle_get_size",
		 bfio_test_file_range_io_handle_get_size,
		 file_range_io_handle );

		/* Clean up
		 */
		result = libbfio_file_range_io_handle_close(
		          file_range_io_handle,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_file_range_io_handle_free(
		          &file_range_io_handle,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "file_range_io_handle",
		 file_range_io_handle );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )
	if( file_range_io_handle != NULL )
	{
		libbfio_file_range_io_handle_free(
		 &file_range_io_handle,
		 NULL );
	}
#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

	return( EXIT_FAILURE );
}

