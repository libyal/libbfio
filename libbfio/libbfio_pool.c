/*
 * The internal pool functions
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
#include "libbfio_pool.h"
#include "libbfio_types.h"

/* Initialize the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_initialize(
     libbfio_pool_t **pool,
     int amount_of_handles,
     int maximum_amount_of_open_handles,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_initialize";
	size_t handles_size                    = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( amount_of_handles < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid amount of handles value less than zero.",
		 function );

		return( -1 );
	}
	if( maximum_amount_of_open_handles < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid maximum amount of open handles value less than zero.",
		 function );

		return( -1 );
	}
	if( *pool == NULL )
	{
		internal_pool = (libbfio_internal_pool_t *) memory_allocate(
		                                             sizeof( libbfio_internal_pool_t ) );

		if( internal_pool == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create pool.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_pool,
		     0,
		     sizeof( libbfio_internal_pool_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear pool.",
			 function );

			memory_free(
			 internal_pool );

			return( -1 );
		}
		if( libbfio_list_initialize(
		     &( internal_pool->last_used_list ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create last used list.",
			 function );

			memory_free(
			 internal_pool );

			return( -1 );
		}
		if( amount_of_handles > 0 )
		{
			handles_size = sizeof( libbfio_handle_t * ) * amount_of_handles;

			if( handles_size > (size_t) SSIZE_MAX )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid handles size value exceeds maximum.",
				 function );

				return( -1 );
			}
			internal_pool->handles = (libbfio_handle_t **) memory_allocate(
			                                                handles_size );

			if( internal_pool->handles == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create handles.",
				 function );

				libbfio_list_free(
				 &( internal_pool->last_used_list ),
				 NULL,
				 NULL );
				memory_free(
				 internal_pool );

				return( -1 );
			}
			if( memory_set(
			     internal_pool->handles,
			     0,
			     handles_size ) == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_SET_FAILED,
				 "%s: unable to clear handles.",
				 function );

				memory_free(
				 internal_pool->handles );
				libbfio_list_free(
				 &( internal_pool->last_used_list ),
				 NULL,
				 NULL );
				memory_free(
				 internal_pool );

				return( -1 );
			}
		}
		internal_pool->amount_of_handles              = amount_of_handles;
		internal_pool->maximum_amount_of_open_handles = maximum_amount_of_open_handles;

		*pool = (libbfio_pool_t *) internal_pool;
	}
	return( 1 );
}

/* Frees the pool including elements
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_free(
     libbfio_pool_t **pool,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_free";
	int handle_iterator                    = 0;
	int result                             = 1;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( *pool != NULL )
	{
		internal_pool = (libbfio_internal_pool_t *) *pool;

		if( internal_pool->handles != NULL )
		{
			for( handle_iterator = 0; handle_iterator < internal_pool->amount_of_handles; handle_iterator++ )
			{
				if( ( internal_pool->handles[ handle_iterator ] != NULL )
				 && ( libbfio_handle_free(
				        &( internal_pool->handles[ handle_iterator ] ),
				        error ) != 1 ) )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_IO,
					 LIBERROR_IO_ERROR_CLOSE_FAILED,
					 "%s: unable to free handle: %d.",
					 function,
					 handle_iterator );

					result = -1;
				}
			}
			memory_free(
			 internal_pool->handles );
		}
		if( ( internal_pool->last_used_list != NULL )
		 && ( libbfio_list_free(
		       &( internal_pool->last_used_list ),
		       NULL,
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free last used list.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_pool );

		*pool = NULL;
	}
	return( result );
}

/* Resizes the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_resize(
     libbfio_pool_t *pool,
     int amount_of_handles,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	void *reallocation                     = NULL;
	static char *function                  = "libbfio_pool_resize";
	size_t handles_size                    = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( amount_of_handles <= 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS,
		 "%s: invalid amount of handles value zero or less.",
		 function );

		return( -1 );
	}
	if( internal_pool->amount_of_handles < amount_of_handles )
	{
		handles_size = sizeof( libbfio_handle_t * ) * amount_of_handles;

		if( handles_size > (size_t) SSIZE_MAX )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid handles size value exceeds maximum.",
			 function );

			return( -1 );
		}
		reallocation = memory_reallocate(
				internal_pool->handles,
				handles_size );

		if( reallocation == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to resize handles.",
			 function );

			return( -1 );
		}
		internal_pool->handles = (libbfio_handle_t **) reallocation;

		if( memory_set(
		     &( internal_pool->handles[ internal_pool->amount_of_handles ] ),
		     0,
		     sizeof( libbfio_handle_t * ) * ( amount_of_handles - internal_pool->amount_of_handles ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear handles.",
			 function );

			return( -1 );
		}
		internal_pool->amount_of_handles = amount_of_handles;
	}
	return( 1 );
}

/* Opens the handle
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_open_handle(
     libbfio_internal_pool_t *internal_pool,
     libbfio_handle_t *handle,
     int flags,
     liberror_error_t **error )
{
	static char *function = "libbfio_pool_open_handle";
	int is_open           = 0;

	if( internal_pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( internal_pool->last_used_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing last used list.",
		 function );

		return( -1 );
	}
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
	is_open = libbfio_handle_is_open(
	           handle,
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if handle is open.",
		 function );

		return( -1 );
	}
	else if( is_open == 1 )
	{
		return( 1 );
	}
	if( internal_pool->maximum_amount_of_open_handles != LIBBFIO_POOL_UNLIMITED_AMOUNT_OF_OPEN_HANDLES )
	{
		if( libbfio_pool_add_handle_to_last_used_list(
		     internal_pool,
		     handle,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append handle to last used list.",
			 function );

			return( -1 );
		}
	}
	if( libbfio_handle_open(
	     handle,
	     flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Adds the handle to the last used list
 * Closes the less frequently used handle if necessary
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_add_handle_to_last_used_list(
     libbfio_internal_pool_t *internal_pool,
     libbfio_handle_t *handle,
     liberror_error_t **error )
{
	libbfio_list_element_t *last_used_list_element = NULL;
	static char *function                          = "libbfio_pool_add_handle_to_last_used_list";

	if( internal_pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( internal_pool->last_used_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing last used list.",
		 function );

		return( -1 );
	}
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
	/* Check if there is room in the pool for another open handle
	 */
	if( ( internal_pool->maximum_amount_of_open_handles != LIBBFIO_POOL_UNLIMITED_AMOUNT_OF_OPEN_HANDLES )
	 && ( ( internal_pool->amount_of_open_handles + 1 ) >= internal_pool->maximum_amount_of_open_handles ) )
	{
		last_used_list_element = internal_pool->last_used_list->last;

		if( libbfio_pool_remove_handle_from_last_used_list(
		     internal_pool,
		     last_used_list_element,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to remove a handle from the last used list.",
			 function );

			return( -1 );
		}
		if( libbfio_handle_close(
		     (libbfio_handle_t *) ( last_used_list_element->value ),
		     error ) != 0 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close handle.",
			 function );

			memory_free(
			 last_used_list_element );

			return( -1 );
		}
		/* Make sure the truncate flag is removed from the handle
		 */
		( (libbfio_internal_handle_t *) ( last_used_list_element->value ) )->flags &= ~LIBBFIO_FLAG_TRUNCATE;

		/* The last used list element is reused to contain the new last used entry
		 */
	}
	else
	{
		last_used_list_element = (libbfio_list_element_t *) memory_allocate(
		                                                     sizeof( libbfio_list_element_t ) );

		if( last_used_list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create last used list element.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     last_used_list_element,
		     0,
		     sizeof( libbfio_list_element_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear last used list element.",
			 function );

			memory_free(
			 last_used_list_element );

			return( -1 );
		}
	}
	last_used_list_element->value = (intptr_t *) handle;

	( (libbfio_internal_handle_t *) handle )->pool_last_used_list_element = last_used_list_element;

	if( libbfio_list_prepend_element(
	     internal_pool->last_used_list,
	     last_used_list_element,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to prepend last used list element to list.",
		 function );

		memory_free(
		 last_used_list_element );

		return( -1 );
	}
	return( 1 );
}

