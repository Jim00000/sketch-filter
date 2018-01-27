#include <QApplication>
#include "ani_window.hpp"

using namespace sketch::gui;

int main(int argc, char* argv[])
{

    QApplication app(argc, argv);

    AniWindow window;

    QSize window_size(820, 780);
    window.resize(window_size);
    window.setWindowTitle("animation filter");
    window.setMaximumSize(window_size);
    window.setMinimumSize(window_size);
    window.show();

    return app.exec();
}