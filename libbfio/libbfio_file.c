/*
 * File functions
 *
 * Copyright (c) 2006-2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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

#include "libbfio_definitions.h"
#include "libbfio_file.h"
#include "libbfio_file_io.h"
#include "libbfio_system_string.h"
#include "libbfio_handle.h"
#include "libbfio_types.h"

/* Initializes the handle
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
		io_handle = (libbfio_file_io_handle_t *) memory_allocate(
		                                          sizeof( libbfio_file_io_handle_t ) );

		if( io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create IO handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     io_handle,
		     0,
		     sizeof( libbfio_file_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear IO handle.\n",
			 function );

			memory_free(
			 io_handle );

			return( -1 );
		}
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
		io_handle->file_handle     = NULL;
#else
		io_handle->file_descriptor = -1;
#endif

		if( libbfio_handle_initialize(
		     handle,
		     (intptr_t *) io_handle,
		     libbfio_file_free_io_handle,
		     libbfio_file_open,
		     libbfio_file_close,
		     libbfio_file_read,
		     libbfio_file_write,
		     libbfio_file_seek_offset,
		     libbfio_file_is_open,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create handle.\n",
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
int libbfio_file_free_io_handle(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_file_free_io_handle";

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

/* Retrieves a name of the handle
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
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
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
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
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

/* Sets a name for the handle
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_set_name(
     libbfio_handle_t *handle,
     const char *name,
     size_t name_size,
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

	if( io_handle->name != NULL )
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
	if( name_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid name size is zero.",
		 function );

		return( -1 );
	}
	if( name_size >= (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
	if( libbfio_system_string_size_from_narrow_string(
	     name,
	     name_size,
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
	io_handle->name_size = name_size;
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
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
	if( libbfio_system_string_copy_from_narrow_string(
	     io_handle->name,
	     io_handle->name_size,
	     name,
	     name_size,
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
	     name_size ) == NULL )
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
	io_handle->name[ name_size - 1 ] = 0;
#endif
	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves a name of the handle
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
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
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
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
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

/* Sets a name for the handle
 * Returns 1 if succesful or -1 on error
 */
int libbfio_file_set_name_wide(
     libbfio_handle_t *handle,
     const wchar_t *name,
     size_t name_size,
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

	if( io_handle->name != NULL )
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
	if( name_size == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid name size is zero.",
		 function );

		return( -1 );
	}
	if( name_size >= (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid name size value exceeds maximum.",
		 function );

		return( -1 );
	}
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
	io_handle->name_size = name_size;
