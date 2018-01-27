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