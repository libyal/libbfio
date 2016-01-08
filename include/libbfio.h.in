/*
 * Library to support (abstracted) basic file input/output (IO)
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBBFIO_H )
#define _LIBBFIO_H

#include <libbfio/definitions.h>
#include <libbfio/codepage.h>
#include <libbfio/error.h>
#include <libbfio/extern.h>
#include <libbfio/features.h>
#include <libbfio/types.h>

#include <stdio.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* -------------------------------------------------------------------------
 * Support functions
 * ------------------------------------------------------------------------- */

/* Returns the library version
 */
LIBBFIO_EXTERN \
const char *libbfio_get_version(
             void );

/* Retrieves the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_get_codepage(
     int *codepage,
     libbfio_error_t **error );

/* Sets the narrow system string codepage
 * A value of 0 represents no codepage, UTF-8 encoding is used instead
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_set_codepage(
     int codepage,
     libbfio_error_t **error );

/* -------------------------------------------------------------------------
 * Error functions
 * ------------------------------------------------------------------------- */

/* Frees an error
 */
LIBBFIO_EXTERN \
void libbfio_error_free(
      libbfio_error_t **error );

/* Prints a descriptive string of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_error_fprint(
     libbfio_error_t *error,
     FILE *stream );

/* Prints a descriptive string of the error to the string
 * Returns the number of printed characters if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_error_sprint(
     libbfio_error_t *error,
     char *string,
     size_t size );

/* Prints a backtrace of the error to the stream
 * Returns the number of printed characters if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_error_backtrace_fprint(
     libbfio_error_t *error,
     FILE *stream );

/* Prints a backtrace of the error to the string
 * Returns the number of printed characters if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_error_backtrace_sprint(
     libbfio_error_t *error,
     char *string,
     size_t size );

/* -------------------------------------------------------------------------
 * Handle functions
 * ------------------------------------------------------------------------- */

/* Creates a handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_initialize(
     libbfio_handle_t **handle,
     intptr_t *io_handle,
     int (*free_io_handle)(
            intptr_t **io_handle,
            libbfio_error_t **error ),
     int (*clone_io_handle)(
            intptr_t **destination_io_handle,
            intptr_t *source_io_handle,
            libbfio_error_t **error ),
     int (*open)(
            intptr_t *io_handle,
            int access_flags,
            libbfio_error_t **error ),
     int (*close)(
            intptr_t *io_handle,
            libbfio_error_t **error ),
     ssize_t (*read)(
                intptr_t *io_handle,
                uint8_t *buffer,
                size_t size,
                libbfio_error_t **error ),
     ssize_t (*write)(
                intptr_t *io_handle,
                const uint8_t *buffer,
                size_t size,
                libbfio_error_t **error ),
     off64_t (*seek_offset)(
                intptr_t *io_handle,
                off64_t offset,
                int whence,
                libbfio_error_t **error ),
     int (*exists)(
            intptr_t *io_handle,
            libbfio_error_t **error ),
     int (*is_open)(
            intptr_t *io_handle,
            libbfio_error_t **error ),
     int (*get_size)(
            intptr_t *io_handle,
            size64_t *size,
            libbfio_error_t **error ),
     uint8_t flags,
     libbfio_error_t **error );

/* Frees a handle
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_free(
     libbfio_handle_t **handle,
     libbfio_error_t **error );

/* Clones (duplicates) the handle
 * The values in the offsets read list are not duplicated
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_clone(
     libbfio_handle_t **destination_handle,
     libbfio_handle_t *source_handle,
     libbfio_error_t **error );

/* Opens the handle
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_open(
     libbfio_handle_t *handle,
     int access_flags,
     libbfio_error_t **error );

/* Reopens the handle
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_reopen(
     libbfio_handle_t *handle,
     int access_flags,
     libbfio_error_t **error );

/* Closes the handle
 * Returns 0 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_close(
     libbfio_handle_t *handle,
     libbfio_error_t **error );

/* Reads a buffer from the handle
 * Returns the number of bytes read if successful, or -1 on error
 */
