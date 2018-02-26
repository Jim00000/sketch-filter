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
#include "sketch_filter.hpp"

#define fsrc() filter::src()
#define msrc() maximum_filter::src()

using namespace sketch;
using namespace cv;

sketch_filter::sketch_filter(const uint alpha) : _max_filter(alpha)
{
}

sketch_filter::~sketch_filter()
{

}


void sketch_filter::process(cv::Mat& src, cv::Mat& dst)
{
    _max_filter.process(src, dst);
    
    #pragma omp parallel for collapse(2)
    for(int r = 0; r < src.rows ; r++) {
        for(int c = 0; c < src.cols; c++) {
            dst.at<uchar>(r, c) = _M * src.at<uchar>(r, c) / dst.at<uchar>(r, c);
        }
    }

}