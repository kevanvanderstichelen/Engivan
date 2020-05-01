#pragma once
#include "MiniginPCH.h"
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#pragma warning(pop)

struct FPoint2
{
	FPoint2() : x(0), y(0) {}
	explicit FPoint2(float x, float y) : x(x), y(y) {}

	float x;
	float y;

	inline bool operator!=(FPoint2& pos) { return (x != pos.x) && (y != pos.y); };
	inline bool operator!=(const FPoint2& pos) { return (x != pos.x) && (y != pos.y); };

};

struct FRect
{
	FRect() :left(0.f), bottom(0.f), width(0.f), height(0.f) {}
	explicit FRect(float left, float bottom, float width, float height)
		:left(left), bottom(bottom), width(width), height(height) {}
	explicit FRect(FPoint2 pos, float width, float height)
		:left(pos.x), bottom(pos.y), width(width), height(height) {}

	const FPoint2 GetHalf() { return FPoint2(width / 2, height / 2); }

	float left, bottom, width, height;
};

struct FColor3
{
	FColor3() :r(0.f), g(0.f), b(0.f) {}
	explicit FColor3(float r, float g, float b)
		:r(r), g(g), b(b) {}

	float r, g, b;
};

struct FColor4
{
	FColor4() :r(0.f), g(0.f), b(0.f), a(1.f) {}
	explicit FColor4(float r, float g, float b, float a)
		:r(r), g(g), b(b), a(a) {}

	float r, g, b, a;
};



struct FCircle
{
	FCircle()
		: center(0, 0), radiusX(0), radiusY(0) {}
	explicit FCircle(const FPoint2& center, float radius)
		: center(center.x, center.y), radiusX(radius), radiusY(radius) {}
	explicit FCircle(float centerX, float centerY, float radius)
		: center(centerX, centerY), radiusX(radius), radiusY(radius) {}
	explicit FCircle(float centerX, float centerY, float radiusX, float radiusY)
		: center(centerX, centerY), radiusX(radiusX), radiusY(radiusY) {}

	FPoint2 center;
	float radiusX;
	float radiusY;

};




typedef unsigned int uint;
typedef glm::vec2 FVector2;
typedef glm::vec3 FVector3;