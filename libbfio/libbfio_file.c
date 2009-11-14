/*
 * File functions
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>

#if defined( HAVE_ERRNO_H ) || defined( WINAPI )
#include <errno.h>
#endif

#if defined( HAVE_SYS_STAT_H ) || defined( WINAPI )
#include <sys/stat.h>
#endif

#if defined( HAVE_FCNTL_H ) || defined( WINAPI )
#include <fcntl.h>
#endif

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_GLIB_H )
#include <glib.h>
#include <glib/gstdio.h>
#endif

#if defined( WINAPI ) && defined( USE_CRT_FUNCTIONS )
#include <io.h>
#include <share.h>
#endif

#include "libbfio_definitions.h"
#include "libbfio_error_string.h"
#include "libbfio_file.h"
#include "libbfio_handle.h"
#include "libbfio_libuna.h"
#include "libbfio_system_string.h"
#include "libbfio_types.h"


/* Initializes the file IO handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_io_handle_initialize(
     libbfio_file_io_handle_t **file_io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_file_io_handle_initialize";

	if( file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( *file_io_handle == NULL )
	{
		*file_io_handle = (libbfio_file_io_handle_t *) memory_allocate(
		                                                sizeof( libbfio_file_io_handle_t ) );

		if( *file_io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create file IO handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *file_io_handle,
		     0,
		     sizeof( libbfio_file_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file IO handle.",
			 function );

			memory_free(
			 *file_io_handle );

			*file_io_handle = NULL;

			return( -1 );
		}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
		( *file_io_handle )->file_handle     = INVALID_HANDLE_VALUE;
#else
		( *file_io_handle )->file_descriptor = -1;
#endif
	}
	return( 1 );
}

/* Initializes the file handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_initialize(
      libbfio_handle_t **handle,
      liberror_error_t **error )
{
	libbfio_file_io_handle_t *io_handle = NULL;
	static char *function               = "libbfio_file_initialize";

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle == NULL )
	{
		if( libbfio_file_io_handle_initialize(
		     &io_handle,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create handle.",
			 function );

			return( -1 );
		}
		if( libbfio_handle_initialize(
		     handle,
		     (intptr_t *) io_handle,
		     libbfio_file_io_handle_free,
		     libbfio_file_io_handle_clone,
		     libbfio_file_open,
		     libbfio_file_close,
		     libbfio_file_read,
		     libbfio_file_write,
		     libbfio_file_seek_offset,
		     libbfio_file_exists,
		     libbfio_file_is_open,
		     libbfio_file_get_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create handle.",
			 function );

			memory_free(
			 io_handle );

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees the file IO handle and its attributes
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_io_handle_free(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_file_io_handle_free";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( libbfio_file_io_handle_t *) io_handle )->name != NULL )
	{
		memory_free(
		 ( ( libbfio_file_io_handle_t *) io_handle )->name );
	}
	memory_free(
	 io_handle );

	return( 1 );
}

/* Clones (duplicates) the file IO handle and its attributes
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_io_handle_clone(
     intptr_t **destination_io_handle,
     intptr_t *source_io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_file_io_handle_clone";

	if( destination_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination IO handle.",
		 function );

		return( -1 );
	}
	if( *destination_io_handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: destination IO handle already set.",
		 function );

		return( -1 );
	}
	if( source_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source IO handle.",
		 function );

		return( -1 );
	}
	if( libbfio_file_io_handle_initialize(
	     (libbfio_file_io_handle_t **) destination_io_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create handle.",
		 function );

		return( -1 );
	}
	( (libbfio_file_io_handle_t *) *destination_io_handle )->name = (libbfio_system_character_t *) memory_allocate(
	                                                                                                sizeof( libbfio_system_character_t ) * ( (libbfio_file_io_handle_t *) source_io_handle )->name_size );

	if( ( (libbfio_file_io_handle_t *) *destination_io_handle )->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		libbfio_file_io_handle_free(
		 *destination_io_handle,
		 NULL );

		*destination_io_handle = NULL;

		return( -1 );
	}
	if( libbfio_system_string_copy(
	     ( (libbfio_file_io_handle_t *) *destination_io_handle )->name,
	     ( (libbfio_file_io_handle_t *) source_io_handle )->name,
	     ( (libbfio_file_io_handle_t *) source_io_handle )->name_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		libbfio_file_io_handle_free(
		 *destination_io_handle,
		 NULL );

		*destination_io_handle = NULL;

		return( -1 );
	}
	( (libbfio_file_io_handle_t *) *destination_io_handle )->name[ ( (libbfio_file_io_handle_t *) source_io_handle )->name_size - 1 ] = 0;

	( (libbfio_file_io_handle_t *) *destination_io_handle )->name_size = ( (libbfio_file_io_handle_t *) source_io_handle )->name_size;

	return( 1 );
}

/* Retrieves the name size of the file handle
 * The name size includes the end of string character
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_get_name_size(
     libbfio_handle_t *handle,
     size_t *name_size,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	libbfio_file_io_handle_t *io_handle        = NULL;
	static char *function                      = "libbfio_file_get_name_size";

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	io_handle = (libbfio_file_io_handle_t *) internal_handle->io_handle;

	if( io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
	if( name_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name size.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( narrow_string_size_from_libbfio_system_string(
	     io_handle->name,
	     io_handle->name_size,
	     name_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#else
	*name_size = io_handle->name_size;
#endif
	return( 1 );
}

/* Retrieves the name of the file handle
 * The name size should include the end of string character
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_get_name(
     libbfio_handle_t *handle,
     char *name,
     size_t name_size,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	libbfio_file_io_handle_t *io_handle        = NULL;
	static char *function                      = "libbfio_file_get_name";
	size_t narrow_name_size                    = 0;

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	io_handle = (libbfio_file_io_handle_t *) internal_handle->io_handle;

	if( io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( narrow_string_size_from_libbfio_system_string(
	     io_handle->name,
	     io_handle->name_size,
	     &narrow_name_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#else
	narrow_name_size = io_handle->name_size;
#endif
	if( name_size < narrow_name_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: name too small.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( narrow_string_copy_from_libbfio_system_string(
	     name,
	     name_size,
	     io_handle->name,
	     io_handle->name_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
#else
	if( libbfio_system_string_copy(
	     name,
	     io_handle->name,
	     io_handle->name_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
	name[ io_handle->name_size - 1 ] = 0;
#endif
	return( 1 );
}

/* Sets the name for the file handle
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_set_name(
     libbfio_handle_t *handle,
     const char *name,
     size_t name_length,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	libbfio_file_io_handle_t *io_handle        = NULL;
	static char *function                      = "libbfio_file_set_name";

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	io_handle = (libbfio_file_io_handle_t *) internal_handle->io_handle;

	if( name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( name_length == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid name length is zero.",
		 function );

		return( -1 );
	}
	if( name_length >= (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( io_handle->name != NULL )
	{
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
		if( io_handle->file_handle != INVALID_HANDLE_VALUE )
#else
		if( io_handle->file_descriptor != -1 )
#endif
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
			 "%s: name already set: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 io_handle->name );

			return( -1 );
		}
		memory_free(
		  io_handle->name );

		 io_handle->name      = NULL;
		 io_handle->name_size = 0;
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_system_string_size_from_narrow_string(
	     name,
	     name_length + 1,
	     &( io_handle->name_size ),
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#else
	io_handle->name_size = name_length + 1;
#endif
	io_handle->name = (libbfio_system_character_t *) memory_allocate(
	                                                  sizeof( libbfio_system_character_t ) * io_handle->name_size );

	if( io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_system_string_copy_from_narrow_string(
	     io_handle->name,
	     io_handle->name_size,
	     name,
	     name_length + 1,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set name.",
		 function );

		memory_free(
		 io_handle->name );

		io_handle->name      = NULL;
		io_handle->name_size = 0;

		return( -1 );
	}
#else
	if( libbfio_system_string_copy(
	     io_handle->name,
	     name,
	     name_length + 1 ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		memory_free(
		 io_handle->name );

		io_handle->name      = NULL;
		io_handle->name_size = 0;

		return( -1 );
	}
	io_handle->name[ name_length ] = 0;
#endif
	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves the name size of the file handle
 * The name size includes the end of string character
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_get_name_size_wide(
     libbfio_handle_t *handle,
     size_t *name_size,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	libbfio_file_io_handle_t *io_handle        = NULL;
	static char *function                      = "libbfio_file_get_name_size_wide";

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	io_handle = (libbfio_file_io_handle_t *) internal_handle->io_handle;

	if( io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
	if( name_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name size.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	*name_size = io_handle->name_size;
#else
	if( wide_string_size_from_libbfio_system_string(
	     io_handle->name,
	     io_handle->name_size,
	     name_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Retrieves the name of the file handle
 * The name size should include the end of string character
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_get_name_wide(
     libbfio_handle_t *handle,
     wchar_t *name,
     size_t name_size,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	libbfio_file_io_handle_t *io_handle        = NULL;
	static char *function                      = "libbfio_file_get_name_wide";
	size_t wide_name_size                      = 0;

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	io_handle = (libbfio_file_io_handle_t *) internal_handle->io_handle;

	if( io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
	if( name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	wide_name_size = io_handle->name_size;
#else
	if( wide_string_size_from_libbfio_system_string(
	     io_handle->name,
	     io_handle->name_size,
	     &wide_name_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#endif
	if( name_size < wide_name_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: name too small.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_system_string_copy(
	     name,
	     io_handle->name,
	     io_handle->name_size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
	name[ io_handle->name_size - 1 ] = 0;
#else
	if( wide_string_copy_from_libbfio_system_string(
	     name,
	     name_size,
	     io_handle->name,
	     io_handle->name_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set name.",
		 function );

		return( -1 );
	}
#endif
	return( 1 );
}

/* Sets the name for the file handle
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_set_name_wide(
     libbfio_handle_t *handle,
     const wchar_t *name,
     size_t name_length,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	libbfio_file_io_handle_t *io_handle        = NULL;
	static char *function                      = "libbfio_file_set_name_wide";

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) handle;

	if( internal_handle->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - missing IO handle.",
		 function );

		return( -1 );
	}
	io_handle = (libbfio_file_io_handle_t *) internal_handle->io_handle;

	if( name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid name.",
		 function );

		return( -1 );
	}
	if( name_length == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid name length is zero.",
		 function );

		return( -1 );
	}
	if( name_length >= (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name length value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( io_handle->name != NULL )
	{
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
		if( io_handle->file_handle != INVALID_HANDLE_VALUE )
#else
		if( io_handle->file_descriptor != -1 )
#endif
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
			 "%s: name already set: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 io_handle->name );

			return( -1 );
		}
		memory_free(
		  io_handle->name );

		 io_handle->name      = NULL;
		 io_handle->name_size = 0;
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	io_handle->name_size = name_length + 1;
#else

	if( libbfio_system_string_size_from_wide_string(
	     name,
	     name_length + 1,
	     &( io_handle->name_size ),
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine name size.",
		 function );

		return( -1 );
	}
#endif
	io_handle->name = (libbfio_system_character_t *) memory_allocate(
	                                                  sizeof( libbfio_system_character_t ) * io_handle->name_size );

	if( io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create name.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( libbfio_system_string_copy(
	     io_handle->name,
	     name,
	     name_length + 1 ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set name.",
		 function );

		memory_free(
		 io_handle->name );

		io_handle->name      = NULL;
		io_handle->name_size = 0;

		return( -1 );
	}
	io_handle->name[ name_length ] = 0;
#else
	if( libbfio_system_string_copy_from_wide_string(
	     io_handle->name,
	     io_handle->name_size,
	     name,
	     name_length + 1,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set name.",
		 function );

		memory_free(
		 io_handle->name );

		io_handle->name      = NULL;
		io_handle->name_size = 0;

		return( -1 );
	}
#endif
	return( 1 );
}

#endif

/* Opens the file handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_open(
     intptr_t *io_handle,
     int flags,
     liberror_error_t **error )
{
	libbfio_system_character_t error_string[ LIBBFIO_ERROR_STRING_DEFAULT_SIZE ];

	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_open";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                         = 0;
	DWORD file_io_access_flags               = 0;
	DWORD file_io_creation_flags             = 0;
	DWORD file_io_shared_flags               = 0;
#else
#if defined( WINAPI )
	int file_io_shared_flags                 = 0;
	int file_io_persmission_flags            = 0;
#endif
	int file_io_flags                        = 0;
#endif
#if !defined( WINAPI ) && defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	char *narrow_filename                    = NULL;
	size_t narrow_filename_size              = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

	if( file_io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( ( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	 && ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE ) )
	{
		file_io_access_flags   = GENERIC_WRITE | GENERIC_READ;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	{
		file_io_access_flags   = GENERIC_READ;
		file_io_creation_flags = OPEN_EXISTING;
		file_io_shared_flags   = FILE_SHARE_READ;
	}
	else if( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	{
		file_io_access_flags   = GENERIC_WRITE;
		file_io_creation_flags = OPEN_ALWAYS;
		file_io_shared_flags   = 0;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02x.",
		 function,
		 flags );

		return( -1 );
	}
	if( ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	 && ( ( flags & LIBBFIO_FLAG_TRUNCATE ) == LIBBFIO_FLAG_TRUNCATE ) )
	{
		file_io_creation_flags = CREATE_ALWAYS;
	}
	if( file_io_handle->file_handle != INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: file handle already set.",
		 function );

		return( -1 );
	}
	file_io_handle->file_handle = CreateFile(
				       (LPCTSTR) file_io_handle->name,
				       file_io_access_flags,
				       file_io_shared_flags,
				       NULL,
				       file_io_creation_flags,
				       FILE_ATTRIBUTE_NORMAL,
				       NULL );

	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBBFIO_SYSTEM ".",
				 function,
				 file_io_handle->name );

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBBFIO_SYSTEM ".",
				 function,
				 file_io_handle->name );

				break;

			default:
				if( libbfio_error_string_copy_from_error_number(
				     error_string,
				     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
					 function,
					 file_io_handle->name,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
					 function,
					 file_io_handle->name );
				}
				break;
		}
		return( -1 );
	}
#else
	if( ( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	 && ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE ) )
	{
#if defined( WINAPI )
		file_io_flags             = _O_RDWR | _O_CREAT;
		file_io_persmission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags = O_RDWR | O_CREAT;
#endif
#if defined( _MSC_VER )
		file_io_shared_flags = _SH_DENYWR;
#endif
	}
	else if( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	{
#if defined( WINAPI )
		file_io_flags = _O_RDONLY;
#else
		file_io_flags = O_RDONLY;
#endif
#if defined( _MSC_VER )
		file_io_shared_flags = _SH_DENYWR;
#endif
	}
	else if( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	{
#if defined( WINAPI )
		file_io_flags             = _O_WRONLY | _O_CREAT;
		file_io_persmission_flags = _S_IREAD | _S_IWRITE;
#else
		file_io_flags = O_WRONLY | O_CREAT;
#endif
#if defined( _MSC_VER )
		file_io_shared_flags = _SH_DENYRW;
#endif
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	 && ( ( flags & LIBBFIO_FLAG_TRUNCATE ) == LIBBFIO_FLAG_TRUNCATE ) )
	{
#if defined( WINAPI )
		file_io_flags |= _O_TRUNC;
#else
		file_io_flags |= O_TRUNC;
#endif
	}
	if( file_io_handle->file_descriptor != -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: file descriptor already set.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
#if defined( _MSC_VER )
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	if( _wsopen_s(
	     &( file_io_handle->file_descriptor ),
	     (wchar_t *) file_io_handle->name,
	     file_io_flags | _O_BINARY,
	     file_io_shared_flags,
	     file_io_persmission_flags ) != 0 )
#else
	if( _sopen_s(
	     &( file_io_handle->file_descriptor ),
	     (char *) file_io_handle->name,
	     file_io_flags | _O_BINARY,
	     file_io_shared_flags,
	     file_io_persmission_flags ) != 0 )
#endif /* LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER */
#else
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	file_io_handle->file_descriptor = _wsopen(
					   (wchar_t *) file_io_handle->name,
					   file_io_flags | _O_BINARY,
					   file_io_persmission_flags );
