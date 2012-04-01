AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

TESTS = \
	test_path.sh

check_SCRIPTS = \
	test_path.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	bfio_test_path

bfio_test_path_SOURCES = \
	bfio_test_libcstring.h \
	bfio_test_libbfio.h \
	bfio_test_path.c

bfio_test_path_LDADD = \
	@LIBCSTRING_LIBADD@ \
	../libbfio/libbfio.la \
        @MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

