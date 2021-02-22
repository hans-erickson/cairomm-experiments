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

#include "text_object_impl.h"


namespace fref
{
    text_object::impl_t::impl_t(Cairo::RefPtr<Cairo::Context> cr_,
                                const std::string& text_,
                                const font_t& font_)
        : cr(cr_), text(text_), font(font_)
    {
        cr->get_matrix(matrix);
        calculate_extents();
    }

    void
    text_object::impl_t::calculate_extents()
    {
        Cairo::TextExtents te;
        cr->save();
        cr->select_font_face(font.name.c_str(),
                             Cairo::FontSlant::FONT_SLANT_NORMAL,
                             Cairo::FontWeight::FONT_WEIGHT_NORMAL);
        cr->set_font_size(font.size);
        cr->get_text_extents(text, te);
        cr->restore();

        matrix.transform_point(te.x_bearing, te.y_bearing);
        matrix.transform_point(te.width, te.height);
        extents = { te.x_bearing, te.y_bearing, te.width, te.height };
    }

    text_object::text_object(context& ctx,
                             const std::string& text,
                             const font_t& font)
        : _impl(std::make_unique<impl_t>(ctx._impl->cctx, text, font))
    {
        // select font
    }

    text_object::~text_object() = default;

    void
    text_object::_draw()
    {
        _impl->cr->save();
        _impl->cr->set_matrix(_impl->matrix);
        _impl->cr->move_to(0.0, 0.0);
        _impl->cr->select_font_face(_impl->font.name.c_str(),
                                    Cairo::FontSlant::FONT_SLANT_NORMAL,
                                    Cairo::FontWeight::FONT_WEIGHT_NORMAL);
        _impl->cr->set_font_size(_impl->font.size);
        _impl->cr->show_text(_impl->text);
        _impl->cr->restore();
    }

    extents_t
    text_object::_get_extents() const
    {
        return _impl->extents;
    }

    void
    text_object::_rotate(double angle)
    {
        _impl->matrix.rotate(angle);
        _impl->calculate_extents();
    }

    void
    text_object::_scale(scale2d_t factor)
    {
        _impl->matrix.scale(factor.s_x, factor.s_y);
        _impl->calculate_extents();
    }

    void
    text_object::_set_color(rgba_t color)
    {
        _impl->color = color;
        _impl->calculate_extents();
    }
        
    void
    text_object::_translate(delta2d_t pt)
    {
        _impl->matrix.translate(pt.d_x, pt.d_y);
        _impl->calculate_extents();
    }

    // TODO: Move this elsewhere
    //auto context = fref::create_context(cr);

    template<typename NativeContext>
    std::shared_ptr<context>
    create_context(NativeContext& nctx)
    {
        return std::move(std::make_unique<Cairo::Context>({nctx}));
    }

    /*
    template<>
    std::unique_ptr<context>&&
    create_context(Cairo::Context& ctx)
    {
        return std::move(std::unique_ptr<CairoContext>({ctx});
    }
    */
}