#else
	file_io_handle->file_descriptor = _sopen(
					   (char *) file_io_handle->name,
					   file_io_flags | _O_BINARY,
					   file_io_persmission_flags );
#endif /* LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER */

	if( file_io_handle->file_descriptor == -1 )
#endif /* _MSC_VER */
	{
		switch( errno )
		{
			case EACCES:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBBFIO_SYSTEM ".",
				 function,
				 file_io_handle->name );

				break;

			case ENOENT:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBBFIO_SYSTEM ".",
				 function,
				 file_io_handle->name );

				break;

			default:
				if( libbfio_error_string_copy_from_error_number(
				     error_string,
				     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
					 function,
					 file_io_handle->name,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
					 function,
					 file_io_handle->name );
				}
				break;
		}
		return( -1 );
	}
#if defined( _MSC_VER )
	if( file_io_handle->file_descriptor == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: invalid file descriptor: %d returned.",
		 function,
		 file_io_handle->file_descriptor );

		return( -1 );
	}
#endif
#else
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	/* Assumed here that the narrow open function can handle UTF-8
	 */
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_size_from_utf32(
	     (libuna_utf32_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     &narrow_filename_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_size_from_utf16(
	     (libuna_utf16_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     &narrow_filename_size,
	     error ) != 2 )
#else
#error Unsupported size of wchar_t
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character filename size.",
		 function );

		return( -1 );
	}
	narrow_filename = (char *) memory_allocate(
				    sizeof( char ) * narrow_filename_size );

	if( narrow_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character filename.",
		 function );

		return( -1 );
	}
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_copy_from_utf32(
	     (libuna_utf8_character_t *) narrow_filename,
	     narrow_filename_size,
	     (libuna_utf32_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_copy_from_utf16(
	     (libuna_utf8_character_t *) narrow_filename,
	     narrow_filename_size,
	     (libuna_utf16_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     error ) != 1 )
#else
#error Unsupported size of wchar_t
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character filename.",
		 function );

		memory_free(
		 narrow_filename );

		return( -1 );
	}
