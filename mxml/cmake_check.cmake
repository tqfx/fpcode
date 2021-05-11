include (CheckIncludeFiles)
include (CheckFunctionExists)
include (CheckSymbolExists)
include (CheckTypeSize)

if (CMAKE_COMPILER_IS_GNUCC AND CMAKE_COMPILER_IS_GNUCXX)
add_definitions (-D_GNU_SOURCE)
endif (CMAKE_COMPILER_IS_GNUCC AND CMAKE_COMPILER_IS_GNUCXX)

# Version number...
set (MXML_VERSION "Mini-XML v3.2")

# Do we have threading support?
check_include_files ("pthread.h" HAVE_PTHREAD_H)

if (HAVE_PTHREAD_H)
add_definitions (-D_THREAD_SAFE)
add_definitions (-D_REENTRANT)
endif (HAVE_PTHREAD_H)

# Inline function support...

# Long long support...  
check_type_size ("long long int" HAVE_LONG_LONG)

# Do we have the *printf() functions?
check_function_exists (snprintf HAVE_SNPRINTF)
check_function_exists (vasprintf HAVE_VASPRINTF)
check_function_exists (vsnprintf HAVE_VSNPRINTF)

# Do we have the strXXX() functions?
check_function_exists (strdup HAVE_STRDUP)
check_function_exists (strlcat HAVE_STRLCAT)
check_function_exists (strlcpy HAVE_STRLCPY)

configure_file (
    "${PROJECT_SOURCE_DIR}/config.h.in"
    "${PROJECT_BINARY_DIR}/config.h"
)

include_directories (
    "${PROJECT_BINARY_DIR}"
)
