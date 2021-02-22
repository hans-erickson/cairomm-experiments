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

#if !defined(FREF_GRAPHICS_OBJECT_H)
#define FREF_GRAPHICS_OBJECT_H

#include "types.h"

#include <memory>

namespace fref
{
    struct context;
    
    class graphics_object
    {
    public:
        virtual ~graphics_object() = default;

        void
        draw()
        {
            _draw();
        }

        point2d_t
        get_center() const
        {
            auto ext = _get_extents();
            return { ext.ul.x + (ext.lr.x - ext.ul.x) / 2,
                     ext.ul.y + (ext.lr.y - ext.ul.y) / 2 };
        }

        extents_t
        get_extents() const
        {
            return _get_extents();
        }

        double
        get_height() const
        {
            auto ext = _get_extents();
            return ext.lr.y - ext.ul.y;
        }

        double
        get_width() const
        {
            auto ext = _get_extents();
            return ext.lr.x - ext.ul.x;
        }

        void
        rotate(double angle)
        {
            _rotate(angle);
        }

        void
        scale(double xy_factor)
        {
            _scale({xy_factor, xy_factor});
        }

        void
        scale(scale2d_t factor)
        {
            _scale(factor);
        }

        void
        set_color(rgba_t color)
        {
            _set_color(color);
        }

        void
        translate(point2d_t pt)
        {
            delta2d_t d { pt.x, pt.y };
            _translate(d);
        }
        
        void
        translate(delta2d_t pt)
        {
            _translate(pt);
        }

    private:
        virtual void
        _draw() = 0;

        virtual extents_t
        _get_extents() const = 0;

        virtual void
        _rotate(double angle) = 0;

        virtual void
        _scale(scale2d_t zoom) = 0;

        virtual void
        _set_color(rgba_t color) = 0;
        
        virtual void
        _translate(delta2d_t pt) = 0;
    };
}

#endif // FREF_GRAPHICS_OBJECT_H
