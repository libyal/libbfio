#!/bin/bash
#
# Basic File IO (BFIO) library path testing script
#
# Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
#
# Refer to AUTHORS for acknowledgements.
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This software is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this software.  If not, see <http://www.gnu.org/licenses/>.
#

EXIT_SUCCESS=0;
EXIT_FAILURE=1;
EXIT_IGNORE=77;

TMP="tmp";

CMP="cmp";

test_path()
{ 
	FILENAME=$1;
	FULLPATH=$2;

	mkdir ${TMP};
	cd ${TMP};

	echo ${FULLPATH} > input;

	../${BFIO_TEST_PATH} ${FILENAME} > output;

	RESULT=$?;

cat input output;

	if test ${RESULT} -eq ${EXIT_SUCCESS};
	then
		if ! ${CMP} -s input output;
		then
			RESULT=${EXIT_FAILURE};
		fi
	fi

	cd ..;
	rm -rf ${TMP};

	echo -n "Testing full path: ${FILENAME} ";

	if test ${RESULT} -ne ${EXIT_SUCCESS};
	then
		echo " (FAIL)";
	else
		echo " (PASS)";
	fi
	return ${RESULT};
}

BFIO_TEST_PATH="bfio_test_path";

if ! test -x ${BFIO_TEST_PATH};
then
	BFIO_TEST_PATH="bfio_test_path.exe";
fi

if ! test -x ${BFIO_TEST_PATH};
then
	echo "Missing executable: ${BFIO_TEST_PATH}";

	exit ${EXIT_FAILURE};
fi

rm -rf ${TMP};

if ! test_path "user/test.txt" "${PWD}/tmp/user/test.txt"
then
	exit ${EXIT_FAILURE};
fi

if ! test_path "username/../user/test.txt" "${PWD}/tmp/user/test.txt"
then
	exit ${EXIT_FAILURE};
fi

if ! test_path "/home/user/test.txt" "/home/user/test.txt"
then
	exit ${EXIT_FAILURE};
fi

if ! test_path "/home/username/../user/test.txt" "/home/user/test.txt"
then
	exit ${EXIT_FAILURE};
fi

if ! test_path "/../home/user/test.txt" "/home/user/test.txt"
then
	exit ${EXIT_FAILURE};
fi

if ! test_path "/../home/username/../user/test.txt" "/home/user/test.txt"
then
	exit ${EXIT_FAILURE};
fi

exit ${EXIT_SUCCESS};

