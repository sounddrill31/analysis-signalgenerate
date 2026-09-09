/* Copyright 2024 The MathWorks, Inc. */
#ifndef SPATIALMATHUTILS_HPP
#define SPATIALMATHUTILS_HPP
#include "SpatialMathUtilsSpec.hpp"
#include <array>
#include <cmath>
#include <tuple>
#include <vector>
namespace spatialmathutils {

/// A 4-by-4 homogeneous transformation matrix
typedef std::array<std::array<real64_T, 4>, 4> HomogeneousTransform;

/// A 3-by-3 matrix.
typedef std::array<std::array<real64_T, 3>, 3> Mat3;

/// A 6-by-6 spatial transformation matrix.
typedef std::array<std::array<real64_T, 6>, 6> SpatialTransform;

/// A 1-by-4 quaternion representing rotation.
typedef std::array<real64_T, 4> Quaternion;

/// An identity homogeneous transformation matrix.
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform identity();

/// Convert a translation vector to a homogeneous transformation matrix.
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform trvec2tform(const std::array<real64_T, 3>&);

/// Convert a translation vector to a homogeneous transformation matrix.
SPATIALMATH_CPP_UTILS_API
std::array<real64_T, 3> tform2trvec(const HomogeneousTransform&);

/// Invert a homogeneous transformation matrix.
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform inverttform(const HomogeneousTransform&);

/** Axis angle to a homogeneous transformation matrix.
 * @param ax a 3 element vector representing the axis of rotation.
 * @param ang a scalar value indicating the angle of rotation about axis ax.
 */
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform axang2tform(std::array<real64_T, 3> ax, real64_T ang);

/** Convert a rotation unit-quaternion to a homogeneous transformation matrix.
 * @param q a 3 element vector representing the axis of rotation.
 */
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform quat2tform(const std::array<real64_T, 4>& q);

/// Convert a homogeneous transform to a position and rotation quaternion.
SPATIALMATH_CPP_UTILS_API
std::tuple<std::array<real64_T, 3>, Quaternion> tform2posquat(const HomogeneousTransform&);

/// A 3-by-3 skew symmetric matrix of a size 3 vector
SPATIALMATH_CPP_UTILS_API
Mat3 skew(const std::array<real64_T, 3>&);

/// Multiply two square matrices
template <typename T, size_t SIZE>
SPATIALMATH_CPP_UTILS_API std::array<std::array<T, SIZE>, SIZE> mult(
    const std::array<std::array<T, SIZE>, SIZE>& mat1,
    const std::array<std::array<T, SIZE>, SIZE>& mat2) {
    std::array<std::array<T, SIZE>, SIZE> out;
    for (size_t i = 0; i < SIZE; ++i) {
        for (size_t j = 0; j < SIZE; ++j) {
            out[i][j] = 0;
            for (size_t k = 0; k < SIZE; ++k) {
                out[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return out;
}

/// Multiply a spatial transform to a Jacobian
SPATIALMATH_CPP_UTILS_API
std::vector<std::array<real64_T, 6>> spatiallyTransformJacobian(
    const SpatialTransform&,
    const std::vector<std::array<real64_T, 6>>&);

/// Multiply a spatial transform to a size 6 column vector
SPATIALMATH_CPP_UTILS_API
std::vector<std::array<real64_T, 6>> spatiallyTransformVector(
    const SpatialTransform&,
    const std::vector<std::array<real64_T, 6>>&);

/// Convert a homogeneous transformation matrix to a spatial transformation
/// matrix
SPATIALMATH_CPP_UTILS_API
SpatialTransform tformToSpatialXform(const HomogeneousTransform&);

/// Convert a C-style array of size 16 to a 4-by-4 homogeneous transformation
/// matrix
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform array2tform(const real64_T[16]);

/// Extract the rotation transformation from a homogeneous transformation
/// matrix
SPATIALMATH_CPP_UTILS_API
HomogeneousTransform tform2rottform(const HomogeneousTransform&);

/// Convert a homogeneous transform to a rotation quaternion.
SPATIALMATH_CPP_UTILS_API
Quaternion tform2quat(const HomogeneousTransform&);

} // namespace spatialmathutils
#endif // SPATIALMATHUTILS_HPP
