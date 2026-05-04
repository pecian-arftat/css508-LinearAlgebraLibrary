#include "pch.h"

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

bool almostEqual(double a, double b, double eps = EPS);

bool almostEqualVec3(const Vec3& a, const Vec3& b, double eps = EPS);

double dot4(const Vec4& a, const Vec4& b);

Vec3 cross3(const Vec3& a, const Vec3& b);

// Added Euler rotation functions for testing purposes (not part of the main implementation)
Vec3 rotateEulerX(const Vec3& v, double angleDegrees);

// Added Euler rotation functions for testing purposes (not part of the main implementation)
Vec3 rotateEulerY(const Vec3& v, double angleDegrees);

Vec3 rotateEulerZ(const Vec3& v, double angleDegrees);

double magnitude(const Vec3& v);

Quat quatFromAxisAngle(const Vec3& axis, double angleDegrees);

Quat normalizeQuat(const Quat& q);

Quat quatMultiply(const Quat& a, const Quat& b);

Vec3 quatRotate(const Quat& q, const Vec3& v);
