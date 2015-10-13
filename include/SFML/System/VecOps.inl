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
template <typename T>
inline T dot(const Vector2<T> &left, const Vector2<T> &right)
{
    return left.x * right.x + left.y * right.y;
}


////////////////////////////////////////////////////////////
template <typename T>
inline T dot(const Vector3<T> &left, const Vector3<T> &right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z;
}


////////////////////////////////////////////////////////////
template <typename T>
inline T dot(const Vector4<T> &left, const Vector4<T> &right)
{
    return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
}


////////////////////////////////////////////////////////////
template <typename T>
inline T det(const Vector2<T> &left, const Vector2<T> &right)
{
    return left.x * right.y - left.y * right.x;
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> cross(const Vector3<T> &left, const Vector3<T> &right)
{
    return Vector3<T>(left.y * right.z - left.z * right.y,
                      left.z * right.x - left.x * right.z,
                      left.x * right.y - left.y * right.x);
}


////////////////////////////////////////////////////////////
template <typename T>
inline Vector4<T> qmul(const Vector4<T> &left, const Vector4<T> &right)
{
    return Vector4<T>(
        left.w * right.x + left.x * right.w + left.y * right.z - left.z * right.y,
        left.w * right.y + left.y * right.w + left.z * right.x - left.x * right.z,
        left.w * right.z + left.z * right.w + left.x * right.y - left.y * right.x,
        left.w * right.w - left.x * right.x - left.y * right.y - left.z * right.z);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> conj(const Vector2<T> &left)
{
    return Vector2<T>(left.x, -left.y);
}

////////////////////////////////////////////////////////////
template <typename T>
inline Vector4<T> conj(const Vector4<T> &left)
{
    return Vector2<T>(-left.x, -left.y, -left.z, left.w);
}
