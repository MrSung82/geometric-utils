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

#include "gerealutl.h"
#include <limits>
#include <cmath>

// Endianness
constexpr
inline
bool GeIsLittleEndian()
{
    const GeUint32 ku32Value{0x12345678};
    const GeUint8* pu8Array = reinterpret_cast<const GeUint8*>(&ku32Value);
    return pu8Array[0] == 0x78;
}

namespace ge
{
constexpr
inline
bool IsLittleEndian()
{
    return GeIsLittleEndian();
}

} // eof ge

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
constexpr inline T GeIntAbs(T x)
{
    return x >= 0 ? x : -x;
}



namespace ge
{
    template <typename T>
    constexpr inline T IntAbs(T x)
    {
        return GeIntAbs(x);
    }

    template <typename T>
    inline T RealAbs(T x)
    {
        return GeRealAbs(x);
    }
} // eof gu

// Real comparision

template <typename T>
bool GeRealEqual(T a, T b, T tol)
{
    T ma = GeRealAbs(a);
    T mb = GeRealAbs(b);
    return GeRealAbs(a - b) <= (tol * (ma < mb ? mb : ma));
}

template <>
bool GeRealEqual<GeReal32>(GeReal32 a, GeReal32 b, GeReal32 tol)
{
    GeReal32 ma = GeRealAbs(a);
    GeReal32 mb = GeRealAbs(b);

    if (ma < 10.f * std::numeric_limits<float>::epsilon() ||
        mb < 10.f * std::numeric_limits<float>::epsilon())
    {
        return GeIsRealEqualByUlps(a, b, 1);
    }
    else
    {
        GeReal32 minmulbytol = tol * ((ma < mb) ? ma : mb);
        if (minmulbytol < 10 * std::numeric_limits<float>::epsilon())
        {
            return GeIsRealEqualByUlps(a, b, 1);
        }
    }
    GeReal32 maxmulbytol = tol * ((ma < mb) ? mb : ma);
    return GeRealAbs(a - b) <= maxmulbytol;
}

template <typename T>
bool GeRealGreater(T a, T b, T epsilon)
{
    return (a - b) > ( (GeRealAbs(a) < GeRealAbs(b) ? GeRealAbs(b) : GeRealAbs(a)) * epsilon);
}

template <typename T>
bool GeRealLess(T a, T b, T epsilon)
{
    return (b - a) > ( (GeRealAbs(a) < GeRealAbs(b) ? GeRealAbs(b) : GeRealAbs(a)) * epsilon);
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
constexpr inline T GeIntMax(T x1, T x2)
{
    return x1 >= x2 ? x1 : x2;
}

template <typename T>
constexpr inline T GeIntMin(T x1, T x2)
{
    return x1 <= x2 ? x1 : x2;
}

template <typename T>
inline T GeRealMax(T x1, T x2, T tol);

template <typename T>
inline T GeRealMin(T x1, T x2, T tol);

template <>
inline float GeRealMax<float>(float x1, float x2, float epsilon)
{
    return GeRealGreater(x1, x2, epsilon) ? x1 : x2;
}

template <>
inline double GeRealMax<double>(double x1, double x2, double epsilon)
{
    return GeRealGreater(x1, x2, epsilon) ? x1 : x2;
}

template <>
inline float GeRealMin<float>(float x1, float x2, float epsilon)
{
    return GeRealLess(x1, x2, epsilon) ? x1 : x2;
}

template <>
inline double GeRealMin<double>(double x1, double x2, double epsilon)
{
    return GeRealLess(x1, x2, epsilon) ? x1 : x2;
}

namespace ge
{
    template <typename T>
    inline T maximum(T x1, T x2, T epsilon = 0)
    {
        return GeRealMax(x1, x2, epsilon);
    }

    template <typename T>
    inline T minimum(T x1, T x2, T epsilon = 0)
    {
        return GeRealMin(x1, x2, epsilon);
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
