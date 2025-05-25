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
#ifndef GEOMUTILS_REALUTL_H
#define GEOMUTILS_REALUTL_H

#include "gebasedefs.h"
#include <limits>
#include <cmath>

const GeReal32 kGE_REAL32_DEFAULT_EPSILON = 1.e-6f;
const GeReal64 kGE_REAL64_DEFAULT_EPSILON = 1.e-15f;

template <typename T>
class GeDefaultEpsilon;

template <>
class GeDefaultEpsilon<GeReal32>
{
public:
    static GeReal32 Value()
    {
        return kGE_REAL32_DEFAULT_EPSILON;
    }
};


template <>
class GeDefaultEpsilon<GeReal64>
{
public:
    static GeReal64 Value()
    {
        return kGE_REAL64_DEFAULT_EPSILON;
    }
};

//==============================================================================
// Real absolute and sign

template <typename T>
inline T GeRealAbs(T x);

template <>
inline GeReal32 GeRealAbs<GeReal32>(GeReal32 x);

template <>
inline GeReal64 GeRealAbs<GeReal64>(GeReal64 x);

template <typename T>
inline bool GeIsRealNegative(T x);

template <>
inline bool GeIsRealNegative<GeReal32>(GeReal32 x);

template <>
inline bool GeIsRealNegative<GeReal64>(GeReal64 x);

namespace ge
{
    template <typename T>
    inline T RealAbs(T x)
    {
        return GeRealAbs(x);
    }
} // eof gu

//==============================================================================
// Real comparision


//------------------------------------------------------------------------------
/**
*/
bool GeIsRealEqualByUlps(GeReal32 a, GeReal32 b, GeInt32 tolInUlps);

//------------------------------------------------------------------------------
/**
    @param tol tolerance
    @return Returns true if reals are equal
*/
template <typename T>
bool GeRealEqual(T a, T b, T tol)
{
    T absOfA = GeRealAbs(a);
    T absOfB = GeRealAbs(b);
    return GeRealAbs(a - b) <= (tol * (absOfA < absOfB ? absOfB : absOfA));
}

template <>
bool GeRealEqual<GeReal32>(GeReal32 a, GeReal32 b, GeReal32 tol);

template <>
bool GeRealEqual<GeReal64>(GeReal64 a, GeReal64 b, GeReal64 tol);


//------------------------------------------------------------------------------
/**
*/
template <typename T>
bool GeRealLess(T a, T b, T tol)
{
    return (b - a) > ( (GeRealAbs(a) < GeRealAbs(b) ? GeRealAbs(b) : GeRealAbs(a)) * tol);
}

template <>
bool GeRealLess<GeReal32>(GeReal32 a, GeReal32 b, GeReal32 tol);

template <>
bool GeRealLess<GeReal64>(GeReal64 a, GeReal64 b, GeReal64 tol);


//------------------------------------------------------------------------------
/**
*/
template <typename T>
inline bool GeRealGreater(T a, T b, T tol)
{
    return GeRealLess(b, a, tol);
}


#endif // GEOMUTILS_REALUTL_H
