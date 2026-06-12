#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libbfio/.libs/libbfio.1.dylib && test -f ./pybfio/.libs/pybfio.so
then
	install_name_tool -change /usr/local/lib/libbfio.1.dylib ${PWD}/libbfio/.libs/libbfio.1.dylib ./pybfio/.libs/pybfio.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

