/*
 * Library system string functions test program
 *
 * Copyright (C) 2009-2025, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "bfio_test_libbfio.h"
#include "bfio_test_libcerror.h"
#include "bfio_test_macros.h"
#include "bfio_test_unused.h"

#include "../libbfio/libbfio_system_string.h"

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

/* Tests the libbfio_system_string_size_to_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_size_to_narrow_string(
     void )
{
	system_character_t system_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };

	libcerror_error_t *error  = NULL;
	size_t narrow_string_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_size_to_narrow_string(
	          system_string,
	          5,
	          &narrow_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_EQUAL_SIZE(
	 "narrow_string_size",
	 narrow_string_size,
	 (size_t) 5 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_system_string_size_to_narrow_string(
	          NULL,
	          5,
	          &narrow_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_to_narrow_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          &narrow_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_to_narrow_string(
	          system_string,
	          5,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_system_string_copy_to_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_copy_to_narrow_string(
     void )
{
	system_character_t system_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };
	char expected_narrow_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };
	char narrow_string[ 5 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_copy_to_narrow_string(
	          system_string,
	          5,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          narrow_string,
	          expected_narrow_string,
	          sizeof( char ) * 5 );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libbfio_system_string_copy_to_narrow_string(
	          NULL,
	          5,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_narrow_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_narrow_string(
	          system_string,
	          5,
	          NULL,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_narrow_string(
	          system_string,
	          5,
	          narrow_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_narrow_string(
	          system_string,
	          5,
	          narrow_string,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

/* TODO test libbfio_system_string_copy_to_narrow_string with failing system_string_copy */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_system_string_size_from_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_size_from_narrow_string(
     void )
{
	char narrow_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };

	libcerror_error_t *error  = NULL;
	size_t system_string_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_size_from_narrow_string(
	          narrow_string,
	          5,
	          &system_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_EQUAL_SIZE(
	 "system_string_size",
	 system_string_size,
	 (size_t) 5 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_system_string_size_from_narrow_string(
	          NULL,
	          5,
	          &system_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_from_narrow_string(
	          narrow_string,
	          (size_t) SSIZE_MAX + 1,
	          &system_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_from_narrow_string(
	          narrow_string,
	          5,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_system_string_copy_from_narrow_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_copy_from_narrow_string(
     void )
{
	system_character_t expected_system_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };
	system_character_t system_string[ 5 ];
	char narrow_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_copy_from_narrow_string(
	          system_string,
	          5,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          system_string,
	          expected_system_string,
	          sizeof( system_character_t ) * 5 );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libbfio_system_string_copy_from_narrow_string(
	          NULL,
	          5,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_narrow_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_narrow_string(
	          system_string,
	          5,
	          NULL,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_narrow_string(
	          system_string,
	          5,
	          narrow_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_narrow_string(
	          system_string,
	          0,
	          narrow_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

/* TODO test libbfio_system_string_copy_from_narrow_string with failing system_string_copy */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libbfio_system_string_size_to_wide_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_size_to_wide_string(
     void )
{
	system_character_t system_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };

	libcerror_error_t *error = NULL;
	size_t wide_string_size  = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_size_to_wide_string(
	          system_string,
	          5,
	          &wide_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_EQUAL_SIZE(
	 "wide_string_size",
	 wide_string_size,
	 (size_t) 5 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_system_string_size_to_wide_string(
	          NULL,
	          5,
	          &wide_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_to_wide_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          &wide_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_to_wide_string(
	          system_string,
	          5,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_system_string_copy_to_wide_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_copy_to_wide_string(
     void )
{
	system_character_t system_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };
	wchar_t expected_wide_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };
	wchar_t wide_string[ 5 ];

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_copy_to_wide_string(
	          system_string,
	          5,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          wide_string,
	          expected_wide_string,
	          sizeof( wchar_t ) * 5 );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libbfio_system_string_copy_to_wide_string(
	          NULL,
	          5,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_wide_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_wide_string(
	          system_string,
	          5,
	          NULL,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_wide_string(
	          system_string,
	          5,
	          wide_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_to_wide_string(
	          system_string,
	          5,
	          wide_string,
	          0,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_system_string_size_from_wide_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_size_from_wide_string(
     void )
{
	wchar_t wide_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };

	libcerror_error_t *error  = NULL;
	size_t system_string_size = 0;
	int result                = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_size_from_wide_string(
	          wide_string,
	          5,
	          &system_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_EQUAL_SIZE(
	 "system_string_size",
	 system_string_size,
	 (size_t) 5 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libbfio_system_string_size_from_wide_string(
	          NULL,
	          5,
	          &system_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_from_wide_string(
	          wide_string,
	          (size_t) SSIZE_MAX + 1,
	          &system_string_size,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_size_from_wide_string(
	          wide_string,
	          5,
	          NULL,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libbfio_system_string_copy_from_wide_string function
 * Returns 1 if successful or 0 if not
 */
int bfio_test_system_string_copy_from_wide_string(
     void )
{
	system_character_t expected_system_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };
	system_character_t system_string[ 5 ];
	wchar_t wide_string[ 5 ] = {
		'T', 'e', 's', 't', 0 };

	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libbfio_system_string_copy_from_wide_string(
	          system_string,
	          5,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	BFIO_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = memory_compare(
	          system_string,
	          expected_system_string,
	          sizeof( system_character_t ) * 5 );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	/* Test error cases
	 */
	result = libbfio_system_string_copy_from_wide_string(
	          NULL,
	          5,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_wide_string(
	          system_string,
	          (size_t) SSIZE_MAX + 1,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_wide_string(
	          system_string,
	          5,
	          NULL,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_wide_string(
	          system_string,
	          5,
	          wide_string,
	          (size_t) SSIZE_MAX + 1,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libbfio_system_string_copy_from_wide_string(
	          system_string,
	          0,
	          wide_string,
	          5,
	          &error );

	BFIO_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	BFIO_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc BFIO_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] BFIO_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc BFIO_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] BFIO_TEST_ATTRIBUTE_UNUSED )
#endif
{
	BFIO_TEST_UNREFERENCED_PARAMETER( argc )
	BFIO_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT )

	BFIO_TEST_RUN(
	 "libbfio_system_string_size_to_narrow_string",
	 bfio_test_system_string_size_to_narrow_string );

	BFIO_TEST_RUN(
	 "libbfio_system_string_copy_to_narrow_string",
	 bfio_test_system_string_copy_to_narrow_string );

	BFIO_TEST_RUN(
	 "libbfio_system_string_size_from_narrow_string",
	 bfio_test_system_string_size_from_narrow_string );

	BFIO_TEST_RUN(
	 "libbfio_system_string_copy_from_narrow_string",
	 bfio_test_system_string_copy_from_narrow_string );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

	BFIO_TEST_RUN(
	 "libbfio_system_string_size_to_wide_string",
	 bfio_test_system_string_size_to_wide_string );

	BFIO_TEST_RUN(
	 "libbfio_system_string_copy_to_wide_string",
	 bfio_test_system_string_copy_to_wide_string );

	BFIO_TEST_RUN(
	 "libbfio_system_string_size_from_wide_string",
	 bfio_test_system_string_size_from_wide_string );

	BFIO_TEST_RUN(
	 "libbfio_system_string_copy_from_wide_string",
	 bfio_test_system_string_copy_from_wide_string );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

#endif /* defined( __GNUC__ ) && !defined( LIBBFIO_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