#if defined( HAVE_GLIB_H )
	file_io_handle->file_descriptor = g_open(
					   narrow_filename,
					   file_io_flags,
					   0644 );
#else
	file_io_handle->file_descriptor = open(
					   narrow_filename,
					   file_io_flags,
					   0644 );
#endif /* HAVE_GLIB_H */

	memory_free(
	 narrow_filename );
#else
#if defined( HAVE_GLIB_H )
	file_io_handle->file_descriptor = g_open(
					   file_io_handle->name,
					   file_io_flags,
					   0644 );
#else
	file_io_handle->file_descriptor = open(
					   file_io_handle->name,
					   file_io_flags,
					   0644 );
#endif /* HAVE_GLIB_H */
#endif

	if( file_io_handle->file_descriptor == -1 )
	{
		switch( errno )
		{
			case EACCES:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_ACCESS_DENIED,
				 "%s: access denied to file: %" PRIs_LIBBFIO_SYSTEM ".",
				 function,
				 file_io_handle->name );

				break;

			case ENOENT:
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_INVALID_RESOURCE,
				 "%s: no such file: %" PRIs_LIBBFIO_SYSTEM ".",
				 function,
				 file_io_handle->name );

				break;

			default:
				if( libbfio_error_string_copy_from_error_number(
				     error_string,
				     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
					 function,
					 file_io_handle->name,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
					 function,
					 file_io_handle->name );
				}
				break;
		}
		return( -1 );
	}
