include_HEADERS = \
	libbfio.h

pkginclude_HEADERS = \
	libbfio/codepage.h \
	libbfio/definitions.h \
	libbfio/error.h \
	libbfio/extern.h \
	libbfio/features.h \
	libbfio/types.h

EXTRA_DIST = \
	libbfio.h.in \
	libbfio/definitions.h.in \
	libbfio/features.h.in \
	libbfio/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libbfio.h
	-rm -f libbfio/definitions.h
	-rm -f libbfio/features.h
	-rm -f libbfio/types.h
	-rm -f Makefile