LIBBFIO_EXTERN \
ssize_t libbfio_handle_read_buffer(
         libbfio_handle_t *handle,
         uint8_t *buffer,
         size_t size,
         libbfio_error_t **error );

/* Writes a buffer to the handle
 * Returns the number of bytes written if successful, or -1 on error
 */
LIBBFIO_EXTERN \
ssize_t libbfio_handle_write_buffer(
         libbfio_handle_t *handle,
         const uint8_t *buffer,
         size_t size,
         libbfio_error_t **error );

/* Seeks a certain offset within the handle
 * Returns the offset if the seek is successful or -1 on error
 */
LIBBFIO_EXTERN \
off64_t libbfio_handle_seek_offset(
         libbfio_handle_t *handle,
         off64_t offset,
         int whence,
         libbfio_error_t **error );

/* Function to determine if a file object exists
 * Return 1 if file object exists, 0 if not or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_exists(
     libbfio_handle_t *handle,
     libbfio_error_t **error );

/* Check if the handle is open
 * Returns 1 if open, 0 if not or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_is_open(
     libbfio_handle_t *handle,
     libbfio_error_t **error );

/* Retrieves the IO handle
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_get_io_handle(
     libbfio_handle_t *handle,
     intptr_t **io_handle,
     libbfio_error_t **error );

/* Retrieves the access flags
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_get_access_flags(
     libbfio_handle_t *handle,
     int *access_flags,
     libbfio_error_t **error );

/* Sets the access flags
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_set_access_flags(
     libbfio_handle_t *handle,
     int access_flags,
     libbfio_error_t **error );

/* Returns the size of the data of the handle
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_get_size(
     libbfio_handle_t *handle,
     size64_t *size,
     libbfio_error_t **error );

/* Sets the value to have the library open and close
 * the systems file descriptor or handle on demand
 * 0 disables open on demand any other value enables it
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_set_open_on_demand(
     libbfio_handle_t *handle,
     uint8_t open_on_demand,
     libbfio_error_t **error );

/* Sets the value to have the library track the offsets read
 * 0 disables tracking any other value enables it
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_set_track_offsets_read(
     libbfio_handle_t *handle,
     uint8_t track_offsets_read,
     libbfio_error_t **error );

/* Retrieves the current offset
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_get_offset(
     libbfio_handle_t *handle,
     off64_t *offset,
     libbfio_error_t **error );

/* Retrieves the number of offsets read
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_get_number_of_offsets_read(
     libbfio_handle_t *handle,
     int *number_of_read_offsets,
     libbfio_error_t **error );

/* Retrieves the information of an offset read
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_handle_get_offset_read(
     libbfio_handle_t *handle,
     int index,
     off64_t *offset,
     size64_t *size,
     libbfio_error_t **error );

/* -------------------------------------------------------------------------
 * File functions
 * ------------------------------------------------------------------------- */

/* Creates a file handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_initialize(
     libbfio_handle_t **handle,
     libbfio_error_t **error );

/* Retrieves a name size of the file handle
 * The name size includes the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_get_name_size(
     libbfio_handle_t *handle,
     size_t *name_size,
     libbfio_error_t **error );

/* Retrieves a name of the file handle
 * The name size should include the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_get_name(
     libbfio_handle_t *handle,
     char *name,
     size_t name_size,
     libbfio_error_t **error );

/* Sets a name for the file handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_set_name(
     libbfio_handle_t *handle,
     const char *name,
     size_t name_length,
     libbfio_error_t **error );

#if defined( LIBBFIO_HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves a name size of the file handle
 * The name size includes the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_get_name_size_wide(
     libbfio_handle_t *handle,
     size_t *name_size,
     libbfio_error_t **error );

/* Retrieves a name of the file handle
 * The name size should include the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_get_name_wide(
     libbfio_handle_t *handle,
     wchar_t *name,
     size_t name_size,
     libbfio_error_t **error );

/* Sets a name for the file handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_set_name_wide(
     libbfio_handle_t *handle,
     const wchar_t *name,
     size_t name_length,
     libbfio_error_t **error );

#endif /* defined( LIBBFIO_HAVE_WIDE_CHARACTER_TYPE ) */

