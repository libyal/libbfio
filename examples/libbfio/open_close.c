/*
 * C application to open and close a file using libbfio
 *
 * Copyright (c) 2011-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libbfio.h>

int main( int argc, char * const argv[] )
{
	libbfio_error_t *error   = NULL;
	libbfio_handle_t *handle = NULL;
	size_t name_length       = 0;

	if( argc <= 1 )
	{
		fprintf(
		 stderr,
		 "Usage: ./open_close filename\n" );

		return( EXIT_FAILURE );
	}
	/* The function will return 1 if successful or -1 on error.
	 * On error the error 'object' is created by the library.
	 *
	 * handle must refer to NULL to create a new libbfio handle 'object'.
	 *
	 * If error is NULL e.g. libbfio_handle_initialize( &handle, NULL )
	 * no error 'object' is created
	 *
	 * The error 'object' can be freed by libbfio_error_free()
	 */
	if( libbfio_file_initialize(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize file handle.\n" );

		goto on_error;
	}
	name_length = strlen(
	               argv[ 1 ] );

	if( libbfio_file_set_name(
	     handle,
	     argv[ 1 ],
	     name_length,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to set file name.\n" );

		goto on_error;
	}
	if( libbfio_handle_open(
	     handle,
	     LIBBFIO_OPEN_READ,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to open handle.\n" );

		goto on_error;
	}
	if( libbfio_handle_close(
	     handle,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Unable to close handle.\n" );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &handle,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free handle.\n" );

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
		libbfio_handle_free(
		 &handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

