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

#ifndef _ANIMATION_FILTER_HPP_
#define _ANIMATION_FILTER_HPP_

#include <string>
#include "IFilter.hpp"
#include "sketch_filter.hpp"

namespace sketch
{
    class animation_filter : public IFilter
    {
    public:
        animation_filter(const uint alpha = 5, const float beta = 0.5f);

        virtual ~animation_filter();

        virtual void process(cv::Mat& src, cv::Mat& dst) override;

    private:
        float _beta;
        sketch::sketch_filter _sketch_filter;
    };
}

#endif