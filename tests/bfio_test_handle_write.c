/*
 * Basic File IO (BFIO) library handle write testing program
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
#include <memory.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include <stdio.h>

#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_libcpath.h"
#include "bfio_test_libcstring.h"

#define BFIO_TEST_BUFFER_SIZE	4096

int bfio_test_handle_write(
     const libcstring_system_character_t *filename,
     size_t data_size,
     libcerror_error_t **error )
{
	libbfio_handle_t *handle = NULL;
	uint8_t *buffer          = NULL;
	static char *function    = "bfio_test_handle_write";
	size_t filename_length   = 0;
	size_t write_size        = 0;
	ssize_t write_count      = 0;
	int result               = 1;
	int sector_iterator      = 0;

	fprintf(
	 stdout,
	 "Testing writing file size: %" PRIzd "\t",
	 data_size );

	filename_length = libcstring_system_string_length(
	                   filename );

	/* Initialization
	 */
	if( libbfio_file_initialize(
	     &handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable create file handle.",
		 function );

		goto on_error;
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_file_set_name_wide(
	     handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#else
	if( libbfio_file_set_name(
	     handle,
	     filename,
	     filename_length,
	     error ) != 1 )
#endif
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable set filename in file handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_open(
	     handle,
	     LIBBFIO_OPEN_WRITE,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file handle.",
		 function );

		goto on_error;
	}
	buffer = (uint8_t *) memory_allocate(
	                      BFIO_TEST_BUFFER_SIZE );

	if( buffer == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable create buffer.",
		 function );

		goto on_error;
	}
	write_size = 512;

	for( sector_iterator = 0;
	     sector_iterator < 26;
	     sector_iterator++ )
	{
		if( memory_set(
		     buffer,
		     (int) 'A' + sector_iterator,
		     write_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable set value in buffer.",
			 function );

			goto on_error;
		}
		write_count = libbfio_handle_write_buffer(
		               handle,
		               buffer,
		               write_size,
		               error );

		if( write_count != (ssize_t) write_size )
		{
			if( write_count != (ssize_t) data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable write buffer of size: %" PRIzd ".",
				 function,
				 write_size );

				goto on_error;
			}
		}
		if( data_size > 0 )
		{
			data_size -= write_count;
		}
	}
	write_size = 3751;

	for( sector_iterator = 0;
	     sector_iterator < 26;
	     sector_iterator++ )
	{
		if( memory_set(
		     buffer,
		     (int) 'a' + sector_iterator,
		     write_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable set value in buffer.",
			 function );

			goto on_error;
		}
		write_count = libbfio_handle_write_buffer(
		               handle,
		               buffer,
		               write_size,
		               error );

		if( write_count != (ssize_t) write_size )
		{
			if( write_count != (ssize_t) data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable write buffer of size: %" PRIzd ".",
				 function,
				 write_size );

				goto on_error;
			}
		}
		if( data_size > 0 )
		{
			data_size -= write_count;
		}
	}
	memory_free(
	 buffer );

	buffer = NULL;

	/* Clean up
	 */
	if( libbfio_handle_close(
	     handle,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file handle.",
		 function );

		goto on_error;
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

on_error:
	if( buffer != NULL )
	{
		memory_free(
		 buffer );
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
	return( -1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	libcstring_system_character_t *filename = NULL;
	libcerror_error_t *error                = NULL;
	size_t filename_size                    = 0;

	if( argc < 2 )
	{
		fprintf(
		 stderr,
		 "Missing test path.\n" );

		return( EXIT_FAILURE );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcpath_path_join_wide(
	     &filename,
	     &filename_size,
	     argv[ 1 ],
	     libcstring_system_string_length(
	      argv[ 1 ] ),
	     _LIBCSTRING_SYSTEM_STRING( "test1" ),
	     5,
	     &error ) != 1 )
#else
	if( libcpath_path_join(
	     &filename,
	     &filename_size,
	     argv[ 1 ],
	     libcstring_system_string_length(
	      argv[ 1 ] ),
	     _LIBCSTRING_SYSTEM_STRING( "test1" ),
	     5,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to create filename.\n" );

		goto on_error;
	}
	if( bfio_test_handle_write(
	     filename,
	     0,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test write.\n" );

		goto on_error;
	}
	memory_free(
	 filename );

	filename = NULL;

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libcpath_path_join_wide(
	     &filename,
	     &filename_size,
	     argv[ 1 ],
	     libcstring_system_string_length(
	      argv[ 1 ] ),
	     _LIBCSTRING_SYSTEM_STRING( "test2" ),
	     5,
	     &error ) != 1 )
#else
	if( libcpath_path_join(
	     &filename,
	     &filename_size,
	     argv[ 1 ],
	     libcstring_system_string_length(
	      argv[ 1 ] ),
	     _LIBCSTRING_SYSTEM_STRING( "test2" ),
	     5,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Unable to create filename.\n" );

		goto on_error;
	}
	if( bfio_test_handle_write(
	     filename,
	     100000,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to test write.\n" );

		goto on_error;
	}
	memory_free(
	 filename );

	filename = NULL;

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
	if( filename != NULL )
	{
		memory_free(
		 filename );
	}
	return( EXIT_FAILURE );
}

