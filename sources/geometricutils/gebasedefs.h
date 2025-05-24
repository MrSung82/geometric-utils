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
#ifndef GEOMUTILS_BASEDEFS_H
#define GEOMUTILS_BASEDEFS_H

#include <cstdint>

using GeInt8 = std::int8_t;
using GeInt16 = std::int16_t;
using GeInt32 = std::int32_t;

using GeUint8 = std::uint8_t;
using GeUint32 = std::uint32_t;

using GeByte = GeUint8;
using GeSize = std::size_t;

using GeReal32 = float;
using GeReal64 = double;

namespace ge
{
    using int8_t = GeInt8;
    using int16_t = GeInt16;
    using int32_t = GeInt32;

    using uint8_t = GeUint8;
    using uint32_t = GeUint32;

    using byte_t = GeByte;
    using size_t = GeSize;

    using real32_t = GeReal32;
    using real64_t = GeReal64;
} // eof gu

#define GE_UNUSED(x) ((void)x)

#endif // GEOMUTILS_BASEDEFS_H