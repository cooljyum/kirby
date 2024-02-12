#include "Framework.h"
#include "Math.h"

int GameMath::Random(const int& min, const int& max)
{
    return rand() % (max - min) + min;
}

float GameMath::Random(const float& min, const float& max)
{
    float normal = (float)rand() / RAND_MAX;

    return (max - min) * normal + min;
}

Vector2 GameMath::Random(const Vector2& min, const Vector2& max)
{
    return Vector2(Random(min.x, max.x), Random(min.y, max.y));
}

float GameMath::Lerp(const float& s, const float& e, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return s + (e - s) * t;
}

Vector2 GameMath::Lerp(const Vector2& s, const Vector2& e, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return s + (e - s) * t;
}

float GameMath::SLerp(const float& s, const float& e, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return s + (e - s) * t * t;
}

Vector2 GameMath::SLerp(const Vector2& s, const Vector2& e, float t)
{
    t = Clamp(0.0f, 1.0f, t);

    return s + (e - s) * pow(t, 2.0f);    
}

float GameMath::Clamp(const float& min, const float& max, const float& value)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}

float GameMath::Distance(const Vector2& v1, const Vector2& v2)
{
    return (v1 - v2).Magnitude();
}
