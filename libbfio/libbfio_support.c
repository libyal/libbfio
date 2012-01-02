/*
 * Support functions
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include <stdio.h>

#include "libbfio_codepage.h"
#include "libbfio_definitions.h"
#include "libbfio_support.h"

#if !defined( HAVE_LOCAL_LIBBFIO )

/* Returns the library version as a string
 */
const char *libbfio_get_version(
             void )
{
	return( (const char *) LIBBFIO_VERSION_STRING );
}

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
int libbfio_get_codepage(
     int *codepage,
     liberror_error_t **error )
{
	static char *function = "libbfio_get_codepage";

	if( codepage == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid codepage.",
		 function );

		return( -1 );
	}
	*codepage = libcstring_narrow_system_string_codepage;

	return( 1 );
}

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
int libbfio_set_codepage(
     int codepage,
     liberror_error_t **error )
{
	static char *function = "libbfio_set_codepage";

	if( ( codepage != LIBBFIO_CODEPAGE_ASCII )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_1 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_2 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_3 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_4 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_5 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_6 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_7 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_8 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_9 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_10 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_11 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_13 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_14 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_15 )
	 && ( codepage != LIBBFIO_CODEPAGE_ISO_8859_16 )
	 && ( codepage != LIBBFIO_CODEPAGE_KOI8_R )
	 && ( codepage != LIBBFIO_CODEPAGE_KOI8_U )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_874 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_932 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_936 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1250 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1251 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1252 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1253 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1254 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1256 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1257 )
	 && ( codepage != LIBBFIO_CODEPAGE_WINDOWS_1258 )
	 && ( codepage != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported codepage.",
		 function );

		return( -1 );
	}
	libcstring_narrow_system_string_codepage = codepage;

	return( 1 );
}

#endif /* !defined( HAVE_LOCAL_LIBBFIO ) */

