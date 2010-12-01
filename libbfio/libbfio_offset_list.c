/*
 * Offset list
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

/* Creates an offset list value
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_value_initialize(
     libbfio_offset_list_value_t **offset_list_value,
     liberror_error_t **error )
{
	static char *function = "libbfio_offset_list_value_initialize";

	if( offset_list_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list value.",
		 function );

		return( -1 );
	}
	if( *offset_list_value == NULL )
	{
		*offset_list_value = (libbfio_offset_list_value_t *) memory_allocate(
		                                                      sizeof( libbfio_offset_list_value_t ) );

		if( *offset_list_value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create offset list value.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *offset_list_value,
		     0,
		     sizeof( libbfio_offset_list_value_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear offset list value.",
			 function );

			memory_free(
			 *offset_list_value );

			*offset_list_value = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees an offset list value
 */
int libbfio_offset_list_value_free(
     intptr_t *offset_list_value,
     liberror_error_t **error )
{
	static char *function = "libbfio_offset_list_value_free";

	if( offset_list_value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid offset list value.",
		 function );

		return( -1 );
	}
	memory_free(
	 offset_list_value );

	return( 1 );
}

/* Creates an offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_initialize(
     libbfio_offset_list_t **offset_list,
     liberror_error_t **error )
{
	static char *function = "libbfio_offset_list_initialize";

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
	if( *offset_list == NULL )
	{
		*offset_list = (libbfio_offset_list_t *) memory_allocate(
		                                          sizeof( libbfio_offset_list_t ) );

		if( *offset_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create offset list.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *offset_list,
		     0,
		     sizeof( libbfio_offset_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear offset list.",
			 function );

			memory_free(
			 *offset_list );

			*offset_list = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees an offset list including the elements
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_free(
     libbfio_offset_list_t **offset_list,
     liberror_error_t **error )
{
	static char *function = "libbfio_offset_list_free";
	int result            = 1;

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
	if( *offset_list != NULL )
	{
		result = libbfio_offset_list_empty(
		          *offset_list,
		          error );

		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
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
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element = NULL;
	static char *function                = "libbfio_offset_list_empty";
	int element_index                    = 0;
	int number_of_elements               = 0;
	int result                           = 1;

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
	if( offset_list->number_of_elements > 0 )
	{
		number_of_elements = offset_list->number_of_elements;

		for( element_index = 0;
		     element_index < number_of_elements;
		     element_index++ )
		{
			list_element = offset_list->first_element;

			if( list_element == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: corruption detected in element: %d.",
				 function,
				 element_index );

				return( -1 );
			}
			offset_list->first_element = list_element->next_element;

			if( offset_list->last_element == list_element )
			{
				offset_list->last_element = list_element->next_element;
			}
			offset_list->number_of_elements -= 1;

			if( list_element->next_element != NULL )
			{
				list_element->next_element->previous_element = NULL;
			}
			list_element->next_element = NULL;

			if( libbfio_list_element_free(
			     &list_element,
			     &libbfio_offset_list_value_free,
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free element: %d.",
				 function,
				 element_index );

				result = -1;
			}
		}
		offset_list->current_element       = NULL;
		offset_list->current_element_index = 0;
	}
	return( result );
}

/* Retrieves the number of elements in the offset list
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_get_number_of_elements(
     libbfio_offset_list_t *offset_list,
     int *number_of_elements,
     liberror_error_t **error )
{
	static char *function = "libbfio_offset_list_get_number_of_elements";

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
	if( number_of_elements == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid number of elements.",
		 function );

		return( -1 );
	}
	*number_of_elements = offset_list->number_of_elements;

	return( 1 );
}

/* Appends an offset
 * Returns 1 if successful, or -1 on error
 */
