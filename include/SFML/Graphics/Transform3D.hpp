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

#ifndef SFML_TRANSFORM3D_HPP
#define SFML_TRANSFORM3D_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/TransformBase.hpp>
#include <SFML/System/Vector3.hpp>


namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Define a 4x4 transform matrix
///
////////////////////////////////////////////////////////////
class SFML_GRAPHICS_API Transform3D : public TransformBase
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Creates an identity transform (a transform that does nothing).
    ///
    ////////////////////////////////////////////////////////////
    Transform3D();

    ////////////////////////////////////////////////////////////
    /// \brief Construct a transform from a 4x4 matrix
    ///
    /// \param a00 Element (0, 0) of the matrix
    /// \param a01 Element (0, 1) of the matrix
    /// \param a02 Element (0, 2) of the matrix
    /// \param a03 Element (0, 3) of the matrix
    /// \param a10 Element (1, 0) of the matrix
    /// \param a11 Element (1, 1) of the matrix
    /// \param a12 Element (1, 2) of the matrix
    /// \param a13 Element (1, 3) of the matrix
    /// \param a20 Element (2, 0) of the matrix
    /// \param a21 Element (2, 1) of the matrix
    /// \param a22 Element (2, 2) of the matrix
    /// \param a23 Element (2, 3) of the matrix
    /// \param a30 Element (3, 0) of the matrix
    /// \param a31 Element (3, 1) of the matrix
    /// \param a32 Element (3, 2) of the matrix
    /// \param a33 Element (3, 3) of the matrix
    ///
    ////////////////////////////////////////////////////////////
    Transform3D(float a00, float a01, float a02, float a03,
                float a10, float a11, float a12, float a13,
                float a20, float a21, float a22, float a23,
                float a30, float a31, float a32, float a33);

    ////////////////////////////////////////////////////////////
    /// \brief Construct a transform from another
    ///
    /// Copies the matrix from another transform (2D or 3D).
    ///
    ////////////////////////////////////////////////////////////
    Transform3D(const TransformBase &transform);

    ////////////////////////////////////////////////////////////
    /// \brief Return the inverse of the transform
    ///
    /// If the inverse cannot be computed, an identity transform
    /// is returned.
    ///
    /// \return A new transform which is the inverse of self
    ///
    ////////////////////////////////////////////////////////////
    Transform3D getInverse() const;

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with another one
    ///
    /// The result is a transform that is equivalent to applying
    /// *this followed by \a transform. Mathematically, it is
    /// equivalent to a matrix multiplication.
    ///
    /// \param transform Transform to combine with this transform
    ///
    /// \return Reference to *this
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& combine(const TransformBase& transform);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with an orthographic projection
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.frustum(-1, 1, -1, 1, -1, 1);
    /// \endcode
    ///
    /// \param left X-coordinate projected to left edge of screen
    /// \param right X-coordinate projected to right edge of screen
    /// \param bottom Y-coordinate projected to bottom edge of screen
    /// \param top Y-coordinate projected to top edge of screen
    /// \param znear Z-coordinate projected to near clipping plane
    /// \param zfar Z-coordinate projected to far clipping plane
    ///
    /// \return Reference to *this
    ///
    /// \see frustum, perspective, lookAt
    ///
    ////////////////////////////////////////////////////////////
    Transform3D &orthographic(float left, float right, float bottom, float top, float znear, float zfar);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with an orthographic projection
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.frustum(-1, 1, -1, 1, -1, 1);
    /// \endcode
    ///
    /// \param left X-coordinate projected to left edge of screen
    /// \param right X-coordinate projected to right edge of screen
    /// \param bottom Y-coordinate projected to bottom edge of screen
    /// \param top Y-coordinate projected to top edge of screen
    ///
    /// \return Reference to *this
    ///
    /// \see frustum, perspective, lookAt
    ///
    ////////////////////////////////////////////////////////////
    Transform3D &orthographic(float left, float right, float bottom, float top);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a frustum projection
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.frustum(-1, 1, -1, 1, 0.1, 100.0);
    /// \endcode
    ///
    /// \param left X-coordinate projected to left edge of screen
    /// \param right X-coordinate projected to right edge of screen
    /// \param bottom Y-coordinate projected to bottom edge of screen
    /// \param top Y-coordinate projected to top edge of screen
    /// \param znear Z-coordinate projected to near clipping plane
    /// \param zfar Z-coordinate projected to far clipping plane
    ///
    /// \return Reference to *this
    ///
    /// \see orthographic, perspective, lookAt
    ///
    ////////////////////////////////////////////////////////////
    Transform3D &frustum(float left, float right, float bottom, float top, float znear, float zfar);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a perspective projection
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.perspective(75, 16.f/9.f, 0.1, 100.0);
    /// \endcode
    ///
    /// \param fov Field of view (in degrees) between top and bottom of screen
    /// \param aspect Aspect ratio of screen (width / height)
    /// \param znear Z-coordinate projected to near clipping plane
    /// \param zfar Z-coordinate projected to far clipping plane
    ///
    /// \return Reference to *this
    ///
    /// \see orthographic, frustum, lookAt
    ///
    ////////////////////////////////////////////////////////////
    Transform3D &perspective(float fov, float aspect, float znear, float zfar);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with an orientation transform
    ///
    /// An orientation transform adjusts the projection such that the viewer is
    /// positioned at \a eye, looking toward \a target, with \a up pointing
    /// toward the top of the screen.
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.lookAt(eye, target, up);
    /// \endcode
    ///
    /// \param eye Field of view (in degrees) between top and bottom of screen
    /// \param target Aspect ratio of screen (width / height)
    /// \param up Z-coordinate projected to near clipping plane
    ///
    /// \return Reference to *this
    ///
    /// \see orthographic, frustum, perspective
    ///
    ////////////////////////////////////////////////////////////
    Transform3D &lookAt(const sf::Vector3f &eye, const sf::Vector3f &target, const sf::Vector3f &up = sf::Vector3f(0.0f, 1.0f, 0.0f));

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a translation
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.translate(sf::Vector3f(100, 200)).rotate(45);
    /// \endcode
    ///
    /// \param offset Translation offset to apply
    ///
    /// \return Reference to *this
    ///
    /// \see rotate, scale
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& translate(const Vector3f& offset);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a rotation
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.rotate(90).translate(50, 20);
    /// \endcode
    ///
    /// \param angle Rotation angle, in degrees
    /// \param axis Rotation axis
    ///
    /// \return Reference to *this
    ///
    /// \see translate, scale
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& rotate(float angle, const Vector3f &axis);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a rotation
    ///
    /// The center of rotation is provided for convenience as a second
    /// argument, so that you can build rotations around arbitrary points
    /// more easily (and efficiently) than the usual
    /// translate(-center).rotate(angle).translate(center).
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.rotate(90, sf::Vector3f(8, 3)).translate(sf::Vector3f(50, 20));
    /// \endcode
    ///
    /// \param angle Rotation angle, in degrees
    /// \param axis Rotation axis
    /// \param center Center of rotation
    ///
    /// \return Reference to *this
    ///
    /// \see translate, scale
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& rotate(float angle, const Vector3f &axis, const Vector3f& center);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a scaling
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.scale(2, 1).rotate(45);
    /// \endcode
    ///
    /// \param factor Scaling factor
    ///
    /// \return Reference to *this
    ///
    /// \see translate, rotate
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& scale(float factor);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a scaling
    ///
    /// The center of scaling is provided for convenience as a second
    /// argument, so that you can build scaling around arbitrary points
    /// more easily (and efficiently) than the usual
    /// translate(-center).scale(factors).translate(center).
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.scale(sf::Vector3f(2, 1), sf::Vector3f(8, 3)).rotate(45);
    /// \endcode
    ///
    /// \param factor Scaling factor
    /// \param center Center of scaling
    ///
    /// \return Reference to *this
    ///
    /// \see translate, rotate
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& scale(float factor, const Vector3f& center);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a scaling
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.scale(sf::Vector3f(2, 1)).rotate(45);
    /// \endcode
    ///
    /// \param factors Scaling factors
    ///
    /// \return Reference to *this
    ///
    /// \see translate, rotate
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& scale(const Vector3f& factors);

    ////////////////////////////////////////////////////////////
    /// \brief Combine the current transform with a scaling
    ///
    /// The center of scaling is provided for convenience as a second
    /// argument, so that you can build scaling around arbitrary points
    /// more easily (and efficiently) than the usual
    /// translate(-center).scale(factors).translate(center).
    ///
    /// This function returns a reference to *this, so that calls
    /// can be chained.
    /// \code
    /// sf::Transform3D transform;
    /// transform.scale(sf::Vector3f(2, 1), sf::Vector3f(8, 3)).rotate(45);
    /// \endcode
    ///
    /// \param factors Scaling factors
    /// \param center Center of scaling
    ///
    /// \return Reference to *this
    ///
    /// \see translate, rotate
    ///
    ////////////////////////////////////////////////////////////
    Transform3D& scale(const Vector3f& factors, const Vector3f& center);
};

} // namespace sf


