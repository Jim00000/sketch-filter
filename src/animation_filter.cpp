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

animation_filter::animation_filter(const uint alpha,
                                   const float beta)  : _sketch_filter(alpha)
{
    _beta = beta;
}

animation_filter::~animation_filter()
{

}

void animation_filter::process(cv::Mat& src, cv::Mat& dst)
{
    Mat gray_src;
    cvtColor(src, gray_src, CV_BGR2GRAY);

    _sketch_filter.process(gray_src, dst);

    Mat ani_filter(src.rows, src.cols, src.type());

    #pragma omp parallel for collapse(2)
    for(int r = 0; r < src.rows ; r++) {
        for(int c = 0; c < src.cols; c++) {
            Vec3b rgb = src.at<Vec3b>(r, c);
            uchar v = dst.at<uchar>(r, c);
            ani_filter.at<Vec3b>(r, c)[0] = tau_function(_beta * v + (1 - _beta) * rgb[0], 255.0f);
            ani_filter.at<Vec3b>(r, c)[1] = tau_function(_beta * v + (1 - _beta) * rgb[1], 255.0f);
            ani_filter.at<Vec3b>(r, c)[2] = tau_function(_beta * v + (1 - _beta) * rgb[2], 255.0f);
        }
    }

    dst = std::move(ani_filter);
}
