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
#include "edge_feature_filter.hpp"

#define fsrc() filter::src()
#define msrc() maximum_filter::src()
#define ssrc() sketch_filter::src()

using namespace sketch;
using namespace cv;

edge_feature_filter::edge_feature_filter(const std::string filename,
        const uint alpha, const uchar threshold) : sketch_filter(filename, alpha) , _threshold(threshold)
{
    Mat edge_feature_filter(ssrc().rows, ssrc().cols, ssrc().type());
    src() = std::move(edge_feature_filter);
    process();
}

edge_feature_filter::~edge_feature_filter()
{

}

cv::Mat& edge_feature_filter::src()
{
    return _edge_feature_filter;
}

void edge_feature_filter::process()
{
    #pragma omp parallel for collapse(2)
    for(int r = 0; r < fsrc().rows ; r++) {
        for(int c = 0; c < fsrc().cols; c++) {
            if(ssrc().at<uchar>(r, c) < _threshold) {
                src().at<uchar>(r, c) = 0;
            } else {
                src().at<uchar>(r, c) = 255;
            }
        }
    }
}