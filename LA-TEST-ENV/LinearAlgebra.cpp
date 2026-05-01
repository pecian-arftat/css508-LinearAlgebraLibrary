#include "pch.h"

#include "LinearAlgebra.h"

bool almostEqual(double a, double b, double eps)
{
    return std::abs(a - b) < eps;
}

bool almostEqualVec3(const Vec3& a, const Vec3& b, double eps)
{
    return almostEqual(a.x, b.x, eps) &&
        almostEqual(a.y, b.y, eps) &&
        almostEqual(a.z, b.z, eps);
}


double dot4(const Vec4& a, const Vec4& b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

Vec3 cross3(const Vec3& a, const Vec3& b)
{
    return {
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    };
}

Vec3 rotateEulerZ(const Vec3& v, double angleDegrees)
{
    double radians = angleDegrees * PI / 180.0;
    double cosA = std::cos(radians);
    double sinA = std::sin(radians);

    return {
        v.x * cosA - v.y * sinA,
        v.x * sinA + v.y * cosA,
        v.z
    };
}

double magnitude(const Vec3& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

Quat quatFromAxisAngle(const Vec3& axis, double angleDegrees)
{
    double radians = angleDegrees * PI / 180.0;
    double halfAngle = radians / 2.0;
    double sinHalf = std::sin(halfAngle);

    return {
        std::cos(halfAngle),
        axis.x * sinHalf,
        axis.y * sinHalf,
        axis.z * sinHalf
    };
}

Quat normalizeQuat(const Quat& q)
{
    double mag = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
    return {
        q.w / mag,
        q.x / mag,
        q.y / mag,
        q.z / mag
    };
}

Quat quatMultiply(const Quat& a, const Quat& b)
{
    return {
		a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,  // Scalar part
        a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,  // i component
        a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x,  // j component
        a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w   // k component
    };
}

Vec3 quatRotate(const Quat& q, const Vec3& v)
{
    // Convert vector to quaternion form (w=0)
    Quat vq{ 0, v.x, v.y, v.z };

    // Calculate q * vq * q^-1
    Quat qInv{ q.w, -q.x, -q.y, -q.z }; // Inverse of a unit quaternion is its conjugate
    Quat temp = quatMultiply(q, quatMultiply(vq, qInv));

    return { temp.x, temp.y, temp.z };
}

