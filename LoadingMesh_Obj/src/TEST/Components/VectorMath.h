#ifndef VECTORMATH_H
#define VECTORMATH_H

#include "Vector2f.h"
#include "Vector3f.h"

namespace gfx
{
// Cross product:

	// Vector2 Cross Product.
	Vector3f CrossProduct(const Vector3f a, const Vector3f b);


// DotProduct:

	// Vector2 DotProduct.
	float DotProduct(const Vector2f a, const Vector2f b);

	// Vector3 DotProduct.
	float DotProduct(const Vector3f a, const Vector3f b);


// Magnitude:

	// Vector2 Magnitude calculation.
	float Magnitude(const Vector2f in);

	// Vector3 Magnitude calculation.
	float Magnitude(const Vector3f in);


// Angle between:

	// Angle between 2 Vector2 Objects.
	float AngleBetween(const Vector2f a, const Vector2f b);

	// Angle between 2 Vector3 Objects.
	float AngleBetween(const Vector3f a, const Vector3f b);


// Projection:

	// Projection Calculation of a onto b.
	Vector2f Projection(const Vector2f a, const Vector2f b);

	// Projection Calculation of a onto b.
	Vector3f Projection(const Vector3f a, const Vector3f b);


// Same Size:

	// A test to see if P1 is on the same side as P2 of a line segment ab.
	bool SameSide(Vector3f p1, Vector3f p2, Vector3f a, Vector3f b);


// Generate Triangle Normal:

	// Generate a cross produect normal for a triangle.
	Vector3f GenerateTriangleNormal(Vector3f t1, Vector3f t2, Vector3f t3);


// In Triangle:

	// Check to see if a Vector3 Point is within a 3 Vector3 Triangle.
	bool InTriangle(Vector3f point, Vector3f tri1, Vector3f tri2, Vector3f tri3);
}

#endif // VERTORMATH_H