MSVSCPP_FILES = \
	bfio_test_handle_read/bfio_test_handle_read.vcproj \
	bfio_test_handle_seek/bfio_test_handle_seek.vcproj \
	bfio_test_handle_write/bfio_test_handle_write.vcproj \
	bfio_test_pool_read/bfio_test_pool_read.vcproj \
	bfio_test_pool_seek/bfio_test_pool_seek.vcproj \
	bfio_test_pool_write/bfio_test_pool_write.vcproj \
	libbfio/libbfio.vcproj \
	libcdata/libcdata.vcproj \
	libcerror/libcerror.vcproj \
	libcfile/libcfile.vcproj \
	libclocale/libclocale.vcproj \
	libcnotify/libcnotify.vcproj \
	libcpath/libcpath.vcproj \
	libcsplit/libcsplit.vcproj \
	libcstring/libcstring.vcproj \
	libcthreads/libcthreads.vcproj \
	libuna/libuna.vcproj \
	libbfio.sln

SCRIPT_FILES = \
	scripts/vs2008_x64.sh \
	scripts/vs2008_x64_sln.sed \
	scripts/vs2008_x64_vcproj.sed \
	scripts/vs2010_x64.sh \
	scripts/vs2010_x64_sln.sed \
	scripts/vs2010_x64_vcxproj.sed

EXTRA_DIST = \
	$(MSVSCPP_FILES) \
	$(SCRIPT_FILES)

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

