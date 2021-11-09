#include "../../PrecompiledHeaders/stdafx.h"
#include "Vector2f.h"

namespace gfx
{
// Constructors:

	Vector2f::Vector2f()
	{
		x = 0.0f;
		y = 0.0f;
	}

	Vector2f::Vector2f(float _x, float _y)
	{
		x = _x;
		y = _y;
	}


// Operators:

	bool Vector2f::operator == (const Vector2f& other) const
	{
		return (x == other.x && y == other.y);
	}

	bool Vector2f::operator != (const Vector2f& other) const
	{
		return !(x == other.x && y == other.y);
	}

	Vector2f Vector2f::operator + (const Vector2f& right) const
	{
		return Vector2f(x + right.x, y + right.y);
	}

	Vector2f Vector2f::operator - (const Vector2f& right) const
	{
		return Vector2f(x - right.x, y - right.y);
	}

	Vector2f Vector2f::operator * (const float& other) const
	{
		return Vector2f(x * other, y * other);
	}

	Vector2f Vector2f::operator / (const float& other) const
	{
		return Vector2f(x / other, y / other);
	}

}