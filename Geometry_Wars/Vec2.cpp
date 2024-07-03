
#include "Vec2.h"
#include <cmath> // for std::sqrt


Vec2::Vec2()
	: x(0.0f)
	, y(0.0f)
{}

Vec2::Vec2( float xin , float yin )
	: x(xin)
	, y(yin) 
{}



bool Vec2::operator == (const Vec2& rhs) const
{
	return (x == rhs.x && y == rhs.y);
}

bool Vec2::operator != (const Vec2& rhs) const
{
	return !(x == rhs.x && y == rhs.y);
}



Vec2 Vec2::operator + (const Vec2& rhs) const
{
	return Vec2(x + rhs.x, y + rhs.y);
}

Vec2 Vec2::operator - (const Vec2& rhs) const
{
	return Vec2(x - rhs.x, y - rhs.y);
}

Vec2 Vec2::operator / (const Vec2& rhs) const
{
	return Vec2(x / rhs.x, y / rhs.y);
}

Vec2 Vec2::operator * (const Vec2& rhs) const
{
	return Vec2(x * rhs.x, y * rhs.y);
}


void Vec2::operator += (const Vec2& rhs)
{
	x += rhs.x;
	y += rhs.y;
}
void Vec2::operator -= (const Vec2& rhs)
{
	x -= rhs.x;
	y -= rhs.y;
}
void Vec2::operator /= (const Vec2& rhs)
{
	x /= rhs.x;
	y /= rhs.y;
}
void Vec2::operator *= (const Vec2& rhs)
{
	x *= rhs.x;
	y *= rhs.y;
}


float Vec2::dist(const Vec2& rhs) const
{
	return sqrt(((x - rhs.x) * (x - rhs.x)) + ((y - rhs.y) * (y - rhs.y)));
}
