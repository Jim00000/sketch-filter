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
#include "edge_feature_filter.hpp"
#include "animation_filter.hpp"

using namespace sketch;
using namespace cv;

int main(int argc, char* argv[])
{
    // edge_feature_filter edge("../Lenna.png", 3, 180);
    animation_filter ani("../Lenna.png", 5, 0.75);
    namedWindow("Display window", WINDOW_AUTOSIZE);
    imshow("Display window", ani.src());
    // imshow("Display window", edge.src());
    waitKey(0);
    return 0;
}