#pragma once

#include "Vector2f.h"
#include "Vector3f.h"

namespace dx9
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

}
