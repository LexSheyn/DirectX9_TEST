#include "../../PrecompiledHeaders/stdafx.h"
#include "VectorMath.h"

namespace dx9
{
// Cross Product:

	Vector3f CrossProduct(const Vector3f a, const Vector3f b)
	{
		return Vector3f(a.y * b.z - a.z * b.y,
			            a.z * b.x - a.x * b.z,
			            a.x * b.y - a.y * b.x);
	}


// Dot Product:

	float DotProduct(const Vector2f a, const Vector2f b)
	{
		return (a.x * b.x) + (a.y * b.y);
	}

	float DotProduct(const Vector3f a, const Vector3f b)
	{
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	}


// Magnitude:

	float Magnitude(const Vector2f in)
	{
		return (std::sqrtf(std::powf(in.x, 2) + std::powf(in.y, 2)));
	}

	float Magnitude(const Vector3f in)
	{
		return (std::sqrtf(std::powf(in.x, 2) + std::powf(in.y, 2) + std::powf(in.z, 2)));
	}


// Angle between:

	float AngleBetween(const Vector2f a, const Vector2f b)
	{
		float angle = DotProduct(a, b);

		angle /= (Magnitude(a) * Magnitude(b));

		return angle = std::acosf(angle);
	}

	float AngleBetween(const Vector3f a, const Vector3f b)
	{
		float angle = DotProduct(a, b);

		angle /= (Magnitude(a) * Magnitude(b));

		return angle = std::acosf(angle);
	}


// Projection:

	Vector2f Projection(const Vector2f a, const Vector2f b)
	{
		Vector2f unit_b = b / Magnitude(b);

		return unit_b * DotProduct(a, unit_b);
	}

	Vector3f Projection(const Vector3f a, const Vector3f b)
	{
		Vector3f unit_b = b / Magnitude(b);

		return unit_b * DotProduct(a, unit_b);
	}

}