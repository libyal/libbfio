/*
 * Basic File IO (BFIO) library handle read testing program
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

#define BFIO_TEST_READ_BUFFER_SIZE	4096

/* Tests libbfio_handle_get_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bfio_test_handle_get_offset(
     libbfio_handle_t *handle,
     off64_t expected_offset,
     libcerror_error_t **error )
{
	static char *function = "bfio_test_handle_get_offset";
	off64_t result_offset = 0;

	if( expected_offset != -1 )
	{
		if( libbfio_handle_get_offset(
		     handle,
		     &result_offset,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset.",
			 function );

			return( -1 );
		}
		if( result_offset != expected_offset )
		{
			fprintf(
			 stderr,
			 "%s: unexpected result offset: %" PRIi64 "\n",
			 function,
			 result_offset );

			return( 0 );
		}
	}
	return( 1 );
}

/* Tests libbfio_handle_seek_offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bfio_test_handle_seek_offset(
     libbfio_handle_t *handle,
     off64_t input_offset,
     int input_whence,
     off64_t expected_offset )
{
	libcerror_error_t *error = NULL;
	off64_t result_offset    = 0;
	int result               = 0;

	if( handle == NULL )
	{
		return( -1 );
	}
	result_offset = libbfio_handle_seek_offset(
	                 handle,
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
	if( result_offset == -1 )
	{
		libbfio_error_backtrace_fprint(
		 error,
		 stderr );

		libbfio_error_free(
		 &error );
	}
	if( result_offset != expected_offset )
	{
		fprintf(
		 stderr,
		 "Unexpected result offset: %" PRIi64 "\n",
		 result_offset );
	}
	else
	{
		result = 1;
	}
	return( result );
}

/* Tests libbfio_handle_read_buffer
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bfio_test_handle_read_buffer(
     libbfio_handle_t *handle,
     size64_t input_size,
     size64_t expected_size )
{
	uint8_t buffer[ BFIO_TEST_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	size64_t remaining_size  = 0;
	size64_t result_size     = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	int result               = 0;

	if( handle == NULL )
	{
		return( -1 );
	}
	remaining_size = input_size;

	while( remaining_size > 0 )
	{
		read_size = BFIO_TEST_READ_BUFFER_SIZE;

		if( remaining_size < (size64_t) read_size )
		{
			read_size = (size_t) remaining_size;
		}
		read_count = libbfio_handle_read_buffer(
			      handle,
			      buffer,
			      read_size,
			      &error );

		if( read_count < 0 )
		{
			libbfio_error_backtrace_fprint(
			 error,
			 stderr );

			libbfio_error_free(
			 &error );

			break;
		}
		remaining_size -= (size64_t) read_count;
		result_size    += (size64_t) read_count;

		if( read_count != (ssize_t) read_size )
		{
			break;
		}
	}
	if( expected_size == result_size )
	{
		result = 1;
	}
	else
	{
		fprintf(
		 stderr,
		 "Unexpected read count: %" PRIu64 "\n",
		 result_size );
	}
	return( result );
}

/* Tests reading data at a specific offset
 * Returns 1 if successful, 0 if not or -1 on error
 */