int libbfio_offset_list_append_offset(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     size64_t size,
     uint8_t merge_ranges,
     liberror_error_t **error )
{
	libbfio_list_element_t *last_list_element      = NULL;
	libbfio_list_element_t *list_element           = NULL;
	libbfio_list_element_t *remove_element         = NULL;
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_append_offset";
	off64_t last_offset                            = 0;
	off64_t last_range_offset                      = 0;
	int create_list_element                        = 0;
	int element_index                              = 0;
	int merge_next_list_element_check              = 0;
	int merge_previous_list_element_check          = 0;

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
		 "%s: invalid offset value less than zero.",
		 function );

		return( -1 );
	}
	if( size > (size64_t) INT64_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	create_list_element = 1;

	/* Check if new range should be merged with an existing range
	 */
        if( merge_ranges == 0 )
        {
                last_list_element = offset_list->last_element;
        }
	else if( offset_list->number_of_elements > 0 )
	{
		last_offset = offset + size;

		/* Check the last element first, most often the list will be filled linear 
		 */
		list_element = offset_list->last_element;

		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected for list element: %d.",
			 function,
			 offset_list->number_of_elements - 1 );

			return( -1 );
		}
		if( list_element->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value for list element: %d.",
			 function,
			 offset_list->number_of_elements - 1 );

			return( -1 );
		}
		offset_list_value = (libbfio_offset_list_value_t *) list_element->value;

		last_range_offset = offset_list_value->offset + offset_list_value->size;

		/* Check if the offset range overlaps at the end of the last offset range
		 */
		if( ( offset >= offset_list_value->offset )
		 && ( offset <= last_range_offset ) )
		{
			if( last_offset > last_range_offset )
			{
				offset_list_value->size += (size64_t) ( last_offset - last_range_offset );
			}
			create_list_element           = 0;
			merge_next_list_element_check = 1;
		}
		/* Check if the offset range overlaps at the beginning of the last offset range
		 */
		else if( ( last_offset >= offset_list_value->offset )
		      && ( last_offset <= last_range_offset ) )
		{
			if( offset < offset_list_value->offset )
			{
				offset_list_value->offset  = offset;
				offset_list_value->size   += (size64_t) ( offset_list_value->offset - offset );
			}
			create_list_element               = 0;
			merge_previous_list_element_check = 1;
		}
		/* Check if the offset range overlaps the last offset range entirely
		 */
		else if( ( offset < offset_list_value->offset )
		      && ( last_offset > last_range_offset ) )
		{
			offset_list_value->offset = offset;
			offset_list_value->size   = size;

			create_list_element               = 0;
			merge_previous_list_element_check = 1;
		}
		/* Check if the offset range is beyond the last range
		 */
		else if( last_offset > last_range_offset )
		{
			last_list_element = list_element;
		}
		else if( offset_list->number_of_elements > 1 )
		{
			if( last_offset > ( last_range_offset / 2 ) )
			{
				list_element = list_element->previous_element;

				for( element_index = ( offset_list->number_of_elements - 2 );
				     element_index >= 0;
				     element_index-- )
				{
					if( list_element == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: corruption detected for list element: %d.",
						 function,
						 element_index );

						return( -1 );
					}
					if( list_element->value == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: missing offset list value for list element: %d.",
						 function,
						 element_index );

						return( -1 );
					}
					offset_list_value = (libbfio_offset_list_value_t *) list_element->value;

					last_range_offset = offset_list_value->offset + offset_list_value->size;

					/* Check if the offset range overlaps at the end of an existing offset range
					 */
					if( ( offset >= offset_list_value->offset )
					 && ( offset <= last_range_offset ) )
					{
						if( last_offset > last_range_offset )
						{
							offset_list_value->size += (size64_t) ( last_offset - last_range_offset );
						}
						create_list_element           = 0;
						merge_next_list_element_check = 1;
					}
					/* Check if the offset range overlaps at the beginning of an existing offset range
					 */
					else if( ( last_offset >= offset_list_value->offset )
					      && ( last_offset <= last_range_offset ) )
					{
						if( offset < offset_list_value->offset )
						{
							offset_list_value->offset  = offset;
							offset_list_value->size   += (size64_t) ( offset_list_value->offset - offset );
						}
						create_list_element               = 0;
						merge_previous_list_element_check = 1;
					}
					/* Check if the offset range overlaps an existing offset range entirely
					 */
					else if( ( offset < offset_list_value->offset )
					      && ( last_offset > last_range_offset ) )
					{
						offset_list_value->offset = offset;
						offset_list_value->size   = size;

						create_list_element               = 0;
						merge_next_list_element_check     = 1;
						merge_previous_list_element_check = 1;
					}
					if( create_list_element == 0 )
					{
						break;
					}
					/* Check if the offset range belongs after the exising offset range
					 */
					if( last_offset > last_range_offset )
					{
						last_list_element = list_element;

						break;
					}
					last_list_element = list_element;
					list_element      = list_element->previous_element;
				}
			}
			else
			{
				list_element = offset_list->first_element;

				for( element_index = 0;
				     element_index < ( offset_list->number_of_elements - 1 );
				     element_index++ )
				{
					if( list_element == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: corruption detected for list element: %d.",
						 function,
						 element_index );

						return( -1 );
					}
					if( list_element->value == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: missing offset list value for list element: %d.",
						 function,
						 element_index );

						return( -1 );
					}
					offset_list_value = (libbfio_offset_list_value_t *) list_element->value;

					last_range_offset = offset_list_value->offset + offset_list_value->size;

					/* Check if the offset range overlaps at the end of an existing offset range
					 */
					if( ( offset >= offset_list_value->offset )
					 && ( offset <= last_range_offset ) )
					{
						if( last_offset > last_range_offset )
						{
							offset_list_value->size += (size64_t) ( last_offset - last_range_offset );
						}
						create_list_element           = 0;
						merge_next_list_element_check = 1;
					}
					/* Check if the offset range overlaps at the beginning of an existing offset range
					 */
					else if( ( last_offset >= offset_list_value->offset )
					      && ( last_offset <= last_range_offset ) )
					{
						if( offset < offset_list_value->offset )
						{
							offset_list_value->offset  = offset;
							offset_list_value->size   += (size64_t) ( offset_list_value->offset - offset );
						}
						create_list_element               = 0;
						merge_previous_list_element_check = 1;
					}
					/* Check if the offset range overlaps an existing offset range entirely
					 */
					else if( ( offset < offset_list_value->offset )
					      && ( last_offset > last_range_offset ) )
					{
						offset_list_value->offset = offset;
						offset_list_value->size   = size;

						create_list_element               = 0;
						merge_next_list_element_check     = 1;
						merge_previous_list_element_check = 1;
					}
					if( create_list_element == 0 )
					{
						break;
					}
					/* Check if the offset range belongs before the current offset range
					 */
					if( last_offset < last_range_offset )
					{
                                        	last_list_element = list_element->previous_element;

						break;
					}
                                        last_list_element = list_element;
                                        list_element      = list_element->next_element;
				}
			}
		}
		/* Check if the current range should be merged with the previous range
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
			if( list_element->previous_element != NULL )
			{
				if( list_element->previous_element->value == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing offset list value for previous list element.",
					 function );

					return( -1 );
				}
				last_offset = ( (libbfio_offset_list_value_t *) list_element->previous_element->value )->offset
				            + ( (libbfio_offset_list_value_t *) list_element->previous_element->value )->size;

				if( last_offset == offset_list_value->offset )
				{
					/* Merge offset range with previous
					 */
					offset_list_value->offset  = ( (libbfio_offset_list_value_t *) list_element->previous_element->value )->offset;
					offset_list_value->size   += ( (libbfio_offset_list_value_t *) list_element->previous_element->value )->size;

					/* Remove previous list element
					 */
					remove_element = list_element->previous_element;

					if( remove_element == offset_list->first_element )
					{
						offset_list->first_element = remove_element->next_element;
					}
					if( remove_element == offset_list->last_element )
					{
						offset_list->last_element = remove_element->previous_element;
					}
					if( remove_element->next_element != NULL )
					{
						remove_element->next_element->previous_element = remove_element->previous_element;
					}
					if( remove_element->previous_element != NULL )
					{
						remove_element->previous_element->next_element = remove_element->next_element;
					}
					remove_element->next_element     = NULL;
					remove_element->previous_element = NULL;
					offset_list->number_of_elements -= 1;

					if( libbfio_list_element_free(
					     &remove_element,
					     &libbfio_offset_list_value_free,
					     error ) != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free element: %d.",
						 function,
						 element_index );

						return( -1 );
					}
				}
			}
		}
		/* Check if the current range should be merged with the next range
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
			if( list_element->next_element != NULL )
			{
				if( list_element->next_element->value == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: missing offset list value for next list element.",
					 function );

					return( -1 );
				}
				last_offset = offset_list_value->offset + offset_list_value->size;

				if( last_offset == ( (libbfio_offset_list_value_t *) list_element->next_element->value )->offset )
				{
					/* Merge offset range with next
					 */
					offset_list_value->size += ( (libbfio_offset_list_value_t *) list_element->next_element->value )->size;

					/* Remove next list element
					 */
					remove_element = list_element->next_element;

					if( remove_element == offset_list->first_element )
					{
						offset_list->first_element = remove_element->next_element;
					}
					if( remove_element == offset_list->last_element )
					{
						offset_list->last_element = remove_element->previous_element;
					}
					if( remove_element->next_element != NULL )
					{
						remove_element->next_element->previous_element = remove_element->previous_element;
					}
					if( remove_element->previous_element != NULL )
					{
						remove_element->previous_element->next_element = remove_element->next_element;
					}
					remove_element->next_element     = NULL;
					remove_element->previous_element = NULL;
					offset_list->number_of_elements -= 1;

					if( libbfio_list_element_free(
					     &remove_element,
					     &libbfio_offset_list_value_free,
					     error ) != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
						 "%s: unable to free element: %d.",
						 function,
						 element_index );

						return( -1 );
					}
				}
			}
		}
	}
	if( create_list_element != 0 )
	{
		offset_list_value = NULL;

		if( libbfio_offset_list_value_initialize(
		     &offset_list_value,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create offset list value.",
			 function );

			return( -1 );
		}
		if( offset_list_value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value.",
			 function );

			return( -1 );
		}
		offset_list_value->offset = offset;
		offset_list_value->size   = size;

		list_element = NULL;

		if( libbfio_list_element_initialize(
		     &list_element,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create list element.",
			 function );

			libbfio_offset_list_value_free(
			 (intptr_t *) offset_list_value,
			 NULL );

			return( -1 );
		}
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing list element.",
			 function );

			libbfio_offset_list_value_free(
			 (intptr_t *) offset_list_value,
			 NULL );

		}
		list_element->value = (intptr_t *) offset_list_value;

		if( offset_list->number_of_elements == 0 )
		{
			if( offset_list->first_element != NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: corruption detected - first element already set.",
				 function );

				libbfio_list_element_free(
				 &list_element,
				 &libbfio_offset_list_value_free,
				 NULL );

				return( -1 );
			}
			if( offset_list->last_element != NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: corruption detected - last element already set.",
				 function );

				libbfio_list_element_free(
				 &list_element,
				 &libbfio_offset_list_value_free,
				 NULL );

				return( -1 );
			}
			offset_list->first_element = list_element;
			offset_list->last_element  = list_element;
		}
		else
		{
			if( offset_list->first_element == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: corruption detected - missing first.",
				 function );

				libbfio_list_element_free(
				 &list_element,
				 &libbfio_offset_list_value_free,
				 NULL );

				return( -1 );
			}
			if( offset_list->last_element == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
				 "%s: corruption detected - missing last.",
				 function );

				libbfio_list_element_free(
				 &list_element,
				 &libbfio_offset_list_value_free,
				 NULL );

				return( -1 );
			}
			if( last_list_element == NULL )
			{
				offset_list->first_element->previous_element = list_element;
				list_element->next_element                   = offset_list->first_element;

				offset_list->first_element = list_element;
			}
			else
			{
				list_element->previous_element = last_list_element;
				list_element->next_element     = last_list_element->next_element;

				if( last_list_element == offset_list->last_element )
				{
					offset_list->last_element = list_element;
				}
				else if( last_list_element->next_element == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: corruption detected - missing next in last list element.",
					 function );

					return( -1 );
				}
				else
				{
					last_list_element->next_element->previous_element = list_element;
				}
				last_list_element->next_element = list_element;
			}
		}
		offset_list->number_of_elements++;
	}
	return( 1 );
}

