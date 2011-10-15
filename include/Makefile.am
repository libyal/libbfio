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
	/bin/rm -f libbfio.h
	/bin/rm -f libbfio/definitions.h
	/bin/rm -f libbfio/features.h
	/bin/rm -f libbfio/types.h
	/bin/rm -f Makefile

