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


#include "gebasedefs.h"
#include "gerealutl.h"
#include <limits>
#include <cmath>

namespace ge
{
    namespace details
    {
        namespace realmath
        {
            template <typename TInt>
            constexpr inline TInt IntAbsImpl(TInt x)
            {
                return x >= 0 ? x : -x;
            }
        } // end of realmath

    } // end of details
} // end of ge

namespace ge
{
namespace details
{
    struct IEEE754FloatFormat{};

#ifdef GE_LITTLE_ENDIAN
    struct IEEE754FloatFormatLE : IEEE754FloatFormat
    {
        uint32_t mantissa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    };

    const size_t kIEEE754FloatFormatMemSize = sizeof(IEEE754FloatFormatLE);
#else
    struct IEEE754FloatFormatBE : IEEE754FloatFormat
    {
#error "Not implemented yet!"
        uint32_t raw;
    };

    const size_t kIEEE754FloatFormatMemSize = sizeof(IEEE754FloatFormatBE);
#endif // endianness

    inline IEEE754FloatFormat* ToIeee754FloatFormat(void* pMem)
    {
#ifdef GE_LITTLE_ENDIAN
            return reinterpret_cast<IEEE754FloatFormatLE*>(pMem);
#else
            return reinterpret_cast<IEEE754FloatFormatBE*>(pMem);
#endif
    }
} // end of details
} // end of ge


namespace ge
{
namespace details
{
    class Real32Impl
    {
        union
        {
            int32_t asInt;
            real32_t asFlt;
        } m_data;

    public:
        Real32Impl(real32_t val = 0.0f)
        {
            m_data.asFlt = val;
        }

        bool IsNegative() const
        {
            return m_data.asInt < 0;
        }

        int32_t ExtractMantissa() const
        {
#ifdef GE_LITTLE_ENDIAN
            return m_data.asInt & 0x7FFFFF;
#elif GE_BIG_ENDIAN
#   error "Not implemented yet!"
#else
#   error "Not implemented yet!"
#endif
        }

        int32_t ExtractExponent() const
        {
#ifdef GE_LITTLE_ENDIAN
            return (m_data.asInt >> 23) & 0xFF;
#elif GE_BIG_ENDIAN
#   error "Not implemented yet!"
#else
#   error "Not implemented yet!"
#endif
        }

        int32_t AsInt32() const { return m_data.asInt; }

        real32_t ToAbs()
        {
#ifdef GE_LITTLE_ENDIAN
            m_data.asInt &= 0x7FFFFFFF;
            return m_data.asFlt;
#elif GE_BIG_ENDIAN
#   error "Not implemented yet!"
#else
#   error "Not implemented yet!"
#endif
        }
    };


} // end of details
} // end of ge


//==============================================================================
// Real absolute

template <>
inline GeReal32 GeRealAbs<GeReal32>(GeReal32 x)
{
#ifdef GE_FLOAT_ABS_STD_IMPL
    return reinterpret_cast<float>(std::fabs(x));
#else
    ge::details::Real32Impl fX(x);
    return fX.ToAbs();
#endif
}

//==============================================================================
// Real comparision

bool GeIsRealEqualByUlps(GeReal32 a, GeReal32 b, GeInt32 tolInUlps)
{
    ge::details::Real32Impl fA(a);
    ge::details::Real32Impl fB(b);

    if (fA.IsNegative() != fB.IsNegative())
    {
        // +0 == -0 case
        return (a == b);
    }

    GeInt32 ulpsDiff = ge::details::realmath::IntAbsImpl(fA.AsInt32() - fB.AsInt32());
    return (ulpsDiff <= tolInUlps);
}


namespace ge
{
namespace details
{
template <typename T>
class RealCompareAux
{
    enum Flags
    {
        kEmpty,
        kFirstBelowThreshold = 1 << 0,
        kSecondBelowThreshold = 1 << 1,
        kBelowThresholdMask = 0x00000003,
        kMinFactoredBelowThreshold = 1 << 2,

    };

public:
    RealCompareAux(T x1, T x2,
                   T factor = GeDefaultEpsilon<T>(),
                   T threshold = 10 * std::numeric_limits<T>::epsilon())
        : m_x1{x1}
        , m_x2{x2}
        , m_factor{factor}
        , m_threshold{threshold}
        , m_flags{0}
    {
        m_absX1 = GeRealAbs(m_x1);
        m_absX2 = GeRealAbs(m_x2);

        if (m_absX1 < m_threshold)
        {
            m_flags |= kFirstBelowThreshold;
        }

        if (m_absX2 < m_threshold)
        {
            m_flags |= kSecondBelowThreshold;
        }

        m_minAbsFactored = m_factor * ((m_absX1 < m_absX2) ? m_absX1 : m_absX2);
        m_maxAbsFactored = m_factor * ((m_absX1 < m_absX2) ? m_absX2 : m_absX1);

        if (m_minAbsFactored < m_threshold)
        {
            m_flags |= kMinFactoredBelowThreshold;
        }
    }

    bool IsAnyOfAbsBelowTheshold() const
    {
        return m_flags & kBelowThresholdMask;
    }

    bool IsMinOfAbsBelowTheshold() const
    {
        return m_flags & kMinFactoredBelowThreshold;
    }

    T GetMaxAbsFactored() const
    {
        return m_maxAbsFactored;
    }

private:
    T m_x1{};
    T m_x2{};
    T m_factor{};
    T m_threshold{}; // low values ceil

    T m_absX1{};
    T m_absX2{};

    T m_minAbsFactored{};
    T m_maxAbsFactored{};

    uint32_t m_flags{};
};

} // end of details
} // end of ge

template <>
bool GeRealEqual<GeReal32>(GeReal32 a, GeReal32 b, GeReal32 tol)
{
    ge::details::RealCompareAux aux(a, b, tol);

    if (aux.IsAnyOfAbsBelowTheshold() ||
        aux.IsMinOfAbsBelowTheshold())
    {
        return GeIsRealEqualByUlps(a, b, 1);
    }

    return GeRealAbs(a - b) <= aux.GetMaxAbsFactored();
}

/// @todo not implemented yet
template <>
bool GeRealEqual<GeReal64>(GeReal64 a, GeReal64 b, GeReal64 tol);



template <>
bool GeRealLess<GeReal32>(GeReal32 a, GeReal32 b, GeReal32 tol)
{
    ge::details::RealCompareAux aux(a, b, tol);



    return (b - a) > aux.GetMaxAbsFactored();
}
