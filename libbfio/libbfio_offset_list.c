/*
 * Offset list
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#include "libbfio_list_type.h"
#include "libbfio_offset_list.h"

/* Frees offset list values
 */
int libbfio_offset_list_values_free(
     intptr_t *values,
     liberror_error_t **error )
{
	if( values != NULL )
	{
		memory_free(
		 values );
	}
	return( 1 );
}

/* Compares two offset list values
 * Returns LIBBFIO_LIST_COMPARE_LESS, LIBBFIO_LIST_COMPARE_EQUAL, LIBBFIO_LIST_COMPARE_GREATER if successful or -1 on error
 */
int libbfio_offset_list_values_compare(
     intptr_t *first,
     intptr_t *second,
     liberror_error_t **error )
{
	static char *function = "libbfio_offset_list_values_compare";

	if( first == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid first offset list value.",
		 function );

		return( -1 );
	}
	if( second == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid second offset list value.",
		 function );

		return( 1 );
	}
	if( ( (libbfio_offset_list_values_t *) first )->offset < ( (libbfio_offset_list_values_t *) second )->offset )
	{
		return( LIBBFIO_LIST_COMPARE_LESS );
	}
	else if( ( (libbfio_offset_list_values_t *) first )->offset > ( (libbfio_offset_list_values_t *) second )->offset )
	{
		return( LIBBFIO_LIST_COMPARE_GREATER );
	}
	return( LIBBFIO_LIST_COMPARE_EQUAL );
}

/* Add an offset
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_add_offset(
     libbfio_list_t *offset_list,
     off64_t offset,
     size64_t size,
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element        = NULL;
	libbfio_list_element_t *remove_element      = NULL;
	libbfio_offset_list_values_t *offset_values = NULL;
	static char *function                      = "libbfio_offset_list_add_offset";
	off64_t last_offset                        = 0;
	off64_t last_range_offset                  = 0;
	int iterator                               = 0;
	int create_list_element                    = 1;
	int merge_next_list_element_check          = 0;
	int merge_previous_list_element_check      = 0;
	int result                                 = 0;

	if( offset_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid offset value is below zero.",
		 function );

		return( -1 );
	}
	/* Check if new range should be merged with an existing range
	 */
	if( offset_list->amount_of_elements > 0 )
	{
		list_element = offset_list->first;

		for( iterator = 0; iterator < offset_list->amount_of_elements; iterator++ )
		{
			if( list_element == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: corruption detected for element: %d.",
				 function,
				 iterator + 1 );

				return( -1 );
			}
			if( list_element->value == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: missing offset list values for element: %d.",
				 function,
				 iterator + 1 );

				return( -1 );
			}
			offset_values = (libbfio_offset_list_values_t *) list_element->value;

			last_offset       = offset + size;
			last_range_offset = offset_values->offset + offset_values->size;

			/* Check if the offset range overlaps at the end of an existing offset range
			 */
			if( ( offset >= offset_values->offset )
			 && ( offset <= last_range_offset ) )
			{
				if( last_offset > last_range_offset )
				{
					offset_values->size += (size64_t) ( last_offset - last_range_offset );
				}
				create_list_element           = 0;
				merge_next_list_element_check = 1;
			}
			/* Check if the offset range overlaps at the beginning of an existing offset range
			 */
			else if( ( last_offset >= offset_values->offset )
			      && ( last_offset <= last_range_offset ) )
			{
				if( offset < offset_values->offset )
				{
					offset_values->offset  = offset;
					offset_values->size   += (size64_t) ( offset_values->offset - offset );
				}
				create_list_element               = 0;
				merge_previous_list_element_check = 1;
			}
			/* Check if the offset range overlaps an existing offset range entirely
			 */
			else if( ( offset < offset_values->offset )
			      && ( last_offset > last_range_offset ) )
			{
				offset_values->offset = offset;
				offset_values->size   = size;

				create_list_element               = 0;
				merge_next_list_element_check     = 1;
				merge_previous_list_element_check = 1;
			}
			if( create_list_element == 0 )
			{
				break;
			}
			list_element = list_element->next;
		}
		/* Check if current range should also be merged with previous
		 */
		if( merge_previous_list_element_check != 0 )
		{
			if( list_element == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid list element.",
				 function );

				return( -1 );
			}
			if( list_element->previous != NULL )
			{
				if( list_element->previous->value == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing offset list values for previous list element.",
					 function );

					return( -1 );
				}
				last_offset = ( (libbfio_offset_list_values_t *) list_element->previous->value )->offset + ( (libbfio_offset_list_values_t *) list_element->previous->value )->size;

				if( last_offset == offset_values->offset )
				{
					/* Merge offset range with previous
					 */
					offset_values->offset  = ( (libbfio_offset_list_values_t *) list_element->previous->value )->offset;
					offset_values->size   += ( (libbfio_offset_list_values_t *) list_element->previous->value )->size;

					/* Remove previous list element
					 */
					remove_element = list_element->previous;

					if( libbfio_list_remove_element(
					     offset_list,
					     remove_element,
					     error ) != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
						 "%s: unable to remove next list element.",
						 function );

						return( -1 );
					}
					memory_free(
					 remove_element->value );
					memory_free(
					 remove_element );
				}
			}
		}
		/* Check if current range should also be merged with next
		 */
		if( merge_next_list_element_check != 0 )
		{
			if( list_element == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: invalid list element.",
				 function );

				return( -1 );
			}
			if( list_element->next != NULL )
			{
				if( list_element->next->value == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing offset list values for next list element.",
					 function );

					return( -1 );
				}
				last_offset = offset_values->offset + offset_values->size;

				if( last_offset == ( (libbfio_offset_list_values_t *) list_element->next->value )->offset )
				{
					/* Merge offset range with next
					 */
					offset_values->size += ( (libbfio_offset_list_values_t *) list_element->next->value )->size;

					/* Remove next list element
					 */
					remove_element = list_element->next;

					if( libbfio_list_remove_element(
					     offset_list,
					     remove_element,
					     error ) != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_REMOVE_FAILED,
						 "%s: unable to remove next list element.",
						 function );

						return( -1 );
					}
					memory_free(
					 remove_element->value );
					memory_free(
					 remove_element );
				}
			}
		}
	}
	if( create_list_element != 0 )
	{
		offset_values = (libbfio_offset_list_values_t *) memory_allocate(
		                                                 sizeof( libbfio_offset_list_values_t ) );

		if( offset_values == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create offset values.",
			 function );

			return( -1 );
		}
		offset_values->offset = offset;
		offset_values->size   = size;

		result = libbfio_list_insert_value(
		          offset_list,
		          (intptr_t *) offset_values,
		          &libbfio_offset_list_values_compare,
		          error );

		if( result != 1 )
		{
			memory_free(
			 offset_values );
		}
		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_APPEND_FAILED,
			 "%s: unable to insert offset values in offset list.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Retrieves a specific offset
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libbfio_offset_list_get_offset(
     libbfio_list_t *offset_list,
     int index,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element = NULL;
	static char *function               = "libbfio_offset_list_get_offset";
	int result                          = 0;

	if( offset_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
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
	result = libbfio_list_get_element(
	          offset_list,
	          index,
	          &list_element,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve list element.",
		 function );

		return( -1 );
	}
	else if( result == 1 )
	{
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: invalid list element.",
			 function );

			return( -1 );
		}
		*offset = ( (libbfio_offset_list_values_t *) list_element->value )->offset;
		*size   = ( (libbfio_offset_list_values_t *) list_element->value )->size;
	}
	return( result );
}

