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

#ifndef __ANI_WINDOW_HPP__
#define __ANI_WINDOW_HPP__

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSlider>
#include <opencv2/opencv.hpp>

namespace sketch {
    namespace gui {
        class AniWindow : public QWidget
        {

            Q_OBJECT

        public:
            AniWindow(QWidget* parent = 0);
            ~AniWindow();
        protected:

        private:
            QLabel* image;
            QPushButton* loadBtn;
            QPushButton* genBtn;
            QPushButton* saveBtn;
            QLineEdit* imagepath;
            QSlider* alpha_slider;
            QSlider* beta_slider;
            cv::Mat src_image;
            cv::Mat dst_image;
            int alpha;
            float beta;
            bool isImageRead;
            bool isOutput;

        private slots:
            void load_image_path_event();
            void save_image_event();
            void generate_image_event();
            void change_alpha_event(const int value);
            void change_beta_event(const int value);
        };
    }
}


#endif