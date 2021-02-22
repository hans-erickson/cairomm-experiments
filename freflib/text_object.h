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

#if !defined(FREF_TEXT_OBJECT_H)
#define FREF_TEXT_OBJECT_H

#include "context.h"
#include "graphics_object.h"

#include <memory>
#include <string>

namespace fref
{
    struct font_t
    {
        std::string name;
        // TODO: Slant or whatever
        int size { 10 };
    };
    
    class text_object
        : public graphics_object
    {
    public:
        text_object(context& context,
                    const std::string& text = "",
                    const font_t& font = {});

        ~text_object() override;
        
    private:
        void
        _draw() override;

        extents_t
        _get_extents() const override;

        void
        _rotate(double angle) override;

        void
        _scale(scale2d_t zoom) override;

        void
        _set_color(rgba_t color) override;
        
        void
        _translate(delta2d_t pt) override;

        struct impl_t;
        std::unique_ptr<impl_t> _impl;
    };
}

#endif // FREF_TEXT_OBJECT_H
