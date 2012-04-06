AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_seek.sh \
	test_read.sh \
	test_write.sh

check_SCRIPTS = \
	test_seek.sh \
	test_read.sh \
	test_write.sh

input_FILES = \
	input/test.raw

EXTRA_DIST = \
	$(check_SCRIPTS) \
	$(input_FILES)

check_PROGRAMS = \
	bfio_test_read \
	bfio_test_seek \
	bfio_test_write

bfio_test_read_SOURCES = \
	bfio_test_libcerror.h \
	bfio_test_libbfio.h \
	bfio_test_libcstring.h \
	bfio_test_read.c

bfio_test_read_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libbfio/libbfio.la \
        @MEMWATCH_LIBADD@

bfio_test_seek_SOURCES = \
	bfio_test_libcerror.h \
	bfio_test_libbfio.h \
	bfio_test_libcstring.h \
	bfio_test_seek.c

bfio_test_seek_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libbfio/libbfio.la \
        @MEMWATCH_LIBADD@

bfio_test_write_SOURCES = \
	bfio_test_libcerror.h \
	bfio_test_libbfio.h \
	bfio_test_libcstring.h \
	bfio_test_write.c

bfio_test_write_LDADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../libbfio/libbfio.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

