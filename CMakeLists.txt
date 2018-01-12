cmake_minimum_required (VERSION 3.0)

set (CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS_RELEASE "-Wall -O2") 
set (CMAKE_CXX_FLAGS_DEBUG  "-Wall -O0 -g")

find_package ( OpenCV REQUIRED )
find_package ( OpenMP REQUIRED )

if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif ()

if (OpenCV_FOUND)
    include_directories(${OpenCV_INCLUDE_DIRS})
endif ()

include_directories (include/)
add_subdirectory (src/)
add_subdirectory (test/)