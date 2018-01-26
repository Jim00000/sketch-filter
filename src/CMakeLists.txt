cmake_minimum_required (VERSION 3.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
if (CMAKE_BUILD_TYPE MATCHES Release)
    set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif ()

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library (sketch-filter-lib filter.cpp maximum_filter.cpp sketch_filter.cpp edge_feature_filter.cpp animation_filter.cpp)
add_executable (sketch-filter-edge main_edge.cpp)
add_executable (sketch-filter-ani main_ani.cpp)
target_link_libraries (sketch-filter-edge sketch-filter-lib ${OpenCV_LIBS})
target_link_libraries (sketch-filter-ani sketch-filter-lib ${OpenCV_LIBS})