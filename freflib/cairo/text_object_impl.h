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

#if !defined(FREF_TEXT_OBJECT_IMPL_H)
#define FREF_TEXT_OBJECT_IMPL_H

#include "../text_object.h"

#include "context_impl.h"

namespace fref
{
    struct text_object::impl_t
    {
        impl_t(Cairo::RefPtr<Cairo::Context> cr_,
               const std::string& text_,
               const font_t& font_);

        void
        calculate_extents();

        Cairo::RefPtr<Cairo::Context> cr;
        Cairo::Matrix matrix;
        std::string text;
        font_t font;
        rgba_t color;
        extents_t extents;
    };
}

#endif // FREF_TEXT_OBJECT_IMPL_H
