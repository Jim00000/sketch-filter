cmake_minimum_required (VERSION 3.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package (Qt5Widgets REQUIRED)

include_directories (include/)
add_subdirectory (src/)