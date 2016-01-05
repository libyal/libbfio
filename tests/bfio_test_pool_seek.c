/*
 * Basic File IO (BFIO) library pool seek offset testing program
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

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "bfio_test_libcerror.h"
#include "bfio_test_libbfio.h"
#include "bfio_test_libcstring.h"

/* Tests libbfio_pool_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bfio_pool_test_seek_offset(
     libbfio_pool_t *pool,
     int pool_entry,
     off64_t input_offset,
     int input_whence,
     off64_t output_offset )
{
	const char *whence_string = NULL;
	libcerror_error_t *error  = NULL;
	off64_t result_offset     = 0;
	int result                = 0;

	if( pool == NULL )
	{
		return( -1 );
	}
	if( input_whence == SEEK_CUR )
	{
		whence_string = "SEEK_CUR";
	}
	else if( input_whence == SEEK_END )
	{
		whence_string = "SEEK_END";
	}
	else if( input_whence == SEEK_SET )
	{
		whence_string = "SEEK_SET";
	}
	else
	{
		whence_string = "UNKNOWN";
	}
	fprintf(
	 stdout,
	 "Testing seek of offset: %" PRIi64 " and whence: %s\t",
	 input_offset,
	 whence_string );

	result_offset = libbfio_pool_seek_offset(
	                 pool,
	                 pool_entry,
	                 input_offset,
	                 input_whence,
	                 &error );

	if( result_offset == -1 )
	{
		libbfio_error_backtrace_fprint(
		 error,
		 stderr );

		libbfio_error_free(
		 &error );
	}
	if( result_offset == output_offset )
	{
		result = 1;
	}
	if( result != 0 )
	{
		fprintf(
		 stdout,
		 "(PASS)" );
	}
	else
	{
		fprintf(
		 stdout,
		 "(FAIL)" );
	}
	fprintf(
	 stdout,
	 "\n" );

	return( result );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcerror_error_t *error = NULL;
	libbfio_handle_t *handle = NULL;
	libbfio_pool_t *pool     = NULL;
	size64_t data_size       = 0;
	size_t filename_length   = 0;
	int pool_entry           = 0;

	if( argc != 2 )
	{
		fprintf(
		 stderr,
		 "Unsupported number of arguments.\n" );

		return( EXIT_FAILURE );
	}
	filename_length = libcstring_system_string_length(
	                   argv[ 1 ] );

	/* Initialization
	 */
	if( libbfio_file_initialize(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create file handle.\n" );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_file_set_name_wide(
	     handle,
	     argv[ 1 ],
	     filename_length,
	     &error ) != 1 )
#else
	if( libbfio_file_set_name(
	     handle,
	     argv[ 1 ],
	     filename_length,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to set filename in file handle.\n" );

		goto on_error;
	}
	if( libbfio_pool_initialize(
	     &pool,
	     10,
	     5,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to create pool.\n" );

		goto on_error;
	}
	if( libbfio_pool_append_handle(
	     pool,
	     &pool_entry,
	     handle,
	     LIBBFIO_OPEN_READ,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to append file handle to pool.\n" );

		goto on_error;
	}
	handle = NULL;

	if( libbfio_pool_open(
	     pool,
	     pool_entry,
	     LIBBFIO_OPEN_READ,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open pool.\n" );

		goto on_error;
	}
	if( libbfio_pool_get_size(
	     pool,
	     pool_entry,
	     &data_size,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to retrieve data size.\n" );

		goto on_error;
	}
	if( data_size > (size64_t) INT64_MAX )
	{
		fprintf(
		 stderr,
		 "File size exceeds maximum.\n" );

		goto on_error;
	}
	/* Test: SEEK_SET offset: 0
	 * Expected result: 0
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     0,
	     SEEK_SET,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_SET offset: <data_size>
	 * Expected result: <data_size>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     (off64_t) data_size,
	     SEEK_SET,
	     (off64_t) data_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_SET offset: <data_size / 5>
	 * Expected result: <data_size / 5>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     (off64_t) ( data_size / 5 ),
	     SEEK_SET,
	     (off64_t) ( data_size / 5 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_SET offset: <data_size + 987>
	 * Expected result: <data_size + 987>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     (off64_t) ( data_size + 987 ),
	     SEEK_SET,
	     (off64_t) ( data_size + 987 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_SET offset: -987
	 * Expected result: -1
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     -987,
	     SEEK_SET,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_CUR offset: 0
	 * Expected result: <data_size + 987>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     0,
	     SEEK_CUR,
	     (off64_t) ( data_size + 987 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_CUR offset: <-1 * (data_size + 987)>
	 * Expected result: 0
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     -1 * (off64_t) ( data_size + 987 ),
	     SEEK_CUR,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_CUR offset: <data_size / 3>
	 * Expected result: <data_size / 3>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     (off64_t) ( data_size / 3 ),
	     SEEK_CUR,
	     (off64_t) ( data_size / 3 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	if( data_size == 0 )
	{
		/* Test: SEEK_CUR offset: <-2 * (data_size / 3)>
		 * Expected result: 0
		 */
		if( bfio_pool_test_seek_offset(
		     pool,
		     pool_entry,
		     -2 * (off64_t) ( data_size / 3 ),
		     SEEK_CUR,
		     0 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			goto on_error;
		}
	}
	else
	{
		/* Test: SEEK_CUR offset: <-2 * (data_size / 3)>
		 * Expected result: -1
		 */
		if( bfio_pool_test_seek_offset(
		     pool,
		     pool_entry,
		     -2 * (off64_t) ( data_size / 3 ),
		     SEEK_CUR,
		     -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test seek offset.\n" );

			goto on_error;
		}
	}
	/* Test: SEEK_END offset: 0
	 * Expected result: <data_size>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     0,
	     SEEK_END,
	     (off64_t) data_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_END offset: <-1 * data_size>
	 * Expected result: 0
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     -1 * (off64_t) data_size,
	     SEEK_END,
	     0 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_END offset: <-1 * (data_size / 4)>
	 * Expected result: <data_size - (data_size / 4)>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     -1 * (off64_t) ( data_size / 4 ),
	     SEEK_END,
	     (off64_t) data_size - (off64_t) ( data_size / 4 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_END offset: 542
	 * Expected result: <data_size + 542>
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     542,
	     SEEK_END,
	     (off64_t) ( data_size + 542 ) ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: SEEK_END offset: <-1 * (data_size + 542)>
	 * Expected result: -1
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     -1 * (off64_t) ( data_size + 542 ),
	     SEEK_END,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Test: UNKNOWN (88) offset: 0
	 * Expected result: -1
	 */
	if( bfio_pool_test_seek_offset(
	     pool,
	     pool_entry,
	     0,
	     88,
	     -1 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test seek offset.\n" );

		goto on_error;
	}
	/* Clean up
	 */
	if( libbfio_pool_close_all(
	     pool,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close pool.\n" );

		goto on_error;
	}
	if( libbfio_pool_free(
	     &pool,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free pool.\n" );

		goto on_error;
	}
	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libbfio_error_backtrace_fprint(
		 error,
		 stderr );
		libbfio_error_free(
		 &error );
	}
	if( handle != NULL )
	{
		libbfio_handle_close(
		 handle,
		 NULL );
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	if( pool != NULL )
	{
		libbfio_pool_close_all(
		 pool,
		 NULL );
		libbfio_pool_free(
		 &pool,
		 NULL );
	}
	return( EXIT_FAILURE );
}

