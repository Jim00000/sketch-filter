cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_BUILD_TYPE DEBUG)
set (CMAKE_CXX_FLAGS_RELEASE "-Wall -O2") 
set (CMAKE_CXX_FLAGS_DEBUG  "-Wall -O0 -g")

find_package( OpenCV REQUIRED )

if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif()

include_directories (include/)
add_subdirectory (src/)
add_subdirectory (test/)