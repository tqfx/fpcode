
cmake_minimum_required (VERSION 3.0)

project (CJSON)

include (../cmake_flags.cmake)

aux_source_directory(. SRC_CJSON)

add_library(cjson STATIC ${SRC_CJSON})
