cmake_minimum_required(VERSION 3.10)
project(rtmp_ingest)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBRTMP REQUIRED librtmp)

include_directories(${LIBRTMP_INCLUDE_DIRS})
link_directories(${LIBRTMP_LIBRARY_DIRS})

add_executable(rtmp_ingest main.c)
target_link_libraries(rtmp_ingest ${LIBRTMP_LIBRARIES})
