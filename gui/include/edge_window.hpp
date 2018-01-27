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

#ifndef __EDGE_WINDOW_HPP__
#define __EDGE_WINDOW_HPP__

#include "ani_window.hpp"

namespace sketch {
    namespace gui {
        class EdgeWindow : public AniWindow
        {

            Q_OBJECT

        public:
            EdgeWindow(QWidget* parent = 0);
            ~EdgeWindow();
        protected:

        private:
            int threshold;

        protected slots:
            virtual void generate_image_event() override;
            virtual void change_threshold_event(const int value);

        };
    }
}


#endif