#include "pch.h"

// ------------------------------------------------------------
// Constants and Type Definitions
// ------------------------------------------------------------

const double EPS = 1e-6; // Tolerance for floating-point comparisons
const double PI = 3.14159265358979323846; // Pi constant

struct Vec3 
{
	double x, y, z;

	Vec3 operator+(const Vec3& other) const 
	{
		return { x + other.x, y + other.y, z + other.z };
	}

	Vec3 operator-(const Vec3& other) const 
	{
		return { x - other.x, y - other.y, z - other.z };
	}

	Vec3 operator*(double scalar) const 
	{
		return { x * scalar, y * scalar, z * scalar };
	}

	friend Vec3 operator*(double scalar, const Vec3& v)
	{
		return { v.x * scalar, v.y * scalar, v.z * scalar };
	}

	Vec3 operator/(double scalar) const 
	{
		return { x / scalar, y / scalar, z / scalar };
	}

};

struct Vec4 
{
	double x, y, z, w;

	Vec4 operator+(const Vec4& other) const 
	{
		return { x + other.x, y + other.y, z + other.z, w + other.w };
	}

	Vec4 operator-(const Vec4& other) const 
	{
		return { x - other.x, y - other.y, z - other.z, w - other.w };
	}

	Vec4 operator*(double scalar) const 
	{
		return { x * scalar, y * scalar, z * scalar, w * scalar };
	}

	Vec4 operator/(double scalar) const
	{
		return { x / scalar, y / scalar, z / scalar, w / scalar };
	}
};

struct Quat 
{
	double w, x, y, z;
};

// ------------------------------------------------------------
// Utility functions (Not intended to be part of the main implementation, but useful for testing and validation)
// ------------------------------------------------------------

// This function is intended to take in expected values and actual values, and compare them within a specified tolerance (EPS).
bool almostEqual(double a, double b, double eps = EPS);

// This function is intended to compare two Vec3 objects for approximate equality, component-wise, within a specified tolerance (EPS).
bool almostEqualVec3(const Vec3& a, const Vec3& b, double eps = EPS);

// ------------------------------------------------------------
// Utility function intended to be used by clients. 
// ------------------------------------------------------------

// Usage: This function takes two Vec3 objects and computes their dot product, which is the sum of the products of their corresponding components (x, y, z).
double dot3(const Vec3& a, const Vec3& b);

// Usage: This function takes two Vec3 objects and computes their cross product, which results in a new Vec3 that is perpendicular to both input vectors. 
// The components of the resulting vector are calculated using the determinant of a matrix formed by the input vectors.
Vec3 cross3(const Vec3& a, const Vec3& b);

// Usage: This function applies a rotation around the X-axis to a Vec3 using Euler angles. 
// The angle is provided in degrees, and the function converts it to radians before applying the rotation transformation to the input vector.
Vec3 rotateEulerX(const Vec3& v, double angleDegrees);

// Usage: This function applies a rotation around the Y-axis to a Vec3 using Euler angles. 
// The angle is provided in degrees, and the function converts it to radians before applying the rotation transformation to the input vector.
Vec3 rotateEulerY(const Vec3& v, double angleDegrees);

// Usage: This function applies a rotation around the Z-axis to a Vec3 using Euler angles.
// The angle is provided in degrees, and the function converts it to radians before applying the rotation transformation to the input vector.
Vec3 rotateEulerZ(const Vec3& v, double angleDegrees);

// Usage: This function calculates the magnitude (length) of a Vec3 vector, which is the square root of the sum of the squares of its components (x, y, z).
double magnitude(const Vec3& v);

// Usage: This function creates a quaternion representing a rotation around a specified axis by a given angle in degrees.
Quat quatFromAxisAngle(const Vec3& axis, double angleDegrees);

// Usage: This function normalizes a quaternion, which involves scaling the quaternion so that its magnitude (length) is 1.
Quat normalizeQuat(const Quat& q);

// Usage: This function multiplies two quaternions, which combines their rotations. 
// The resulting quaternion represents the rotation of applying the second quaternion followed by the first quaternion.
Quat quatMultiply(const Quat& a, const Quat& b);

// Usage: This function applies a quaternion rotation to a Vec3 vector.
// The function converts the vector into a quaternion form (with w=0), 
// then performs the rotation by multiplying the quaternion with the vector quaternion and the inverse of the quaternion.
// It is expected that the input quaternion is normalized for correct rotation results.
Vec3 quatRotate(const Quat& q, const Vec3& v);
