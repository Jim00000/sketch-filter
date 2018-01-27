#include <string>
#include "ani_window.hpp"
#include <QFileDialog>
#include "animation_filter.hpp"

using namespace cv;
using namespace sketch;
using namespace sketch::gui;

AniWindow::AniWindow(QWidget* parent) : QWidget(parent)
{
    loadBtn = new QPushButton("Load image", this);
    loadBtn->setGeometry(10, 10, 100, 30);
    connect(loadBtn, &QPushButton::clicked, this, &AniWindow::load_image_path_event);

    imagepath = new QLineEdit(this);
    imagepath->setGeometry(110 + 10, 10, 690, 30);
    imagepath->setReadOnly(true);

    image = new QLabel(this);
    image->setGeometry(10, 50, 800, 600);
    QPixmap pixmap(500, 500);
    pixmap.fill(QColor("gray"));
    image->setPixmap(pixmap);
    image->setScaledContents(true);
    image->show();

    alpha_slider = new QSlider(Qt::Orientation::Horizontal, this);
    alpha_slider->setValue(0);
    alpha_slider->setGeometry(10, 660, 800, 30);
    alpha_slider->setMinimum(0);
    alpha_slider->setMaximum(9);
    alpha_slider->setSingleStep(1);
    alpha_slider->setTickPosition(QSlider::TickPosition::TicksAbove);
    alpha_slider->setTickInterval(1);
    connect(alpha_slider, &QSlider::valueChanged, this, &AniWindow::change_alpha_event);

    beta_slider = new QSlider(Qt::Orientation::Horizontal, this);
    beta_slider->setValue(0);
    beta_slider->setGeometry(10, 700, 800, 30);
    beta_slider->setMinimum(0);
    beta_slider->setMaximum(100);
    beta_slider->setSingleStep(1);
    beta_slider->setTickPosition(QSlider::TickPosition::TicksAbove);
    beta_slider->setTickInterval(10);
    connect(beta_slider, &QSlider::valueChanged, this, &AniWindow::change_beta_event);

    alpha = 3;
    beta = 0.0;
    isImageRead = false;
    isOutput = false;

    genBtn = new QPushButton("Generate", this);
    genBtn->setGeometry(10, 740, 100, 30);
    connect(genBtn, &QPushButton::clicked, this, &AniWindow::generate_image_event);

    saveBtn = new QPushButton("Save image", this);
    saveBtn->setGeometry(120, 740, 100, 30);
    connect(saveBtn, &QPushButton::clicked, this, &AniWindow::save_image_event);
}

AniWindow::~AniWindow()
{
    delete image;
    delete loadBtn;
    delete genBtn;
    delete saveBtn;
    delete imagepath;
    delete alpha_slider;
    delete beta_slider;
}

void AniWindow::load_image_path_event()
{
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Load an image file"), "",
                       tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;All Files (*)"));

    if (filename.isEmpty() == false) {
        imagepath->setText(filename);
        src_image = imread(filename.toUtf8().constData());
        Mat rst;
        cv::cvtColor(src_image, rst, CV_BGR2RGB);
        image->setPixmap(QPixmap::fromImage(QImage(rst.data, rst.cols, rst.rows, rst.step,
                                            QImage::Format_RGB888)));
        isImageRead = true;
    }
}

void AniWindow::save_image_event()
{
    if(isOutput == true) {
        QString filename = QFileDialog::getSaveFileName(this,
                           tr("Save an output image"), "",
                           tr("JPEG (*.jpg *.jpeg);;PNG (*.png);;All Files (*)"));

        if(filename.isEmpty() == false) {
            imwrite(filename.toUtf8().constData(), dst_image);
        }
    }
}

void AniWindow::change_alpha_event(const int value)
{
    alpha = 3 + 2 * value;
}

void AniWindow::change_beta_event(const int value)
{
    beta = value / 100.0;
}

void AniWindow::generate_image_event()
{
    if(isImageRead == true) {
        genBtn->setEnabled(false);
        animation_filter ani(src_image, alpha, beta);
        dst_image = ani.src();
        Mat rst = dst_image.clone();
        cv::cvtColor(rst, rst, CV_BGR2RGB);
        image->setPixmap(QPixmap::fromImage(QImage(rst.data, rst.cols, rst.rows, rst.step,
                                            QImage::Format_RGB888)));
        image->setScaledContents(true);
        image->show();
        genBtn->setEnabled(true);

        isOutput = true;
    }
}