/* Retrieves a specific offset by its value
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libbfio_offset_list_get_offset_by_value(
     libbfio_list_t *offset_list,
     off64_t offset_value,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element        = NULL;
	libbfio_offset_list_values_t *offset_values = NULL;
	static char *function                      = "libbfio_offset_list_get_offset_by_value";
	int iterator                               = 0;

	if( offset_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( offset == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset.",
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
	list_element = offset_list->first;

	for( iterator = 0; iterator < offset_list->amount_of_elements; iterator++ )
	{
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected for element: %d.",
			 function,
			 iterator + 1 );

			return( -1 );
		}
		if( list_element->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list values for element: %d.",
			 function,
			 iterator + 1 );

			return( -1 );
		}
		offset_values = (libbfio_offset_list_values_t *) list_element->value;

		if( ( offset_value >= offset_values->offset )
		 && ( offset_value <= (off64_t) ( offset_values->offset + offset_values->size ) ) )
		{
			*offset = offset_values->offset;
			*size   = offset_values->size;

			return( 1 );
		}
		list_element = list_element->next;
	}
	return( 0 );
}

/* Determines if a certain offset range is present in the list
 * Returns 1 if present, 0 if not present or -1 on error
 */
int libbfio_offset_list_range_is_present(
     libbfio_list_t *offset_list,
     off64_t offset,
     size64_t size,
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element        = NULL;
	libbfio_offset_list_values_t *offset_values = NULL;
	static char *function                      = "libbfio_offset_list_range_is_present";
	off64_t last_offset                        = 0;
	int iterator                               = 0;

	if( offset_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list.",
		 function );

		return( -1 );
	}
	if( offset < 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO,
		 "%s: invalid offset negative value.",
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
	last_offset  = offset + size;
	list_element = offset_list->first;

	for( iterator = 0; iterator < offset_list->amount_of_elements; iterator++ )
	{
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected for element: %d.",
			 function,
			 iterator + 1 );

			return( -1 );
		}
		if( list_element->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list values for element: %d.",
			 function,
			 iterator + 1 );

			return( -1 );
		}
		offset_values = (libbfio_offset_list_values_t *) list_element->value;

		if( ( offset >= offset_values->offset )
		 && ( offset < (off64_t) ( offset_values->offset + offset_values->size ) ) )
		{
			return( 1 );
		}
		if( ( offset_values->offset >= offset )
		 && ( offset_values->offset < last_offset ) )
		{
			return( 1 );
		}
		list_element = list_element->next;
	}
	return( 0 );
}

