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

//#include "freflib/graphics_object.h"
//#include "freflib/factory.h"
#include "freflib/context.h"
#include "freflib/text_object.h"

#include <cairomm/cairomm.h>
#include <iostream>

/*
namespace
{
    // Frame transform properties
    //   Background
    //     Color - fill
    //     Translate - relative to previous frame
    //     Rotate - relative to previous frame
    //     Scale - relative to previous frame
    //   Foreground object
    //     Color - stroke color
    //     Location
    //     Scale
    //     Rotate
    

    // Frame transform properties
    //   zoom - zoom from previous frame
    //   fade - fade alpha from last frame
    //   rotate - foreground
    //   rotate - background
    //   color - foreground
    //   color - background
    //   translate - background
    struct frame_transform
    {
        double scale = 1.0;
        double angle = 0.0;
    };

    struct Angle
    {
        explicit
        Angle(double angle_)
            : angle(angle_)
        {
        }
            
        double angle = 0.0;
    };

    class Actor
    {
    public:
        
    };

    / *
    class KeyFrameManager
    {
    public:
        KeyFrameManager(int frames_per_second)
            : _frames_per_second(frames_per_second)
        {
        }

        void
        add_key_frame(double time,
                      Angle angle)
        {
        }

    private:
        int
        get_frame_index(double time)
        {
            return static_cast<int>(time * _frames_per_second);
        }
        
        int _frames_per_second = 0;
    };
    * /


    //effects.zoom(zoom_scale);
    //effects.fade(fade_color);
    //effects.rotate(angle);

    class Background
    {
    public:
        Background(fref::Frame& frame)
            : _frame(frame)
        {
        }

    private:
        fref::Frame& _frame;
    };
    
    void
    status(int i, int count)
    {
        std::cout << i << "/" << count << '\r' << std::flush;
    }

    struct background_actions
    {
        double zoom_scale { 1.0 };
        fref::rgba fade_color { 0.0, 0.0, 0.0, 0.0 };
        double angle { 0.0 };
    };

    void
    draw_loop(fref::Frame& effects, int count)
    {
        double zoom_scale = 1.1;
        int end_count = count * 3;
        const std::string s("Hello world!");
        fref::rgba background { 0.2, 0.2, 0.8, 1.0 };
        fref::rgba fade_color { 0.8, 0.2, 0.2, 0.3 };
        effects.translate(effects.get_center());

        int x_offset = effects.get_width() / 200.0;
        int y_offset = effects.get_height() / 20.0;
        fref::point2d offset { x_offset, y_offset };
        double angle = 2.0 * M_PI / count;

        background_actions bg_actions
            {
                1.1, { 0.8, 0.2, 0.2, 0.3 }, 0.0
            };
        
        int i = 0;
        for (i = 0; i < count; i++)
        {
            status(i, end_count);
            effects.draw_text(s, offset);

            effects.write_next_frame(background);

            effects.zoom(zoom_scale);
            effects.fade(fade_color);
            effects.rotate(angle);
        }

        double saved_alpha = fade_color.a;
        for (; i < count * 2; i++)
        {
            status(i, end_count);
            effects.draw_text(s, offset);

            effects.write_next_frame(background);

            if (i != count * 2 - 1)
            {
                effects.zoom(zoom_scale);
                effects.fade(fade_color);

                fade_color.a *= 1.05;
            }
        }

        fade_color.a = saved_alpha;
        for (; i < count * 3; i++)
        {
            zoom_scale += 0.01;

            status(i, end_count);

            effects.write_next_frame(background);
            effects.zoom(zoom_scale);
            effects.fade(fade_color);
        }
    }

    // Separate rendering into layers
    //   1. Background layer
    //   2. Previous frame layer with transparent background
    //   3. Actors (such as text)
}
*/

int main(void)
{
    /*static constexpr int width     = 1920;
      static constexpr int height    = 1080;*/

    static constexpr int width     = 640;
    static constexpr int height    = 360;
    static constexpr int text_size = height / 10;

    auto surface = Cairo::ImageSurface::create(Cairo::Format::FORMAT_ARGB32, width, height);


    fref::image img(width, height);

    fref::context ctx(img);

    fref::text_object txt(ctx, "Hello world!", { "Bitstream Vera Sans", 50});

    txt.translate(txt.get_center());

    int max = 12;
    double angle = (M_PI * 2) / max;
    for (int x = 0; x < max; ++x)
    {
        txt.rotate(angle);
        txt.draw();
    }

    img.save("stuff.png");
    //auto cr = Cairo::Context::create(surface);

    //fref::context ctx(cr);
}
