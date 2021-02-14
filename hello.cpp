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

#include "freflib/frame.h"

namespace
{
    void
    draw_loop(fref::Frame& effects, int count)
    {
        const std::string s("Hello world!");
        effects.translate(effects.get_center());

        fref::point2d offset { 5.0, 100.0 };
        double angle = 2.0 * M_PI / count;
        for (int i = 0; i < count; i++)
        {
            effects.draw_text(s, offset);

            effects.write_frame(i);

            effects.zoom(1.1);
            effects.fade(0.8);

            effects.rotate(angle);
        }

        for (int i = 0; i < count; i++)
        {
            effects.draw_text(s, offset);

            effects.write_frame(i + count);

            effects.zoom(1.1);
            effects.fade(0.8);
        }

    }

    void
    initialize_context(Cairo::RefPtr<Cairo::Context> cr)
    {
        constexpr int TextSize = 100;
        cr->select_font_face("Bitstream Vera Sans", Cairo::FontSlant::FONT_SLANT_NORMAL,
                             Cairo::FontWeight::FONT_WEIGHT_NORMAL);
        cr->set_font_size(TextSize);

        cr->set_source_rgb(0.0, 0.0, 0.0);
    }
}

int main (void)
{
    static constexpr int width = 1920;
    static constexpr int height = 1080;

    auto surface = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, width, height);
    auto cr = Cairo::Context::create(surface);

    fref::Frame e(cr);
    initialize_context(cr);
    draw_loop(e, 20);
}
