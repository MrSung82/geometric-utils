/*
MIT License

Copyright (c) 2025 Marat Sungatullin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef GEOMUTILS_BASEUTL_H
#define GEOMUTILS_BASEUTL_H

#include "gebasedefs.h"
#include <limits>
#include <cmath>

// Zero
template <typename T>
constexpr inline T GeZero()
{
    return 0;
}

template <>
constexpr inline float GeZero<float>()
{
    return 0.0f;
}

template <>
constexpr inline double GeZero<double>()
{
    return 0.0;
}

// Abs
template <typename T>
constexpr inline T GeAbs(T x)
{
    return x >= 0 ? x : -x;
}

template<>
constexpr inline float GeAbs<float>(float x) 
{ 
    return reinterpret_cast<float>(std::fabs(x));
}

template<>
constexpr inline double GeAbs<double>(double x) 
{ 
    return std::fabs(x);
}

namespace ge
{
    template <typename T>
    constexpr inline T abs(T x)
    {
        return GeAbs(x);
    }
} // eof gu

// Real comparision

template <typename T>
constexpr inline bool GeEqual(T a, T b, T epsilon)
{
    return GeAbs(a - b) <= ( (GeAbs(a) < GeAbs(b) ? GeAbs(b) : GeAbs(a)) * epsilon);
}

template <typename T>
constexpr inline bool GeGreater(T a, T b, T epsilon)
{
    return (a - b) > ( (GeAbs(a) < GeAbs(b) ? GeAbs(b) : GeAbs(a)) * epsilon);
}

template <typename T>
constexpr inline bool GeLess(T a, T b, T epsilon)
{
    return (b - a) > ( (GeAbs(a) < GeAbs(b) ? GeAbs(b) : GeAbs(a)) * epsilon);
}

namespace ge
{
    template <typename T>
    constexpr inline bool equal(T x1, T x2, T epsilon = 0)
    {
        return GeEqual(x1, x2, epsilon);
    }

    template <typename T>
    constexpr inline bool greater(T x1, T x2, T epsilon = 0)
    {
        return GeGreater(x1, x2, epsilon);
    }

    template <typename T>
    constexpr inline bool less(T x1, T x2, T epsilon = 0)
    {
        return GeLess(x1, x2, epsilon);
    }
} // eof ge

// Max/Min

template <typename T>
constexpr inline T GeMax(T x1, T x2, T unused = 0)
{
    GE_UNUSED(unused);
    return x1 >= x2 ? x1 : x2;
}

template <typename T>
constexpr inline T GeMin(T x1, T x2, T unused = 0)
{
    GE_UNUSED(unused);
    return x1 <= x2 ? x1 : x2;
}

template <>
constexpr inline float GeMax<float>(float x1, float x2, float epsilon)
{
    return GeGreater(x1, x2, epsilon) ? x1 : x2;
}

template <>
constexpr inline double GeMax<double>(double x1, double x2, double epsilon)
{
    return GeGreater(x1, x2, epsilon) ? x1 : x2;
}

template <>
constexpr inline float GeMin<float>(float x1, float x2, float epsilon)
{
    return GeLess(x1, x2, epsilon) ? x1 : x2;
}

template <>
constexpr inline double GeMin<double>(double x1, double x2, double epsilon)
{
    return GeLess(x1, x2, epsilon) ? x1 : x2;
}

namespace ge
{
    template <typename T>
    constexpr inline T maximum(T x1, T x2, T epsilon = 0)
    {
        return GeMax(x1, x2, epsilon);
    }

    template <typename T>
    constexpr inline T minimum(T x1, T x2, T epsilon = 0)
    {
        return GeMin(x1, x2, epsilon);
    }


} // eof ge


// square root
template <typename T>
inline T GeSqrt(T x)
{
    return static_cast<T>(std::sqrt(x));
}

namespace ge
{
    template <typename T>
    inline T sqrt(T x)
    {
        return GeSqrt(x);
    }


} // eof ge
#endif // GEOMUTILS_BASEUTL_H