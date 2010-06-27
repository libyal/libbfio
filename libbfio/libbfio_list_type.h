/*
 * List type functions
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

#if !defined( _LIBBFIO_LIST_TYPE_H )
#define _LIBBFIO_LIST_TYPE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

enum LIBBFIO_LIST_COMPARE_DEFINITIONS
{
	LIBBFIO_LIST_COMPARE_LESS,
	LIBBFIO_LIST_COMPARE_EQUAL,
	LIBBFIO_LIST_COMPARE_GREATER
};

typedef struct libbfio_list_element libbfio_list_element_t;

struct libbfio_list_element
{
	/* The previous element
	 */
	libbfio_list_element_t *previous;

	/* The next element
	 */
	libbfio_list_element_t *next;

	/* The list element value
	 */
	intptr_t *value;
};

typedef struct libbfio_list libbfio_list_t;

struct libbfio_list
{
	/* The number of elements
	 */
	int number_of_elements;

	/* The first list element
	 */
	libbfio_list_element_t *first;

	/* The last list element
	 */
	libbfio_list_element_t *last;
};

int libbfio_list_element_initialize(
     libbfio_list_element_t **list_element,
     liberror_error_t **error );

int libbfio_list_element_free(
     libbfio_list_element_t **list_element,
     int (*value_free_function)(
            intptr_t *value,
            liberror_error_t **error ),
     liberror_error_t **error );

int libbfio_list_initialize(
     libbfio_list_t **list,
     liberror_error_t **error );

int libbfio_list_free(
     libbfio_list_t **list,
     int (*value_free_function)(
            intptr_t *value,
            liberror_error_t **error ),
     liberror_error_t **error );

int libbfio_list_empty(
     libbfio_list_t *list,
     int (*value_free_function)(
            intptr_t *value,
            liberror_error_t **error ),
     liberror_error_t **error );

int libbfio_list_clone(
     libbfio_list_t **destination,
     libbfio_list_t *source,
     int (*value_clone_function)(
            intptr_t **destination,
            intptr_t *source,
            liberror_error_t **error ),
     liberror_error_t **error );

int libbfio_list_get_number_of_elements(
     libbfio_list_t *list,
     int *number_of_elements,
     liberror_error_t **error );

int libbfio_list_get_element(
     libbfio_list_t *list,
     int element_index,
     libbfio_list_element_t **element,
     liberror_error_t **error );

int libbfio_list_get_value(
     libbfio_list_t *list,
     int element_index,
     intptr_t **value,
     liberror_error_t **error );

int libbfio_list_prepend_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     liberror_error_t **error );

int libbfio_list_prepend_value(
     libbfio_list_t *list,
     intptr_t *value,
     liberror_error_t **error );

int libbfio_list_append_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     liberror_error_t **error );

int libbfio_list_append_value(
     libbfio_list_t *list,
     intptr_t *value,
     liberror_error_t **error );

int libbfio_list_insert_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     int (*value_compare_function)(
            intptr_t *first,
            intptr_t *second,
            liberror_error_t **error ),
     liberror_error_t **error );

int libbfio_list_insert_value(
     libbfio_list_t *list,
     intptr_t *value,
     int (*value_compare_function)(
            intptr_t *first,
            intptr_t *second,
            liberror_error_t **error ),
     liberror_error_t **error );

int libbfio_list_remove_element(
     libbfio_list_t *list,
     libbfio_list_element_t *element,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