#endif
#endif
	file_io_handle->access_flags = flags;

	return( 1 );
}

/* Closes the file handle
 * Returns 0 if successful or -1 on error
 */
int libbfio_file_close(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_system_character_t error_string[ LIBBFIO_ERROR_STRING_DEFAULT_SIZE ];

	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_close";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                         = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

	if( file_io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_io_handle->file_descriptor == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file descriptor.",
		 function );

		return( -1 );
	}
#endif
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( CloseHandle(
	     file_io_handle->file_handle ) == 0 )
	{
		error_code = GetLastError();

		if( libbfio_error_string_copy_from_error_number(
		     error_string,
		     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to close file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
			 function,
			 file_io_handle->name,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to close file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );
		}
		return( -1 );
	}
	file_io_handle->file_handle = INVALID_HANDLE_VALUE;
#else
#if defined( WINAPI )
	if( _close(
	     file_io_handle->file_descriptor ) != 0 )
#else
	if( close(
	     file_io_handle->file_descriptor ) != 0 )
#endif
	{
		if( libbfio_error_string_copy_from_error_number(
		     error_string,
		     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to close file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
			 function,
			 file_io_handle->name,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to close file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );
		}
		return( -1 );
	}
	file_io_handle->file_descriptor = -1;
#endif
	file_io_handle->access_flags = 0;

	return( 0 );
}