/* Retrieves a specific offset
 * Returns 1 if successful or -1 on error
 */
int libbfio_offset_list_get_offset(
     libbfio_offset_list_t *offset_list,
     int index,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_get_offset";

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
	if( ( index < 0 )
	 || ( index >= offset_list->number_of_elements ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid index value out of bounds.",
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
	if( ( offset_list->current_element != NULL )
	 && ( offset_list->current_element_index != index ) )
	{
		if( index < offset_list->current_element_index )
		{
			if( ( offset_list->current_element_index - index ) < ( offset_list->number_of_elements / 2 ) )
			{
				while( offset_list->current_element_index > index )
				{
					if( offset_list->current_element == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: corruption detected in element: %d.",
						 function,
						 offset_list->current_element_index );

						return( -1 );
					}
					offset_list->current_element = offset_list->current_element->next_element;

					offset_list->current_element_index--;
				}
			}
		}
		else
		{
			if( ( index - offset_list->current_element_index ) < ( offset_list->number_of_elements / 2 ) )
			{
				while( offset_list->current_element_index < index )
				{
					if( offset_list->current_element == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
						 "%s: corruption detected in element: %d.",
						 function,
						 offset_list->current_element_index );

						return( -1 );
					}
					offset_list->current_element = offset_list->current_element->next_element;

					offset_list->current_element_index++;
				}
			}
		}
	}
	if( ( offset_list->current_element == NULL )
	 || ( offset_list->current_element_index != index ) )
	{
		if( index < ( offset_list->number_of_elements / 2 ) )
		{
			offset_list->current_element = offset_list->first_element;

			for( offset_list->current_element_index = 0;
			     offset_list->current_element_index < index;
			     offset_list->current_element_index++ )
			{
				if( offset_list->current_element == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: corruption detected in element: %d.",
					 function,
					 offset_list->current_element_index );

					return( -1 );
				}
				offset_list->current_element = offset_list->current_element->next_element;
			}
		}
		else
		{
			offset_list->current_element = offset_list->last_element;

			for( offset_list->current_element_index = ( offset_list->number_of_elements - 1 );
			     offset_list->current_element_index > index;
			     offset_list->current_element_index-- )
			{
				if( offset_list->current_element == NULL )
				{
					liberror_error_set(
					 error,
					 LIBERROR_ERROR_DOMAIN_RUNTIME,
					 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
					 "%s: corruption detected in element: %d.",
					 function,
					 offset_list->current_element_index );

					return( -1 );
				}
				offset_list->current_element = offset_list->current_element->previous_element;
			}
		}
	}
	if( offset_list->current_element == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing offset list element: %d.",
		 function,
		 offset_list->current_element_index );

		return( -1 );
	}
	if( offset_list->current_element->value == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing offset list value for list element: %d.",
		 function,
		 offset_list->current_element_index );

		return( -1 );
	}
	offset_list_value = (libbfio_offset_list_value_t *) offset_list->current_element->value;

	*offset = offset_list_value->offset;
	*size   = offset_list_value->size;

	return( 1 );
}

