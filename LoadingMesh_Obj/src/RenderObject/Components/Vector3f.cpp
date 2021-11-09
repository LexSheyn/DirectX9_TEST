#include "../../PrecompiledHeaders/stdafx.h"
#include "Vector3f.h"

namespace dx9
{
// Constructors:

	Vector3f::Vector3f()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}

	Vector3f::Vector3f(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}


// Operators:

	bool Vector3f::operator == (const Vector3f& other) const
	{
		return (x == other.x && y == other.y && z == other.z);
	}

	bool Vector3f::operator != (const Vector3f& other) const
	{
		return !(x == other.x && y == other.y && z == other.z);
	}

	Vector3f Vector3f::operator + (const Vector3f& right) const
	{
		return Vector3f(x + right.x, y + right.y, z + right.z);
	}

	Vector3f Vector3f::operator - (const Vector3f& right) const
	{
		return Vector3f(x - right.x, y - right.y, z - right.z);
	}

	Vector3f Vector3f::operator * (const float& other) const
	{
		return Vector3f(x * other, y * other, z * other);
	}

	Vector3f operator * (const float& left, const Vector3f& right)
	{
		return Vector3f(left * right.x, left * right.y, left * right.z);
	}

	Vector3f Vector3f::operator / (const float& other) const
	{
		return Vector3f(x / other, y / other, z / other);
	}

}