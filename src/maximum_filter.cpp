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
#include "maximum_filter.hpp"

using namespace std;
using namespace sketch;
using namespace cv;

template<typename T>
inline T adjust_zero_above(T value) __attribute__((always_inline));

template<typename T>
inline T adjust_bound_below(T value, T bound) __attribute__((always_inline));

maximum_filter::maximum_filter(const uint alpha) : _alpha(alpha)
{
}

maximum_filter::~maximum_filter()
{
}

void
maximum_filter::process(cv::Mat& src, cv::Mat& dst)
{
    Mat max_filter(src.rows, src.cols, src.type());
    const int half_length = static_cast<int>(_alpha) / 2;

    #pragma omp parallel for collapse(2)
    for(int r = 0; r < src.rows ; r++) {
        for(int c = 0; c < src.cols; c++) {
            double maxVal = 0.0;
            int row_start = adjust_zero_above(r - half_length);
            int row_end = adjust_bound_below(r + half_length + 1, src.rows);
            int col_start = adjust_zero_above(c - half_length);
            int col_end = adjust_bound_below(c + half_length + 1, src.cols);
            Mat mask = src.rowRange(row_start, row_end).colRange(col_start, col_end);
            minMaxLoc(mask, nullptr, &maxVal);

            // If maxVal is zero then set it to one to avoid divide by zero exception
            if(maxVal == 0) {
                max_filter.at<uchar>(r, c) = 1;

            } else {
                max_filter.at<uchar>(r, c) = maxVal;
            }
        }
    }

    dst = std::move(max_filter);
}

template<typename T>
inline T
adjust_zero_above(T value)
{
    return value >= 0 ? value : 0;
}

template<typename T>
inline T
adjust_bound_below(T value, T bound)
{
    return value < bound ? value : bound - static_cast<T>(1);
}