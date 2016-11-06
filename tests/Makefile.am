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
	@LIBBFIO_DLL_IMPORT@

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_write_functions.sh

check_SCRIPTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_runner.sh \
	test_write_functions.sh

input_FILES = \
	input/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	bfio_test_error \
	bfio_test_handle \
	bfio_test_handle_read \
	bfio_test_handle_seek \
	bfio_test_handle_write \
	bfio_test_pool \
	bfio_test_pool_seek \
	bfio_test_pool_read \
	bfio_test_pool_write \
	bfio_test_support

bfio_test_error_SOURCES = \
	bfio_test_error.c \
	bfio_test_libbfio.h \
	bfio_test_macros.h \
	bfio_test_unused.h

bfio_test_error_LDADD = \
	../libbfio/libbfio.la

bfio_test_handle_SOURCES = \
	bfio_test_handle.c \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_unused.h

bfio_test_handle_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_handle_read_SOURCES = \
	bfio_test_handle_read.c \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h

bfio_test_handle_read_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_handle_seek_SOURCES = \
	bfio_test_handle_seek.c \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h

bfio_test_handle_seek_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_handle_write_SOURCES = \
	bfio_test_handle_write.c \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcpath.h

bfio_test_handle_write_LDADD = \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_pool_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_memory.c bfio_test_memory.h \
	bfio_test_pool.c \
	bfio_test_unused.h

bfio_test_pool_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_pool_read_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_pool_read.c

bfio_test_pool_read_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_pool_seek_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_pool_seek.c

bfio_test_pool_seek_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

bfio_test_pool_write_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcpath.h \
	bfio_test_pool_write.c

bfio_test_pool_write_LDADD = \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
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

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

