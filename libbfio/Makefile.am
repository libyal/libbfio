AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common -I$(top_srcdir)/liberror @LIBUNA_CPPFLAGS@ @MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = libbfio.la

libbfio_la_SOURCES = \
	libbfio.c \
	libbfio_codepage.h \
	libbfio_definitions.h \
	libbfio_error.c libbfio_error.h \
	libbfio_error_string.c libbfio_error_string.h \
	libbfio_extern.h \
	libbfio_file.c libbfio_file.h \
	libbfio_file_pool.c libbfio_file_pool.h \
	libbfio_handle.c libbfio_handle.h \
	libbfio_libuna.h \
	libbfio_list_type.c libbfio_list_type.h \
	libbfio_memory_range.c libbfio_memory_range.h \
	libbfio_offset_list.c libbfio_offset_list.h \
	libbfio_pool.c libbfio_pool.h \
	libbfio_support.c libbfio_support.h \
	libbfio_system_string.c libbfio_system_string.h \
	libbfio_types.h

libbfio_la_LIBADD  = ../liberror/liberror.la @LIBUNA_LIBADD@
libbfio_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libbfio_definitions.h.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libbfio ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libbfio_la_SOURCES) 