/* -------------------------------------------------------------------------
 * File range functions
 * ------------------------------------------------------------------------- */

/* Creates a file range handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_initialize(
     libbfio_handle_t **handle,
     libbfio_error_t **error );

/* Retrieves a name size of the file range handle
 * The name size includes the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_get_name_size(
     libbfio_handle_t *handle,
     size_t *name_size,
     libbfio_error_t **error );

/* Retrieves a name of the file range handle
 * The name size should include the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_get_name(
     libbfio_handle_t *handle,
     char *name,
     size_t name_size,
     libbfio_error_t **error );

/* Sets a name for the file range handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_set_name(
     libbfio_handle_t *handle,
     const char *name,
     size_t name_length,
     libbfio_error_t **error );

#if defined( LIBBFIO_HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves a name size of the file range handle
 * The name size includes the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_get_name_size_wide(
     libbfio_handle_t *handle,
     size_t *name_size,
     libbfio_error_t **error );

/* Retrieves a name of the file range handle
 * The name size should include the end of string character
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_get_name_wide(
     libbfio_handle_t *handle,
     wchar_t *name,
     size_t name_size,
     libbfio_error_t **error );

/* Sets a name for the file range handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_set_name_wide(
     libbfio_handle_t *handle,
     const wchar_t *name,
     size_t name_length,
     libbfio_error_t **error );

#endif /* defined( LIBBFIO_HAVE_WIDE_CHARACTER_TYPE ) */

/* Retrieves the range of the file range handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_get(
     libbfio_handle_t *handle,
     off64_t *range_offset,
     size64_t *range_size,
     libbfio_error_t **error );

/* Sets the range of the file range handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_range_set(
     libbfio_handle_t *handle,
     off64_t range_offset,
     size64_t range_size,
     libbfio_error_t **error );

/* -------------------------------------------------------------------------
 * Memory range functions
 * ------------------------------------------------------------------------- */

/* Creates a memory range handle
 * Make sure the value handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_memory_range_initialize(
     libbfio_handle_t **handle,
     libbfio_error_t **error );

/* Retrieves the range of the memory range handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_memory_range_get(
     libbfio_handle_t *handle,
     uint8_t **start,
     size_t *size,
     libbfio_error_t **error );

/* Sets the range of the memory range handle
 * Returns 1 if succesful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_memory_range_set(
     libbfio_handle_t *handle,
     uint8_t *start,
     size_t size,
     libbfio_error_t **error );

/* -------------------------------------------------------------------------
 * Pool functions
 * ------------------------------------------------------------------------- */

