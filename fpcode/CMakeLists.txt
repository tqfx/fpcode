
cmake_minimum_required(VERSION 3.10)

project(FPCODE)

include(../cmake-flags.cmake)

include_directories("../md5")

add_library(fpcode STATIC fpcode.c fpcode-private.c)
target_include_directories(fpcode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(fpcode INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../md5)

add_library(fpcodex STATIC fpcodex.c fpcode-private.c)
target_include_directories(fpcodex INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(fpcodex INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../md5)
