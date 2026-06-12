AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages

input_FILES = \
	input/raw/test.raw

check_PROGRAMS = \
	bfio_test_error \
	bfio_test_file \
	bfio_test_file_io_handle \
	bfio_test_file_pool \
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
	bfio_test_libcfile.h \
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

bfio_test_file_pool_SOURCES = \
	bfio_test_file_pool.c \
	bfio_test_functions.c bfio_test_functions.h \
	bfio_test_getopt.c bfio_test_getopt.h \
	bfio_test_libbfio.h \
	bfio_test_libcdata.h \
	bfio_test_libcerror.h \
	bfio_test_libclocale.h \
	bfio_test_libcnotify.h \
	bfio_test_libuna.h \
	bfio_test_macros.h \
	bfio_test_unused.h

bfio_test_file_pool_LDADD = \
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
	bfio_test_extern.h \
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
	bfio_test_extern.h \
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
	bfio_test_libcerror.h \
	bfio_test_macros.h \
	bfio_test_system_string.c \
	bfio_test_unused.h

bfio_test_system_string_LDADD = \
	../libbfio/libbfio.la \
	@LIBCERROR_LIBADD@

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libbfio.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libbfio

test_library: package.m4 test_inputs_libbfio.at test_library.at test_macros.at

test_manpages: package.m4 test_manpages.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(input_FILES) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in


