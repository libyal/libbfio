/*
 * Library pool type test program
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

#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

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

	pool = NULL;

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
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;

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

