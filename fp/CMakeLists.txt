cmake_minimum_required(VERSION 3.10)

project(FP)

include(../cmake-flags.cmake)

include_directories("../klib")
include_directories("../cJSON")
include_directories("../mxml")
include_directories("../fpcode")
include_directories("../md5")

aux_source_directory(. SOURCE_FP)

add_library(fp STATIC ${SOURCE_FP})

target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../md5)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../klib)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../fpcode)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../cJSON)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../mxml)
