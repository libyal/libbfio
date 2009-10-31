/*
 * Codepage definitions for libbfio
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

#if !defined( _LIBBFIO_CODEPAGE_H )
#define _LIBBFIO_CODEPAGE_H

#include <libbfio/types.h>

/* The ASCII codepages
 */
enum LIBBFIO_CODEPAGES
{
	LIBBFIO_CODEPAGE_ASCII				= 0x41,
	LIBBFIO_CODEPAGE_WINDOWS_1250			= 1250,
	LIBBFIO_CODEPAGE_WINDOWS_1251			= 1251,
	LIBBFIO_CODEPAGE_WINDOWS_1252			= 1252,
	LIBBFIO_CODEPAGE_WINDOWS_1253			= 1253,
	LIBBFIO_CODEPAGE_WINDOWS_1254			= 1254,
	LIBBFIO_CODEPAGE_WINDOWS_1255			= 1255,
	LIBBFIO_CODEPAGE_WINDOWS_1256			= 1256,
	LIBBFIO_CODEPAGE_WINDOWS_1257			= 1257,
	LIBBFIO_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBBFIO_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBBFIO_CODEPAGE_WINDOWS_1250
#define LIBBFIO_CODEPAGE_WINDOWS_CYRILLIC		LIBBFIO_CODEPAGE_WINDOWS_1251
#define LIBBFIO_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBBFIO_CODEPAGE_WINDOWS_1252
#define LIBBFIO_CODEPAGE_WINDOWS_GREEK			LIBBFIO_CODEPAGE_WINDOWS_1253
#define LIBBFIO_CODEPAGE_WINDOWS_TURKISH			LIBBFIO_CODEPAGE_WINDOWS_1254
#define LIBBFIO_CODEPAGE_WINDOWS_HEBREW			LIBBFIO_CODEPAGE_WINDOWS_1255
#define LIBBFIO_CODEPAGE_WINDOWS_ARABIC			LIBBFIO_CODEPAGE_WINDOWS_1256
#define LIBBFIO_CODEPAGE_WINDOWS_BALTIC			LIBBFIO_CODEPAGE_WINDOWS_1257
#define LIBBFIO_CODEPAGE_WINDOWS_VIETNAMESE		LIBBFIO_CODEPAGE_WINDOWS_1258

#endif

