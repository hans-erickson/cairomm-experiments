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

#if !defined(FREF_CONTEXT_IMPL_H)
#define FREF_CONTEXT_IMPL_H

#include "../context.h"

#include "image_impl.h"

#include <cairomm/cairomm.h>

namespace fref
{
    namespace impl {}

    /*
    struct cairo_context_impl_t
    {
        static std::shared_ptr<Cairo::Context>
        get_cairo_context(fref::context& context)
        {
        }

        std::shared_ptr<Cairo::Context>
        virtual get_cairo_context(cairo_context_impl_t* impl) = 0;
    };
    */
    
    struct context::impl_t
    {
        impl_t(Cairo::RefPtr<Cairo::ImageSurface> surface_);

            
        Cairo::RefPtr<Cairo::Context> cctx;

        /*
        static Cairo::RefPtr<Cairo::Context>
        get_cairo_context(fref::context& ctx)
        {
            return ctx._impl->context;
        }
        */
    };

    /*
    struct impl_accessor
    {
        static Cairo::RefPtr<Cairo::Context>
        get_cairo_context(fref::context& context)
        {
            return context::impl_t::get_cairo_context(context);
        }
    };
    */

    namespace impl
    {
        /*
        std::shared_ptr<Cairo::Context> get_cairo_context(fref::context::impl_t)
        {
            //fref::context::_impl& impl = *reinterpret_cast<fref::context::_impl*>(impl_ptr);
            //return ctx._impl.context;
        }
        */
    }


}

#endif // FREF_CONTEXT_IMPL_H