int bfio_test_handle_read(
     libbfio_handle_t *handle,
     off64_t input_offset,
     int input_whence,
     size64_t input_size,
     off64_t expected_offset,
     size64_t expected_size )
{
	libcerror_error_t *error  = NULL;
	const char *whence_string = NULL;
	int result                = 0;

	if( handle == NULL )
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
	 "Testing reading range with offset: %" PRIi64 ", whence: %s and size: %" PRIu64 "\t",
	 input_offset,
	 whence_string,
	 input_size );

	result = bfio_test_handle_seek_offset(
	          handle,
	          input_offset,
	          input_whence,
	          expected_offset );

	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = bfio_test_handle_read_buffer(
				  handle,
				  input_size,
				  expected_size );
		}
	}
	if( result == 1 )
	{
		if( input_offset >= 0 )
		{
			result = bfio_test_handle_get_offset(
			          handle,
			          input_offset + expected_size,
			          &error );
		}
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

	if( result == -1 )
	{
		libcerror_error_backtrace_fprint(
		 error,
		 stdout );

		libcerror_error_free(
		 &error );
	}
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
	size64_t data_size       = 0;
	size_t filename_length   = 0;

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
	if( libbfio_handle_open(
	     handle,
	     LIBBFIO_OPEN_READ,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open file handle.\n" );

		goto on_error;
	}
	if( libbfio_handle_get_size(
	     handle,
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
		 "Data size exceeds maximum.\n" );

		goto on_error;
	}
	fprintf(
	 stdout,
	 "Data size: %" PRIu64 " bytes\n",
	 data_size );

	/* Case 0: test full read
	 */

	/* Test: offset: 0 size: <data_size>
	 * Expected result: offset: 0 size: <data_size>
	 */
	if( bfio_test_handle_read(
	     handle,
	     0,
	     SEEK_SET,
	     data_size,
	     0,
	     data_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	/* Test: offset: 0 size: <data_size>
	 * Expected result: offset: 0 size: <data_size>
	 */
	if( bfio_test_handle_read(
	     handle,
	     0,
	     SEEK_SET,
	     data_size,
	     0,
	     data_size ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}

	/* Case 1: test random read
	 */

	/* Test: offset: <data_size / 7> size: <data_size / 2>
	 * Expected result: offset: <data_size / 7> size: <data_size / 2>
	 */
	if( bfio_test_handle_read(
	     handle,
	     (off64_t) ( data_size / 7 ),
	     SEEK_SET,
	     data_size / 2,
	     (off64_t) ( data_size / 7 ),
	     data_size / 2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}
	/* Test: offset: <data_size / 7> size: <data_size / 2>
	 * Expected result: offset: <data_size / 7> size: <data_size / 2>
	 */
	if( bfio_test_handle_read(
	     handle,
	     (off64_t) ( data_size / 7 ),
	     SEEK_SET,
	     data_size / 2,
	     (off64_t) ( data_size / 7 ),
	     data_size / 2 ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test read.\n" );

		goto on_error;
	}

	/* Case 3: test read beyond data size
	 */

	if( data_size < 1024 )
	{
		/* Test: offset: <data_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		if( bfio_test_handle_read(
		     handle,
		     (off64_t) ( data_size - 1024 ),
		     SEEK_SET,
		     4096,
		     -1,
		     (size64_t) -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
		/* Test: offset: <data_size - 1024> size: 4096
		 * Expected result: offset: -1 size: <undetermined>
		 */
		if( bfio_test_handle_read(
		     handle,
		     (off64_t) ( data_size - 1024 ),
		     SEEK_SET,
		     4096,
		     -1,
		     (size64_t) -1 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
	}
	else
	{
		/* Test: offset: <data_size - 1024> size: 4096
		 * Expected result: offset: <data_size - 1024> size: 1024
		 */
		if( bfio_test_handle_read(
		     handle,
		     (off64_t) ( data_size - 1024 ),
		     SEEK_SET,
		     4096,
		     (off64_t) ( data_size - 1024 ),
		     1024 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
		/* Test: offset: <data_size - 1024> size: 4096
		 * Expected result: offset: <data_size - 1024> size: 1024
		 */
		if( bfio_test_handle_read(
		     handle,
		     (off64_t) ( data_size - 1024 ),
		     SEEK_SET,
		     4096,
		     (off64_t) ( data_size - 1024 ),
		     1024 ) != 1 )
		{
			fprintf(
			 stderr,
			 "Unable to test read.\n" );

			goto on_error;
		}
	}
	/* Clean up
	 */
	if( libbfio_handle_close(
	     handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close file handle.\n" );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free file handle.\n" );

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
	return( EXIT_FAILURE );
}

