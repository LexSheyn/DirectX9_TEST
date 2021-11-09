#pragma once

namespace dx9
{
	class Vector2f
	{
	public:

	// Constructors:

		Vector2f();
		Vector2f(float _x, float _y);

	// Operators:

		bool operator == (const Vector2f& other) const;

		bool operator != (const Vector2f& other) const;

		Vector2f operator + (const Vector2f& right) const;

		Vector2f operator - (const Vector2f& right) const;

		Vector2f operator * (const float& other) const;

		Vector2f operator / (const float& other) const;

	// Variables:

		float x;
		float y;
	};
}
