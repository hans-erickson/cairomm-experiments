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

#if !defined(FREF_TYPES_H)
#define FREF_TYPES_H

namespace fref
{
    struct delta2d_t
    {
        double d_x { 0.0 };
        double d_y { 0.0 };
    };
    
    struct point2d_t
    {
        double x { 0.0 };
        double y { 0.0 };
    };

    struct extents_t
    {
        point2d_t ul;
        point2d_t lr;
    };

    struct rgba_t
    {
        double r { 0.0 };
        double g { 0.0 };
        double b { 0.0 };
        double a { 0.0 };
    };

    struct scale2d_t
    {
        double s_x { 1.0 };
        double s_y { 1.0 };
    };
}

#endif // FREF_TYPES_H
