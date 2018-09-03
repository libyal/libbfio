/*
 * Library file type test program
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
#include "bfio_test_unused.h"

#include "../libbfio/libbfio_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_file_io_handle_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_io_handle_initialize(
     void )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	libcerror_error_t *error                 = NULL;
	int result                               = 0;

	/* Test regular cases
	 */
	result = libbfio_file_io_handle_initialize(
	          &file_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_file_io_handle_free(
	          &file_io_handle,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_file_io_handle_initialize(
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

	file_io_handle = (libbfio_file_io_handle_t *) 0x12345678UL;

	result = libbfio_file_io_handle_initialize(
	          &file_io_handle,
	          &error );

	file_io_handle = NULL;

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

	/* Test libbfio_file_io_handle_initialize with malloc failing
	 */
	bfio_test_malloc_attempts_before_fail = 0;

	result = libbfio_file_io_handle_initialize(
	          &file_io_handle,
	          &error );

	if( bfio_test_malloc_attempts_before_fail != -1 )
	{
		bfio_test_malloc_attempts_before_fail = -1;

		if( file_io_handle != NULL )
		{
			libbfio_file_io_handle_free(
			 &file_io_handle,
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
		 "file_io_handle",
		 file_io_handle );

		BFIO_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libbfio_file_io_handle_initialize with memset failing
	 */
	bfio_test_memset_attempts_before_fail = 0;

	result = libbfio_file_io_handle_initialize(
	          &file_io_handle,
	          &error );

	if( bfio_test_memset_attempts_before_fail != -1 )
	{
		bfio_test_memset_attempts_before_fail = -1;

		if( file_io_handle != NULL )
		{
			libbfio_file_io_handle_free(
			 &file_io_handle,
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
		 "file_io_handle",
		 file_io_handle );

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
	if( file_io_handle != NULL )
	{
		libbfio_file_io_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libbfio_file_io_handle_free function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_io_handle_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libbfio_file_io_handle_free(
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

/* Tests the libbfio_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_file_initialize(
     void )
{
	libbfio_handle_t *handle = NULL;
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
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
	result = libbfio_file_initialize(
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

	result = libbfio_file_initialize(
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

	/* Test libbfio_file_initialize with malloc failing in libbfio_file_io_handle_initialize
	 */
	bfio_test_malloc_attempts_before_fail = 0;

	result = libbfio_file_initialize(
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
	BFIO_TEST_UNREFERENCED_PARAMETER( argc )
	BFIO_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

	BFIO_TEST_RUN(
	 "libbfio_file_io_handle_initialize",
	 bfio_test_file_io_handle_initialize );

	BFIO_TEST_RUN(
	 "libbfio_file_io_handle_free",
	 bfio_test_file_io_handle_free );

/* TODO add test for libbfio_file_io_handle_clone */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

	BFIO_TEST_RUN(
	 "libbfio_file_initialize",
	 bfio_test_file_initialize );

/* TODO add test for libbfio_file_get_name_size */

/* TODO add test for libbfio_file_get_name */

/* TODO add test for libbfio_file_set_name */

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* TODO add test for libbfio_file_io_handle_get_name_size */

/* TODO add test for libbfio_file_io_handle_get_name */

/* TODO add test for libbfio_file_io_handle_set_name */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* TODO add test for libbfio_file_get_name_size_wide */

/* TODO add test for libbfio_file_get_name_wide */

/* TODO add test for libbfio_file_set_name_wide */

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* TODO add test for libbfio_file_io_handle_get_name_size_wide */

/* TODO add test for libbfio_file_io_handle_get_name_wide */

/* TODO add test for libbfio_file_io_handle_set_name_wide */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* TODO add test for libbfio_file_open */

/* TODO add test for libbfio_file_close */

/* TODO add test for libbfio_file_read */

/* TODO add test for libbfio_file_write */

/* TODO add test for libbfio_file_seek_offset */

/* TODO add test for libbfio_file_exists */

/* TODO add test for libbfio_file_is_open */

/* TODO add test for libbfio_file_get_size */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