/* Reads a buffer from the file handle
 * Returns the amount of bytes read if successful, or -1 on errror
 */
ssize_t libbfio_file_read(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_system_character_t error_string[ LIBBFIO_ERROR_STRING_DEFAULT_SIZE ];

	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_read";
	ssize_t read_count                       = 0;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                         = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

	if( file_io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_io_handle->file_descriptor == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file descriptor.",
		 function );

		return( -1 );
	}
#endif
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
#if UINT_MAX < SIZE_MAX
	if( size > (size_t) UINT_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#else
	if( size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( ReadFile(
	     file_io_handle->file_handle,
	     buffer,
	     size,
	     (LPDWORD) &read_count,
	     NULL ) == 0 )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_HANDLE_EOF:
				break;

			default:
				if( libbfio_error_string_copy_from_error_number(
				     error_string,
				     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to read from file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
					 function,
					 file_io_handle->name,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to read from file: %" PRIs_LIBBFIO_SYSTEM ".",
					 function,
					 file_io_handle->name );
				}
				break;
		}
		return( -1 );
	}
	if( read_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: invalid read count: %" PRIzd " returned.",
		 function,
		 read_count );
	}
#else
#if defined( WINAPI )
	read_count = _read(
	              file_io_handle->file_descriptor,
	              (void *) buffer,
	              (unsigned int) size );
#else
	read_count = read(
	              file_io_handle->file_descriptor,
	              (void *) buffer,
	              size );
#endif

	if( read_count < 0 )
	{
		if( libbfio_error_string_copy_from_error_number(
		     error_string,
		     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to read from file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
			 function,
			 file_io_handle->name,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to read from file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );
		}
		return( -1 );
	}
#endif
	return( read_count );
}

/* Writes a buffer to the file handle
 * Returns the amount of bytes written if successful, or -1 on errror
 */
ssize_t libbfio_file_write(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_system_character_t error_string[ LIBBFIO_ERROR_STRING_DEFAULT_SIZE ];

	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_write";
	ssize_t write_count                      = 0;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                         = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

	if( file_io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_io_handle->file_descriptor == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file descriptor.",
		 function );

		return( -1 );
	}
#endif
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
#if defined( WINAPI )
#if UINT_MAX < SIZE_MAX
	if( size > (size_t) UINT_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#else
	if( size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
#endif
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( WriteFile(
	     file_io_handle->file_handle,
	     buffer,
	     size,
	     (LPDWORD) &write_count,
	     NULL ) == 0 )
	{
		error_code = GetLastError();

		if( libbfio_error_string_copy_from_error_number(
		     error_string,
		     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
		     error_code,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
			 function,
			 file_io_handle->name,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );
		}
		return( -1 );
	}
	if( write_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: invalid write count: %" PRIzd " returned.",
		 function,
		 write_count );
	}
#else
#if defined( WINAPI )
	write_count = _write(
	               file_io_handle->file_descriptor,
	               (void *) buffer,
	               (unsigned int) size );
#else
	write_count = write(
	               file_io_handle->file_descriptor,
	               (void *) buffer,
	               size );
#endif

	if( write_count < 0 )
	{
		if( libbfio_error_string_copy_from_error_number(
		     error_string,
		     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
		     errno,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
			 function,
			 file_io_handle->name,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to write to file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );
		}
		return( -1 );
	}
#endif
	return( write_count );
}

