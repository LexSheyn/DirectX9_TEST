#include "../../PrecompiledHeaders/stdafx.h"
#include "VectorMath.h"

namespace gfx
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


// Same Size:

	bool SameSide(Vector3f p1, Vector3f p2, Vector3f a, Vector3f b)
	{
		Vector3f cp1 = CrossProduct(b - a, p1 - a);
		Vector3f cp2 = CrossProduct(b - a, p2 - a);

		if (DotProduct(cp1, cp2) >= 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


// Generate Triangle Normal:

	Vector3f GenerateTriangleNormal(Vector3f t1, Vector3f t2, Vector3f t3)
	{
		Vector3f u = t2 - t1;
		Vector3f v = t3 - t1;

		Vector3f normal = CrossProduct(u, v);

		return normal;
	}


// In Triangle: 

	bool inTriangle(Vector3f point, Vector3f tri1, Vector3f tri2, Vector3f tri3)
	{
		// Test to see if it is within an infinite prism that the triangle outlines.
		bool within_triangle_prism = SameSide(point, tri1, tri2, tri3) && SameSide(point, tri2, tri1, tri3) && SameSide(point, tri3, tri1, tri2);

		// If it isn't it will never be on the triangle.
		if (!within_triangle_prism)
		{
			return false;
		}

		// Calulate Triangle's Normal.
		Vector3f n = GenerateTriangleNormal(tri1, tri2, tri3);

		// Project the point onto this normal.
		Vector3f projection = Projection(point, n);

		// If the distance from the triangle to the point is 0
		// it lies on the triangle.
		if (Magnitude(projection) == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}