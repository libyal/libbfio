#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libbfio/.libs/libbfio.1.dylib && test -f ./pybfio/.libs/pybfio.so;
then
	install_name_tool -change /usr/local/lib/libbfio.1.dylib ${PWD}/libbfio/.libs/libbfio.1.dylib ./pybfio/.libs/pybfio.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

