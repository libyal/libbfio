/*
 * Offset list
 *
 * Copyright (c) 2009-2012, Joachim Metz <joachim.metz@gmail.com>
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

#include "libbfio_libcdata.h"
#include "libbfio_libcerror.h"
#include "libbfio_offset_list.h"

/* Creates an offset list value
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_value_initialize(
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_value_initialize";

	if( offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list value.",
		 function );

		return( -1 );
	}
	if( *offset_list_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid offset list value value already set.",
		 function );

		return( -1 );
	}
	*offset_list_value = memory_allocate_structure(
	                      libbfio_offset_list_value_t );

	if( *offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create offset list value.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *offset_list_value,
	     0,
	     sizeof( libbfio_offset_list_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear offset list value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *offset_list_value != NULL )
	{
		memory_free(
		 *offset_list_value );

		*offset_list_value = NULL;
	}
	return( -1 );
}

/* Frees an offset list value
 */
int libbfio_offset_list_value_free(
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_value_free";

	if( offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list value.",
		 function );

		return( -1 );
	}
	if( *offset_list_value != NULL )
	{
		memory_free(
		 *offset_list_value );

		*offset_list_value = NULL;
	}
	return( 1 );
}

/* Clones the offset list value
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_value_clone(
     libbfio_offset_list_value_t **destination_offset_list_value,
     libbfio_offset_list_value_t *source_offset_list_value,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_value_clone";

	if( destination_offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination offset list value.",
		 function );

		return( -1 );
	}
	if( *destination_offset_list_value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination offset list value value already set.",
		 function );

		return( -1 );
	}
	if( source_offset_list_value == NULL )
	{
		*destination_offset_list_value = NULL;

		return( 1 );
	}
	*destination_offset_list_value = memory_allocate_structure(
	                                  libbfio_offset_list_value_t );

	if( *destination_offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create destination offset list value.",
		 function );

		goto on_error;
	}
	if( memory_copy(
	     *destination_offset_list_value,
	     source_offset_list_value,
	     sizeof( libbfio_offset_list_value_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy source to destination offset list value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *destination_offset_list_value != NULL )
	{
		memory_free(
		 *destination_offset_list_value );

		*destination_offset_list_value = NULL;
	}
	return( -1 );
}

/* Creates an offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_initialize(
     libbfio_offset_list_t **offset_list,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_initialize";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( *offset_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid offset list value already set.",
		 function );

		return( -1 );
	}
	*offset_list = memory_allocate_structure(
	                libbfio_offset_list_t );

	if( *offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create offset list.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *offset_list,
	     0,
	     sizeof( libbfio_offset_list_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear offset list.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *offset_list != NULL )
	{
		memory_free(
		 *offset_list );

		*offset_list = NULL;
	}
	return( -1 );
}

/* Frees an offset list including the elements
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_free(
     libbfio_offset_list_t **offset_list,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_free";
	int result            = 1;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( *offset_list != NULL )
	{
		result = libbfio_offset_list_empty(
		          *offset_list,
		          error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to empty offset list.",
			 function );
		}
		memory_free(
		 *offset_list );

		*offset_list = NULL;
	}
	return( result );
}

/* Empties an offset list and frees the elements
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_empty(
     libbfio_offset_list_t *offset_list,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element = NULL;
	libcdata_list_element_t *next_element = NULL;
	static char *function                 = "libbfio_offset_list_empty";
	int element_index                     = 0;
	int number_of_elements                = 0;
	int result                            = 1;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( offset_list->number_of_elements > 0 )
	{
		number_of_elements = offset_list->number_of_elements;

		list_element = offset_list->first_element;

		for( element_index = 0;
		     element_index < number_of_elements;
		     element_index++ )
		{
			if( libcdata_list_element_get_next_element(
			     list_element,
			     &next_element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve next element from list element: %d.",
				 function,
				 element_index );

				return( -1 );
			}
			offset_list->first_element = next_element;

			if( offset_list->last_element == list_element )
			{
				offset_list->last_element = next_element;
			}
			offset_list->number_of_elements -= 1;

			if( next_element != NULL )
			{
				if( libcdata_list_element_set_previous_element(
				     next_element,
				     NULL,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set previous element of list element: %d.",
					 function,
					 element_index + 1 );

					return( -1 );
				}
			}
			if( libcdata_list_element_set_next_element(
			     list_element,
			     NULL,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set next element of list element: %d.",
				 function,
				 element_index );

				return( -1 );
			}
			if( libcdata_list_element_free(
			     &list_element,
			     (int (*)(intptr_t **, libcerror_error_t **)) &libbfio_offset_list_value_free,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free element: %d.",
				 function,
				 element_index );

				result = -1;
			}
			list_element = next_element;
		}
		offset_list->current_element       = NULL;
		offset_list->current_element_index = 0;
	}
	return( result );
}

/* Clones the offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_clone(
     libbfio_offset_list_t **destination_offset_list,
     libbfio_offset_list_t *source_offset_list,
     libcerror_error_t **error )
{
	libcdata_list_element_t *source_list_element   = NULL;
	libbfio_offset_list_value_t *destination_value = NULL;
	libbfio_offset_list_value_t *source_value      = NULL;
	static char *function                          = "libbfio_offset_list_clone";
	int element_index                              = 0;

	if( destination_offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination offset list.",
		 function );

		return( -1 );
	}
	if( *destination_offset_list != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid destination offset list value already set.",
		 function );

		return( -1 );
	}
	if( source_offset_list == NULL )
	{
		*destination_offset_list = NULL;

		return( 1 );
	}
	if( libbfio_offset_list_initialize(
	     destination_offset_list,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create destination offset list.",
		 function );

		goto on_error;
	}
	if( *destination_offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing destination offset list.",
		 function );

		goto on_error;
	}
	source_list_element = source_offset_list->first_element;

	for( element_index = 0;
	     element_index < source_offset_list->number_of_elements;
	     element_index++ )
	{
		if( libcdata_list_element_get_value(
		     source_list_element,
		     (intptr_t **) &source_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from source list element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		if( libbfio_offset_list_value_clone(
		     &destination_value,
		     source_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create destination offset list value: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		if( libbfio_offset_list_append_value(
		     *destination_offset_list,
		     destination_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to set value of destination element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		destination_value = NULL;

		if( libcdata_list_element_get_next_element(
		     source_list_element,
		     &source_list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next element from list element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( destination_value != NULL )
	{
		libbfio_offset_list_value_free(
		 &destination_value,
		 NULL );
	}
	if( *destination_offset_list != NULL )
	{
		libbfio_offset_list_free(
		 destination_offset_list,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the number of elements in the offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_get_number_of_elements(
     libbfio_offset_list_t *offset_list,
     int *number_of_elements,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_get_number_of_elements";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( number_of_elements == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of elements.",
		 function );

		return( -1 );
	}
	*number_of_elements = offset_list->number_of_elements;

	return( 1 );
}

/* Sets the first element in the offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_set_first_element(
     libbfio_offset_list_t *offset_list,
     libcdata_list_element_t *element,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_set_first_element";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( element != NULL )
	{
		if( libcdata_list_element_set_next_element(
		     element,
		     offset_list->first_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set next element of list element.",
			 function );

			return( -1 );
		}
	}
	if( offset_list->first_element != NULL )
	{
		if( libcdata_list_element_set_previous_element(
		     offset_list->first_element,
		     element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set previous element of first element.",
			 function );

			return( -1 );
		}
	}
	offset_list->first_element = element;

	return( 1 );
}

/* Sets the last element in the list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_set_last_element(
     libbfio_offset_list_t *offset_list,
     libcdata_list_element_t *element,
     libcerror_error_t **error )
{
	static char *function = "libcdata_list_set_last_element";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( element != NULL )
	{
		if( libcdata_list_element_set_previous_element(
		     element,
		     offset_list->last_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set previous element of list element.",
			 function );

			return( -1 );
		}
	}
	if( offset_list->last_element != NULL )
	{
		if( libcdata_list_element_set_next_element(
		     offset_list->last_element,
		     element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set next element of last element.",
			 function );

			return( -1 );
		}
	}
	offset_list->last_element = element;

	return( 1 );
}

/* Append a list element to the list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_append_element(
     libbfio_offset_list_t *offset_list,
     libcdata_list_element_t *element,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_append_element";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( element == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid list element.",
		 function );

		return( -1 );
	}
	if( offset_list->first_element == NULL )
	{
		offset_list->first_element = element;
	}
	if( libbfio_offset_list_set_last_element(
	     offset_list,
	     element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set last element.",
		 function );

		return( -1 );
	}
	offset_list->number_of_elements += 1;

	return( 1 );
}

/* Append a value to the list
 * Creates a new list element
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_append_value(
     libbfio_offset_list_t *offset_list,
     libbfio_offset_list_value_t *value,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element = NULL;
	static char *function                 = "libbfio_offset_list_append_value";

	if( libcdata_list_element_initialize(
	     &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create list element.",
		 function );

		goto on_error;
	}
	if( libbfio_offset_list_append_element(
	     offset_list,
	     list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to append element to list.",
		 function );

		goto on_error;
	}
	if( libcdata_list_element_set_value(
	     list_element,
	     (intptr_t *) value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to set value of list element.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( list_element != NULL )
	{
		libcdata_list_element_free(
		 &list_element,
		 NULL,
		 NULL );
	}
	return( -1 );
}

/* Appends a range
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_append_range(
     libbfio_offset_list_t *offset_list,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error )
{
	libcdata_list_element_t *last_element                   = NULL;
	libcdata_list_element_t *list_element                   = NULL;
	libcdata_list_element_t *next_element                   = NULL;
	libcdata_list_element_t *previous_element               = NULL;
	libbfio_offset_list_value_t *next_offset_list_value     = NULL;
	libbfio_offset_list_value_t *offset_list_value          = NULL;
	libbfio_offset_list_value_t *previous_offset_list_value = NULL;
	libbfio_offset_list_value_t *split_offset_list_value    = NULL;
	static char *function                                   = "libbfio_offset_list_append_range";
	off64_t range_last_offset                               = 0;
	int create_element                                      = 0;
	int element_index                                       = 0;
	int merge_next_element_check                            = 0;
	int merge_previous_element_check                        = 0;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( range_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid range offset value less than zero.",
		 function );

		return( -1 );
	}
	if( range_size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid range size value exceeds maximum.",
		 function );

		return( -1 );
	}
	range_last_offset = range_offset + range_size;

	if( range_last_offset < range_offset )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid range last offset value out of bounds.",
		 function );

		goto on_error;
	}
	create_element = 1;

	if( offset_list->number_of_elements > 0 )
	{
		/* Check the last element first, most often the list will be filled linear 
		 */
		list_element  = offset_list->last_element;
		element_index = offset_list->number_of_elements - 1;

		if( libcdata_list_element_get_value(
		     list_element,
		     (intptr_t **) &offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from list element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		if( offset_list_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value element: %d.",
			 function,
			 element_index );

			goto on_error;
		}
		/* Check if the offset range overlaps at the end of the last offset range
		 */
		if( ( range_offset >= offset_list_value->offset )
		 && ( range_offset <= offset_list_value->last_offset ) )
		{
			if( range_last_offset > offset_list_value->last_offset )
			{
				offset_list_value->size       += (size64_t) ( range_last_offset - offset_list_value->last_offset );
				offset_list_value->last_offset = range_last_offset;
			}
			create_element           = 0;
			merge_next_element_check = 1;
		}
		/* Check if the offset range overlaps at the beginning of the last offset range
		 */
		else if( ( range_last_offset >= offset_list_value->offset )
		      && ( range_last_offset <= offset_list_value->last_offset ) )
		{
			if( range_offset < offset_list_value->offset )
			{
				offset_list_value->size  += (size64_t) ( offset_list_value->offset - range_offset );
				offset_list_value->offset = range_offset;
			}
			create_element               = 0;
			merge_previous_element_check = 1;
		}
		/* Check if the offset range overlaps the last offset range entirely
		 */
		else if( ( range_offset < offset_list_value->offset )
		      && ( range_last_offset > offset_list_value->last_offset ) )
		{
			offset_list_value->offset      = range_offset;
			offset_list_value->size        = range_size;
			offset_list_value->last_offset = range_last_offset;

			create_element               = 0;
			merge_previous_element_check = 1;
		}
		/* Check if the offset range is beyond the last range
		 */
		else if( range_last_offset > offset_list_value->last_offset )
		{
			last_element = list_element;
		}
		else if( offset_list->number_of_elements > 1 )
		{
			if( range_last_offset > ( offset_list_value->last_offset / 2 ) )
			{
				if( libcdata_list_element_get_previous_element(
				     list_element,
				     &list_element,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve previous element from list element: %d.",
					 function,
					 element_index );

					goto on_error;
				}
				for( element_index = ( offset_list->number_of_elements - 2 );
				     element_index >= 0;
				     element_index-- )
				{
					if( libcdata_list_element_get_value(
					     list_element,
					     (intptr_t **) &offset_list_value,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve value from list element: %d.",
						 function,
						 element_index );

						goto on_error;
					}
					if( offset_list_value == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: missing offset list value element: %d.",
						 function,
						 element_index );

						goto on_error;
					}
					/* Check if the offset range overlaps at the end of an existing offset range
					 */
					if( ( range_offset >= offset_list_value->offset )
					 && ( range_offset <= offset_list_value->last_offset ) )
					{
						if( range_last_offset > offset_list_value->last_offset )
						{
							offset_list_value->size       += (size64_t) ( range_last_offset - offset_list_value->last_offset );
							offset_list_value->last_offset = range_last_offset;
						}
						create_element           = 0;
						merge_next_element_check = 1;
					}
					/* Check if the offset range overlaps at the beginning of an existing offset range
					 */
					else if( ( range_last_offset >= offset_list_value->offset )
					      && ( range_last_offset <= offset_list_value->last_offset ) )
					{
						if( range_offset < offset_list_value->offset )
						{
							offset_list_value->size  += (size64_t) ( offset_list_value->offset - range_offset );
							offset_list_value->offset = range_offset;
						}
						create_element               = 0;
						merge_previous_element_check = 1;
					}
					/* Check if the offset range overlaps an existing offset range entirely
					 */
					else if( ( range_offset < offset_list_value->offset )
					      && ( range_last_offset > offset_list_value->last_offset ) )
					{
						offset_list_value->offset      = range_offset;
						offset_list_value->size        = range_size;
						offset_list_value->last_offset = range_last_offset;

						create_element               = 0;
						merge_next_element_check     = 1;
						merge_previous_element_check = 1;
					}
					if( create_element == 0 )
					{
						break;
					}
					/* Check if the offset range belongs after the exising offset range
					 */
					if( range_last_offset > offset_list_value->last_offset )
					{
						last_element = list_element;

						break;
					}
					last_element = list_element;

					if( libcdata_list_element_get_previous_element(
					     list_element,
					     &list_element,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve previous element from list element: %d.",
						 function,
						 element_index );

						goto on_error;
					}
				}
			}
			else
			{
				list_element = offset_list->first_element;

				for( element_index = 0;
				     element_index < ( offset_list->number_of_elements - 1 );
				     element_index++ )
				{
					if( libcdata_list_element_get_value(
					     list_element,
					     (intptr_t **) &offset_list_value,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve value from list element: %d.",
						 function,
						 element_index );

						goto on_error;
					}
					if( offset_list_value == NULL )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: missing offset list value element: %d.",
						 function,
						 element_index );

						goto on_error;
					}
					/* Check if the offset range overlaps at the end of an existing offset range
					 */
					if( ( range_offset >= offset_list_value->offset )
					 && ( range_offset <= offset_list_value->last_offset ) )
					{
						if( range_last_offset > offset_list_value->last_offset )
						{
							offset_list_value->size       += (size64_t) ( range_last_offset - offset_list_value->last_offset );
							offset_list_value->last_offset = range_last_offset;
						}
						create_element           = 0;
						merge_next_element_check = 1;
					}
					/* Check if the offset range overlaps at the beginning of an existing offset range
					 */
					else if( ( range_last_offset >= offset_list_value->offset )
					      && ( range_last_offset <= offset_list_value->last_offset ) )
					{
						if( range_offset < offset_list_value->offset )
						{
							offset_list_value->size  += (size64_t) ( offset_list_value->offset - range_offset );
							offset_list_value->offset = range_offset;
						}
						create_element               = 0;
						merge_previous_element_check = 1;
					}
					/* Check if the offset range overlaps an existing offset range entirely
					 */
					else if( ( range_offset < offset_list_value->offset )
					      && ( range_last_offset > offset_list_value->last_offset ) )
					{
						offset_list_value->offset      = range_offset;
						offset_list_value->size        = range_size;
						offset_list_value->last_offset = range_last_offset;

						create_element               = 0;
						merge_next_element_check     = 1;
						merge_previous_element_check = 1;
					}
					if( create_element == 0 )
					{
						break;
					}
					/* Check if the offset range belongs before the current offset range
					 */
					if( range_last_offset < offset_list_value->last_offset )
					{
						if( libcdata_list_element_get_previous_element(
						     list_element,
						     &last_element,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
							 "%s: unable to retrieve previous element from list element: %d.",
							 function,
							 element_index );

							goto on_error;
						}
						break;
					}
					last_element = list_element;

					if( libcdata_list_element_get_next_element(
					     list_element,
					     &list_element,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve next element from list element: %d.",
						 function,
						 element_index );

						goto on_error;
					}
				}
			}
		}
		/* Check if the current range should be merged with the previous range
		 */
		if( merge_previous_element_check != 0 )
		{
			if( libcdata_list_element_get_previous_element(
			     list_element,
			     &previous_element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve previous element from list element: %d.",
				 function,
				 element_index );

				goto on_error;
			}
			if( previous_element != NULL )
			{
				if( libcdata_list_element_get_value(
				     previous_element,
				     (intptr_t **) &previous_offset_list_value,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve value from list element: %d.",
					 function,
					 element_index - 1 );

					goto on_error;
				}
				if( previous_offset_list_value == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing offset list value element: %d.",
					 function,
					 element_index - 1 );

					goto on_error;
				}
				if( offset_list_value->offset <= previous_offset_list_value->last_offset )
				{
					/* Merge offset range with previous
					 */
					offset_list_value->size  += offset_list_value->offset - previous_offset_list_value->offset;
					offset_list_value->offset = previous_offset_list_value->offset;

					/* Remove previous list element
					 */
					if( libbfio_offset_list_remove_element(
					     offset_list,
					     previous_element,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
						 "%s: unable to remove list element: %d.",
						 function,
						 element_index - 1 );

						goto on_error;
					}
					if( libcdata_list_element_free(
					     &previous_element,
					     (int (*)(intptr_t **, libcerror_error_t **)) &libbfio_offset_list_value_free,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free list element: %d.",
						 function,
						 element_index - 1 );

						goto on_error;
					}
				}
			}
		}
		/* Check if the current range should be merged with the next range
		 */
		if( merge_next_element_check != 0 )
		{
			if( libcdata_list_element_get_next_element(
			     list_element,
			     &next_element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve next element from list element: %d.",
				 function,
				 element_index );

				goto on_error;
			}
			if( next_element != NULL )
			{
				if( libcdata_list_element_get_value(
				     next_element,
				     (intptr_t **) &next_offset_list_value,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve value from list element: %d.",
					 function,
					 element_index + 1 );

					goto on_error;
				}
				if( next_offset_list_value == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing offset list value element: %d.",
					 function,
					 element_index + 1 );

					goto on_error;
				}
				if( offset_list_value->last_offset >= next_offset_list_value->offset )
				{
					/* Merge offset range with next
					 */
					offset_list_value->size       += next_offset_list_value->last_offset - offset_list_value->last_offset;
					offset_list_value->last_offset = next_offset_list_value->last_offset;

					/* Remove next list element
					 */
					if( libbfio_offset_list_remove_element(
					     offset_list,
					     next_element,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
						 "%s: unable to remove list element: %d.",
						 function,
						 element_index + 1 );

						goto on_error;
					}
					if( libcdata_list_element_free(
					     &next_element,
					     (int (*)(intptr_t **, libcerror_error_t **)) &libbfio_offset_list_value_free,
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free list element: %d.",
						 function,
						 element_index + 1 );

						goto on_error;
					}
				}
			}
		}
	}
	if( create_element != 0 )
	{
		if( libbfio_offset_list_value_initialize(
		     &split_offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create offset list value.",
			 function );

			goto on_error;
		}
		if( split_offset_list_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value.",
			 function );

			goto on_error;
		}
		split_offset_list_value->offset      = range_offset;
		split_offset_list_value->size        = range_size;
		split_offset_list_value->last_offset = range_last_offset;

		if( libbfio_offset_list_insert_value(
		     offset_list,
		     last_element,
		     split_offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert offset list value in offset list.",
			 function );

			goto on_error;
		}
		split_offset_list_value = NULL;
	}
	return( 1 );

