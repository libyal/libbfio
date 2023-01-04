/*
 * Library memory_range type test program
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"
#include "bfio_test_unused.h"

#include "../libbfio/libbfio_memory_range.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make bfio_test_file generate verbose output
#define BFIO_TEST_MEMORY_RANGE_VERBOSE
 */

uint8_t bfio_test_memory_range_data[ 4096 ];

/* Tests the libbfio_memory_range_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_memory_range_initialize(
     void )
{
	libbfio_handle_t *handle        = NULL;
	libcerror_error_t *error        = NULL;
	int result                      = 0;

#if defined( HAVE_BFIO_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libbfio_memory_range_initialize(
	          &handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_memory_range_initialize(
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

	handle = (libbfio_handle_t *) 0x12345678UL;

	result = libbfio_memory_range_initialize(
	          &handle,
	          &error );

	handle = NULL;

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
		/* Test libbfio_memory_range_initialize with malloc failing
		 */
		bfio_test_malloc_attempts_before_fail = test_number;

		result = libbfio_memory_range_initialize(
		          &handle,
		          &error );

		if( bfio_test_malloc_attempts_before_fail != -1 )
		{
			bfio_test_malloc_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libbfio_handle_free(
				 &handle,
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
			 "handle",
			 handle );

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
		/* Test libbfio_memory_range_initialize with memset failing
		 */
		bfio_test_memset_attempts_before_fail = test_number;

		result = libbfio_memory_range_initialize(
		          &handle,
		          &error );

		if( bfio_test_memset_attempts_before_fail != -1 )
		{
			bfio_test_memset_attempts_before_fail = -1;

			if( handle != NULL )
			{
				libbfio_handle_free(
				 &handle,
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
			 "handle",
			 handle );

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
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_memory_range_get function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_memory_range_get(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	uint8_t *range_start     = NULL;
	size_t range_size        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_memory_range_get(
	          handle,
	          &range_start,
	          &range_size,
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
	result = libbfio_memory_range_get(
	          NULL,
	          &range_start,
	          &range_size,
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

	result = libbfio_memory_range_get(
	          handle,
	          NULL,
	          &range_size,
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

	result = libbfio_memory_range_get(
	          handle,
	          &range_start,
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

/* Tests the libbfio_memory_range_set function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_memory_range_set(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbfio_memory_range_set(
	          NULL,
	          bfio_test_memory_range_data,
	          4096,
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

	result = libbfio_memory_range_set(
	          handle,
	          NULL,
	          4096,
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

	result = libbfio_memory_range_set(
	          handle,
	          bfio_test_memory_range_data,
	          (size_t) SSIZE_MAX + 1,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc BFIO_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] BFIO_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc BFIO_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] BFIO_TEST_ATTRIBUTE_UNUSED )
#endif
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

#if defined( HAVE_DEBUG_OUTPUT ) && defined( BFIO_TEST_MEMORY_RANGE_VERBOSE )
	libbfio_notify_set_verbose(
	 1 );
	libbfio_notify_set_stream(
	 stderr,
	 NULL );
#endif

	BFIO_TEST_RUN(
	 "libbfio_memory_range_initialize",
	 bfio_test_memory_range_initialize );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )

	/* Initialize test
	 */
	result = libbfio_memory_range_initialize(
	          &handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "handle",
	 handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_memory_range_set(
	          handle,
	          bfio_test_memory_range_data,
	          4096,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	BFIO_TEST_RUN_WITH_ARGS(
	 "libbfio_memory_range_get",
	 bfio_test_memory_range_get,
	 handle );

	BFIO_TEST_RUN_WITH_ARGS(
	 "libbfio_memory_range_set",
	 bfio_test_memory_range_set,
	 handle );

	/* Clean up
	 */
	result = libbfio_handle_free(
	          &handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "handle",
	 handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

