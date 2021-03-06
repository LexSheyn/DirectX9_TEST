#ifndef VECTOR3F_H
#define VECTOR3F_H

namespace gfx
{
	class Vector3f
	{
	public:

	// Constructors:

		Vector3f();
		Vector3f(float _x, float _y, float _z);

	// Operators:

		bool operator == (const Vector3f& other) const;

		bool operator != (const Vector3f& other) const;

		Vector3f operator + (const Vector3f& right) const;

		Vector3f operator - (const Vector3f& right) const;
		
		Vector3f operator * (const float& other) const;

		friend Vector3f operator * (const float& left, const Vector3f& right);

		Vector3f operator / (const float& other) const;

	// Variables:

		float x;
		float y;
		float z;
	};
}

#endif // VECTOR3F_H