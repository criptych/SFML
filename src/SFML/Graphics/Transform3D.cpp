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
#include <SFML/Graphics/Transform3D.hpp>
#include <SFML/System/VecOps.hpp>
#include <cmath>


namespace sf
{
////////////////////////////////////////////////////////////
Transform3D::Transform3D() :
TransformBase()
{

}


////////////////////////////////////////////////////////////
Transform3D::Transform3D(const TransformBase &transform) :
TransformBase(transform)
{

}


////////////////////////////////////////////////////////////
Transform3D::Transform3D(float a00, float a01, float a02, float a03,
                         float a10, float a11, float a12, float a13,
                         float a20, float a21, float a22, float a23,
                         float a30, float a31, float a32, float a33) :
TransformBase(a00, a01, a02, a03,
              a10, a11, a12, a13,
              a20, a21, a22, a23,
              a30, a31, a32, a33)
{

}


////////////////////////////////////////////////////////////
Transform3D Transform3D::getInverse() const
{
    const float *a = getMatrix();
    float b[16];

    b[0]  =  a[5] * a[10] * a[15] - a[5]  * a[11] * a[14] - a[9]  * a[6] * a[15] +
             a[9] * a[7]  * a[14] + a[13] * a[6]  * a[11] - a[13] * a[7] * a[10];
    b[4]  = -a[4] * a[10] * a[15] + a[4]  * a[11] * a[14] + a[8]  * a[6] * a[15] -
             a[8] * a[7]  * a[14] - a[12] * a[6]  * a[11] + a[12] * a[7] * a[10];
    b[8]  =  a[4] * a[9]  * a[15] - a[4]  * a[11] * a[13] - a[8]  * a[5] * a[15] +
             a[8] * a[7]  * a[13] + a[12] * a[5]  * a[11] - a[12] * a[7] * a[9];
    b[12] = -a[4] * a[9]  * a[14] + a[4]  * a[10] * a[13] + a[8]  * a[5] * a[14] -
             a[8] * a[6]  * a[13] - a[12] * a[5]  * a[10] + a[12] * a[6] * a[9];

    b[1]  = -a[1] * a[10] * a[15] + a[1]  * a[11] * a[14] + a[9]  * a[2] * a[15] -
             a[9] * a[3]  * a[14] - a[13] * a[2]  * a[11] + a[13] * a[3] * a[10];
    b[5]  =  a[0] * a[10] * a[15] - a[0]  * a[11] * a[14] - a[8]  * a[2] * a[15] +
             a[8] * a[3]  * a[14] + a[12] * a[2]  * a[11] - a[12] * a[3] * a[10];
    b[9]  = -a[0] * a[9]  * a[15] + a[0]  * a[11] * a[13] + a[8]  * a[1] * a[15] -
             a[8] * a[3]  * a[13] - a[12] * a[1]  * a[11] + a[12] * a[3] * a[9];
    b[13] =  a[0] * a[9]  * a[14] - a[0]  * a[10] * a[13] - a[8]  * a[1] * a[14] +
             a[8] * a[2]  * a[13] + a[12] * a[1]  * a[10] - a[12] * a[2] * a[9];

    b[2]  =  a[1] * a[6]  * a[15] - a[1]  * a[7]  * a[14] - a[5]  * a[2] * a[15] +
             a[5] * a[3]  * a[14] + a[13] * a[2]  * a[7]  - a[13] * a[3] * a[6];
    b[6]  = -a[0] * a[6]  * a[15] + a[0]  * a[7]  * a[14] + a[4]  * a[2] * a[15] -
             a[4] * a[3]  * a[14] - a[12] * a[2]  * a[7]  + a[12] * a[3] * a[6];
    b[10] =  a[0] * a[5]  * a[15] - a[0]  * a[7]  * a[13] - a[4]  * a[1] * a[15] +
             a[4] * a[3]  * a[13] + a[12] * a[1]  * a[7]  - a[12] * a[3] * a[5];
    b[14] = -a[0] * a[5]  * a[14] + a[0]  * a[6]  * a[13] + a[4]  * a[1] * a[14] -
             a[4] * a[2]  * a[13] - a[12] * a[1]  * a[6]  + a[12] * a[2] * a[5];

    b[3]  = -a[1] * a[6]  * a[11] + a[1]  * a[7]  * a[10] + a[5]  * a[2] * a[11] -
             a[5] * a[3]  * a[10] - a[9]  * a[2]  * a[7]  + a[9]  * a[3] * a[6];
    b[7]  =  a[0] * a[6]  * a[11] - a[0]  * a[7]  * a[10] - a[4]  * a[2] * a[11] +
             a[4] * a[3]  * a[10] + a[8]  * a[2]  * a[7]  - a[8]  * a[3] * a[6];
    b[11] = -a[0] * a[5]  * a[11] + a[0]  * a[7]  * a[9]  + a[4]  * a[1] * a[11] -
             a[4] * a[3]  * a[9]  - a[8]  * a[1]  * a[7]  + a[8]  * a[3] * a[5];
    b[15] =  a[0] * a[5]  * a[10] - a[0]  * a[6]  * a[9]  - a[4]  * a[1] * a[10] +
             a[4] * a[2]  * a[9]  + a[8]  * a[1]  * a[6]  - a[8]  * a[2] * a[5];

    // Compute the determinant
    float det = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];

