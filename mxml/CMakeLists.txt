
cmake_minimum_required (VERSION 3.0)

project (MXML)

include (cmake-flags.cmake)
include (cmake-check.cmake)

aux_source_directory(. SRC_MXML)

add_library(mxml STATIC ${SRC_MXML})
if (HAVE_PTHREAD_H)
target_link_libraries (mxml pthread)
endif (HAVE_PTHREAD_H)