/* Retrieves a specific offset by its value
 * Returns 1 if successful, 0 if not available or -1 on error
 */
int libbfio_offset_list_get_offset_by_value(
     libbfio_offset_list_t *offset_list,
     off64_t offset_value,
     off64_t *offset,
     size64_t *size,
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element           = NULL;
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_get_offset_by_value";
	int element_index                              = 0;

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
	list_element = offset_list->first_element;

	for( element_index = 0;
	     element_index < offset_list->number_of_elements;
	     element_index++ )
	{
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected for list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( list_element->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value for list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		offset_list_value = (libbfio_offset_list_value_t *) list_element->value;

		if( ( offset_value >= offset_list_value->offset )
		 && ( offset_value <= (off64_t) ( offset_list_value->offset + offset_list_value->size ) ) )
		{
			*offset = offset_list_value->offset;
			*size   = offset_list_value->size;

			return( 1 );
		}
		list_element = list_element->next_element;
	}
	return( 0 );
}

/* Determines if a certain offset range is present in the list
 * Returns 1 if present, 0 if not present or -1 on error
 */
int libbfio_offset_list_range_is_present(
     libbfio_offset_list_t *offset_list,
     off64_t offset,
     size64_t size,
     liberror_error_t **error )
{
	libbfio_list_element_t *list_element           = NULL;
	libbfio_offset_list_value_t *offset_list_value = NULL;
	static char *function                          = "libbfio_offset_list_range_is_present";
	off64_t last_offset                            = 0;
	int element_index                              = 0;

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
		 "%s: invalid offset value less than zero.",
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
	list_element = offset_list->first_element;

	for( element_index = 0;
	     element_index < offset_list->number_of_elements;
	     element_index++ )
	{
		if( list_element == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: corruption detected for list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		if( list_element->value == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
			 "%s: missing offset list value for list element: %d.",
			 function,
			 element_index );

			return( -1 );
		}
		offset_list_value = (libbfio_offset_list_value_t *) list_element->value;

		if( ( offset >= offset_list_value->offset )
		 && ( offset < (off64_t) ( offset_list_value->offset + offset_list_value->size ) ) )
		{
			return( 1 );
		}
		if( ( offset_list_value->offset >= offset )
		 && ( offset_list_value->offset < last_offset ) )
		{
			return( 1 );
		}
		list_element = list_element->next_element;
	}
	return( 0 );
}