    // Compute the inverse if the determinant is not zero
    // (don't use an epsilon because the determinant may *really* be tiny)
    if (det != 0.f)
    {
        return Transform3D(b[0] / det, b[4] / det, b[8]  / det, b[12] / det,
                           b[1] / det, b[5] / det, b[9]  / det, b[13] / det,
                           b[2] / det, b[6] / det, b[10] / det, b[14] / det,
                           b[3] / det, b[7] / det, b[11] / det, b[15] / det);
    }
    else
    {
        return Transform3D(Identity);
    }
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::combine(const TransformBase& transform)
{
    TransformBase::combine(transform);
    return *this;
}


////////////////////////////////////////////////////////////
Transform3D &Transform3D::orthographic(float left, float right, float bottom, float top, float znear, float zfar) {
    Transform3D transform(
        2 / (right - left), 0.0f, 0.0f, (left + right) / (left - right),
        0.0f, 2 / (top - bottom), 0.0f, (bottom + top) / (bottom - top),
        0.0f, 0.0f, 2 / (znear - zfar), (znear + zfar) / (znear - zfar),
        0.0f, 0.0f, 0.0f, 1.0f);

    return combine(transform);
}


////////////////////////////////////////////////////////////
Transform3D &Transform3D::orthographic(float left, float right, float bottom, float top) {
    return orthographic(left, right, bottom, top, -1, 1);
}


////////////////////////////////////////////////////////////
Transform3D &Transform3D::frustum(float left, float right, float bottom, float top, float znear, float zfar) {
    Transform3D transform(
        (2 * znear) / (right - left), 0.0f, (right + left) / (right - left), 0.0f,
        0.0f, (2 * znear) / (top - bottom), (top + bottom) / (top - bottom), 0.0f,
        0.0f, 0.0f, (znear + zfar) / (znear - zfar), (2 * znear * zfar) / (znear - zfar),
        0.0f, 0.0f, -1.0f, 0.0f);

    return combine(transform);
}


////////////////////////////////////////////////////////////
Transform3D &Transform3D::perspective(float fov, float aspect, float znear, float zfar) {
    float fh = std::tan(fov*(3.14159265358979/360.0))*znear;
    float fw = fh * aspect;
    return frustum(-fw, fw, -fh, fh, znear, zfar);
}


////////////////////////////////////////////////////////////
Transform3D &Transform3D::lookAt(const sf::Vector3f &eye, const sf::Vector3f &target, const sf::Vector3f &up) {
    sf::Vector3f f, r, u;
    f = normalize(eye - target);
    r = normalize(cross(up, f));
    u = normalize(cross(f, r));

    Transform3D transform(r.x, u.x, f.x, 0,
                          r.y, u.y, f.y, 0,
                          r.z, u.z, f.z, 0,
                          0,   0,   0,   1);

    return combine(transform);
}

////////////////////////////////////////////////////////////
Transform3D& Transform3D::translate(const Vector3f& offset)
{
    Transform3D translation(1, 0, 0, offset.x,
                            0, 1, 0, offset.y,
                            0, 0, 1, offset.z,
                            0, 0, 0, 1);

    return combine(translation);
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::rotate(float angle, const Vector3f& axis)
{
    float rad = angle * 3.141592654f / 180.f;
    float cos = std::cos(rad);
    float sin = std::sin(rad);

    //~ Vector3f v = axis / std::sqrt(axis.x * axis.x +
                                  //~ axis.y * axis.y +
                                  //~ axis.z * axis.z);

    float xx = axis.x * axis.x;
    float xy = axis.x * axis.y;
    float xz = axis.x * axis.z;
    float yy = axis.y * axis.y;
    float yz = axis.y * axis.z;
    float zz = axis.z * axis.z;
    float xs = axis.x * sin;
    float ys = axis.y * sin;
    float zs = axis.z * sin;
    float mc = 1.0f - cos;

    Transform3D rotation(xx * mc + cos, xy * mc - zs,  xz * mc + ys,  0,
                         xy * mc + zs,  yy * mc + cos, yz * mc - xs,  0,
                         xz * mc - ys,  yz * mc + xs,  zz * mc + cos, 0,
                         0,             0,             0,             1);

    return combine(rotation);
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::rotate(float angle, const Vector3f& axis, const Vector3f& center)
{
    //! @todo implement "more easily (and efficiently) than":
    return translate(-center).rotate(angle, axis).translate(center);
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::scale(float factor)
{
    Transform3D scaling(factor, 0,      0,      0,
                        0,      factor, 0,      0,
                        0,      0,      factor, 0,
                        0,      0,      0,      1);

    return combine(scaling);
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::scale(float factor, const Vector3f& center)
{
    //! @todo implement "more easily (and efficiently) than":
    return translate(-center).scale(factor).translate(center);
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::scale(const Vector3f& factors)
{
    Transform3D scaling(factors.x, 0,         0,         0,
                        0,         factors.y, 0,         0,
                        0,         0,         factors.z, 0,
                        0,         0,         0,         1);

    return combine(scaling);
}


////////////////////////////////////////////////////////////
Transform3D& Transform3D::scale(const Vector3f& factors, const Vector3f& center)
{
    //! @todo implement "more easily (and efficiently) than":
    return translate(-center).scale(factors).translate(center);
}


////////////////////////////////////////////////////////////
Transform3D operator *(const Transform3D& left, const Transform3D& right)
{
    return Transform3D(left).combine(right);
}


////////////////////////////////////////////////////////////
Transform3D& operator *=(Transform3D& left, const Transform3D& right)
{
    return left.combine(right);
}


////////////////////////////////////////////////////////////
Vector3f operator *(const Transform3D& left, const Vector3f& right)
{
    return left.transformPoint(right);
}

} // namespace sf
