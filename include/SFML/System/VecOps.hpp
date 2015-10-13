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

#ifndef SFML_VECOPS_HPP
#define SFML_VECOPS_HPP

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector4.hpp>

namespace sf
{
////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Calculate the 2-dimensional dot product.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Dot product of \a left and \a right
///
////////////////////////////////////////////////////////////
template <typename T>
inline T dot(const Vector2<T> &left, const Vector2<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Calculate the 3-dimensional dot product.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Dot product of \a left and \a right
///
////////////////////////////////////////////////////////////
template <typename T>
inline T dot(const Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector4
/// \brief Calculate the 4-dimensional dot product.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Dot product of \a left and \a right
///
////////////////////////////////////////////////////////////
template <typename T>
inline T dot(const Vector4<T> &left, const Vector4<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Calculate the vector determinant.
///
/// Equivalent to the magnitude of the cross product, if \a left
/// and \a right were 3D vectors with a Z-coordinate of zero.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Determinant of \a left and \a right
///
////////////////////////////////////////////////////////////
template <typename T>
inline T det(const Vector2<T> &left, const Vector2<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector3
/// \brief Calculate the cross product.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Cross product of \a left and \a right
///
////////////////////////////////////////////////////////////
template <typename T>
inline Vector3<T> cross(const Vector3<T> &left, const Vector3<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector4
/// \brief Calculate the quaternion product.
///
/// \param left  Left operand (a vector)
/// \param right Right operand (a vector)
///
/// \return Quaternion product of \a left and \a right
///
////////////////////////////////////////////////////////////
template <typename T>
inline Vector4<T> qmul(const Vector4<T> &left, const Vector4<T> &right);

////////////////////////////////////////////////////////////
/// \relates Vector2
/// \brief Calculate the complex conjugate.
///
/// The complex conjugate has an equal X (real) coordinate and
/// negated Y (imaginary) coordinate.
///
/// \param left  Left operand (a vector)
///
/// \return Complex conjugate of \a left
///
////////////////////////////////////////////////////////////
template <typename T>
inline Vector2<T> conj(const Vector2<T> &left);

////////////////////////////////////////////////////////////
/// \relates Vector4
/// \brief Calculate the quaternion conjugate.
///
/// The quaternion conjugate has an equal scalar (W) coordinate
/// and negated vector (XYZ) coordinates.
///
/// \param left  Left operand (a vector)
///
/// \return Quaternion conjugate of \a left
///
////////////////////////////////////////////////////////////
template <typename T>
inline Vector4<T> conj(const Vector4<T> &left);

#include <SFML/System/VecOps.inl>

} // namespace sf


#endif // SFML_VECOPS_HPP