#if defined( WINAPI ) && !defined( HAVE_SETFILEPOINTEREX )

/* Cross Windows safe version of SetFilePointerEx
 * Returns TRUE if successful or FALSE on error
 */
BOOL SafeSetFilePointerEx(
      HANDLE file_handle,
      LARGE_INTEGER distance_to_move_large_integer,
      LARGE_INTEGER *new_file_pointer_large_integer,
      DWORD move_method )
{
	FARPROC function                 = NULL;
	HMODULE library_handle           = NULL;
	LONG distance_to_move_lower_long = 0;
	LONG distance_to_move_upper_long = 0;
	DWORD error_number               = 0;
	BOOL result                      = FALSE;

	if( file_handle == NULL )
	{
		return( FALSE );
	}
	if( new_file_pointer_large_integer == NULL )
	{
		return( FALSE );
	}
	library_handle = LoadLibrary(
	                  _LIBBFIO_SYSTEM_STRING( "kernel32.dll" ) );

	if( library_handle == NULL )
	{
		return( FALSE );
	}
	function = GetProcAddress(
		    library_handle,
		    (LPCSTR) "SetFilePointerEx" );

	if( FreeLibrary(
	     library_handle ) != TRUE )
	{
		result = FALSE;
	}
	if( function != NULL )
	{
		result = function(
			  file_handle,
			  distance_to_move_large_integer,
			  new_file_pointer_large_integer,
			  move_method );
	}
	else
	{
		distance_to_move_lower_long = distance_to_move_large_integer.LowPart;
		distance_to_move_upper_long = distance_to_move_large_integer.HighPart;

		distance_to_move_lower_long = SetFilePointer(
					       file_handle,
					       distance_to_move_lower_long,
					       &distance_to_move_upper_long,
					       move_method );

		error_number = GetLastError();

		if( ( distance_to_move_lower_long == (LONG) INVALID_SET_FILE_POINTER )
		 && ( error_number != NO_ERROR ) )
		{
		}
		else
		{
			new_file_pointer_large_integer->HighPart = distance_to_move_upper_long;
			new_file_pointer_large_integer->LowPart  = distance_to_move_lower_long;

			result = TRUE;
		}
	}
	return( result );
}

#endif

/* Seeks a certain offset within the file handle
 * Returns the offset if the seek is successful or -1 on error
 */
off64_t libbfio_file_seek_offset(
         intptr_t *io_handle,
         off64_t offset,
         int whence,
         liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_seek_offset";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	LARGE_INTEGER large_integer_offset       = LIBBFIO_LARGE_INTEGER_ZERO;
	DWORD move_method                        = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

	if( file_io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_io_handle->file_descriptor == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file descriptor.",
		 function );

		return( -1 );
	}
#endif
	if( offset > (off64_t) INT64_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( whence == SEEK_SET )
	{
		move_method = FILE_BEGIN;
	}
	else if( whence == SEEK_CUR )
	{
		move_method = FILE_CURRENT;
	}
	else if( whence == SEEK_END )
	{
		move_method = FILE_END;
	}
	large_integer_offset.LowPart  = (DWORD) ( 0x0ffffffffUL & offset );
	large_integer_offset.HighPart = (LONG) ( offset >> 32 );

#if defined( HAVE_SETFILEPOINTEREX )
	if( SetFilePointerEx(
	     file_io_handle->file_handle,
	     large_integer_offset,
	     &large_integer_offset,
	     move_method ) == 0 )
#else
	if( SafeSetFilePointerEx(
	     file_io_handle->file_handle,
	     large_integer_offset,
	     &large_integer_offset,
	     move_method ) == 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to find offset: %" PRIi64 " in file: %" PRIs_LIBBFIO_SYSTEM ".",
		 function,
		 offset,
		 file_io_handle->name );

		return( -1 );
	}
	offset = ( (off64_t) large_integer_offset.HighPart << 32 ) + large_integer_offset.LowPart;

	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: invalid offset: %" PRIi64 " returned.",
		 function,
		 offset );

		return( -1 );
	}
#else
#if defined( WINAPI )
	offset = _lseeki64(
	          file_io_handle->file_descriptor,
	          offset,
	          whence );
#else
	offset = lseek(
	          file_io_handle->file_descriptor,
	          (off_t) offset,
	          whence );
#endif

	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in file: %" PRIs_LIBBFIO_SYSTEM ".",
		 function,
		 file_io_handle->name );

		return( -1 );
	}
#endif
	return( offset );
}

