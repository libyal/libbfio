/*
 * Library handle type test program
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
#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libclocale.h"
#include "bfio_test_libuna.h"
#include "bfio_test_macros.h"
#include "bfio_test_memory.h"

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
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

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

	/* Test libbfio_handle_initialize with malloc failing
	 */
	bfio_test_malloc_attempts_before_fail = 0;

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
	/* Test libbfio_handle_initialize with memset failing
	 */
	bfio_test_memset_attempts_before_fail = 0;

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
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
	result = libbfio_handle_initialize(
	          &source_handle,
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

	/* Test libbfio_handle_clone with memcpy failing
	 */
	bfio_test_memcpy_attempts_before_fail = 0;

	result = libbfio_handle_clone(
	          &destination_handle,
	          source_handle,
	          &error );

	if( bfio_test_memcpy_attempts_before_fail != -1 )
	{
		bfio_test_memcpy_attempts_before_fail = -1;

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

/* Tests the libbfio_file_set_name and libbfio_handle_open functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libbfio_handle_t *handle = NULL;
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

	/* Test open
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

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libbfio_file_set_name_wide and libbfio_handle_open functions
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libbfio_handle_t *handle = NULL;
	size_t source_length     = 0;
	int result               = 0;

	/* Initialize test
	 */
	result = bfio_test_get_wide_source(
	          source,
	          wide_source,
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

	source_length = wide_string_length(
	                 wide_source );

	result = libbfio_file_set_name_wide(
	          handle,
	          wide_source,
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

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libbfio_handle_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_read_buffer(
     libbfio_handle_t *handle )
{
	uint8_t buffer[ 32 ];

	libbfio_handle_t *closed_handle = NULL;
	libcerror_error_t *error                        = NULL;
	size64_t file_size                              = 0;
	ssize_t read_count                              = 0;
	off64_t offset                                  = 0;
	int result                                      = 0;

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

	read_count = libbfio_handle_read_buffer(
	              handle,
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

	/* Test read buffer with error code on a closed file IO handle
	 */
	read_count = libbfio_handle_read_buffer(
	              closed_handle,
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

/* Tests the libbfio_handle_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_handle_seek_offset(
     libbfio_handle_t *handle )
{
	libbfio_handle_t *closed_handle = NULL;
	libcerror_error_t *error                        = NULL;
	size64_t file_size                              = 0;
	off64_t offset                                  = 0;
	off64_t seek_offset                             = 0;
	int result                                      = 0;

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
	libcerror_error_t *error = NULL;
	int result               = 0;

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
	libcerror_error_t *error = NULL;
	int result               = 0;

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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
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

	result = libbfio_handle_get_number_of_offsets_read(
	          handle,
	          &number_of_offsets_read,
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
	libbfio_handle_t *handle   = NULL;
	int result                 = 0;

	if( argc >= 2 )
	{
		source = argv[ 1 ];
	}
	BFIO_TEST_RUN(
	 "libbfio_handle_initialize",
	 bfio_test_handle_initialize );

	BFIO_TEST_RUN(
	 "libbfio_handle_free",
	 bfio_test_handle_free );

/* TODO fix test

	BFIO_TEST_RUN(
	 "libbfio_handle_clone",
	 bfio_test_handle_clone );
*/

/* TODO add test for libbfio_handle_write_buffer */

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
/* TODO change to set name test */
		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_open",
		 bfio_test_handle_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_open_wide",
		 bfio_test_handle_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* TODO add test for libbfio_handle_open */

/* TODO add test for libbfio_handle_close */

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

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_seek_offset",
		 bfio_test_handle_seek_offset,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_read_buffer",
		 bfio_test_handle_read_buffer,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_exists",
		 bfio_test_handle_exists,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_is_open",
		 bfio_test_handle_is_open,
		 handle );

/* TODO add test for libbfio_handle_get_io_handle */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_access_flags",
		 bfio_test_handle_get_access_flags,
		 handle );

/* TODO add test for libbfio_handle_set_access_flags */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_size",
		 bfio_test_handle_get_size,
		 handle );

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_offset",
		 bfio_test_handle_get_offset,
		 handle );

/* TODO add test for libbfio_handle_set_open_on_demand */

/* TODO add test for libbfio_handle_set_track_offsets_read */

		BFIO_TEST_RUN_WITH_ARGS(
		 "libbfio_handle_get_number_of_offsets_read",
		 bfio_test_handle_get_number_of_offsets_read,
		 handle );

/* TODO add test for libbfio_handle_get_offset_read */

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

