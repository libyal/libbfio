/*
 * Memory range functions
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
#include <types.h>

#include <liberror.h>

#include "libbfio_definitions.h"
#include "libbfio_handle.h"
#include "libbfio_memory_range.h"
#include "libbfio_types.h"

/* Initializes the memory range IO handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_memory_range_io_handle_initialize(
     libbfio_memory_range_io_handle_t **memory_range_io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_memory_range_io_handle_initialize";

	if( memory_range_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid memory range IO handle.",
		 function );

		return( -1 );
	}
	if( *memory_range_io_handle == NULL )
	{
		*memory_range_io_handle = (libbfio_memory_range_io_handle_t *) memory_allocate(
		                                                                sizeof( libbfio_memory_range_io_handle_t ) );

		if( *memory_range_io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create memory range IO handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *memory_range_io_handle,
		     0,
		     sizeof( libbfio_memory_range_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear memory range IO handle.",
			 function );

			memory_free(
			 *memory_range_io_handle );

			*memory_range_io_handle = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Initializes the memory range handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_memory_range_initialize(
      libbfio_handle_t **handle,
      liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *io_handle = NULL;
	static char *function                       = "libbfio_memory_range_initialize";

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
		if( libbfio_memory_range_io_handle_initialize(
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
		     libbfio_memory_range_io_handle_free,
		     libbfio_memory_range_io_handle_clone,
		     libbfio_memory_range_open,
		     libbfio_memory_range_close,
		     libbfio_memory_range_read,
		     libbfio_memory_range_write,
		     libbfio_memory_range_seek_offset,
		     libbfio_memory_range_exists,
		     libbfio_memory_range_is_open,
		     libbfio_memory_range_get_size,
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

/* Frees the memory range IO handle and its attributes
 * Returns 1 if succesful or -1 on error
 */
int libbfio_memory_range_io_handle_free(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_memory_range_io_handle_free";

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
	memory_free(
	 io_handle );

	return( 1 );
}

/* Clones (duplicates) the memory range IO handle and its attributes
 * Returns 1 if succesful or -1 on error
 */
int libbfio_memory_range_io_handle_clone(
     intptr_t **destination_io_handle,
     intptr_t *source_io_handle,
     liberror_error_t **error )
{
	static char *function = "libbfio_memory_range_io_handle_clone";

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
	if( libbfio_memory_range_io_handle_initialize(
	     (libbfio_memory_range_io_handle_t **) destination_io_handle,
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
	( (libbfio_memory_range_io_handle_t *) *destination_io_handle )->range_start  = ( (libbfio_memory_range_io_handle_t *) source_io_handle )->range_start;
	( (libbfio_memory_range_io_handle_t *) *destination_io_handle )->range_size   = ( (libbfio_memory_range_io_handle_t *) source_io_handle )->range_size;
	( (libbfio_memory_range_io_handle_t *) *destination_io_handle )->range_offset = ( (libbfio_memory_range_io_handle_t *) source_io_handle )->range_offset;
	( (libbfio_memory_range_io_handle_t *) *destination_io_handle )->access_flags = ( (libbfio_memory_range_io_handle_t *) source_io_handle )->access_flags;

	return( 1 );
}

/* Retrieves the range for the memory range handle
 * Returns 1 if succesful or -1 on error
 */
int libbfio_memory_range_get(
     libbfio_handle_t *handle,
     uint8_t **range_start,
     size_t *range_size,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle  = NULL;
	libbfio_memory_range_io_handle_t *io_handle = NULL;
	static char *function                       = "libbfio_memory_range_get";

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
	io_handle = (libbfio_memory_range_io_handle_t *) internal_handle->io_handle;

	if( range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range start.",
		 function );

		return( -1 );
	}
	if( range_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range size.",
		 function );

		return( -1 );
	}
	*range_start = io_handle->range_start;
	*range_size  = io_handle->range_size;

	return( 1 );
}

/* Sets the range for the memory range handle
 * Returns 1 if succesful or -1 on error
 */
int libbfio_memory_range_set(
     libbfio_handle_t *handle,
     uint8_t *range_start,
     size_t range_size,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle  = NULL;
	libbfio_memory_range_io_handle_t *io_handle = NULL;
	static char *function                       = "libbfio_memory_range_set";

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
	io_handle = (libbfio_memory_range_io_handle_t *) internal_handle->io_handle;

	if( range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range start.",
		 function );

		return( -1 );
	}
	if( range_size >= (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid range size value exceeds maximum.",
		 function );

		return( -1 );
	}
	io_handle->range_start = range_start;
	io_handle->range_size  = range_size;

	return( 1 );
}

/* Opens the memory range handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_memory_range_open(
     intptr_t *io_handle,
     int flags,
     liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_open";

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing range start.",
		 function );

		return( -1 );
	}
	if( memory_range_io_handle->access_flags != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: IO handle already open.",
		 function );

		return( -1 );
	}
	/* Either read or write flag should be set
	 */
	if( ( ( flags & LIBBFIO_FLAG_READ ) == 0 )
	 && ( ( flags & LIBBFIO_FLAG_WRITE ) == 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags: 0x%02x.",
		 function );

		return( -1 );
	}
	memory_range_io_handle->range_offset = 0;
	memory_range_io_handle->access_flags = flags;

	return( 1 );
}