/* Function to determine if a file exists
 * Return 1 if file exists, 0 if not or -1 on error
 */
int libbfio_file_exists(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_system_character_t error_string[ LIBBFIO_ERROR_STRING_DEFAULT_SIZE ];

	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_exists";
	int result                               = 1;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	DWORD error_code                         = 0;
#endif

#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER ) && !defined( WINAPI )
	char *narrow_filename                    = NULL;
	size_t narrow_filename_size              = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

	if( file_io_handle->name == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
	/* Must use CreateFileW here because filename is a 
	 * wide character string and CreateFile is dependent
	 * on UNICODE directives
	 */
	file_io_handle->file_handle = CreateFileW(
	                               (LPCWSTR) file_io_handle->name,
	                               GENERIC_READ,
	                               FILE_SHARE_READ,
	                               NULL,
	                               OPEN_EXISTING,
	                               FILE_ATTRIBUTE_NORMAL,
	                               NULL );
#else
	/* Must use CreateFileA here because filename is a 
	 * narrow character string and CreateFile is dependent
	 * on UNICODE directives
	 */
	file_io_handle->file_handle = CreateFileA(
	                               (LPCSTR) file_io_handle->name,
	                               GENERIC_READ,
	                               FILE_SHARE_READ,
	                               NULL,
	                               OPEN_EXISTING,
	                               FILE_ATTRIBUTE_NORMAL,
	                               NULL );
#endif

	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		error_code = GetLastError();

		switch( error_code )
		{
			case ERROR_ACCESS_DENIED:
				result = 1;

				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				result = 0;

				break;

			default:
				if( libbfio_error_string_copy_from_error_number(
				     error_string,
				     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
				     error_code,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
					 function,
					 file_io_handle->name,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
					 function,
					 file_io_handle->name );
				}
				result = -1;

				break;
		}
	}
	else if( CloseHandle(
	          file_io_handle->file_handle ) == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file: %s.",
		 function,
		 file_io_handle->name );

		return( -1 );
	}
	file_io_handle->file_handle = INVALID_HANDLE_VALUE;
#else
#if defined( LIBBFIO_HAVE_WIDE_SYSTEM_CHARACTER )
#if defined( _MSC_VER )
	if( _wsopen_s(
	     &( file_io_handle->file_descriptor ),
	     (wchar_t *) file_io_handle->name,
	     _O_RDONLY | _O_BINARY,
	     _SH_DENYWR,
	     0 ) != 0 )
	{
		file_io_handle->file_descriptor = -1;
	}
#elif defined( WINAPI )
	file_io_handle->file_descriptor = _wsopen(
	                                   (wchar_t *) file_io_handle->name,
	                                   _O_RDONLY | _O_BINARY,
	                                   0 );
#else
	/* Assumed here that the narrow open function can handle UTF-8
	 */
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_size_from_utf32(
	     (libuna_utf32_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     &narrow_filename_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_size_from_utf16(
	     (libuna_utf16_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     &narrow_filename_size,
	     error ) != 2 )
#else
#error Unsupported size of wchar_t
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow character filename size.",
		 function );

		return( -1 );
	}
	narrow_filename = (char *) memory_allocate(
	                            sizeof( char ) * narrow_filename_size );

	if( narrow_filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create narrow character filename.",
		 function );

		return( -1 );
	}
#if SIZEOF_WCHAR_T == 4
	if( libuna_utf8_string_copy_from_utf32(
	     (libuna_utf8_character_t *) narrow_filename,
	     narrow_filename_size,
	     (libuna_utf32_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     error ) != 1 )
#elif SIZEOF_WCHAR_T == 2
	if( libuna_utf8_string_copy_from_utf16(
	     (libuna_utf8_character_t *) narrow_filename,
	     narrow_filename_size,
	     (libuna_utf16_character_t *) file_io_handle->name,
	     file_io_handle->name_size,
	     error ) != 1 )
#else
#error Unsupported size of wchar_t
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow character filename.",
		 function );

		memory_free(
		 narrow_filename );

		return( -1 );
	}
	file_io_handle->file_descriptor = open(
	                                   narrow_filename,
	                                   O_RDONLY,
	                                   0644 );

	memory_free(
	 narrow_filename );
#endif
#else
#if defined( _MSC_VER )
	if( _sopen_s(
	     &( file_io_handle->file_descriptor ),
	     (char *) file_io_handle->name,
	     _O_RDONLY | _O_BINARY,
	     _SH_DENYWR,
	     0 ) != 0 )
	{
		file_io_handle->file_descriptor = -1;
	}
#elif defined( WINAPI )
	file_io_handle->file_descriptor = _sopen(
					   (char *) file_io_handle->name,
					   _O_RDONLY | _O_BINARY,
					   0 );
#else
	file_io_handle->file_descriptor = open(
	                                   file_io_handle->name,
	                                   O_RDONLY,
	                                   0644 );
