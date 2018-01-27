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

#include <omp.h>
#include "animation_filter.hpp"

#define fsrc() filter::src()
#define msrc() maximum_filter::src()
#define ssrc() sketch_filter::src()

using namespace sketch;
using namespace cv;

template<typename T>
inline T tau_function(const T x, const T M) __attribute__((always_inline));

template<typename T>
inline T tau_function(const T x, const T M)
{
    return (x > M) ? M : x;
}

template<>
inline Vec3b tau_function<Vec3b>(const Vec3b x, const Vec3b M)
{
    return Vec3b(tau_function(x[0], M[0]), tau_function(x[1], M[1]), tau_function(x[2], M[2]));
}

animation_filter::animation_filter(const std::string filename,
                                   const uint alpha, const float beta) : sketch_filter(filename, alpha), _beta(beta)
{
    Mat ani_filter(fsrc().rows, fsrc().cols, CV_8UC3);
    src() = std::move(ani_filter);
    process(filename);
}

animation_filter::animation_filter(const cv::Mat& img, const uint alpha,
                                   const float beta)  : sketch_filter(img, alpha), _beta(beta)
{
    Mat ani_filter(fsrc().rows, fsrc().cols, CV_8UC3);
    src() = std::move(ani_filter);
    process(img);
}

animation_filter::~animation_filter()
{

}

cv::Mat& animation_filter::src()
{
    return _ani_filter;
}

const float animation_filter::beta() const
{
    return _beta;
}

void animation_filter::process(const std::string filename)
{
    Mat img = imread(filename);
    process(img);
}

void animation_filter::process(const cv::Mat& img)
{
    const uchar M = sketch_filter::M();

    #pragma omp parallel for collapse(2)

    for(int r = 0; r < img.rows ; r++) {
        for(int c = 0; c < img.cols; c++) {
            Vec3b rgb = img.at<Vec3b>(r, c);
            uchar v = ssrc().at<uchar>(r, c);
            src().at<Vec3b>(r, c)[0] = tau_function(beta() * v + (1 - beta()) * rgb[0], static_cast<float>(M));
            src().at<Vec3b>(r, c)[1] = tau_function(beta() * v + (1 - beta()) * rgb[1], static_cast<float>(M));
            src().at<Vec3b>(r, c)[2] = tau_function(beta() * v + (1 - beta()) * rgb[2], static_cast<float>(M));
        }
    }
}
