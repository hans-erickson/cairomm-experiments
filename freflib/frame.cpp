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

#include "frame.h"

#include <iostream> // TODO: Remove!

namespace fref
{
    struct Frame::Implementation
    {
        struct State
        {
            State(Implementation& impl)
                : _impl(impl)
            {
                _impl._cr->save();
            }

            ~State()
            {
                _impl._cr->restore();
            }

            Implementation& _impl;
        };


        Implementation(Cairo::RefPtr<Cairo::Context> cr,
                       const std::string& frame_format)
            : _cr(cr),
              _frame_format(frame_format)
        {
            _cr->save();
            _cr->set_identity_matrix();
            _cr->get_clip_extents(_upper_left_x, _upper_left_y,
                                  _lower_right_x, _lower_right_y);
            auto center = get_center();
            _cr->restore();
        }

        std::pair<double, double>
        get_center() const
        {
            return { get_width() / 2.0, get_height() / 2.0 };
        }

        double
        get_height() const
        {
            return _lower_right_y - _upper_left_y;
        }

        double
        get_width() const
        {
            return _lower_right_x - _upper_left_x;
        }

        void
        increment_frame()
        {
            ++_index;
        }

        State
        save()
        {
            return State(*this);
        }

        void
        write_next_frame(Cairo::RefPtr<Cairo::Surface> surface)
        {
            char filename[256];
            std::snprintf(filename, sizeof(filename), _frame_format.c_str(), _index);
            increment_frame();
            surface->write_to_png(filename);
        }

        double _upper_left_x  = 0.0;
        double _upper_left_y  = 0.0;
        double _lower_right_x = 0.0;
        double _lower_right_y = 0.0;
        int _index = 0;
        std::string _frame_format;

        Cairo::RefPtr<Cairo::Context> _cr;
    };

    Frame::Frame(Cairo::RefPtr<Cairo::Context> cr,
                 const std::string& frame_format)
        : _impl(std::make_unique<Implementation>(cr, frame_format))
    {
    }

    Frame::~Frame() = default;

    void
    Frame::clear()
    {
        auto raii(_impl->save());

        _impl->_cr->set_source_rgba(0.0, 0.0, 0.0, 0.0);
        _impl->_cr->set_operator(Cairo::Operator::OPERATOR_CLEAR);
        _impl->_cr->paint();
    }

    void
    Frame::draw_text(const std::string& text, point2d xy)
    {
        auto raii(_impl->save());

        move_to(xy);
        _impl->_cr->set_source_rgb(0, 0, 0);
        _impl->_cr->show_text(text);
    }

    void
    Frame::fade(double fade_value)
    {
        fade({0.0, 0.0, 0.0, fade_value});
    }

    void
    Frame::fade(const rgba& color)
    {
        auto raii(_impl->save());

        _impl->_cr->set_source_rgba(color.r, color.g, color.b, color.a);
        _impl->_cr->set_operator(Cairo::Operator::OPERATOR_ATOP);
        _impl->_cr->paint();
    }

    std::pair<double, double>
    Frame::get_center() const
    {
        return _impl->get_center();
    }

    double
    Frame::get_height() const
    {
        return _impl->get_height();
    }

    double
    Frame::get_width() const
    {
        return _impl->get_width();
    }

    void
    Frame::move_to(point2d pt)
    {
        _impl->_cr->move_to(pt.first, pt.second);
    }

    void
    Frame::pop_group_to_source()
    {
        _impl->_cr->pop_group_to_source();
    }

    void
    Frame::push_group()
    {
        _impl->_cr->push_group();
    }

    void
    Frame::rotate(double angle)
    {
        _impl->_cr->rotate(angle);
    }

    void
    Frame::scale(double scale_xy)
    {
        scale(scale_xy, scale_xy);
    }

    void
    Frame::scale(double scale_x, double scale_y)
    {
        _impl->_cr->scale(scale_x, scale_y);
    }

    void
    Frame::select_font(const std::string& font_name, int text_size)
    {
        _impl->_cr->select_font_face(font_name.c_str(), Cairo::FontSlant::FONT_SLANT_NORMAL,
                             Cairo::FontWeight::FONT_WEIGHT_NORMAL);
        _impl->_cr->set_font_size(text_size);
    }

    void
    Frame::set_background(const rgba& color)
    {
        _impl->_cr->set_source_rgba(color.r, color.g, color.b, color.a);
        _impl->_cr->set_operator(Cairo::Operator::OPERATOR_DEST_OVER);
        _impl->_cr->paint();
    }

    void
    Frame::translate(point2d pt)
    {
        _impl->_cr->translate(pt.first, pt.second);
    }

    void
    Frame::write_next_frame()
    {
        _impl->write_next_frame(_impl->_cr->get_target());
    }

    void
    Frame::write_next_frame(const rgba& background)
    {
        _impl->_cr->push_group();
        _impl->_cr->set_identity_matrix();
        _impl->_cr->set_source(_impl->_cr->get_target(), 0.0, 0.0);
        _impl->_cr->set_operator(Cairo::Operator::OPERATOR_SOURCE);
        _impl->_cr->paint();
        set_background(background);
        _impl->write_next_frame(_impl->_cr->get_group_target());
        _impl->_cr->pop_group();
    }

    void
    Frame::zoom(double scale_xy)
    {
        _impl->_cr->push_group();
        _impl->_cr->set_identity_matrix();
        scale(scale_xy);
        double x_offset = get_width() * (1.0 - scale_xy) / 2.0;
        double y_offset = get_height() * (1.0 - scale_xy) / 2.0;
        _impl->_cr->set_source(_impl->_cr->get_target(), x_offset, y_offset);
        _impl->_cr->set_operator(Cairo::Operator::OPERATOR_SOURCE);
        _impl->_cr->paint();
        _impl->_cr->pop_group_to_source();
        clear();
        _impl->_cr->paint();
    }
}