#endif
#endif
	if( file_io_handle->file_descriptor == -1 )
	{
		switch( errno )
		{
			case EACCES:
				result = 1;

				break;

			case ENOENT:
				result = 0;

				break;

			default:
				if( libbfio_error_string_copy_from_error_number(
				     error_string,
				     LIBBFIO_ERROR_STRING_DEFAULT_SIZE,
				     errno,
				     error ) != 1 )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM " with error: %" PRIs_LIBBFIO_SYSTEM "",
					 function,
					 file_io_handle->name,
					 error_string );
				}
				else
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_OPEN_FAILED,
					 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
					 function,
					 file_io_handle->name );
				}
				result = -1;

				break;
		}
	}
#if defined( WINAPI )
	else if( _close(
		  file_io_handle->file_descriptor ) != 0 )
#else
	else if( close(
		  file_io_handle->file_descriptor ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file: %s.",
		 function,
		 file_io_handle->name );

		return( -1 );
	}
	file_io_handle->file_descriptor = -1;	
#endif
	return( result );
}

/* Check if the file is open
 * Returns 1 if open, 0 if not or -1 on error
 */
int libbfio_file_is_open(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_is_open";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		return( 0 );
	}
#else
	if( file_io_handle->file_descriptor == -1 )
	{
		return( 0 );
	}
#endif
	return( 1 );
}

#if defined( WINAPI ) && !defined( HAVE_GETFILESIZEEX )

/* Cross Windows safe version of GetFileSizeEx
 * Returns TRUE if successful or FALSE on error
 */
BOOL SafeGetFileSizeEx(
      HANDLE file_handle,
      LARGE_INTEGER *file_size_large_integer )
{
	FARPROC function            = NULL;
	HMODULE library_handle      = NULL;
	DWORD error_number          = 0;
	DWORD file_size_upper_dword = 0;
	DWORD file_size_lower_dword = 0;
	BOOL result                 = FALSE;

	if( file_handle == NULL )
	{
		return( FALSE );
	}
	if( file_size_large_integer == NULL )
	{
		return( FALSE );
	}
	library_handle = LoadLibrary(
	                  _LIBBFIO_SYSTEM_STRING( "kernel32.dll" ) );

	if( library_handle == NULL )
	{
		return( FALSE );
	}
	function = GetProcAddress(
		    library_handle,
		    (LPCSTR) "GetFileSizeEx" );

	if( FreeLibrary(
	     library_handle ) != TRUE )
	{
		result = FALSE;
	}
	if( function != NULL )
	{
		result = function(
			  file_handle,
			  file_size_large_integer );
	}
	else
	{
		file_size_lower_dword = GetFileSize(
		                         file_handle,
		                         &file_size_upper_dword );

		error_number = GetLastError();

		if( ( file_size_lower_dword == INVALID_FILE_SIZE )
		 && ( error_number != NO_ERROR ) )
		{
		}
		else
		{
			file_size_large_integer->HighPart = file_size_upper_dword;
			file_size_large_integer->LowPart  = file_size_lower_dword;

			result = TRUE;
		}
	}
	return( result );
}

#endif

/* Retrieves the file size
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_get_size(
     intptr_t *io_handle,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_get_size";

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	LARGE_INTEGER large_integer_size         = LIBBFIO_LARGE_INTEGER_ZERO;
#elif defined( _MSC_VER )
	struct __stat64 file_stat;
#elif defined( __BORLANDC__ )
	struct stati64 file_stat;
#else
	struct stat file_stat;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	file_io_handle = (libbfio_file_io_handle_t *) io_handle;

#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
	if( file_io_handle->file_handle == INVALID_HANDLE_VALUE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file handle.",
		 function );

		return( -1 );
	}
#else
	if( file_io_handle->file_descriptor == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid file descriptor.",
		 function );

		return( -1 );
	}
#endif
	if( size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && !defined( USE_CRT_FUNCTIONS )
#if defined( HAVE_GETFILESIZEEX )
	if( GetFileSizeEx(
	     file_io_handle->file_handle,
	     &large_integer_size ) == 0 )
#else
	if( SafeGetFileSizeEx(
	     file_io_handle->file_handle,
	     &large_integer_size ) == 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		return( -1 );
	}
	*size = ( (size64_t) large_integer_size.HighPart << 32 ) + large_integer_size.LowPart;
#else
#if defined( _MSC_VER )
	if( _fstat64(
	     file_io_handle->file_descriptor,
	     &file_stat ) != 0 )
#elif defined( __BORLANDC__ )
	if( _fstati64(
	     file_io_handle->file_descriptor,
	     &file_stat ) != 0 )
#else
	if( fstat(
	     file_io_handle->file_descriptor,
	     &file_stat ) != 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: file stat failed.",
		 function );

		return( -1 );
	}
	*size = (size64_t) file_stat.st_size;
#endif
	return( 1 );
}

