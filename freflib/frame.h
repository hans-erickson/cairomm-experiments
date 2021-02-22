//
//  MIT License
//  
//  Copyright (c) 2021 Hans Erickson
//  
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//  
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//  
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//  

#if !defined(FREF_FRAME_H)
#define FREF_FRAME_H

#include <cairomm/cairomm.h>

#include <memory>
#include <string>
#include <utility>

namespace fref
{
    struct rgba
    {
        double r = 0.0;
        double g = 0.0;
        double b = 0.0;
        double a = 0.0;
    };

    using point2d = std::pair<double, double>;

    class Frame
    {
    public:
        Frame(Cairo::RefPtr<Cairo::Context> cr,
              const std::string& frame_format = "frame-%06d.png");

        ~Frame();

        void
        clear();

        void
        draw_edge();

        void
        draw_text(const std::string& text, point2d xy = {0.0, 0.0});

        void
        fade(double fade_value);

        void
        fade(const rgba& color);

        point2d
        get_center() const;

        double
        get_height() const;

        double
        get_width() const;

        void
        move_to(point2d pt);

        void
        pop_group_to_source();

        void
        push_group();

        void
        rotate(double angle);

        void
        scale(double scale_xy);

        void
        scale(double scale_x, double scale_y);

        void
        select_font(const std::string& font_name, int text_size);

        void
        set_background(const rgba& color);

        void
        translate(point2d pt);

        void
        write_next_frame();

        void
        write_next_frame(const rgba& color);

        void
        zoom(double scale);

    private:
        struct Implementation;
        std::unique_ptr<Implementation> _impl;
    };
}

#endif // FREF_FRAME_H
