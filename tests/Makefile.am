AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
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
	test_handle_seek.sh \
	test_handle_read.sh \
	test_handle_write.sh \
	test_pool_seek.sh \
	test_pool_read.sh \
	test_pool_write.sh

check_SCRIPTS = \
	test_handle_seek.sh \
	test_handle_read.sh \
	test_handle_write.sh \
	test_pool_read.sh \
	test_pool_seek.sh \
	test_pool_write.sh \
	test_runner.sh

input_FILES = \
	input/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	bfio_test_handle_read \
	bfio_test_handle_seek \
	bfio_test_handle_write \
	bfio_test_pool_seek \
	bfio_test_pool_read \
	bfio_test_pool_write

bfio_test_handle_read_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcstring.h \
	bfio_test_handle_read.c

bfio_test_handle_read_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

bfio_test_handle_seek_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcstring.h \
	bfio_test_handle_seek.c

bfio_test_handle_seek_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

bfio_test_handle_write_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcpath.h \
	bfio_test_libcstring.h \
	bfio_test_handle_write.c

bfio_test_handle_write_LDADD = \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

bfio_test_pool_read_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcstring.h \
	bfio_test_pool_read.c

bfio_test_pool_read_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

bfio_test_pool_seek_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcstring.h \
	bfio_test_pool_seek.c

bfio_test_pool_seek_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

bfio_test_pool_write_SOURCES = \
	bfio_test_libbfio.h \
	bfio_test_libcerror.h \
	bfio_test_libcstring.h \
	bfio_test_libcpath.h \
	bfio_test_pool_write.c

bfio_test_pool_write_LDADD = \
	@LIBCPATH_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

