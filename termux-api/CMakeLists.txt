cmake_minimum_required(VERSION 3.10)

project(TERMUX_API)

include(../cmake/cmake-flags.cmake)

include_directories("../klib")
include_directories("../cJSON")

aux_source_directory(. SOURCE_TERMUX_API)

add_library(termux-api STATIC ${SOURCE_TERMUX_API})

target_include_directories(termux-api INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(termux-api INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../klib)
target_include_directories(termux-api INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../cJSON)
