cmake_minimum_required (VERSION 3.0)

qt5_wrap_cpp (
    QT5_MOC 
    ../include/ani_window.hpp
)

qt5_wrap_cpp (
    QT5_MOC_1 
    ../include/ani_window.hpp
    ../include/edge_window.hpp
)

add_executable (ani-qt ani_qt.cpp ani_window.cpp ${QT5_MOC})
add_executable (edge-qt edge_qt.cpp edge_window.cpp ani_window.cpp ${QT5_MOC_1})
target_link_libraries (ani-qt Qt5::Widgets sketch-filter-lib ${OpenCV_LIBS})
target_link_libraries (edge-qt Qt5::Widgets sketch-filter-lib ${OpenCV_LIBS})