AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBBFIO_DLL_EXPORT@

lib_LTLIBRARIES = libbfio.la

libbfio_la_SOURCES = \
	libbfio.c \
	libbfio_codepage.h \
	libbfio_definitions.h \
	libbfio_error.c libbfio_error.h \
	libbfio_extern.h \
	libbfio_file.c libbfio_file.h \
	libbfio_file_io_handle.c libbfio_file_io_handle.h \
	libbfio_file_pool.c libbfio_file_pool.h \
	libbfio_file_range.c libbfio_file_range.h \
	libbfio_file_range_io_handle.c libbfio_file_range_io_handle.h \
	libbfio_handle.c libbfio_handle.h \
	libbfio_libcdata.h \
	libbfio_libcerror.h \
	libbfio_libcfile.h \
	libbfio_libclocale.h \
	libbfio_libcpath.h \
	libbfio_libcthreads.h \
	libbfio_libuna.h \
	libbfio_memory_range.c libbfio_memory_range.h \
	libbfio_memory_range_io_handle.c libbfio_memory_range_io_handle.h \
	libbfio_pool.c libbfio_pool.h \
	libbfio_support.c libbfio_support.h \
	libbfio_system_string.c libbfio_system_string.h \
	libbfio_types.h \
	libbfio_unused.h

libbfio_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@PTHREAD_LIBADD@

libbfio_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libbfio_definitions.h.in \
	libbfio.rc \
	libbfio.rc.in

DISTCLEANFILES = \
	libbfio_definitions.h \
	libbfio.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libbfio ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libbfio_la_SOURCES)