on_error:
	if( split_offset_list_value != NULL )
	{
		libbfio_offset_list_value_free(
		 &split_offset_list_value,
		 NULL );
	}
	return( -1 );
}

/* Appends an offset list
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_append_offset_list(
     libbfio_offset_list_t *offset_list,
     libbfio_offset_list_t *source_offset_list,
     libcerror_error_t **error )
{
	libcdata_list_element_t *source_list_element          = NULL;
	libbfio_offset_list_value_t *source_offset_list_value = NULL;
	static char *function                                 = "libbfio_offset_list_append_offset_list";
	int element_index                                     = 0;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( source_offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source offset list.",
		 function );

		return( -1 );
	}
	source_list_element = source_offset_list->first_element;

	for( element_index = 0;
	     element_index < source_offset_list->number_of_elements;
	     element_index++ )
	{
		if( libcdata_list_element_get_value(
		     source_list_element,
		     (intptr_t **) &source_offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from source list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( libbfio_offset_list_append_range(
		     offset_list,
		     source_offset_list_value->offset,
		     source_offset_list_value->size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to append source offset list value: %d to offset list.",
			 function,
			 element_index );

			return( -1 );
		}
		if( libcdata_list_element_get_next_element(
		     source_list_element,
		     &source_list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next element from source list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
	}
	return( 1 );
}

/* Inserts the element in the offset list after the offset list element
 * If offset_list_element is NULL the element is inserted before the first element in the list
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_insert_element(
     libbfio_offset_list_t *offset_list,
     libcdata_list_element_t *offset_list_element,
     libcdata_list_element_t *element,
     libcerror_error_t **error )
{
	libcdata_list_element_t *next_element     = NULL;
	libcdata_list_element_t *previous_element = NULL;
	static char *function                     = "libbfio_offset_list_insert_element";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( libcdata_list_element_get_elements(
	     element,
	     &previous_element,
	     &next_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve previous and next element from list element.",
		 function );

		return( -1 );
	}
	if( ( previous_element != NULL )
	 || ( next_element != NULL ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: list element already part of a list.",
		 function );

		return( -1 );
	}
	if( offset_list->number_of_elements == 0 )
	{
		if( offset_list->first_element != NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid offset list - first element already set.",
			 function );

			return( -1 );
		}
		if( offset_list->last_element != NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid offset list - last element already set.",
			 function );

			return( -1 );
		}
		offset_list->first_element = element;
		offset_list->last_element  = element;
	}
	else
	{
		if( offset_list->first_element == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid offset list - missing first element.",
			 function );

			return( -1 );
		}
		if( offset_list->last_element == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid offset list - missing last element.",
			 function );

			return( -1 );
		}
		if( offset_list_element == NULL )
		{
			if( libbfio_offset_list_set_first_element(
			     offset_list,
			     element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set first element.",
				 function );

				return( -1 );
			}
		}
		else
		{
			if( libcdata_list_element_get_next_element(
			     offset_list_element,
			     &next_element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve next element from offset list element.",
				 function );

				return( -1 );
			}
			if( libcdata_list_element_set_elements(
			     element,
			     offset_list_element,
			     next_element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set previous and next element of list element.",
				 function );

				return( -1 );
			}
			if( offset_list_element == offset_list->last_element )
			{
				offset_list->last_element = element;
			}
			else if( next_element == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid offset list element - missing next element.",
				 function );

				return( -1 );
			}
			else
			{
				if( libcdata_list_element_set_previous_element(
				     next_element,
				     element,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
					 "%s: unable to set previous element of next element.",
					 function );

					return( -1 );
				}
			}
			if( libcdata_list_element_set_next_element(
			     offset_list_element,
			     element,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
				 "%s: unable to set next element of offset list element.",
				 function );

				return( -1 );
			}
		}
	}
	offset_list->number_of_elements += 1;

	return( 1 );
}

/* Inserts the offset list value in the offset list after the offset list element
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_insert_value(
     libbfio_offset_list_t *offset_list,
     libcdata_list_element_t *offset_list_element,
     libbfio_offset_list_value_t *offset_list_value,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element = NULL;
	static char *function                 = "libbfio_offset_list_insert_value";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( libcdata_list_element_initialize(
	     &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create list element.",
		 function );

		goto on_error;
	}
	if( libcdata_list_element_set_value(
	     list_element,
	     (intptr_t *) offset_list_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set value in list element.",
		 function );

		goto on_error;
	}
	if( libbfio_offset_list_insert_element(
	     offset_list,
	     offset_list_element,
	     list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
		 "%s: unable to insert list element in offset list.",
		 function );

		goto on_error;
	}
	list_element = NULL;

	return( 1 );

on_error:
	if( list_element != NULL )
	{
		libcdata_list_element_free(
		 &list_element,
		 NULL,
		 NULL );
	}
	return( -1 );
}

/* Removes an element from the offset list
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_remove_element(
     libbfio_offset_list_t *offset_list,
     libcdata_list_element_t *element,
     libcerror_error_t **error )
{
	libcdata_list_element_t *next_element     = NULL;
	libcdata_list_element_t *previous_element = NULL;
	static char *function                     = "libbfio_offset_list_remove_element";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( libcdata_list_element_get_elements(
	     element,
	     &previous_element,
	     &next_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve previous and next element from list element.",
		 function );

		return( -1 );
	}
	if( element == offset_list->first_element )
	{
		offset_list->first_element = next_element;
	}
	if( element == offset_list->last_element )
	{
		offset_list->last_element = previous_element;
	}
	if( next_element != NULL )
	{
		if( libcdata_list_element_set_previous_element(
		     next_element,
		     previous_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set previous element of next element.",
			 function );

			return( -1 );
		}
	}
	if( previous_element != NULL )
	{
		if( libcdata_list_element_set_next_element(
		     previous_element,
		     next_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set next element of previous element.",
			 function );

			return( -1 );
		}
	}
	if( libcdata_list_element_set_elements(
	     element,
	     NULL,
	     NULL,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set previous and next element of list element.",
		 function );

		return( -1 );
	}
	offset_list->number_of_elements -= 1;

	return( 1 );
}

/* Removes a range
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_remove_range(
     libbfio_offset_list_t *offset_list,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element                = NULL;
	libbfio_offset_list_value_t *offset_list_value       = NULL;
	libbfio_offset_list_value_t *split_offset_list_value = NULL;
	static char *function                                = "libbfio_offset_list_remove_range";
	off64_t range_last_offset                            = 0;
	int result                                           = 0;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( range_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid range offset value less than zero.",
		 function );

		return( -1 );
	}
	if( range_size > (size64_t) INT64_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid range size value exceeds maximum.",
		 function );

		return( -1 );
	}
	range_last_offset = range_offset + range_size;

	if( range_last_offset < range_offset )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid range last offset value out of bounds.",
		 function );

		goto on_error;
	}
	result = libbfio_offset_list_get_element_by_offset(
	          offset_list,
	          range_offset,
	          &list_element,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element for offset: %" PRIi64 ".",
		 function,
		 range_offset );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( libcdata_list_element_get_value(
		     list_element,
		     (intptr_t **) &offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from list element for offset: %" PRIi64 ".",
			 function,
			 range_offset );

			goto on_error;
		}
		if( offset_list_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value element for offset: %" PRIi64 ".",
			 function,
			 range_offset );

			goto on_error;
		}
		if( range_last_offset > offset_list_value->last_offset )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid range last offset value out of bounds.",
			 function );

			goto on_error;
		}
		if( range_offset == offset_list_value->offset )
		{
			if( range_last_offset == offset_list_value->last_offset )
			{
				if( libbfio_offset_list_remove_element(
				     offset_list,
				     list_element,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_REMOVE_FAILED,
					 "%s: unable to remove list element.",
					 function );

					goto on_error;
				}
				if( libcdata_list_element_free(
				     &list_element,
				     (int (*)(intptr_t **, libcerror_error_t **)) &libbfio_offset_list_value_free,
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free list element.",
					 function );

					goto on_error;
				}
			}
			else if( range_last_offset < offset_list_value->last_offset )
			{
				offset_list_value->offset = range_last_offset;
				offset_list_value->size  -= range_size;
			}
		}
		else if( range_last_offset == offset_list_value->last_offset )
		{
			offset_list_value->size       -= range_size;
			offset_list_value->last_offset = range_offset;
		}
		else
		{
			if( libbfio_offset_list_value_initialize(
			     &split_offset_list_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create offset list value.",
				 function );

				goto on_error;
			}
			if( split_offset_list_value == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing offset list value.",
				 function );

				goto on_error;
			}
			split_offset_list_value->offset      = range_last_offset;
			split_offset_list_value->size        = offset_list_value->last_offset - range_last_offset;
			split_offset_list_value->last_offset = offset_list_value->last_offset;

			offset_list_value->size        = range_offset - offset_list_value->offset;
			offset_list_value->last_offset = range_offset;

			if( libbfio_offset_list_insert_value(
			     offset_list,
			     list_element,
			     split_offset_list_value,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_APPEND_FAILED,
				 "%s: unable to insert offset list value in offset list.",
				 function );

				goto on_error;
			}
			split_offset_list_value = NULL;
		}
	}
	return( 1 );

on_error:
	if( split_offset_list_value != NULL )
	{
		libbfio_offset_list_value_free(
		 &split_offset_list_value,
		 NULL );
	}
	return( -1 );
}

/* Retrieves a specific element from the offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_get_element_by_index(
     libbfio_offset_list_t *offset_list,
     int element_index,
     libcdata_list_element_t **element,
     libcerror_error_t **error )
{
	static char *function = "libbfio_offset_list_get_element_by_index";

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( ( element_index < 0 )
	 || ( element_index >= offset_list->number_of_elements ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid element index value out of bounds.",
		 function );

		return( -1 );
	}
	if( element == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element.",
		 function );

		return( -1 );
	}
	if( ( offset_list->current_element != NULL )
	 && ( offset_list->current_element_index != element_index ) )
	{
		if( element_index < offset_list->current_element_index )
		{
			if( ( offset_list->current_element_index - element_index ) < ( offset_list->number_of_elements / 2 ) )
			{
				while( offset_list->current_element_index > element_index )
				{
					if( libcdata_list_element_get_previous_element(
					     offset_list->current_element,
					     &( offset_list->current_element ),
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve previous element from list element: %d.",
						 function,
						 offset_list->current_element_index );

						return( -1 );
					}
					offset_list->current_element_index--;
				}
			}
		}
		else
		{
			if( ( element_index - offset_list->current_element_index ) < ( offset_list->number_of_elements / 2 ) )
			{
				while( offset_list->current_element_index < element_index )
				{
					if( libcdata_list_element_get_next_element(
					     offset_list->current_element,
					     &( offset_list->current_element ),
					     error ) != 1 )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_RUNTIME,
						 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to retrieve next element from list element: %d.",
						 function,
						 offset_list->current_element_index );

						return( -1 );
					}
					offset_list->current_element_index++;
				}
			}
		}
	}
	if( ( offset_list->current_element == NULL )
	 || ( offset_list->current_element_index != element_index ) )
	{
		if( element_index < ( offset_list->number_of_elements / 2 ) )
		{
			offset_list->current_element = offset_list->first_element;

			for( offset_list->current_element_index = 0;
			     offset_list->current_element_index < element_index;
			     offset_list->current_element_index++ )
			{
				if( libcdata_list_element_get_next_element(
				     offset_list->current_element,
				     &( offset_list->current_element ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve next element from list element: %d.",
					 function,
					 offset_list->current_element_index );

					return( -1 );
				}
			}
		}
		else
		{
			offset_list->current_element = offset_list->last_element;

			for( offset_list->current_element_index = ( offset_list->number_of_elements - 1 );
			     offset_list->current_element_index > element_index;
			     offset_list->current_element_index-- )
			{
				if( libcdata_list_element_get_previous_element(
				     offset_list->current_element,
				     &( offset_list->current_element ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
					 "%s: unable to retrieve previous element from list element: %d.",
					 function,
					 offset_list->current_element_index );

					return( -1 );
				}
			}
		}
	}
	*element = offset_list->current_element;

	return( 1 );
}

/* Retrieves the element that contains the offset
 * Returns 1 if successful, 0 if no element was found or -1 on error
 */