#else

	if( libbfio_system_string_size_from_wide_string(
	     name,
	     name_size,
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
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
	if( libbfio_system_string_copy(
	     io_handle->name,
	     name,
	     name_size ) == NULL )
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
	io_handle->name[ name_size - 1 ] = 0;
#else
	if( libbfio_system_string_copy_from_wide_string(
	     io_handle->name,
	     io_handle->name_size,
	     name,
	     name_size,
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

/* Opens the handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_file_open(
     intptr_t *io_handle,
     int flags,
     liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_open";

#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	DWORD file_io_access_flags               = 0;
	DWORD file_io_creation_flags             = 0;
#else
	int file_io_flags                        = 0;
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
		 "%s: invalid handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( ( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	 && ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE ) )
	{
		file_io_access_flags   = GENERIC_WRITE | GENERIC_READ;
		file_io_creation_flags = OPEN_ALWAYS;
	}
	else if( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	{
		file_io_access_flags   = GENERIC_READ;
		file_io_creation_flags = OPEN_EXISTING;
	}
	else if( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	{
		file_io_access_flags   = GENERIC_WRITE;
		file_io_creation_flags = OPEN_ALWAYS;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.\n",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	 && ( ( flags & LIBBFIO_FLAG_TRUNCATE ) == LIBBFIO_FLAG_TRUNCATE ) )
	{
		file_io_creation_flags = TRUNCATE_EXISTING;
	}

	if( file_io_handle->file_handle == NULL )
	{
		file_io_handle->file_handle = CreateFile(
		                               (LPCTSTR) file_io_handle->name,
		                               file_io_access_flags,
		                               0,
		                               NULL,
		                               file_io_creation_flags,
		                               FILE_ATTRIBUTE_NORMAL,
		                               NULL );

		if( file_io_handle->file_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );

			return( -1 );
		}
	}
#else
	if( ( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	 && ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE ) )
	{
		file_io_flags = LIBBFIO_FILE_IO_FLAG_READ_WRITE
		              | LIBBFIO_FILE_IO_FLAG_CREATE;
	}
	else if( ( flags & LIBBFIO_FLAG_READ ) == LIBBFIO_FLAG_READ )
	{
		file_io_flags = LIBBFIO_FILE_IO_FLAG_READ_ONLY;
	}
	else if( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	{
		file_io_flags = LIBBFIO_FILE_IO_FLAG_WRITE_ONLY
		              | LIBBFIO_FILE_IO_FLAG_CREATE;
	}
	else
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.\n",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBBFIO_FLAG_WRITE ) == LIBBFIO_FLAG_WRITE )
	 && ( ( flags & LIBBFIO_FLAG_TRUNCATE ) == LIBBFIO_FLAG_TRUNCATE ) )
	{
		file_io_flags |= LIBBFIO_FILE_IO_FLAG_TRUNCATE;
	}
	if( file_io_handle->file_descriptor == -1 )
	{
#if defined( LIBBFIO_WIDE_SYSTEM_CHARACTER_TYPE )
		file_io_handle->file_descriptor = libbfio_file_io_open_wide(
		                                   file_io_handle->name,
		                                   file_io_flags,
		                                   error );
#else
		file_io_handle->file_descriptor = libbfio_file_io_open(
		                                   file_io_handle->name,
		                                   file_io_flags,
		                                   error );
#endif

		if( file_io_handle->file_descriptor == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );

			return( -1 );
		}
	}
#endif
	return( 1 );
}

/* Closes the handle
 * Returns 0 if successful or -1 on error
 */
int libbfio_file_close(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_close";

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
		 "%s: invalid handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( file_io_handle->file_handle != NULL )
	{
		if( CloseHandle(
		     file_io_handle->file_handle ) == 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );

			/* TODO use GetLastError to get detailed error information */

			return( -1 );
		}
		file_io_handle->file_handle = NULL;
	}
#else
	if( file_io_handle->file_descriptor != -1 )
	{
		if( libbfio_file_io_close(
		     file_io_handle->file_descriptor ) != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file: %" PRIs_LIBBFIO_SYSTEM ".",
			 function,
			 file_io_handle->name );

			return( -1 );
		}
		file_io_handle->file_descriptor = -1;
	}
#endif
	return( 0 );
}

/* Reads a buffer from the handle
 * Returns the amount of bytes read if successful, or -1 on errror
 */
ssize_t libbfio_file_read(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_read";
	ssize_t read_count                       = 0;

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
		 "%s: invalid handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( file_io_handle->file_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid file handle.",
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
		 "%s: invalid handle - invalid file descriptor.",
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
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( ReadFile(
	     file_io_handle->file_handle,
	     buffer,
	     size,
	     (LPDWORD) &read_count,
	     NULL ) == 0 )
#else
	read_count = libbfio_file_io_read(
	              file_io_handle->file_descriptor,
	              buffer,
	              size );

	if( read_count < 0 )
#endif

	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file: %" PRIs_LIBBFIO_SYSTEM ".",
		 function,
		 file_io_handle->name );
	}
	return( read_count );
}

/* Writes a buffer to the handle
 * Returns the amount of bytes written if successful, or -1 on errror
 */
ssize_t libbfio_file_write(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_file_io_handle_t *file_io_handle = NULL;
	static char *function                    = "libbfio_file_write";
	ssize_t write_count                      = 0;

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
		 "%s: invalid handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( file_io_handle->file_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid file handle.",
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
		 "%s: invalid handle - invalid file descriptor.",
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
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( WriteFile(
	     file_io_handle->file_handle,
	     buffer,
	     size,
	     (LPDWORD) &write_count,
	     NULL ) == 0 )
#else
	write_count = libbfio_file_io_write(
	               file_io_handle->file_descriptor,
	               buffer,
	               size );

	if( write_count < 0 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write to file: %" PRIs_LIBBFIO_SYSTEM ".",
		 function,
		 file_io_handle->name );
	}
	return( write_count );
}

