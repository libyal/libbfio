/*
 * Library handle type test program
 *
 * Copyright (C) 2009-2021, Joachim Metz <joachim.metz@gmail.com>
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
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"
#include "bfio_test_rwlock.h"

#include "../libbfio/libbfio_handle.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Creates and opens a source handle
 * Returns 1 if successful or -1 on error
 */
int bfio_test_handle_open_source(
     libbfio_handle_t **handle,
     const system_character_t *source,
     libcerror_error_t **error )
{
	static char *function = "bfio_test_handle_open_source";
	int result            = 0;
	size_t source_length  = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
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
	if( libbfio_file_initialize(
	     handle,
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
	          *handle,
	          source,
	          source_length,
	          error );
#else
	result = libbfio_file_set_name(
	          *handle,
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
	result = libbfio_handle_open(
	          *handle,
	          LIBBFIO_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *handle != NULL )
	{
		libbfio_handle_free(
		 handle,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source handle
 * Returns 1 if successful or -1 on error
 */
int bfio_test_handle_close_source(
     libbfio_handle_t **handle,
     libcerror_error_t **error )
{
	static char *function = "bfio_test_handle_close_source";
	int result            = 0;

	if( handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_close(
	     *handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close handle.",
		 function );

		result = -1;
	}
	if( libbfio_handle_free(
	     handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free handle.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libbfio_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_initialize(
     void )
{
	libbfio_handle_t *handle        = NULL;
	libcerror_error_t *error        = NULL;
	int result                      = 0;

#if defined( HAVE_BFIO_TEST_MEMORY )
	int number_of_malloc_fail_tests = 3;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libbfio_handle_initialize(
	          &handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
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
	result = libbfio_handle_initialize(
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
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

	handle = (libbfio_handle_t *) 0x12345678UL;

	result = libbfio_handle_initialize(
	          &handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
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
		/* Test libbfio_handle_initialize with malloc failing
		 */
		bfio_test_malloc_attempts_before_fail = test_number;

		result = libbfio_handle_initialize(
		          &handle,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          NULL,
		          0,
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

/* Tests the libbfio_handle_free function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

#if defined( HAVE_BFIO_TEST_RWLOCK )
	libbfio_handle_t *handle = NULL;
#endif

	/* Test error cases
	 */
	result = libbfio_handle_free(
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
	result = libbfio_handle_initialize(
	          &handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
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

	/* Test libbfio_handle_free with pthread_rwlock_destroy failing in libcthreads_read_write_lock_free
	 */
	bfio_test_pthread_rwlock_destroy_attempts_before_fail = 0;

	result = libbfio_handle_free(
	          &handle,
	          &error );

	if( bfio_test_pthread_rwlock_destroy_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_destroy_attempts_before_fail = -1;

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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
#if defined( HAVE_BFIO_TEST_RWLOCK )
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
#endif
	return( 0 );
}

/* Tests the libbfio_handle_clone function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_clone(
     void )
{
	libbfio_handle_t *destination_handle = NULL;
	libbfio_handle_t *source_handle      = NULL;
	libcerror_error_t *error             = NULL;
	int result                           = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &source_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "source_handle",
	 source_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	result = libbfio_handle_clone(
	          &destination_handle,
	          source_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "destination_handle",
	 destination_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &destination_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "destination_handle",
	 destination_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_clone(
	          &destination_handle,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "destination_handle",
	 destination_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_handle_clone(
	          NULL,
	          source_handle,
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

	destination_handle = (libbfio_handle_t *) 0x12345678UL;

	result = libbfio_handle_clone(
	          &destination_handle,
	          source_handle,
	          &error );

	destination_handle = NULL;

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

	/* Test libbfio_handle_clone with malloc failing
	 */
	bfio_test_malloc_attempts_before_fail = 0;

	result = libbfio_handle_clone(
	          &destination_handle,
	          source_handle,
	          &error );

	if( bfio_test_malloc_attempts_before_fail != -1 )
	{
		bfio_test_malloc_attempts_before_fail = -1;

		if( destination_handle != NULL )
		{
			libbfio_handle_free(
			 &destination_handle,
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
		 "destination_handle",
		 destination_handle );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_BFIO_TEST_MEMORY ) */

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_handle_clone with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_clone(
	          &destination_handle,
	          source_handle,
	          &error );

	if( bfio_test_pthread_rwlock_rdlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_rdlock_attempts_before_fail = -1;

		if( destination_handle != NULL )
		{
			libbfio_handle_free(
			 &destination_handle,
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
		 "destination_handle",
		 destination_handle );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libbfio_handle_clone with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_clone(
	          &destination_handle,
	          source_handle,
	          &error );

	if( bfio_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		bfio_test_pthread_rwlock_unlock_attempts_before_fail = -1;

		if( destination_handle != NULL )
		{
			libbfio_handle_free(
			 &destination_handle,
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
		 "destination_handle",
		 destination_handle );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	result = libbfio_handle_free(
	          &source_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "source_handle",
	 source_handle );

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
	if( destination_handle != NULL )
	{
		libbfio_handle_free(
		 &destination_handle,
		 NULL );
	}
	if( source_handle != NULL )
	{
		libbfio_handle_free(
		 &source_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_handle_open function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	intptr_t *open_function  = NULL;
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

	/* Test regular cases
	 */
	result = libbfio_handle_open(
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

	/* Test error cases
	 */
	result = libbfio_handle_open(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	result = libbfio_handle_open(
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	open_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->open;

	( (libbfio_internal_handle_t *) handle )->open = NULL;

	result = libbfio_handle_open(
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_handle_t *) handle )->open = (int (*)(intptr_t *, int, libcerror_error_t **)) open_function;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_handle_open(
	          handle,
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

	( (libbfio_internal_handle_t *) handle )->open_on_demand = 1;

	result = libbfio_handle_open(
	          handle,
	          LIBBFIO_OPEN_WRITE,
	          &error );

	( (libbfio_internal_handle_t *) handle )->open_on_demand = 0;

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

	/* Test libbfio_handle_open with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_open(
	          handle,
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
	/* Test libbfio_handle_open with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_open(
	          handle,
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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
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

/* Tests the libbfio_handle_reopen function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_reopen(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libbfio_handle_t *handle       = NULL;
	libcerror_error_t *error       = NULL;
	intptr_t *close_function       = NULL;
	intptr_t *io_handle            = NULL;
	intptr_t *open_function        = NULL;
	intptr_t *seek_offset_function = NULL;
	size_t source_length           = 0;
	int result                     = 0;

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

	result = libbfio_handle_open(
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

	/* Test regular cases
	 */
	result = libbfio_handle_reopen(
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

	/* Test error cases
	 */
	result = libbfio_handle_reopen(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	result = libbfio_handle_reopen(
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	close_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->close;

	( (libbfio_internal_handle_t *) handle )->close = NULL;

	result = libbfio_handle_reopen(
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_handle_t *) handle )->close = (int (*)(intptr_t *, libcerror_error_t **)) close_function;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	open_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->open;

	( (libbfio_internal_handle_t *) handle )->open = NULL;

	result = libbfio_handle_reopen(
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_handle_t *) handle )->open = (int (*)(intptr_t *, int, libcerror_error_t **)) open_function;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	seek_offset_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->seek_offset;

	( (libbfio_internal_handle_t *) handle )->seek_offset = NULL;

	result = libbfio_handle_reopen(
	          handle,
	          LIBBFIO_OPEN_READ,
	          &error );

	( (libbfio_internal_handle_t *) handle )->seek_offset = (off64_t (*)(intptr_t *, off64_t, int, libcerror_error_t **)) seek_offset_function;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_handle_reopen(
	          handle,
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

	/* Test libbfio_handle_reopen with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_reopen(
	          handle,
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
	/* Test libbfio_handle_reopen with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_reopen(
	          handle,
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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
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

/* Tests the libbfio_handle_close function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_close(
     void )
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	intptr_t *close_function = NULL;
	intptr_t *io_handle      = NULL;
	int result               = 0;

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

	/* Test error cases
	 */
	result = libbfio_handle_close(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	result = libbfio_handle_close(
	          handle,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	close_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->close;

	( (libbfio_internal_handle_t *) handle )->close = NULL;

	result = libbfio_handle_close(
	          handle,
	          &error );

	( (libbfio_internal_handle_t *) handle )->close = (int (*)(intptr_t *, libcerror_error_t **)) close_function;

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

	/* Test libbfio_handle_close with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_close(
	          handle,
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
	/* Test libbfio_handle_close with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_close(
	          handle,
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

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_internal_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_handle_read_buffer(
     libbfio_handle_t *handle )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error = NULL;
	intptr_t *read_function  = NULL;
	size64_t file_size       = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_handle_get_size(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	read_count = libbfio_internal_handle_read_buffer(
	              (libbfio_internal_handle_t *) handle,
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
	read_count = libbfio_internal_handle_read_buffer(
	              NULL,
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

	read_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->read;

	( (libbfio_internal_handle_t *) handle )->read = NULL;

	read_count = libbfio_internal_handle_read_buffer(
	              (libbfio_internal_handle_t *) handle,
	              buffer,
	              32,
	              &error );

	( (libbfio_internal_handle_t *) handle )->read = (ssize_t (*)(intptr_t *, uint8_t *, size_t, libcerror_error_t **)) read_function;

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libbfio_internal_handle_read_buffer(
	              (libbfio_internal_handle_t *) handle,
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

	read_count = libbfio_internal_handle_read_buffer(
	              (libbfio_internal_handle_t *) handle,
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

/* Tests the libbfio_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_read_buffer(
     libbfio_handle_t *handle )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	size64_t file_size       = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_handle_get_size(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	read_count = libbfio_handle_read_buffer(
	              handle,
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
	read_count = libbfio_handle_read_buffer(
	              NULL,
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	read_count = libbfio_handle_read_buffer(
	              handle,
	              buffer,
	              32,
	              &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libbfio_handle_read_buffer(
	              handle,
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

	read_count = libbfio_handle_read_buffer(
	              handle,
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

	/* Test libbfio_handle_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libbfio_handle_read_buffer(
	              handle,
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
	/* Test libbfio_handle_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libbfio_handle_read_buffer(
	              handle,
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

/* Tests the libbfio_handle_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_read_buffer_at_offset(
     libbfio_handle_t *handle )
{
	uint8_t buffer[ 32 ];

	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	size64_t file_size       = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_handle_get_size(
	          handle,
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
	/* Test regular cases
	 */
	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
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
	read_count = libbfio_handle_read_buffer_at_offset(
	              NULL,
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
	              buffer,
	              32,
	              0,
	              &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
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

	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
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

	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
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

	/* Test libbfio_handle_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
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
	/* Test libbfio_handle_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libbfio_handle_read_buffer_at_offset(
	              handle,
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

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_internal_handle_write_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_handle_write_buffer(
     void )
{
	char narrow_temporary_filename[ 17 ] = {
		'b', 'f', 'i', 'o', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	intptr_t *write_function = NULL;
	ssize_t write_count      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

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

		/* Test regular cases
		 */
		write_count = libbfio_internal_handle_write_buffer(
		               (libbfio_internal_handle_t *) handle,
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
	write_count = libbfio_internal_handle_write_buffer(
	               NULL,
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

	write_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->write;

	( (libbfio_internal_handle_t *) handle )->write = NULL;

	write_count = libbfio_internal_handle_write_buffer(
	               (libbfio_internal_handle_t *) handle,
	               buffer,
	               32,
	               &error );

	( (libbfio_internal_handle_t *) handle )->write = (ssize_t (*)(intptr_t *, const uint8_t *, size_t, libcerror_error_t **)) write_function;

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libbfio_internal_handle_write_buffer(
	               (libbfio_internal_handle_t *) handle,
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

	write_count = libbfio_internal_handle_write_buffer(
	               (libbfio_internal_handle_t *) handle,
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

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
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
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* Tests the libbfio_handle_write_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_write_buffer(
     void )
{
	char narrow_temporary_filename[ 17 ] = {
		'b', 'f', 'i', 'o', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	ssize_t write_count      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

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

		/* Test regular cases
		 */
		write_count = libbfio_handle_write_buffer(
		               handle,
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
	write_count = libbfio_handle_write_buffer(
	               NULL,
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	write_count = libbfio_handle_write_buffer(
	               handle,
	               buffer,
	               32,
	               &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libbfio_handle_write_buffer(
	               handle,
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

	write_count = libbfio_handle_write_buffer(
	               handle,
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

	/* Test libbfio_handle_write_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	write_count = libbfio_handle_write_buffer(
	               handle,
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
	/* Test libbfio_handle_write_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	write_count = libbfio_handle_write_buffer(
	               handle,
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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
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
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_handle_write_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_write_buffer_at_offset(
     void )
{
	char narrow_temporary_filename[ 17 ] = {
		'b', 'f', 'i', 'o', '_', 't', 'e', 's', 't', '_', 'X', 'X', 'X', 'X', 'X', 'X', 0 };

	uint8_t buffer[ 32 ] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
		'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5' };

	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	ssize_t write_count      = 0;
	int result               = 0;
	int with_temporary_file  = 0;

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

		/* Test regular cases
		 */
		write_count = libbfio_handle_write_buffer_at_offset(
		               handle,
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
	write_count = libbfio_handle_write_buffer_at_offset(
	               NULL,
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	write_count = libbfio_handle_write_buffer_at_offset(
	               handle,
	               buffer,
	               32,
	               0,
	               &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_SSIZE(
	 "write_count",
	 write_count,
	 (ssize_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	write_count = libbfio_handle_write_buffer_at_offset(
	               handle,
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

	write_count = libbfio_handle_write_buffer_at_offset(
	               handle,
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

	write_count = libbfio_handle_write_buffer_at_offset(
	               handle,
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

	/* Test libbfio_handle_write_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	write_count = libbfio_handle_write_buffer_at_offset(
	               handle,
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
	/* Test libbfio_handle_write_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	write_count = libbfio_handle_write_buffer_at_offset(
	               handle,
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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Clean up
	 */
	if( with_temporary_file != 0 )
	{
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
	if( handle != NULL )
	{
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	return( 0 );
}

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_internal_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_internal_handle_seek_offset(
     libbfio_handle_t *handle )
{
	libbfio_handle_t *closed_handle = NULL;
	libcerror_error_t *error        = NULL;
	intptr_t *io_handle             = NULL;
	intptr_t *seek_offset_function  = NULL;
	size64_t file_size              = 0;
	off64_t offset                  = 0;
	off64_t seek_offset             = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libbfio_handle_get_size(
	          handle,
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

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
	          0,
	          SEEK_SET,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	seek_offset_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->seek_offset;

	( (libbfio_internal_handle_t *) handle )->seek_offset = NULL;

	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
	          0,
	          SEEK_SET,
	          &error );

	( (libbfio_internal_handle_t *) handle )->seek_offset = (off64_t (*)(intptr_t *, off64_t, int, libcerror_error_t **)) seek_offset_function;

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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) handle,
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
	result = libbfio_handle_initialize(
	          &closed_handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "closed_handle",
	 closed_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset on a closed file IO handle
	 */
	offset = libbfio_internal_handle_seek_offset(
	          (libbfio_internal_handle_t *) closed_handle,
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
	result = libbfio_handle_free(
	          &closed_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "closed_handle",
	 closed_handle );

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
	if( closed_handle != NULL )
	{
		libbfio_handle_free(
		 &closed_handle,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* Tests the libbfio_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_seek_offset(
     libbfio_handle_t *handle )
{
	libbfio_handle_t *closed_handle = NULL;
	libcerror_error_t *error        = NULL;
	intptr_t *io_handle             = NULL;
	intptr_t *seek_offset_function  = NULL;
	size64_t file_size              = 0;
	off64_t offset                  = 0;
	off64_t seek_offset             = 0;
	int result                      = 0;

	/* Initialize test
	 */
	result = libbfio_handle_get_size(
	          handle,
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

	offset = libbfio_handle_seek_offset(
	          handle,
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

	offset = libbfio_handle_seek_offset(
	          handle,
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

	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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

	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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

	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	offset = libbfio_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	seek_offset_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->seek_offset;

	( (libbfio_internal_handle_t *) handle )->seek_offset = NULL;

	offset = libbfio_handle_seek_offset(
	          handle,
	          0,
	          SEEK_SET,
	          &error );

	( (libbfio_internal_handle_t *) handle )->seek_offset = (off64_t (*)(intptr_t *, off64_t, int, libcerror_error_t **)) seek_offset_function;

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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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
	offset = libbfio_handle_seek_offset(
	          handle,
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

	/* Test libbfio_handle_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libbfio_handle_seek_offset(
	          handle,
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
	/* Test libbfio_handle_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	offset = libbfio_handle_seek_offset(
	          handle,
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
#endif /* defined( HAVE_BFIO_TEST_RWLOCK ) */

	/* Initialize test
	 */
	result = libbfio_handle_initialize(
	          &closed_handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "closed_handle",
	 closed_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test seek offset on a closed file IO handle
	 */
	offset = libbfio_handle_seek_offset(
	          closed_handle,
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
	result = libbfio_handle_free(
	          &closed_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "closed_handle",
	 closed_handle );

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
	if( closed_handle != NULL )
	{
		libbfio_handle_free(
		 &closed_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_handle_exists function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_exists(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error  = NULL;
	intptr_t *exists_function = NULL;
	intptr_t *io_handle       = NULL;
	int result                = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_exists(
	          handle,
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
	result = libbfio_handle_exists(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	result = libbfio_handle_exists(
	          handle,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	exists_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->exists;

	( (libbfio_internal_handle_t *) handle )->exists = NULL;

	result = libbfio_handle_exists(
	          handle,
	          &error );

	( (libbfio_internal_handle_t *) handle )->exists = (int (*)(intptr_t *, libcerror_error_t **)) exists_function;

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

	/* Test libbfio_handle_exists with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_exists(
	          handle,
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
	/* Test libbfio_handle_exists with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_exists(
	          handle,
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

/* Tests the libbfio_handle_is_open function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_is_open(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error   = NULL;
	intptr_t *io_handle        = NULL;
	intptr_t *is_open_function = NULL;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_is_open(
	          handle,
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
	result = libbfio_handle_is_open(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	result = libbfio_handle_is_open(
	          handle,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	is_open_function = (intptr_t *) ( (libbfio_internal_handle_t *) handle )->is_open;

	( (libbfio_internal_handle_t *) handle )->is_open = NULL;

	result = libbfio_handle_is_open(
	          handle,
	          &error );

	( (libbfio_internal_handle_t *) handle )->is_open = (int (*)(intptr_t *, libcerror_error_t **)) is_open_function;

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

	/* Test libbfio_handle_is_open with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_is_open(
	          handle,
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
	/* Test libbfio_handle_is_open with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_is_open(
	          handle,
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

/* Tests the libbfio_handle_get_io_handle function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_get_io_handle(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_get_io_handle(
	          handle,
	          &io_handle,
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
	result = libbfio_handle_get_io_handle(
	          NULL,
	          &io_handle,
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

	result = libbfio_handle_get_io_handle(
	          handle,
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

	/* Test libbfio_handle_get_io_handle with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_get_io_handle(
	          handle,
	          &io_handle,
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
	/* Test libbfio_handle_get_io_handle with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_get_io_handle(
	          handle,
	          &io_handle,
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

/* Tests the libbfio_handle_get_access_flags function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_get_access_flags(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	int access_flags         = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_get_access_flags(
	          handle,
	          &access_flags,
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
	result = libbfio_handle_get_access_flags(
	          NULL,
	          &access_flags,
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

	result = libbfio_handle_get_access_flags(
	          handle,
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

	/* Test libbfio_handle_get_access_flags with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_get_access_flags(
	          handle,
	          &access_flags,
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
	/* Test libbfio_handle_get_access_flags with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_get_access_flags(
	          handle,
	          &access_flags,
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

/* Tests the libbfio_handle_set_access_flags function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_set_access_flags(
     void )
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_handle_initialize(
	          &handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
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

	/* Test regular cases
	 */
	result = libbfio_handle_set_access_flags(
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

	/* Test error cases
	 */
	result = libbfio_handle_set_access_flags(
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

	result = libbfio_handle_set_access_flags(
	          handle,
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

	/* Test libbfio_handle_set_access_flags with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_set_access_flags(
	          handle,
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
	/* Test libbfio_handle_set_access_flags with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_set_access_flags(
	          handle,
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

/* Tests the libbfio_handle_get_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_get_offset(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_get_offset(
	          handle,
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
	result = libbfio_handle_get_offset(
	          NULL,
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

	result = libbfio_handle_get_offset(
	          handle,
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

	/* Test libbfio_handle_get_offset with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_get_offset(
	          handle,
	          &offset,
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
	/* Test libbfio_handle_get_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_get_offset(
	          handle,
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

/* Tests the libbfio_handle_get_size function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_get_size(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	intptr_t *io_handle      = NULL;
	size64_t size            = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_get_size(
	          handle,
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
	result = libbfio_handle_get_size(
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

	io_handle = ( (libbfio_internal_handle_t *) handle )->io_handle;

	( (libbfio_internal_handle_t *) handle )->io_handle = NULL;

	result = libbfio_handle_get_size(
	          handle,
	          &size,
	          &error );

	( (libbfio_internal_handle_t *) handle )->io_handle = io_handle;

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_handle_get_size(
	          handle,
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

	/* Test libbfio_handle_get_size with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_get_size(
	          handle,
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
	/* Test libbfio_handle_get_size with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_get_size(
	          handle,
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

/* Tests the libbfio_handle_set_open_on_demand function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_set_open_on_demand(
     void )
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_handle_initialize(
	          &handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
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

	/* Test regular cases
	 */
	result = libbfio_handle_set_open_on_demand(
	          handle,
	          1,
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
	result = libbfio_handle_set_open_on_demand(
	          NULL,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_handle_set_open_on_demand with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_set_open_on_demand(
	          handle,
	          1,
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
	/* Test libbfio_handle_set_open_on_demand with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_set_open_on_demand(
	          handle,
	          1,
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

/* Tests the libbfio_handle_get_number_of_offsets_read functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_get_number_of_offsets_read(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error   = NULL;
	int number_of_offsets_read = 0;
	int result                 = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_get_number_of_offsets_read(
	          handle,
	          &number_of_offsets_read,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_NOT_EQUAL_INT(
	 "number_of_offsets_read",
	 number_of_offsets_read,
	 0 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_handle_get_number_of_offsets_read(
	          NULL,
	          &number_of_offsets_read,
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

	result = libbfio_handle_get_number_of_offsets_read(
	          handle,
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

	/* Test libbfio_handle_get_number_of_offsets_read with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_get_number_of_offsets_read(
	          handle,
	          &number_of_offsets_read,
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
	/* Test libbfio_handle_get_number_of_offsets_read with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_get_number_of_offsets_read(
	          handle,
	          &number_of_offsets_read,
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

/* Tests the libbfio_handle_get_offset_read functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_get_offset_read(
     libbfio_handle_t *handle )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_handle_get_offset_read(
	          handle,
	          0,
	          &offset,
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
	result = libbfio_handle_get_offset_read(
	          NULL,
	          0,
	          &offset,
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

	result = libbfio_handle_get_offset_read(
	          handle,
	          -1,
	          &offset,
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

	result = libbfio_handle_get_offset_read(
	          handle,
	          0,
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

	result = libbfio_handle_get_offset_read(
	          handle,
	          0,
	          &offset,
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

	/* Test libbfio_handle_get_offset_read with pthread_rwlock_rdlock failing in libcthreads_read_write_lock_grab_for_read
	 */
	bfio_test_pthread_rwlock_rdlock_attempts_before_fail = 0;

	result = libbfio_handle_get_offset_read(
	          handle,
	          0,
	          &offset,
	          &size,
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
	/* Test libbfio_handle_get_offset_read with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_read
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_get_offset_read(
	          handle,
	          0,
	          &offset,
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

/* Tests the libbfio_handle_set_track_offsets_read function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_set_track_offsets_read(
     void )
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libbfio_handle_initialize(
	          &handle,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          NULL,
	          0,
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

	/* Test regular cases
	 */
	result = libbfio_handle_set_track_offsets_read(
	          handle,
	          1,
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
	result = libbfio_handle_set_track_offsets_read(
	          NULL,
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

#if defined( HAVE_BFIO_TEST_RWLOCK )

	/* Test libbfio_handle_set_track_offsets_read with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	bfio_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	result = libbfio_handle_set_track_offsets_read(
	          handle,
	          1,
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
	/* Test libbfio_handle_set_track_offsets_read with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	bfio_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	result = libbfio_handle_set_track_offsets_read(
	          handle,
	          1,
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
	libbfio_handle_t *handle   = NULL;
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
	BFIO_TEST_RUN(
	 "libbfio_handle_initialize",
	 bfio_test_handle_initialize );

	BFIO_TEST_RUN(
	 "libbfio_handle_free",
	 bfio_test_handle_free );

	BFIO_TEST_RUN(
	 "libbfio_handle_clone",
	 bfio_test_handle_clone );

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

	BFIO_TEST_RUN(
	 "libbfio_internal_handle_write_buffer",
	 bfio_test_internal_handle_write_buffer );

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

	BFIO_TEST_RUN(
	 "libbfio_handle_write_buffer",
	 bfio_test_handle_write_buffer );

	BFIO_TEST_RUN(
	 "libbfio_handle_write_buffer_at_offset",
	 bfio_test_handle_write_buffer_at_offset );

	BFIO_TEST_RUN(
	 "libbfio_handle_set_access_flags",
	 bfio_test_handle_set_access_flags );

	BFIO_TEST_RUN(
	 "libbfio_handle_set_open_on_demand",
	 bfio_test_handle_set_open_on_demand );

	BFIO_TEST_RUN(
	 "libbfio_handle_set_track_offsets_read",
	 bfio_test_handle_set_track_offsets_read );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_open",
		 bfio_test_handle_open,
		 source );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_reopen",
		 bfio_test_handle_reopen,
		 source );

		BFIO_TEST_RUN(
		 "libbfio_handle_close",
		 bfio_test_handle_close );

		/* Initialize test
		 */
		result = bfio_test_handle_open_source(
		          &handle,
		          source,
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

		result = libbfio_handle_set_track_offsets_read(
		          handle,
		          1,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        BFIO_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_handle_read_buffer",
		 bfio_test_internal_handle_read_buffer,
		 handle );

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_read_buffer",
		 bfio_test_handle_read_buffer,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_read_buffer_at_offset",
		 bfio_test_handle_read_buffer_at_offset,
		 handle );

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_internal_handle_seek_offset",
		 bfio_test_internal_handle_seek_offset,
		 handle );

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_seek_offset",
		 bfio_test_handle_seek_offset,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_exists",
		 bfio_test_handle_exists,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_is_open",
		 bfio_test_handle_is_open,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_io_handle",
		 bfio_test_handle_get_io_handle,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_access_flags",
		 bfio_test_handle_get_access_flags,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_offset",
		 bfio_test_handle_get_offset,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_size",
		 bfio_test_handle_get_size,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_number_of_offsets_read",
		 bfio_test_handle_get_number_of_offsets_read,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_offset_read",
		 bfio_test_handle_get_offset_read,
		 handle );

		/* Clean up
		 */
		result = bfio_test_handle_close_source(
		          &handle,
		          &error );

		BFIO_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		BFIO_TEST_ASSERT_IS_NULL(
	         "handle",
	         handle );

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
	if( handle != NULL )
	{
		bfio_test_handle_close_source(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

