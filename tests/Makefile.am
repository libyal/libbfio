AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBBFIO_DLL_IMPORT@

TESTS = \
	test_library.sh

check_SCRIPTS = \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

input_FILES = \
	input/raw/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	bfio_test_error \
	bfio_test_file \
	bfio_test_file_io_handle \
	bfio_test_file_range \
	bfio_test_file_range_io_handle \
	bfio_test_handle \
	bfio_test_memory_range \
	bfio_test_memory_range_io_handle \
	bfio_test_pool \
	bfio_test_support \
	bfio_test_system_string

bfio_test_error_SOURCES = \
	bfio_test_error.c \
	bfio_test_libbfio.h \
	bfio_test_macros.h \
	bfio_test_unused.h

bfio_test_error_LDADD = \
	../libbfio/libbfio.la

bfio_test_file_SOURCES = \
	bfio_test_file.c \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_unused.h

bfio_test_file_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_file_io_handle_SOURCES = \
	bfio_test_file_io_handle.c \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_unused.h

bfio_test_file_io_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_file_range_SOURCES = \
	bfio_test_file_range.c \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_unused.h

bfio_test_file_range_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_file_range_io_handle_SOURCES = \
	bfio_test_file_range_io_handle.c \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_unused.h

bfio_test_file_range_io_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_handle_SOURCES = \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_handle.c \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_rwlock.c bfio_test_rwlock.h \
	bfio_test_unused.h

bfio_test_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_memory_range_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_memory_range.c \
	bfio_test_unused.h

bfio_test_memory_range_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_memory_range_io_handle_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_memory_range_io_handle.c \
	bfio_test_unused.h

bfio_test_memory_range_io_handle_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_pool_SOURCES = \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_libbfio.h \
	bfio_test_libcdata.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_pool.c \
	bfio_test_rwlock.c bfio_test_rwlock.h \
	bfio_test_unused.h

bfio_test_pool_LDADD = \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_support_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_macros.h \
	bfio_test_support.c \
	bfio_test_unused.h

bfio_test_support_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_system_string_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_macros.h \
	bfio_test_system_string.c \
	bfio_test_unused.h

bfio_test_system_string_LDADD = \
	../libbfio/libbfio.la

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