/* Closes the memory range handle
 * Returns 0 if successful or -1 on error
 */
int libbfio_memory_range_close(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_close";

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - missing range start.",
		 function );

		return( -1 );
	}
	memory_range_io_handle->range_start  = NULL;
	memory_range_io_handle->range_size   = 0;
	memory_range_io_handle->range_offset = 0;
	memory_range_io_handle->access_flags = 0;

	return( 0 );
}

/* Reads a buffer from the memory range handle
 * Returns the amount of bytes read if successful, or -1 on errror
 */
ssize_t libbfio_memory_range_read(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_read";
	size_t read_size                                         = 0;

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid range start.",
		 function );

		return( -1 );
	}
	if( ( memory_range_io_handle->access_flags & LIBBFIO_FLAG_READ ) == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - no read access.",
		 function );

		return( -1 );
	}
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
	if( memory_range_io_handle->range_offset > memory_range_io_handle->range_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: range offset exceeds range size.",
		 function );

		return( -1 );
	}
	/* Check if the end of the data was reached
	 */
	if( memory_range_io_handle->range_offset == memory_range_io_handle->range_size )
	{
		return( 0 );
	}
	/* Check the amount data available
	 */
	read_size = memory_range_io_handle->range_size - memory_range_io_handle->range_offset;

	/* Cannot read more data than available
	 */
	if( read_size > size )
	{
		read_size = size;
	}
	if( memory_copy(
	     buffer,
	     &( memory_range_io_handle->range_start[ memory_range_io_handle->range_offset ] ),
	     size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to read buffer from memory range.",
		 function );

		return( -1 );
	}
	memory_range_io_handle->range_offset += read_size;

	return( (ssize_t) read_size );
}

/* Writes a buffer to the memory range handle
 * Returns the amount of bytes written if successful, or -1 on errror
 */
ssize_t libbfio_memory_range_write(
         intptr_t *io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_write";
	size_t write_size                                        = 0;

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid range start.",
		 function );

		return( -1 );
	}
	if( ( memory_range_io_handle->access_flags & LIBBFIO_FLAG_WRITE ) == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - no write access.",
		 function );

		return( -1 );
	}
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
	if( memory_range_io_handle->range_offset >= memory_range_io_handle->range_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: range offset exceeds range size.",
		 function );

		return( -1 );
	}
	/* Check the amount data available
	 */
	write_size = memory_range_io_handle->range_size - memory_range_io_handle->range_offset;

	/* Cannot write more data than available
	 */
	if( write_size > size )
	{
		write_size = size;
	}
	if( memory_copy(
	     &( memory_range_io_handle->range_start[ memory_range_io_handle->range_offset ] ),
	     buffer,
	     size ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to write buffer to memory range.",
		 function );

		return( -1 );
	}
	memory_range_io_handle->range_offset += write_size;

	return( (ssize_t) write_size );
}

/* Seeks a certain offset within the memory range handle
 * Returns the offset if the seek is successful or -1 on error
 */
off64_t libbfio_memory_range_seek_offset(
         intptr_t *io_handle,
         off64_t offset,
         int whence,
         liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_seek_offset";

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid range start.",
		 function );

		return( -1 );
	}
	if( memory_range_io_handle->access_flags == 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - no access.",
		 function );

		return( -1 );
	}
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
	if( whence == SEEK_CUR )
	{
		offset += memory_range_io_handle->range_offset;
	}
	else if( whence == SEEK_END )
	{
		offset += memory_range_io_handle->range_size;
	}
	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset.",
		 function );

		return( -1 );
	}
	if( offset > (off64_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	memory_range_io_handle->range_offset = (size_t) offset;

	return( offset );
}

/* Function to determine if a memory range exists
 * Return 1 if the memory range exists, 0 if not or -1 on error
 */
int libbfio_memory_range_exists(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_exists";

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		return( 0 );
	}
	return( 1 );
}

/* Check if the memory range is open
 * Returns 1 if open, 0 if not or -1 on error
 */
int libbfio_memory_range_is_open(
     intptr_t *io_handle,
     liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_is_open";

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid range start.",
		 function );

		return( -1 );
	}
	if( memory_range_io_handle->access_flags == 0 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Retrieves the memory range size
 * Returns 1 if successful or -1 on error
 */
int libbfio_memory_range_get_size(
     intptr_t *io_handle,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_memory_range_io_handle_t *memory_range_io_handle = NULL;
	static char *function                                    = "libbfio_memory_range_get_size";

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
	memory_range_io_handle = (libbfio_memory_range_io_handle_t *) io_handle;

	if( memory_range_io_handle->range_start == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid IO handle - invalid range start.",
		 function );

		return( -1 );
	}
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
	*size = (size64_t) memory_range_io_handle->range_size;

	return( 1 );
}

