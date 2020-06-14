#pragma once
#include "MainStructs.h"
#pragma region UTILITIES

#define SAFE_DELETE(p) if (p) { delete (p); (p) = nullptr; }
#define UNREFERENCED_PARAMETER(x) (x)

inline float Distance(const FVector2 & v1, const FVector2 & v2)
{
	float a = v2.x - v1.x;
	float b = v2.y - v1.y;
	a *= a;
	b *= b;
	return sqrtf(a + b);
}

#pragma endregion UTILITIES