int libbfio_offset_list_get_element_by_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     libcdata_list_element_t **element,
     libcerror_error_t **error )
{
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_get_element_by_offset";
	int element_index                              = 0;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid offset value less than zero.",
		 function );

		return( -1 );
	}
	if( element == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid element.",
		 function );

		return( -1 );
	}
/* TODO add optimization using current element */
	*element = offset_list->first_element;

	for( element_index = 0;
	     element_index < offset_list->number_of_elements;
	     element_index++ )
	{
		if( libcdata_list_element_get_value(
		     *element,
		     (intptr_t **) &offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( offset_list_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( ( offset >= offset_list_value->offset )
		 && ( offset < offset_list_value->last_offset ) )
		{
			return( 1 );
		}
		if( libcdata_list_element_get_next_element(
		     *element,
		     element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next element from list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
	}
	return( 0 );
}

/* Retrieves a specific value from the offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_get_value_by_index(
     libbfio_offset_list_t *offset_list,
     int element_index,
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element = NULL;
	static char *function                 = "libbfio_offset_list_get_value_by_index";

	if( offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list value.",
		 function );

		return( -1 );
	}
	if( libbfio_offset_list_get_element_by_index(
	     offset_list,
	     element_index,
	     &list_element,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	if( libcdata_list_element_get_value(
	     list_element,
	     (intptr_t **) offset_list_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value from list element: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	if( offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing offset list value: %d .",
		 function,
		 element_index );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the value that contains the offset
 * Returns 1 if successful, 0 if no value was found or -1 on error
 */
int libbfio_offset_list_get_value_by_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     libbfio_offset_list_value_t **offset_list_value,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element = NULL;
	static char *function                 = "libbfio_offset_list_get_value_by_offset";
	int result                            = 0;

	if( offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list value.",
		 function );

		return( -1 );
	}
	result = libbfio_offset_list_get_element_by_offset(
	          offset_list,
	          offset,
	          &list_element,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element for offset: %" PRIi64 ".",
		 function,
		 offset );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( libcdata_list_element_get_value(
		     list_element,
		     (intptr_t **) offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from list element for offset: %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
		if( *offset_list_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value for offset: %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
	}
	return( result );
}

/* Retrieves a specific range
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_get_range(
     libbfio_offset_list_t *offset_list,
     int element_index,
     off64_t *range_offset,
     size64_t *range_size,
     libcerror_error_t **error )
{
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_get_range";

	if( range_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range offset.",
		 function );

		return( -1 );
	}
	if( range_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range size.",
		 function );

		return( -1 );
	}
	if( libbfio_offset_list_get_value_by_index(
	     offset_list,
	     element_index,
	     &offset_list_value,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset list value: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	if( offset_list_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing offset list value: %d.",
		 function,
		 element_index );

		return( -1 );
	}
	*range_offset = offset_list_value->offset;
	*range_size   = offset_list_value->size;

	return( 1 );
}

/* Retrieves a range for a specific offset
 * Returns 1 if successful, 0 if no range was found or -1 on error
 */
int libbfio_offset_list_get_range_by_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     off64_t *range_offset,
     size64_t *range_size,
     libcerror_error_t **error )
{
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_get_range_by_offset";
	int result                                     = 0;

	if( range_offset == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range offset.",
		 function );

		return( -1 );
	}
	if( range_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid range size.",
		 function );

		return( -1 );
	}
	result = libbfio_offset_list_get_value_by_offset(
	          offset_list,
	          offset,
	          &offset_list_value,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve offset list value for offset: %" PRIi64 ".",
		 function,
		 offset );

		return( -1 );
	}
	else if( result != 0 )
	{
		if( offset_list_value == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value for offset: %" PRIi64 ".",
			 function,
			 offset );

			return( -1 );
		}
		*range_offset = offset_list_value->offset;
		*range_size   = offset_list_value->size;
	}
	return( result );
}

