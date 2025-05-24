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
#ifndef GEOMUTILS_VECTOR3_H
#define GEOMUTILS_VECTOR3_H

#include "gebaseutl.h"

template <typename T>
class GeVector3 
{
public:
    T x, y, z;

    // Constructors
    Vector3D() 
        : x(GetZero<T>())
        , y(GetZero<T>())
        , z(GetZero<T>()) 
        {}

    Vector3D(T x, T y, T z) 
        : x{x}
        , y{y}
        , z{z}
        {}

    // Vector operations
    Vector3D operator+(const Vector3D& other) const {
        return Vector3D(x + other.x, y + other.y, z + other.z);
    }

    Vector3D operator-(const Vector3D& other) const {
        return Vector3D(x - other.x, y - other.y, z - other.z);
    }

    Vector3D operator*(double scalar) const {
        return Vector3D(x * scalar, y * scalar, z * scalar);
    }

    double dot(const Vector3D& other) const {
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3D cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x
        );
    }

    T magnitude_square() const {
        return (x * x + y * y + z * z);
    }

    T magnitude() const {
        return GeSqrt(x * x + y * y + z * z);
    }

    Vector3D normalize() const {
        double mag = magnitude();
        if (mag != 0.0) {
            return Vector3D(x / mag, y / mag, z / mag);
        } else {
            return Vector3D(0, 0, 0);
        }
    }

    // Display vector
    void print() const {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};

namespace ge
{
    template <typename T>
    using vector3 = GeVector3<T>;
    
} // eof gu




#endif // GEOMUTILS_VECTOR3_H