/* Creates a pool
 * Make sure the value pool is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_initialize(
     libbfio_pool_t **pool,
     int number_of_handles,
     int maximum_number_of_open_handles,
     libbfio_error_t **error );

/* Frees a pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_free(
     libbfio_pool_t **pool,
     libbfio_error_t **error );

/* Clones (duplicates) the pool
 * The values in the offsets read list are not duplicated
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_clone(
     libbfio_pool_t **destination_pool,
     libbfio_pool_t *source_pool,
     libbfio_error_t **error );

/* Resizes the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_resize(
     libbfio_pool_t *pool,
     int number_of_handles,
     libbfio_error_t **error );

/* Retrieves the number of handles in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_get_number_of_handles(
     libbfio_pool_t *pool,
     int *number_of_handles,
     libbfio_error_t **error );

/* Retrieves a certain handle from the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_get_handle(
     libbfio_pool_t *pool,
     int entry,
     libbfio_handle_t **handle,
     libbfio_error_t **error );

/* Appends a handle to the pool
 * Sets the entry
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_append_handle(
     libbfio_pool_t *pool,
     int *entry,
     libbfio_handle_t *handle,
     int access_flags,
     libbfio_error_t **error );

/* Sets a certain handle in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_set_handle(
     libbfio_pool_t *pool,
     int entry,
     libbfio_handle_t *handle,
     int access_flags,
     libbfio_error_t **error );

/* Removes a certain handle from the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_remove_handle(
     libbfio_pool_t *pool,
     int entry,
     libbfio_handle_t **handle,
     libbfio_error_t **error );

/* Retrieves the maximum number of open handles in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_get_maximum_number_of_open_handles(
     libbfio_pool_t *pool,
     int *maximum_number_of_open_handles,
     libbfio_error_t **error );

/* Sets the maximum number of open handles in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_set_maximum_number_of_open_handles(
     libbfio_pool_t *pool,
     int maximum_number_of_open_handles,
     libbfio_error_t **error );

/* Opens a handle in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_open(
     libbfio_pool_t *pool,
     int entry,
     int access_flags,
     libbfio_error_t **error );

/* Reopens a handle in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_reopen(
     libbfio_pool_t *pool,
     int entry,
     int access_flags,
     libbfio_error_t **error );

/* Closes a handle in the pool
 * Returns 0 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_close(
     libbfio_pool_t *pool,
     int entry,
     libbfio_error_t **error );

/* Closes all the files in the pool
 * Returns 0 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_close_all(
     libbfio_pool_t *pool,
     libbfio_error_t **error );

/* Reads a buffer from a handle in the pool
 * Returns the number of bytes read or -1 on error
 */
LIBBFIO_EXTERN \
ssize_t libbfio_pool_read_buffer(
         libbfio_pool_t *pool,
         int entry,
         uint8_t *buffer,
         size_t size,
         libbfio_error_t **error );

/* Writes a buffer to a handle in the pool
 * Returns the number of bytes written or -1 on error
 */
LIBBFIO_EXTERN \
ssize_t libbfio_pool_write_buffer(
         libbfio_pool_t *pool,
         int entry,
         const uint8_t *buffer,
         size_t size,
         libbfio_error_t **error );

/* Seeks an offset in a handle in the pool
 * Returns the offset if successful or -1 on error
 */
LIBBFIO_EXTERN \
off64_t libbfio_pool_seek_offset(
         libbfio_pool_t *pool,
         int entry,
         off64_t offset,
         int whence,
         libbfio_error_t **error );

/* Retrieves the current offset in a handle in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_get_offset(
     libbfio_pool_t *pool,
     int entry,
     off64_t *offset,
     libbfio_error_t **error );

/* Retrieves the size of a handle in the pool
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_pool_get_size(
     libbfio_pool_t *pool,
     int entry,
     size64_t *size,
     libbfio_error_t **error );

/* -------------------------------------------------------------------------
 * File pool functions
 * ------------------------------------------------------------------------- */

/* Appends file handles to the pool for the corresponding filenames
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_pool_append_handles_for_names(
     libbfio_pool_t *pool,
     char * const names[],
     int number_of_names,
     int access_flags,
     libbfio_error_t **error );

#if defined( LIBBFIO_HAVE_WIDE_CHARACTER_TYPE )

/* Appends file handles to the pool for the corresponding filenames
 * Returns 1 if successful or -1 on error
 */
LIBBFIO_EXTERN \
int libbfio_file_pool_append_handle_for_names_wide(
     libbfio_pool_t *pool,
     wchar_t * const names[],
     int number_of_names,
     int access_flags,
     libbfio_error_t **error );

#endif /* defined( LIBBFIO_HAVE_WIDE_CHARACTER_TYPE ) */

#if defined( __cplusplus )
}
#endif

#endif