/* Removes the handle from the last used list
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_remove_handle_from_last_used_list(
     libbfio_internal_pool_t *internal_pool,
     libbfio_list_element_t *last_used_list_element,
     liberror_error_t **error )
{
	libbfio_internal_handle_t *internal_handle = NULL;
	static char *function                      = "libbfio_pool_remove_handle_from_last_used_list";

	if( internal_pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	if( internal_pool->last_used_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing last used list.",
		 function );

		return( -1 );
	}
	if( last_used_list_element == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid last used list element.",
		 function );

		return( -1 );
	}
	internal_handle = (libbfio_internal_handle_t *) last_used_list_element->value;

	if( internal_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	internal_handle->pool_last_used_list_element = NULL;

	if( libbfio_list_remove_element(
	     internal_pool->last_used_list,
	     last_used_list_element,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
		 "%s: unable to remove last used list element from list.",
		 function );

		memory_free(
		 last_used_list_element );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves a certain handle from the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_get_handle(
     libbfio_pool_t *pool,
     int entry,
     libbfio_handle_t **handle,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_get_handle";

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry value out of range.",
		 function );

		return( -1 );
	}
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
	*handle = internal_pool->handles[ entry ];

	return( 1 );
}

/* Appends a handle to the pool
 * Sets the entry
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_add_handle(
     libbfio_pool_t *pool,
     int *entry,
     libbfio_handle_t *handle,
     int flags,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_add_handle";
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->last_used_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing last used list.",
		 function );

		return( -1 );
	}
	if( entry == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
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
	/* Check if the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           handle,
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if handle is open.",
		 function );

		return( -1 );
	}
	/* Resize the pool if necessary
	 */
	if( ( internal_pool->amount_of_used_handles + 1 ) >= internal_pool->amount_of_handles )
	{
		if( libbfio_pool_resize(
		     pool,
		     internal_pool->amount_of_handles + 1,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_RESIZE_FAILED,
			 "%s: unable to resize pool.",
			 function );

			return( -1 );
		}
	}
	*entry = internal_pool->amount_of_used_handles;

	internal_pool->handles[ *entry ] = handle;

	internal_pool->amount_of_used_handles++;

	if( is_open == 0 )
	{
		/* Set the flags is the handle is not open
		 */
		if( libbfio_handle_set_flags(
		     handle,
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to set flags.",
			 function );

			return( -1 );
		}
	}
	else if( internal_pool->maximum_amount_of_open_handles != LIBBFIO_POOL_UNLIMITED_AMOUNT_OF_OPEN_HANDLES )
	{
		if( libbfio_pool_add_handle_to_last_used_list(
		     internal_pool,
		     handle,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append handle to last used list.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets a certain handle in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_set_handle(
     libbfio_pool_t *pool,
     int entry,
     libbfio_handle_t *handle,
     int flags,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_set_handle";
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->last_used_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing last used list.",
		 function );

		return( -1 );
	}
	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry value out of range.",
		 function );

		return( -1 );
	}
	/* TODO allow to re set handles
	 * make sure all pool references are removed
	 */
	if( internal_pool->handles[ entry ] != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid entry value already set.",
		 function );

		return( -1 );
	}
	/* Check if the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           handle,
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if handle is open.",
		 function );

		return( -1 );
	}
	internal_pool->handles[ entry ] = handle;

	if( is_open == 0 )
	{
		/* Set the flags is the handle is not open
		 */
		if( libbfio_handle_set_flags(
		     handle,
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to set flags.",
			 function );

			return( -1 );
		}
	}
	else if( internal_pool->maximum_amount_of_open_handles != LIBBFIO_POOL_UNLIMITED_AMOUNT_OF_OPEN_HANDLES )
	{
		if( libbfio_pool_add_handle_to_last_used_list(
		     internal_pool,
		     handle,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append handle to last used list.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Opens a handle in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_open(
     libbfio_pool_t *pool,
     int entry,
     int flags,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_open";
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry value out of range.",
		 function );

		return( -1 );
	}
	/* Make sure the handle is not open
	 */
	is_open = libbfio_handle_is_open(
	           internal_pool->handles[ entry ],
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if entry: %d is open.",
		 function,
	         entry );

		return( -1 );
	}
	else if( is_open == 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: entry: %d is already open.",
		 function,
	         entry );

		return( -1 );
	}
	if( libbfio_pool_open_handle(
	     internal_pool,
	     internal_pool->handles[ entry ],
	     flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	return( 1 );
}

/* Reopens a handle in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_reopen(
     libbfio_pool_t *pool,
     int entry,
     int flags,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_reopen";

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_reopen(
	     internal_pool->handles[ entry ],
	     flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to reopen handle for entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	return( 1 );
}

/* Closes a handle in the pool
 * Returns 0 if successful or -1 on error
 */
int libbfio_pool_close(
     libbfio_pool_t *pool,
     int entry,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool         = NULL;
	libbfio_list_element_t *last_used_list_element = NULL;
	static char *function                          = "libbfio_pool_close";

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	if( internal_pool->handles[ entry ] == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handle for entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	if( internal_pool->maximum_amount_of_open_handles != LIBBFIO_POOL_UNLIMITED_AMOUNT_OF_OPEN_HANDLES )
	{
		last_used_list_element = ( (libbfio_internal_handle_t *) internal_pool->handles[ entry ] )->pool_last_used_list_element;

		if( libbfio_pool_remove_handle_from_last_used_list(
		     internal_pool,
		     last_used_list_element,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to remove a handle from the last used list.",
			 function );

			return( -1 );
		}
		memory_free(
		 last_used_list_element );
	}
	if( libbfio_handle_close(
	     internal_pool->handles[ entry ],
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close handle for entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	return( 0 );
}

/* Closes all the files in the pool
 * Returns 0 if successful or -1 on error
 */
int libbfio_pool_close_all(
     libbfio_pool_t *pool,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_close_all";
	int handle_iterator                    = 0;
	int is_open                            = 0;
	int result                             = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	for( handle_iterator = 0; handle_iterator < internal_pool->amount_of_handles; handle_iterator++ )
	{
		if( internal_pool->handles[ handle_iterator ] != NULL )
		{
			/* Make sure the handle is open
			 */
			is_open = libbfio_handle_is_open(
				   internal_pool->handles[ handle_iterator ],
				   error );

			if( is_open == -1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to determine if entry: %d is open.",
				 function,
				 handle_iterator );

				result = -1;
			}
			else if( ( is_open == 1 )
			      && ( libbfio_pool_close(
				    pool,
				    handle_iterator,
				    error ) != 0 ) )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close handle: %d.",
				 function,
				 handle_iterator );

				result = -1;
			}
		}
	}
	return( result );
}

/* Read from a handle in the pool
 * Returns the amount of bytes read or -1 on error
 */
ssize_t libbfio_pool_read(
         libbfio_pool_t *pool,
         int entry,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_read";
	ssize_t read_count                     = 0;
	int flags                              = 0;
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	/* Make sure the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           internal_pool->handles[ entry ],
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if entry: %d is open.",
		 function,
	         entry );

		return( -1 );
	}
	else if( is_open == 0 )
	{
		if( libbfio_handle_get_flags(
		     internal_pool->handles[ entry ],
		     &flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve flags.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_open_handle(
		     internal_pool,
		     internal_pool->handles[ entry ],
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open entry: %d.",
			 function,
			 entry );

			return( -1 );
		}
	}
	read_count = libbfio_handle_read(
	              internal_pool->handles[ entry ],
	              buffer,
	              size,
	              error );

	if( read_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	return( read_count );
}

/* Writes to a handle in the pool
 * Returns the amount of bytes written or -1 on error
 */
ssize_t libbfio_pool_write(
         libbfio_pool_t *pool,
         int entry,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_write";
	ssize_t write_count                    = 0;
	int flags                              = 0;
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	/* Make sure the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           internal_pool->handles[ entry ],
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if entry: %d is open.",
		 function,
	         entry );

		return( -1 );
	}
	else if( is_open == 0 )
	{
		if( libbfio_handle_get_flags(
		     internal_pool->handles[ entry ],
		     &flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve flags.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_open_handle(
		     internal_pool,
		     internal_pool->handles[ entry ],
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open entry: %d.",
			 function,
			 entry );

			return( -1 );
		}
	}
	write_count = libbfio_handle_write(
	               internal_pool->handles[ entry ],
	               buffer,
	               size,
	               error );

	if( write_count < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_WRITE_FAILED,
		 "%s: unable to write to entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	return( write_count );
}

/* Seeks an offset in a handle in the pool
 * Returns the offset if successful or -1 on error
 */
off64_t libbfio_pool_seek_offset(
         libbfio_pool_t *pool,
         int entry,
         off64_t offset,
         int whence,
         liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_seek_offset";
	off64_t seek_offset                    = 0;
	int flags                              = 0;
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	/* Make sure the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           internal_pool->handles[ entry ],
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if entry: %d is open.",
		 function,
	         entry );

		return( -1 );
	}
	else if( is_open == 0 )
	{
		if( libbfio_handle_get_flags(
		     internal_pool->handles[ entry ],
		     &flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve flags.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_open_handle(
		     internal_pool,
		     internal_pool->handles[ entry ],
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open entry: %d.",
			 function,
			 entry );

			return( -1 );
		}
	}
	seek_offset = libbfio_handle_seek_offset(
	               internal_pool->handles[ entry ],
	               offset,
	               whence,
	               error );

	if( seek_offset == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek offset in entry: %d.",
		 function,
		 entry );

		return( -1 );
	}
	return( seek_offset );
}

/* Retrieves the size of  a handle in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_get_size(
     libbfio_pool_t *pool,
     int entry,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_get_size";
	int flags                              = 0;
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	/* Make sure the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           internal_pool->handles[ entry ],
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if entry: %d is open.",
		 function,
	         entry );

		return( -1 );
	}
	else if( is_open == 0 )
	{
		if( libbfio_handle_get_flags(
		     internal_pool->handles[ entry ],
		     &flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve flags.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_open_handle(
		     internal_pool,
		     internal_pool->handles[ entry ],
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open entry: %d.",
			 function,
			 entry );

			return( -1 );
		}
	}
	if( libbfio_handle_get_size(
	     internal_pool->handles[ entry ],
	     size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the current offset in a handle in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_get_offset(
     libbfio_pool_t *pool,
     int entry,
     off64_t *offset,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_get_offset";
	int flags                              = 0;
	int is_open                            = 0;

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( internal_pool->handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid pool - missing handles.",
		 function );

		return( -1 );
	}
	if( ( entry < 0 )
	 || ( entry >= internal_pool->amount_of_handles ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_RANGE,
		 "%s: invalid entry.",
		 function );

		return( -1 );
	}
	/* Make sure the handle is open
	 */
	is_open = libbfio_handle_is_open(
	           internal_pool->handles[ entry ],
	           error );

	if( is_open == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if entry: %d is open.",
		 function,
	         entry );

		return( -1 );
	}
	else if( is_open == 0 )
	{
		if( libbfio_handle_get_flags(
		     internal_pool->handles[ entry ],
		     &flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve flags.",
			 function );

			return( -1 );
		}
		if( libbfio_pool_open_handle(
		     internal_pool,
		     internal_pool->handles[ entry ],
		     flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open entry: %d.",
			 function,
			 entry );

			return( -1 );
		}
	}
	if( libbfio_handle_get_offset(
	     internal_pool->handles[ entry ],
	     offset,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the amount of handles in the pool
 * Returns 1 if successful or -1 on error
 */
int libbfio_pool_get_amount_of_handles(
     libbfio_pool_t *pool,
     int *amount_of_handles,
     liberror_error_t **error )
{
	libbfio_internal_pool_t *internal_pool = NULL;
	static char *function                  = "libbfio_pool_get_amount_of_handles";

	if( pool == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid pool.",
		 function );

		return( -1 );
	}
	internal_pool = (libbfio_internal_pool_t *) pool;

	if( amount_of_handles == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid amount of handles.",
		 function );

		return( -1 );
	}
	*amount_of_handles = internal_pool->amount_of_handles;

	return( 1 );
}

