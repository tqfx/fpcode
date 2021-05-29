
cmake_minimum_required (VERSION 3.10)

project (FP)

if (NOT CMAKE_BUILD_TYPE)
set (CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

include (cmake/cmake-flags.cmake)

include_directories (
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/md5"
    "${PROJECT_SOURCE_DIR}/klib"
    "${PROJECT_SOURCE_DIR}/cJSON"
    "${PROJECT_SOURCE_DIR}/mxml"
    "${PROJECT_SOURCE_DIR}/fpcode"
    "${PROJECT_SOURCE_DIR}/fp"
    "${PROJECT_SOURCE_DIR}/app"
)

add_subdirectory (md5)
add_subdirectory (klib)
add_subdirectory (cJSON)
add_subdirectory (fpcode)
add_subdirectory (fp)
add_subdirectory (app)
add_subdirectory (mxml)

add_executable (key main.c)
target_link_libraries (key
    app
    fpcodex
    fp
    mxml
    cjson
    klib
    md5
)
if (MINGW AND HAVE_PTHREAD_H)
target_link_libraries (key -static winpthread)
endif (MINGW AND HAVE_PTHREAD_H)

add_executable (key2 main.c)
target_link_libraries (key2
    app
    fpcode
    fp
    mxml
    cjson
    klib
    md5
)
if (MINGW AND HAVE_PTHREAD_H)
target_link_libraries (key2 -static winpthread)
endif (MINGW AND HAVE_PTHREAD_H)

if (WIN32 OR ANDROID)
install (TARGETS key RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install (TARGETS key2 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif (WIN32 OR ANDROID)

# termux
if (ANDROID)

include_directories (
    "${PROJECT_SOURCE_DIR}/termux-api"
    "${PROJECT_SOURCE_DIR}/app-termux"
)

add_subdirectory (termux-api)
add_subdirectory (app-termux)

add_executable (key.exe main-termux.c)
target_link_libraries (key.exe
    app-termux
    termux-api
    fpcodex
    fp
    klib
    cjson
    mxml
    md5
)

add_executable (key2.exe main-termux.c)
target_link_libraries (key2.exe
    app-termux
    termux-api
    fpcode
    fp
    klib
    cjson
    mxml
    md5
)

install (TARGETS key.exe RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install (TARGETS key2.exe RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

endif (ANDROID)

