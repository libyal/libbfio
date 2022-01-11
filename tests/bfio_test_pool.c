/*
 * Library pool type test program
 *
 * Copyright (C) 2009-2022, Joachim Metz <joachim.metz@gmail.com>
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

#include "bfio_test_functions.h"
#include "bfio_test_getopt.h"
#include "bfio_test_libbfio.h"
#include "bfio_test_libcdata.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"
#include "bfio_test_rwlock.h"

#include "../libbfio/libbfio_pool.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make bfio_test_file generate verbose output
#define BFIO_TEST_POOL_VERBOSE
 */

/* Creates and opens a source pool
 * Returns 1 if successful or -1 on error
 */
int bfio_test_pool_open_source(
     libbfio_pool_t **pool,
     const system_character_t *source,
     libcerror_error_t **error )
{
	libbfio_handle_t *handle = NULL;
	static char *function    = "bfio_test_pool_open_source";
	size_t source_length     = 0;
	int entry_index          = 0;
	int result               = 0;

	if( pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
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
	if( libbfio_pool_initialize(
	     pool,
	     0,
	     LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize pool.",
		 function );

		goto on_error;
	}
	if( libbfio_file_initialize(
	     &handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize handle.",
		 function );

		goto on_error;
	}
	source_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          handle,
	          source,
	          source_length,
	          error );
#else
	result = libbfio_file_set_name(
	          handle,
	          source,
	          source_length,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set name in handle.",
		 function );

		goto on_error;
	}
	result = libbfio_pool_append_handle(
	          *pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append handle to pool.",
		 function );

		goto on_error;
	}
	handle = NULL;

	result = libbfio_pool_open(
	          *pool,
	          0,
	          LIBBFIO_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle: 0 in pool.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	if( *pool != NULL )
	{
		libbfio_pool_free(
		 pool,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source pool
 * Returns 1 if successful or -1 on error
 */
int bfio_test_pool_close_source(
     libbfio_pool_t **pool,
     libcerror_error_t **error )
{
	static char *function = "bfio_test_pool_close_source";
	int result            = 0;

	if( pool == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( libbfio_pool_close_all(
	     *pool,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close pool.",
		 function );

		result = -1;
	}
	if( libbfio_pool_free(
	     pool,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free pool.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libbfio_pool_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_initialize(
     void )
{
	libbfio_pool_t *pool            = NULL;
	libcerror_error_t *error        = NULL;
	int result                      = 0;

#if defined( HAVE_BFIO_TEST_MEMORY )
	int number_of_malloc_fail_tests = 5;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_pool_initialize(
	          &pool,
	          -1,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          -1,
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

#if defined( HAVE_BFIO_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libbfio_pool_initialize with malloc failing
		 */
		bfio_test_malloc_attempts_before_fail = test_number;

		result = libbfio_pool_initialize(
		          &pool,
		          0,
		          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libbfio_pool_initialize with memset failing
		 */
		bfio_test_memset_attempts_before_fail = test_number;

		result = libbfio_pool_initialize(
		          &pool,
		          0,
		          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )
	libbfio_pool_t *pool     = NULL;
#endif

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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Initialize test
	 */
	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	/* Test libbfio_pool_free with pthread_rwlock_destroy failing in libcthreads_read_write_lock_free
	 */
	bfio_test_pthread_rwlock_destroy_attempts_before_fail = 0;

	result = libbfio_pool_free(
	          &pool,
	          &error );

	if( bfio_test_pthread_rwlock_destroy_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_destroy_attempts_before_fail = -1;

		/* Clean up
		 */
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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_BFIO_TEST_RWLOCK )
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
#endif
	return( 0 );
}

/* Tests the libbfio_pool_clone function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_clone(
     void )
{
	libbfio_pool_t *destination_pool = NULL;
	libbfio_pool_t *source_pool      = NULL;
	libcerror_error_t *error         = NULL;
	int result                       = 0;

#if defined( HAVE_BFIO_TEST_MEMORY )
	int number_of_malloc_fail_tests = 5;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Initialize test
	 */
	result = libbfio_pool_initialize(
	          &source_pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "source_pool",
	 source_pool );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbfio_pool_clone(
	          &destination_pool,
	          source_pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "destination_pool",
	 destination_pool );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_pool_free(
	          &destination_pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "destination_pool",
	 destination_pool );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_pool_clone(
	          &destination_pool,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "destination_pool",
	 destination_pool );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_pool_clone(
	          NULL,
	          source_pool,
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

	destination_pool = (libbfio_pool_t *) 0x12345678UL;

	result = libbfio_pool_clone(
	          &destination_pool,
	          source_pool,
	          &error );

	destination_pool = NULL;

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
		/* Test libbfio_pool_clone with malloc failing
		 */
		bfio_test_malloc_attempts_before_fail = test_number;

		result = libbfio_pool_clone(
		          &destination_pool,
		          source_pool,
		          &error );

		if( bfio_test_malloc_attempts_before_fail != -1 )
		{
			bfio_test_malloc_attempts_before_fail = -1;

			if( destination_pool != NULL )
			{
				libbfio_pool_free(
				 &destination_pool,
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
			 "destination_pool",
			 destination_pool );

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
		/* Test libbfio_pool_clone with memset failing
		 */
		bfio_test_memset_attempts_before_fail = test_number;

		result = libbfio_pool_clone(
		          &destination_pool,
		          source_pool,
		          &error );

		if( bfio_test_memset_attempts_before_fail != -1 )
		{
			bfio_test_memset_attempts_before_fail = -1;

			if( destination_pool != NULL )
			{
				libbfio_pool_free(
				 &destination_pool,
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
			 "destination_pool",
			 destination_pool );

			BFIO_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_BFIO_TEST_MEMORY ) */

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_clone with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_pool_clone(
	          &destination_pool,
	          source_pool,
	          &error );

	if( bfio_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_rdlock_attempts_before_fail = -1;

		if( destination_pool != NULL )
		{
			libbfio_pool_free(
			 &destination_pool,
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
		 "destination_pool",
		 destination_pool );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_clone with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_clone(
	          &destination_pool,
	          source_pool,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;

		if( destination_pool != NULL )
		{
			libbfio_pool_free(
			 &destination_pool,
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
		 "destination_pool",
		 destination_pool );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libbfio_pool_free(
	          &source_pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "source_pool",
	 source_pool );

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
	if( destination_pool != NULL )
	{
		libbfio_pool_free(
		 &destination_pool,
		 NULL );
	}
	if( source_pool != NULL )
	{
		libbfio_pool_free(
		 &source_pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_resize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_resize(
     void )
{
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	/* Test regular cases
	 */
	result = libbfio_pool_resize(
	          pool,
	          10,
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

	/* Test error cases
	 */
	result = libbfio_pool_resize(
	          NULL,
	          20,
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

	result = libbfio_pool_resize(
	          pool,
	          -1,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_resize with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_resize(
	          pool,
	          20,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_resize with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_resize(
	          pool,
	          20,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
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

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_internal_pool_open_handle function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_pool_open_handle(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle        = NULL;
	libbfio_handle_t *test_handle   = NULL;
	libbfio_pool_t *pool            = NULL;
	libcdata_list_t *last_used_list = NULL;
	libcerror_error_t *error        = NULL;
	size_t source_length            = 0;
	int entry_index                 = 0;
	int result                      = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	test_handle = handle;
	handle      = NULL;

	/* Test regular cases
	 */
	result = libbfio_internal_pool_open_handle(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_internal_pool_open_handle(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO test with number of open handles exceeding internal_pool->maximum_number_of_open_handles */

	/* Test error cases
	 */
	result = libbfio_internal_pool_open_handle(
	          NULL,
	          test_handle,
	          LIBBFIO_OPEN_READ,
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

	last_used_list = ( (libbfio_internal_pool_t *) pool )->last_used_list;

	( (libbfio_internal_pool_t *) pool )->last_used_list = NULL;

	result = libbfio_internal_pool_open_handle(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_pool_t *) pool )->last_used_list = last_used_list;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_internal_pool_open_handle(
	          (libbfio_internal_pool_t *) pool,
	          NULL,
	          LIBBFIO_OPEN_READ,
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

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_internal_pool_append_handle_to_last_used_list function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_pool_append_handle_to_last_used_list(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle        = NULL;
	libbfio_handle_t *test_handle   = NULL;
	libbfio_pool_t *pool            = NULL;
	libcdata_list_t *last_used_list = NULL;
	libcerror_error_t *error        = NULL;
	size_t source_length            = 0;
	int entry_index                 = 0;
	int result                      = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          2,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	test_handle = handle;
	handle      = NULL;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_internal_pool_append_handle_to_last_used_list(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

/* TODO test with number of open handles exceeding internal_pool->maximum_number_of_open_handles */

	/* Test error cases
	 */
	result = libbfio_internal_pool_append_handle_to_last_used_list(
	          NULL,
	          test_handle,
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

	last_used_list = ( (libbfio_internal_pool_t *) pool )->last_used_list;

	( (libbfio_internal_pool_t *) pool )->last_used_list = NULL;

	result = libbfio_internal_pool_append_handle_to_last_used_list(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
	          &error );

	( (libbfio_internal_pool_t *) pool )->last_used_list = last_used_list;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_internal_pool_append_handle_to_last_used_list(
	          (libbfio_internal_pool_t *) pool,
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

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_internal_pool_move_handle_to_front_of_last_used_list function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_pool_move_handle_to_front_of_last_used_list(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle        = NULL;
	libbfio_handle_t *test_handle   = NULL;
	libbfio_pool_t *pool            = NULL;
	libcdata_list_t *last_used_list = NULL;
	libcerror_error_t *error        = NULL;
	size_t source_length            = 0;
	int entry_index                 = 0;
	int result                      = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	test_handle = handle;
	handle      = NULL;

	result = libbfio_internal_pool_append_handle_to_last_used_list(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
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
	result = libbfio_internal_pool_move_handle_to_front_of_last_used_list(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
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
	result = libbfio_internal_pool_move_handle_to_front_of_last_used_list(
	          NULL,
	          test_handle,
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

	last_used_list = ( (libbfio_internal_pool_t *) pool )->last_used_list;

	( (libbfio_internal_pool_t *) pool )->last_used_list = NULL;

	result = libbfio_internal_pool_move_handle_to_front_of_last_used_list(
	          (libbfio_internal_pool_t *) pool,
	          test_handle,
	          &error );

	( (libbfio_internal_pool_t *) pool )->last_used_list = last_used_list;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_internal_pool_move_handle_to_front_of_last_used_list(
	          (libbfio_internal_pool_t *) pool,
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

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_get_number_of_handles with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_pool_get_number_of_handles(
	          pool,
	          &number_of_handles,
	          &error );

	if( bfio_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_get_number_of_handles with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_get_number_of_handles(
	          pool,
	          &number_of_handles,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_get_handle functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_get_handle(
     libbfio_pool_t *pool )
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libbfio_pool_get_handle(
	          pool,
	          0,
	          &handle,
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
	result = libbfio_pool_get_handle(
	          NULL,
	          0,
	          &handle,
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

	result = libbfio_pool_get_handle(
	          pool,
	          -1,
	          &handle,
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

	result = libbfio_pool_get_handle(
	          pool,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_get_handle with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_pool_get_handle(
	          pool,
	          0,
	          &handle,
	          &error );

	if( bfio_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_get_handle with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_get_handle(
	          pool,
	          0,
	          &handle,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_get_maximum_number_of_open_handles functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_get_maximum_number_of_open_handles(
     libbfio_pool_t *pool )
{
	libcerror_error_t *error           = NULL;
	int maximum_number_of_open_handles = 0;
	int result                         = 0;

	result = libbfio_pool_get_maximum_number_of_open_handles(
	          pool,
	          &maximum_number_of_open_handles,
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
	result = libbfio_pool_get_maximum_number_of_open_handles(
	          NULL,
	          &maximum_number_of_open_handles,
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

	result = libbfio_pool_get_maximum_number_of_open_handles(
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_get_maximum_number_of_open_handles with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_pool_get_maximum_number_of_open_handles(
	          pool,
	          &maximum_number_of_open_handles,
	          &error );

	if( bfio_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_rdlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libbfio_pool_get_maximum_number_of_open_handles with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_get_maximum_number_of_open_handles(
	          pool,
	          &maximum_number_of_open_handles,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_set_maximum_number_of_open_handles functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_set_maximum_number_of_open_handles(
     libbfio_pool_t *pool )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	result = libbfio_pool_set_maximum_number_of_open_handles(
	          pool,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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
	result = libbfio_pool_set_maximum_number_of_open_handles(
	          NULL,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_pool_set_maximum_number_of_open_handles(
	          pool,
	          -1,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_set_maximum_number_of_open_handles with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_set_maximum_number_of_open_handles(
	          pool,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_set_maximum_number_of_open_handles with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_set_maximum_number_of_open_handles(
	          pool,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_append_handle function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_append_handle(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle        = NULL;
	libbfio_handle_t *test_handle   = NULL;
	libbfio_pool_t *pool            = NULL;
	libcdata_list_t *last_used_list = NULL;
	libcerror_error_t *error        = NULL;
	size_t source_length            = 0;
	int entry_index                 = 0;
	int result                      = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	test_handle = handle;

	/* Test regular cases
	 */
	result = libbfio_handle_open(
	          handle,
	          LIBBFIO_OPEN_WRITE,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_close(
	          handle,
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
	result = libbfio_pool_remove_handle(
	          pool,
	          0,
	          &test_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	test_handle = handle;

	/* Test error cases
	 */
	result = libbfio_pool_append_handle(
	          NULL,
	          &entry_index,
	          test_handle,
	          LIBBFIO_OPEN_READ,
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

	last_used_list = ( (libbfio_internal_pool_t *) pool )->last_used_list;

	( (libbfio_internal_pool_t *) pool )->last_used_list = NULL;

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_pool_t *) pool )->last_used_list = last_used_list;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_pool_append_handle(
	          pool,
	          NULL,
	          test_handle,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          NULL,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          test_handle,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_append_handle with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;

		if( result == 1 )
		{
			/* Clean up
			 */
			result = libbfio_pool_remove_handle(
			          pool,
			          0,
			          &test_handle,
			          &error );

			BFIO_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			BFIO_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			test_handle = handle;
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_append_handle with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;

		if( result == 1 )
		{
			/* Clean up
			 */
			result = libbfio_pool_remove_handle(
			          pool,
			          0,
			          &test_handle,
			          &error );

			BFIO_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			BFIO_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			test_handle = handle;
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_set_handle function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_set_handle(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle        = NULL;
	libbfio_handle_t *test_handle   = NULL;
	libbfio_pool_t *pool            = NULL;
	libcdata_list_t *last_used_list = NULL;
	libcerror_error_t *error        = NULL;
	size_t source_length            = 0;
	int result                      = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	test_handle = handle;

	/* Test regular cases
	 */
	result = libbfio_handle_open(
	          handle,
	          LIBBFIO_OPEN_WRITE,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_close(
	          handle,
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
	result = libbfio_pool_remove_handle(
	          pool,
	          0,
	          &test_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	test_handle = handle;

	/* Test error cases
	 */
	result = libbfio_pool_set_handle(
	          NULL,
	          0,
	          test_handle,
	          LIBBFIO_OPEN_READ,
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

	last_used_list = ( (libbfio_internal_pool_t *) pool )->last_used_list;

	( (libbfio_internal_pool_t *) pool )->last_used_list = NULL;

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_pool_t *) pool )->last_used_list = last_used_list;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_pool_set_handle(
	          pool,
	          -1,
	          test_handle,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          NULL,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          test_handle,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_set_handle with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;

		if( result == 1 )
		{
			/* Clean up
			 */
			result = libbfio_pool_remove_handle(
			          pool,
			          0,
			          &test_handle,
			          &error );

			BFIO_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			BFIO_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			test_handle = handle;
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_set_handle with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          test_handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;

		if( result == 1 )
		{
			/* Clean up
			 */
			result = libbfio_pool_remove_handle(
			          pool,
			          0,
			          &test_handle,
			          &error );

			BFIO_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			BFIO_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			test_handle = handle;
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_remove_handle function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_remove_handle(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle        = NULL;
	libbfio_handle_t *test_handle   = NULL;
	libbfio_pool_t *pool            = NULL;
	libcdata_list_t *last_used_list = NULL;
	libcerror_error_t *error        = NULL;
	size_t source_length            = 0;
	int result                      = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	/* Test regular cases
	 */
	result = libbfio_pool_remove_handle(
	          pool,
	          0,
	          &test_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Initialize test
	 */
	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          test_handle,
	          LIBBFIO_OPEN_READ,
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
	test_handle = NULL;

	result = libbfio_pool_remove_handle(
	          NULL,
	          0,
	          &test_handle,
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

	last_used_list = ( (libbfio_internal_pool_t *) pool )->last_used_list;

	( (libbfio_internal_pool_t *) pool )->last_used_list = NULL;

	result = libbfio_pool_remove_handle(
	          pool,
	          0,
	          &test_handle,
	          &error );

	( (libbfio_internal_pool_t *) pool )->last_used_list = last_used_list;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_pool_remove_handle(
	          pool,
	          -1,
	          &test_handle,
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

	result = libbfio_pool_remove_handle(
	          pool,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_remove_handle with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_remove_handle(
	          pool,
	          0,
	          &test_handle,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;

		if( result == 1 )
		{
			result = libbfio_pool_set_handle(
			          pool,
			          0,
			          test_handle,
			          LIBBFIO_OPEN_READ,
			          &error );

			BFIO_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			BFIO_TEST_ASSERT_IS_NULL(
			 "error",
			 error );
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_remove_handle with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_pool_remove_handle(
	          pool,
	          0,
	          &test_handle,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;

		if( result == 1 )
		{
			result = libbfio_pool_set_handle(
			          pool,
			          0,
			          test_handle,
			          LIBBFIO_OPEN_READ,
			          &error );

			BFIO_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 1 );

			BFIO_TEST_ASSERT_IS_NULL(
			 "error",
			 error );
		}
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_internal_pool_open function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_pool_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	size_t source_length     = 0;
	int entry_index          = 0;
	int result               = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	/* Test regular cases
	 */
	result = libbfio_internal_pool_open(
	          (libbfio_internal_pool_t *) pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_internal_pool_open(
	          (libbfio_internal_pool_t *) pool,
	          0,
	          LIBBFIO_OPEN_READ,
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

	/* Clean up
	 */
	result = libbfio_pool_close(
	          pool,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_internal_pool_open(
	          NULL,
	          0,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_internal_pool_open(
	          (libbfio_internal_pool_t *) pool,
	          -1,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_internal_pool_open(
	          (libbfio_internal_pool_t *) pool,
	          0,
	          0,
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

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* Tests the libbfio_pool_open function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	size_t source_length     = 0;
	int entry_index          = 0;
	int result               = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	/* Test regular cases
	 */
	result = libbfio_pool_open(
	          pool,
	          0,
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
	result = libbfio_pool_close(
	          pool,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_pool_open(
	          NULL,
	          0,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_open(
	          pool,
	          -1,
	          LIBBFIO_OPEN_READ,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_open with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_open with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 4;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_reopen function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_reopen(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	size_t source_length     = 0;
	int entry_index          = 0;
	int result               = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_pool_reopen(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_pool_reopen(
	          NULL,
	          0,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_reopen(
	          pool,
	          -1,
	          LIBBFIO_OPEN_READ,
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

	result = libbfio_pool_reopen(
	          pool,
	          0,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_reopen with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_reopen(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_reopen with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 1;

	result = libbfio_pool_reopen(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_internal_pool_close function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_pool_close(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	size_t source_length     = 0;
	int result               = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          1,
	          2,
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

	/* Test error cases
	 */
	result = libbfio_internal_pool_close(
	          (libbfio_internal_pool_t *) pool,
	          0,
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

	/* Initialize test
	 */
	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_set_handle(
	          pool,
	          0,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_internal_pool_close(
	          (libbfio_internal_pool_t *) pool,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_internal_pool_close(
	          NULL,
	          0,
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

	result = libbfio_internal_pool_close(
	          (libbfio_internal_pool_t *) pool,
	          -1,
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

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_pool_free(
	          &pool,
	          &error );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* Tests the libbfio_pool_close function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_close(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	size_t source_length     = 0;
	int entry_index          = 0;
	int result               = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_pool_close(
	          pool,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_pool_close(
	          NULL,
	          0,
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

	result = libbfio_pool_close(
	          pool,
	          -1,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_close with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_close(
	          pool,
	          0,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_close with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 1;

	result = libbfio_pool_close(
	          pool,
	          0,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_close_all function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_close_all(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	size_t source_length     = 0;
	int entry_index          = 0;
	int result               = 0;

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

	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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

	result = libbfio_file_initialize(
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

	source_length = narrow_string_length(
	                 narrow_source );

	result = libbfio_file_set_name(
	          handle,
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

	result = libbfio_pool_append_handle(
	          pool,
	          &entry_index,
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	handle = NULL;

	result = libbfio_pool_open(
	          pool,
	          0,
	          LIBBFIO_OPEN_READ,
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
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_pool_close_all(
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_close_all with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_close_all(
	          pool,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_close_all with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 1;

	result = libbfio_pool_close_all(
	          pool,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libbfio_pool_close_all(
	          pool,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

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
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

	/* TODO add tests for libbfio_internal_pool_get_open_handle */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* Tests the libbfio_pool_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_read_buffer(
     libbfio_pool_t *pool )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_pool_get_size(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	read_count = libbfio_pool_read_buffer(
	              pool,
	              0,
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
	read_count = libbfio_pool_read_buffer(
	              NULL,
	              0,
	              buffer,
	              32,
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

	read_count = libbfio_pool_read_buffer(
	              pool,
	              -1,
	              buffer,
	              32,
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

	read_count = libbfio_pool_read_buffer(
	              pool,
	              0,
	              NULL,
	              32,
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

	read_count = libbfio_pool_read_buffer(
	              pool,
	              0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libbfio_pool_read_buffer(
	              pool,
	              0,
	              buffer,
	              32,
	              &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	read_count = libbfio_pool_read_buffer(
	              pool,
	              0,
	              buffer,
	              32,
	              &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_read_buffer_at_offset(
     libbfio_pool_t *pool )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_pool_get_size(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              0,
	              buffer,
	              32,
	              0,
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
	read_count = libbfio_pool_read_buffer_at_offset(
	              NULL,
	              0,
	              buffer,
	              32,
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

	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              -1,
	              buffer,
	              32,
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

	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              0,
	              NULL,
	              32,
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

	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              0,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
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

	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              0,
	              buffer,
	              32,
	              -1,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              0,
	              buffer,
	              32,
	              0,
	              &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	read_count = libbfio_pool_read_buffer_at_offset(
	              pool,
	              0,
	              buffer,
	              32,
	              0,
	              &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_write_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_write_buffer(
     void )
{
	char narrow_temporary_filename[ 17 ] = {
		'b', 'f', 'i', 'o', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	ssize_t write_count      = 0;
	int entry_index          = 0;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Initialize test
	 */
	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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
		result = libbfio_file_initialize(
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

		result = libbfio_file_set_name(
		          handle,
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

		result = libbfio_handle_open(
		          handle,
		          LIBBFIO_OPEN_WRITE,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_pool_append_handle(
		          pool,
		          &entry_index,
		          handle,
		          LIBBFIO_OPEN_READ,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		handle = NULL;

		/* Test regular cases
		 */
		write_count = libbfio_pool_write_buffer(
		               pool,
		               0,
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
	write_count = libbfio_pool_write_buffer(
	               NULL,
	               0,
	               buffer,
	               32,
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

	write_count = libbfio_pool_write_buffer(
	               pool,
	               -1,
	               buffer,
	               32,
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

	write_count = libbfio_pool_write_buffer(
	               pool,
	               0,
	               NULL,
	               32,
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

	write_count = libbfio_pool_write_buffer(
	               pool,
	               0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_write_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	write_count = libbfio_pool_write_buffer(
	               pool,
	               0,
	               buffer,
	               32,
	               &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_write_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	write_count = libbfio_pool_write_buffer(
	               pool,
	               0,
	               buffer,
	               32,
	               &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
		result = libbfio_pool_close_all(
		          pool,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( with_temporary_file != 0 )
	{
		bfio_test_remove_temporary_file(
		 narrow_temporary_filename,
		 NULL );
	}
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_write_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_write_buffer_at_offset(
     void )
{
	char narrow_temporary_filename[ 17 ] = {
		'b', 'f', 'i', 'o', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	libcerror_error_t *error = NULL;
	ssize_t write_count      = 0;
	int entry_index          = 0;
	int result               = 0;
	int with_temporary_file  = 0;

	/* Initialize test
	 */
	result = libbfio_pool_initialize(
	          &pool,
	          0,
	          LIBBFIO_POOL_UNLIMITED_NUMBER_OF_OPEN_HANDLES,
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
		result = libbfio_file_initialize(
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

		result = libbfio_file_set_name(
		          handle,
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

		result = libbfio_handle_open(
		          handle,
		          LIBBFIO_OPEN_WRITE,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		result = libbfio_pool_append_handle(
		          pool,
		          &entry_index,
		          handle,
		          LIBBFIO_OPEN_READ,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		handle = NULL;

		/* Test regular cases
		 */
		write_count = libbfio_pool_write_buffer_at_offset(
		               pool,
		               0,
		               buffer,
		               32,
		               0,
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
	write_count = libbfio_pool_write_buffer_at_offset(
	               NULL,
	               0,
	               buffer,
	               32,
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

	write_count = libbfio_pool_write_buffer_at_offset(
	               pool,
	               -1,
	               buffer,
	               32,
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

	write_count = libbfio_pool_write_buffer_at_offset(
	               pool,
	               0,
	               NULL,
	               32,
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

	write_count = libbfio_pool_write_buffer_at_offset(
	               pool,
	               0,
	               buffer,
	               (size_t) SSIZE_MAX + 1,
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

	write_count = libbfio_pool_write_buffer_at_offset(
	               pool,
	               0,
	               buffer,
	               32,
	               -1,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_write_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	write_count = libbfio_pool_write_buffer_at_offset(
	               pool,
	               0,
	               buffer,
	               32,
	               0,
	               &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_write_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	write_count = libbfio_pool_write_buffer_at_offset(
	               pool,
	               0,
	               buffer,
	               32,
	               0,
	               &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_SSIZE(
		 "write_count",
		 write_count,
		 (ssize_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
		result = libbfio_pool_close_all(
		          pool,
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( with_temporary_file != 0 )
	{
		bfio_test_remove_temporary_file(
		 narrow_temporary_filename,
		 NULL );
	}
	if( pool != NULL )
	{
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_pool_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_seek_offset(
     libbfio_pool_t *pool )
{
	libcerror_error_t *error = NULL;
	size64_t file_size       = 0;
	off64_t offset           = 0;
	off64_t seek_offset      = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_pool_get_size(
	          pool,
	          0,
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

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          NULL,
	          0,
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

	offset = libbfio_pool_seek_offset(
	          pool,
	          -1,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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
	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
	          0,
	          SEEK_SET,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	offset = libbfio_pool_seek_offset(
	          pool,
	          0,
	          0,
	          SEEK_SET,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_get_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_get_offset(
     libbfio_pool_t *pool )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_pool_get_offset(
	          pool,
	          0,
	          &offset,
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
	result = libbfio_pool_get_offset(
	          NULL,
	          0,
	          &offset,
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

	result = libbfio_pool_get_offset(
	          pool,
	          -1,
	          &offset,
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

	result = libbfio_pool_get_offset(
	          pool,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_get_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_get_offset(
	          pool,
	          0,
	          &offset,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_get_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	result = libbfio_pool_get_offset(
	          pool,
	          0,
	          &offset,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_pool_get_size function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_pool_get_size(
     libbfio_pool_t *pool )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_pool_get_size(
	          pool,
	          0,
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
	result = libbfio_pool_get_size(
	          NULL,
	          0,
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

	result = libbfio_pool_get_size(
	          pool,
	          -1,
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

	result = libbfio_pool_get_size(
	          pool,
	          0,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_pool_get_size with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_pool_get_size(
	          pool,
	          0,
	          &size,
	          &error );

	if( bfio_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_LOCAL_LIBCDATA )

	/* Test libbfio_pool_get_size with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 2;

	result = libbfio_pool_get_size(
	          pool,
	          0,
	          &size,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_LOCAL_LIBCDATA ) */
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

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
	libbfio_pool_t *pool       = NULL;
	libcerror_error_t *error   = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

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
#if defined( HAVE_DEBUG_OUTPUT ) && defined( BFIO_TEST_POOL_VERBOSE )
	libbfio_notify_set_verbose(
	 1 );
	libbfio_notify_set_stream(
	 stderr,
	 NULL );
#endif

	BFIO_TEST_RUN(
	 "libbfio_pool_initialize",
	 bfio_test_pool_initialize );

	BFIO_TEST_RUN(
	 "libbfio_pool_free",
	 bfio_test_pool_free );

	BFIO_TEST_RUN(
	 "libbfio_pool_clone",
	 bfio_test_pool_clone );

	BFIO_TEST_RUN(
	 "libbfio_pool_resize",
	 bfio_test_pool_resize );

	BFIO_TEST_RUN(
	 "libbfio_pool_write_buffer",
	 bfio_test_pool_write_buffer );

	BFIO_TEST_RUN(
	 "libbfio_pool_write_buffer_at_offset",
	 bfio_test_pool_write_buffer_at_offset );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_pool_open_handle",
		 bfio_test_internal_pool_open_handle,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_pool_append_handle_to_last_used_list",
		 bfio_test_internal_pool_append_handle_to_last_used_list,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_pool_move_handle_to_front_of_last_used_list",
		 bfio_test_internal_pool_move_handle_to_front_of_last_used_list,
		 source );

		/* TODO add tests for libbfio_internal_pool_remove_handle_from_last_used_list */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_append_handle",
		 bfio_test_pool_append_handle,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_set_handle",
		 bfio_test_pool_set_handle,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_remove_handle",
		 bfio_test_pool_remove_handle,
		 source );

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_pool_open",
		 bfio_test_internal_pool_open,
		 source );

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_open",
		 bfio_test_pool_open,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_reopen",
		 bfio_test_pool_reopen,
		 source );

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_pool_close",
		 bfio_test_internal_pool_close,
		 source );

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_close",
		 bfio_test_pool_close,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_close_all",
		 bfio_test_pool_close_all,
		 source );

		/* Initialize test
		 */
		result = bfio_test_pool_open_source(
		          &pool,
		          source,
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

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_get_number_of_handles",
		 bfio_test_pool_get_number_of_handles,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_get_handle",
		 bfio_test_pool_get_handle,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_get_maximum_number_of_open_handles",
		 bfio_test_pool_get_maximum_number_of_open_handles,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_set_maximum_number_of_open_handles",
		 bfio_test_pool_set_maximum_number_of_open_handles,
		 pool );

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

		/* TODO add tests for libbfio_internal_pool_get_open_handle */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_read_buffer",
		 bfio_test_pool_read_buffer,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_read_buffer_at_offset",
		 bfio_test_pool_read_buffer_at_offset,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_seek_offset",
		 bfio_test_pool_seek_offset,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_get_offset",
		 bfio_test_pool_get_offset,
		 pool );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_pool_get_size",
		 bfio_test_pool_get_size,
		 pool );

		/* Clean up
		 */
		result = bfio_test_pool_close_source(
		          &pool,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		BFIO_TEST_ASSERT_IS_NULL(
		 "pool",
		 pool );

		BFIO_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

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
	return( EXIT_FAILURE );
}

