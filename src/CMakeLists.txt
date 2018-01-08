cmake_minimum_required (VERSION 3.0)

if (CMAKE_BUILD_TYPE MATCHES DEBUG)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
elseif (CMAKE_BUILD_TYPE MATCHES RELEASE)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library (sketch-filter-lib filter.cpp maximum_filter.cpp sketch_filter.cpp edge_feature_filter.cpp animation_filter.cpp)
add_executable (test-sketch-filter main.cpp)
target_link_libraries (test-sketch-filter sketch-filter-lib ${OpenCV_LIBS})