#endif // SFML_TRANSFORM3D_HPP


////////////////////////////////////////////////////////////
/// \class sf::Transform3D
/// \ingroup graphics
///
/// A sf::Transform3D specifies how to translate, rotate, scale,
/// shear, project, whatever things. In mathematical terms, it defines
/// how to transform a coordinate system into another.
///
/// For example, if you apply a rotation transform to a sprite, the
/// result will be a rotated sprite. And anything that is transformed
/// by this rotation transform will be rotated the same way, according
/// to its initial position.
///
/// Transforms are typically used for drawing. But they can also be
/// used for any computation that requires to transform points between
/// the local and global coordinate systems of an entity (like collision
/// detection).
///
/// Example:
/// \code
/// // define a translation transform
/// sf::Transform3D translation;
/// translation.translate(20, 50);
///
/// // define a rotation transform
/// sf::Transform3D rotation;
/// rotation.rotate(45);
///
/// // combine them
/// sf::Transform3D transform = translation * rotation;
///
/// // use the result to transform stuff...
/// sf::Vector3f point = transform.transformPoint(10, 20);
/// sf::FloatRect rect = transform.transformRect(sf::FloatRect(0, 0, 10, 100));
/// \endcode
///
/// \see sf::Transformable, sf::RenderStates
///
////////////////////////////////////////////////////////////
