cmake_minimum_required (VERSION 3.0)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package (Qt5Widgets REQUIRED)

include_directories (include/)
qt5_wrap_cpp (QT5_MOC include/ani_window.hpp)

add_executable (ani-qt ani_qt.cpp ani_window.cpp ${QT5_MOC})
target_link_libraries (ani-qt Qt5::Widgets sketch-filter-lib ${OpenCV_LIBS})