/* Seeks a certain offset within the handle
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

#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	LARGE_INTEGER large_integer_offset	 = { 0, 0 };
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
		 "%s: invalid handle - missing name.",
		 function );

		return( -1 );
	}
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( file_io_handle->file_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle - invalid file handle.",
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
		 "%s: invalid handle - invalid file descriptor.",
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
#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
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
	large_integer_offset.LowPart  = (DWORD) ( 0x0ffffffff & offset );
	large_integer_offset.HighPart = (LONG) ( offset >> 32 );

	if( SetFilePointerEx(
	     file_io_handle->file_handle,
	     large_integer_offset,
	     NULL,
	     move_method ) == 0 )
#else
	if( libbfio_file_io_lseek(
	     file_io_handle->file_descriptor,
	     offset,
	     whence ) == -1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to find offset: %" PRIjd " in file: %" PRIs_LIBBFIO_SYSTEM ".",
		 function,
		 offset,
		 file_io_handle->name );

		return( -1 );
	}
	return( offset );
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

#if defined( WINAPI ) && defined( HAVE_NATIVE_WINAPI_FILE_ACCESS )
	if( file_io_handle->file_handle == NULL )
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

/* Function to determine if a file exists
 * Return 1 if file exists, 0 if not or -1 on error
 */
int libbfio_file_exists(
     const char *filename,
     liberror_error_t **error )
{
	liberror_error_t *local_error = NULL;
	static char *function         = "libbfio_file_exists";
	int file_descriptor           = 0;
	int result                    = 1;

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( error == NULL )
	{
		error = &local_error;
	}
	file_descriptor = libbfio_file_io_open(
	                   filename,
	                   LIBBFIO_FILE_IO_FLAG_READ_ONLY,
	                   error );

	if( file_descriptor == -1 )
	{
		if( liberror_error_matches(
		     *error,
		     LIBERROR_ERROR_DOMAIN_IO,
		     LIBERROR_IO_ERROR_ACCESS_DENIED ) != 0 )
		{
			liberror_error_free(
			 error );

			result = 1;
		}
		else if( liberror_error_matches(
		          *error,
		          LIBERROR_ERROR_DOMAIN_IO,
		          LIBERROR_IO_ERROR_INVALID_RESOURCE ) != 0 )
		{
			liberror_error_free(
			 error );

			result = 0;
		}
		else
		{
			if( error == &local_error )
			{
				liberror_error_free(
				 error );
			}
			result = -1;
		}
	}
	else if( libbfio_file_io_close(
		  file_descriptor ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file: %s.",
		 function,
		 filename );

		return( -1 );
	}
	return( result );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Function to determine if a file exists
 * Return 1 if file exists, 0 if not or -1 on error
 */
int libbfio_file_exists_wide(
     const wchar_t *filename,
     liberror_error_t **error )
{
	liberror_error_t *local_error = NULL;
	static char *function         = "libbfio_file_exists_wide";
	int file_descriptor           = 0;
	int result                    = 1;

	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( error == NULL )
	{
		error = &local_error;
	}
	file_descriptor = libbfio_file_io_open_wide(
	                   filename,
	                   LIBBFIO_FILE_IO_FLAG_READ_ONLY,
	                   error );

	if( file_descriptor == -1 )
	{
		if( liberror_error_matches(
		     *error,
		     LIBERROR_ERROR_DOMAIN_IO,
		     LIBERROR_IO_ERROR_ACCESS_DENIED ) != 0 )
		{
			liberror_error_free(
			 error );

			result = 1;
		}
		else if( liberror_error_matches(
		          *error,
		          LIBERROR_ERROR_DOMAIN_IO,
		          LIBERROR_IO_ERROR_INVALID_RESOURCE ) != 0 )
		{
			liberror_error_free(
			 error );

			result = 0;
		}
		else
		{
			if( error == &local_error )
			{
				liberror_error_free(
				 error );
			}
			result = -1;
		}
	}
	else if( libbfio_file_io_close(
		  file_descriptor ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file: %ls.",
		 function,
		 filename );

		return( -1 );
	}
	return( result );
}

#endif

