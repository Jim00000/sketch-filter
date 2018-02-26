/**
 * The sketch filter based on "Sketch filter for feature extraction and
 * rendering applications, G. Kim, T. Kim, D.-H. Lim and C. Yim"
 *
 * Copyright (C) 2018  Jim00000
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <string>
#include <QFileDialog>
#include "edge_window.hpp"
#include "edge_feature_filter.hpp"

using namespace cv;
using namespace sketch;
using namespace sketch::gui;

EdgeWindow::EdgeWindow(QWidget* parent) : AniWindow(parent)
{
    threshold = 0;
    beta_slider->setMaximum(255);
    disconnect(beta_slider.get(), &QSlider::valueChanged, this, &AniWindow::change_beta_event);
    connect(beta_slider.get(), &QSlider::valueChanged, this, &EdgeWindow::change_threshold_event);
}

EdgeWindow::~EdgeWindow()
{

}

void EdgeWindow::change_threshold_event(const int value)
{
    threshold = value;
    generate_image_event();
}

void EdgeWindow::generate_image_event()
{
    if(isImageRead == true) {
        genBtn->setEnabled(false);
        edge_feature_filter edge(alpha, threshold);
        edge.process(src_image, dst_image);
        image->setPixmap(QPixmap::fromImage(QImage(dst_image.data, dst_image.cols, dst_image.rows, dst_image.step,
                                            QImage::Format_Grayscale8)));
        image->setScaledContents(true);
        image->show();
        genBtn->setEnabled(true);

        isOutput = true;
    }
}