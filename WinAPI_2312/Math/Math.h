#pragma once

namespace GameMath
{
	int Random(const int& min, const int& max);
	float Random(const float& min, const float& max);
	Vector2 Random(const Vector2& min, const Vector2& max);

	float Lerp(const float& s, const float& e, float t);
	Vector2 Lerp(const Vector2& s, const Vector2& e, float t);

	float SLerp(const float& s, const float& e, float t);
	Vector2 SLerp(const Vector2& s, const Vector2& e, float t);

	float Clamp(const float& min, const float& max, const float& value);

	float Distance(const Vector2& v1, const Vector2& v2);
}

using namespace GameMath;