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

#ifndef _SKETCH_FILTER_HPP_
#define _SKETCH_FILTER_HPP_

#include <string>
#include "IFilter.hpp"
#include "maximum_filter.hpp"

namespace sketch
{
    class sketch_filter : public IFilter
    {
    public:
        sketch_filter(const uint alpha = 5);
        
        virtual ~sketch_filter();

        virtual void process(cv::Mat& src, cv::Mat& dst) override;

    private:
        const static uchar _M = 255;
        sketch::maximum_filter _max_filter;
    };
}

#endif