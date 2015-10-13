////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2015 Laurent Gomila (laurent@sfml-dev.org)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/TransformBase.hpp>
#include <cmath>


namespace sf
{
////////////////////////////////////////////////////////////
const TransformBase TransformBase::Identity;


////////////////////////////////////////////////////////////
TransformBase::TransformBase()
{
    // Identity matrix
    m_matrix[0] = 1.f; m_matrix[4] = 0.f; m_matrix[8]  = 0.f; m_matrix[12] = 0.f;
    m_matrix[1] = 0.f; m_matrix[5] = 1.f; m_matrix[9]  = 0.f; m_matrix[13] = 0.f;
    m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
    m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
}


////////////////////////////////////////////////////////////
TransformBase::TransformBase(const TransformBase &transform)
{
    std::copy(transform.m_matrix, transform.m_matrix+16, m_matrix);
}


////////////////////////////////////////////////////////////
TransformBase::TransformBase(float a00, float a01, float a02,
                             float a10, float a11, float a12,
                             float a20, float a21, float a22)
{
    m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8]  = 0.f; m_matrix[12] = a02;
    m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9]  = 0.f; m_matrix[13] = a12;
    m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
    m_matrix[3] = a20; m_matrix[7] = a21; m_matrix[11] = 0.f; m_matrix[15] = a22;
}


////////////////////////////////////////////////////////////
TransformBase::TransformBase(float a00, float a01, float a02, float a03,
                             float a10, float a11, float a12, float a13,
                             float a20, float a21, float a22, float a23,
                             float a30, float a31, float a32, float a33)
{
    m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8]  = a02; m_matrix[12] = a03;
    m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9]  = a12; m_matrix[13] = a13;
    m_matrix[2] = a20; m_matrix[6] = a21; m_matrix[10] = a22; m_matrix[14] = a23;
    m_matrix[3] = a30; m_matrix[7] = a31; m_matrix[11] = a32; m_matrix[15] = a33;
}


////////////////////////////////////////////////////////////
const float* TransformBase::getMatrix() const
{
    return m_matrix;
}


////////////////////////////////////////////////////////////
Vector2f TransformBase::transformPoint(float x, float y) const
{
    return Vector2f(m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
                    m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
}


////////////////////////////////////////////////////////////
Vector2f TransformBase::transformPoint(const Vector2f& point) const
{
    return transformPoint(point.x, point.y);
}


////////////////////////////////////////////////////////////
Vector3f TransformBase::transformPoint(float x, float y, float z) const
{
    return Vector3f(m_matrix[0] * x + m_matrix[4] * y + m_matrix[8]  * z + m_matrix[12],
                    m_matrix[1] * x + m_matrix[5] * y + m_matrix[9]  * z + m_matrix[13],
                    m_matrix[2] * x + m_matrix[6] * y + m_matrix[10] * z + m_matrix[14]);
}


////////////////////////////////////////////////////////////
Vector3f TransformBase::transformPoint(const Vector3f& point) const
{
    return transformPoint(point.x, point.y, point.z);
}


////////////////////////////////////////////////////////////
FloatRect TransformBase::transformRect(const FloatRect& rectangle) const
{
    // Transform the 4 corners of the rectangle
    const Vector2f points[] =
    {
        transformPoint(rectangle.left, rectangle.top),
        transformPoint(rectangle.left, rectangle.top + rectangle.height),
        transformPoint(rectangle.left + rectangle.width, rectangle.top),
        transformPoint(rectangle.left + rectangle.width, rectangle.top + rectangle.height)
    };

    // Compute the bounding rectangle of the transformed points
    float left = points[0].x;
    float top = points[0].y;
    float right = points[0].x;
    float bottom = points[0].y;
    for (int i = 1; i < 4; ++i)
    {
        if      (points[i].x < left)   left = points[i].x;
        else if (points[i].x > right)  right = points[i].x;
        if      (points[i].y < top)    top = points[i].y;
        else if (points[i].y > bottom) bottom = points[i].y;
    }

    return FloatRect(left, top, right - left, bottom - top);
}


////////////////////////////////////////////////////////////
TransformBase& TransformBase::combine(const TransformBase& transform)
{
    const float* a = m_matrix;
    const float* b = transform.m_matrix;

    *this = TransformBase(
        a[0] * b[0]  + a[4] * b[1]  + a[8]  * b[2]  + a[12] * b[3],
        a[0] * b[4]  + a[4] * b[5]  + a[8]  * b[6]  + a[12] * b[7],
        a[0] * b[8]  + a[4] * b[9]  + a[8]  * b[10] + a[12] * b[11],
        a[0] * b[12] + a[4] * b[13] + a[8]  * b[14] + a[12] * b[15],
        a[1] * b[0]  + a[5] * b[1]  + a[9]  * b[2]  + a[13] * b[3],
        a[1] * b[4]  + a[5] * b[5]  + a[9]  * b[6]  + a[13] * b[7],
        a[1] * b[8]  + a[5] * b[9]  + a[9]  * b[10] + a[13] * b[11],
        a[1] * b[12] + a[5] * b[13] + a[9]  * b[14] + a[13] * b[15],
        a[2] * b[0]  + a[6] * b[1]  + a[10] * b[2]  + a[14] * b[3],
        a[2] * b[4]  + a[6] * b[5]  + a[10] * b[6]  + a[14] * b[7],
        a[2] * b[8]  + a[6] * b[9]  + a[10] * b[10] + a[14] * b[11],
        a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15],
        a[3] * b[0]  + a[7] * b[1]  + a[11] * b[2]  + a[15] * b[3],
        a[3] * b[4]  + a[7] * b[5]  + a[11] * b[6]  + a[15] * b[7],
        a[3] * b[8]  + a[7] * b[9]  + a[11] * b[10] + a[15] * b[11],
        a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15]);

    return *this;
}


////////////////////////////////////////////////////////////
TransformBase operator *(const TransformBase& left, const TransformBase& right)
{
    return TransformBase(left).combine(right);
}


////////////////////////////////////////////////////////////
TransformBase& operator *=(TransformBase& left, const TransformBase& right)
{
    return left.combine(right);
}


////////////////////////////////////////////////////////////
Vector2f operator *(const TransformBase& left, const Vector2f& right)
{
    return left.transformPoint(right);
}

////////////////////////////////////////////////////////////
Vector3f operator *(const TransformBase& left, const Vector3f& right)
{
    return left.transformPoint(right);
}

} // namespace sf
