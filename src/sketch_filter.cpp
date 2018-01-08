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

#include "sketch_filter.hpp"

#define fsrc() filter::src()
#define msrc() maximum_filter::src()

using namespace sketch;
using namespace cv;

sketch_filter::sketch_filter(const std::string filename,
                             const uint alpha) : maximum_filter(filename, alpha)
{
    Mat sketch_filter(msrc().rows, msrc().cols, msrc().type());
    src() = std::move(sketch_filter);
    process();
}

sketch_filter::~sketch_filter()
{

}

cv::Mat& sketch_filter::src()
{
    return _sketch_filter;
}

const uchar sketch_filter::M() const
{
    return _M;
}

void sketch_filter::process()
{
    for(int r = 0; r < fsrc().rows ; r++) {
        for(int c = 0; c < fsrc().cols; c++) {
            src().at<uchar>(r, c) = M() * fsrc().at<uchar>(r, c) / msrc().at<uchar>(r, c);
        }
    }
}