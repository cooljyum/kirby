#pragma once

struct Vector2
{
	float x = 0.0f;
	float y = 0.0f;

	Vector2() = default;
	Vector2(float x, float y) : x(x), y(y)
	{
	}
	Vector2(POINT point) : x(point.x), y(point.y)
	{}

	//operator POINT()
	//{
	//	return { (int)x, (int)y };
	//}

	Vector2 operator+(const Vector2& v) const
	{
		return Vector2(x + v.x, y + v.y);
	}

	Vector2 operator-(const Vector2& v) const
	{
		return Vector2(x - v.x, y - v.y);
	}

	Vector2 operator*(const Vector2& v) const
	{
		return Vector2(x * v.x, y * v.y);
	}

	Vector2 operator/(const Vector2& v) const
	{
		return Vector2(x / v.x, y / v.y);
	}

	void operator+=(const Vector2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator-=(const Vector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	Vector2 operator*(const float& s) const
	{
		return Vector2(x * s, y * s);
	}

	Vector2 operator/(const float& s) const
	{
		return Vector2(x / s, y / s);
	}

	void operator*=(const float& s)
	{
		x *= s;
		y *= s;
	}
	void operator/=(const float& s)
	{
		x /= s;
		y /= s;
	}

	float Magnitude() const
	{
		return sqrt(x * x + y * y);
	}

	float SqrMagnitude() const
	{
		return x * x + y * y;
	}

	void Normalize()
	{
		float length = Magnitude();

		x /= length;
		y /= length;
	}

	float Angle() const
	{
		return atan2(-y, x);
	}

	Vector2 Normalized() const
	{
		float length = Magnitude();

		return Vector2(x / length, y / length);
	}

	static float Cross(const Vector2& v1, const Vector2& v2)
	{
		return v1.x * v2.y - v1.y * v2.x;
	}

	static Vector2 Left() { return Vector2(-1.0f, 0.0f); }
	static Vector2 Right() { return Vector2(+1.0f, 0.0f); }
	static Vector2 Up() { return Vector2(0.0f, -1.0f); }
	static Vector2 Down() { return Vector2(0.0f, +1.0f); }
};