/* Determines if a certain range is present
 * Returns 1 if present, 0 if not present or -1 on error
 */
int libbfio_offset_list_range_is_present(
     libbfio_offset_list_t *offset_list,
     off64_t range_offset,
     size64_t range_size,
     libcerror_error_t **error )
{
	libcdata_list_element_t *list_element          = NULL;
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_range_is_present";
	off64_t range_last_offset                      = 0;
	int element_index                              = 0;

	if( offset_list == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( range_offset < 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid range offset value less than zero.",
		 function );

		return( -1 );
	}
	if( range_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
/* TODO refactor to get by range function ? */
	range_last_offset = range_offset + range_size;

	if( range_last_offset < range_offset )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid range last offset value out of bounds.",
		 function );

		return( -1 );
	}
/* TODO add optimization using current element */
	list_element = offset_list->first_element;

	for( element_index = 0;
	     element_index < offset_list->number_of_elements;
	     element_index++ )
	{
		if( libcdata_list_element_get_value(
		     list_element,
		     (intptr_t **) &offset_list_value,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve value from list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( ( range_offset >= offset_list_value->offset )
		 && ( range_offset < offset_list_value->last_offset ) )
		{
			return( 1 );
		}
/* TODO is this necessary ? */
		if( ( offset_list_value->offset >= range_offset )
		 && ( offset_list_value->offset < range_last_offset ) )
		{
			return( 1 );
		}
		if( libcdata_list_element_get_next_element(
		     list_element,
		     &list_element,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve next element from list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
	}
	return( 0 );
}

