cmake_minimum_required(VERSION 3.27)
project(libbfio)

add_library(libbfio STATIC
../libbfio/libbfio_error.c
../libbfio/libbfio_file.c
../libbfio/libbfio_file_io_handle.c
../libbfio/libbfio_file_pool.c
../libbfio/libbfio_file_range.c
../libbfio/libbfio_file_range_io_handle.c
../libbfio/libbfio_handle.c
../libbfio/libbfio_memory_range.c
../libbfio/libbfio_memory_range_io_handle.c
../libbfio/libbfio_pool.c
../libbfio/libbfio_support.c
../libbfio/libbfio_system_string.c)

target_include_directories(libbfio PRIVATE 
../include
../include/libbfio
../common
../../libcerror/include
../../libcdata/include
../../libcdata/include/libcdata
../../libcfile/include
../../libclocale/include
../../libcpath/include
../../libcthreads/include
../../libuna/include)
