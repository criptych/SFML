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
#include <SFML/Graphics/Transform.hpp>
#include <cmath>


namespace sf
{
////////////////////////////////////////////////////////////
Transform::Transform() :
TransformBase()
{

}


////////////////////////////////////////////////////////////
Transform::Transform(const TransformBase &transform) :
TransformBase(transform)
{

}


////////////////////////////////////////////////////////////
Transform::Transform(float a00, float a01, float a02,
                     float a10, float a11, float a12,
                     float a20, float a21, float a22) :
TransformBase(a00, a01, a02,
              a10, a11, a12,
              a20, a21, a22)
{

}


////////////////////////////////////////////////////////////
Transform Transform::getInverse() const
{
    // Compute the determinant
    float det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
                m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
                m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);

    // Compute the inverse if the determinant is not zero
    // (don't use an epsilon because the determinant may *really* be tiny)
    if (det != 0.f)
    {
        return Transform( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
                         -(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
                          (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
                         -(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
                          (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
                         -(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
                          (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
                         -(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
                          (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
    }
    else
    {
        return Transform(Identity);
    }
}


////////////////////////////////////////////////////////////
Transform& Transform::combine(const TransformBase& transform)
{
    const float* a = m_matrix;
    const float* b = transform.getMatrix();

    *this = Transform(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
                      a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
                      a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
                      a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
                      a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
                      a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
                      a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
                      a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
                      a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);

    return *this;
}


////////////////////////////////////////////////////////////
Transform& Transform::translate(float x, float y)
{
    Transform translation(1, 0, x,
                          0, 1, y,
                          0, 0, 1);

    return combine(translation);
}


////////////////////////////////////////////////////////////
Transform& Transform::translate(const Vector2f& offset)
{
    return translate(offset.x, offset.y);
}


////////////////////////////////////////////////////////////
Transform& Transform::rotate(float angle)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Transform rotation(cos, -sin, 0,
                       sin,  cos, 0,
                       0,    0,   1);

    return combine(rotation);
}


////////////////////////////////////////////////////////////
Transform& Transform::rotate(float angle, float centerX, float centerY)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    Transform rotation(cos, -sin, centerX * (1 - cos) + centerY * sin,
                       sin,  cos, centerY * (1 - cos) - centerX * sin,
                       0,    0,   1);

    return combine(rotation);
}


////////////////////////////////////////////////////////////
Transform& Transform::rotate(float angle, const Vector2f& center)
{
    return rotate(angle, center.x, center.y);
}


////////////////////////////////////////////////////////////
Transform& Transform::scale(float scaleX, float scaleY)
{
    Transform scaling(scaleX, 0,      0,
                      0,      scaleY, 0,
                      0,      0,      1);

    return combine(scaling);
}


////////////////////////////////////////////////////////////
Transform& Transform::scale(float scaleX, float scaleY, float centerX, float centerY)
{
    Transform scaling(scaleX, 0,      centerX * (1 - scaleX),
                      0,      scaleY, centerY * (1 - scaleY),
                      0,      0,      1);

    return combine(scaling);
}


////////////////////////////////////////////////////////////
Transform& Transform::scale(const Vector2f& factors)
{
    return scale(factors.x, factors.y);
}


////////////////////////////////////////////////////////////
Transform& Transform::scale(const Vector2f& factors, const Vector2f& center)
{
    return scale(factors.x, factors.y, center.x, center.y);
}


////////////////////////////////////////////////////////////
Transform operator *(const Transform& left, const Transform& right)
{
    return Transform(left).combine(right);
}


////////////////////////////////////////////////////////////
Transform& operator *=(Transform& left, const Transform& right)
{
    return left.combine(right);
}


////////////////////////////////////////////////////////////
Vector2f operator *(const Transform& left, const Vector2f& right)
{
    return left.transformPoint(right);
}

} // namespace sf
