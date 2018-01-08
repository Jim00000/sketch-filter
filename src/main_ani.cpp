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
#include "animation_filter.hpp"

using namespace std;
using namespace sketch;
using namespace cv;

/**
 * Usgae: sketch-filter-ani image-name [output-image-name(default : output.jpg) [alpha(default : 5) [beta(default : 0.75)] ]]]
 * alpha must be odd value
 */
int main(int argc, char* argv[])
{
    string filename;
    string outputname = "output.jpg";
    int alpha = 5;
    float beta = 0.75f;
    switch(argc) {
    case 5:
        beta = std::stof(argv[4]);
    case 4:
        alpha = std::stoi(argv[3]);
    case 3:
        outputname = string(argv[2]);
    case 2:
        filename = string(argv[1]);
        break;
    default:
        cerr << "sketch-filter-ani image-name [output-image-name(default : output.jpg) [alpha(default : 5) [beta(default : 0.75)] ]]]"
             << endl << "alpha must be odd value" << endl;
        return 0;
    }

    animation_filter ani(filename, alpha, beta);
    imwrite(outputname, ani.src());
    return 0;
}