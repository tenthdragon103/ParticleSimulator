//
// Created by tdragon on 9/8/26.
//

#include "vec2.h"

#include <math.h>

Vec2 vec2_create(float x, float y)
{
    Vec2 result;

    result.x = x;
    result.y = y;

    return result;
}

Vec2 vec2_zero(void)
{
    return vec2_create(0.0f, 0.0f);
}

Vec2 vec2_add(Vec2 a, Vec2 b)
{
    return vec2_create(
        a.x + b.x,
        a.y + b.y
    );
}

Vec2 vec2_sub(Vec2 a, Vec2 b)
{
    return vec2_create(
        a.x - b.x,
        a.y - b.y
    );
}

Vec2 vec2_mul(Vec2 v, float scalar)
{
    return vec2_create(
        v.x * scalar,
        v.y * scalar
    );
}

Vec2 vec2_div(Vec2 v, float scalar)
{
    if (scalar == 0.0f)
    {
        return vec2_zero();
    }

    return vec2_create(
        v.x / scalar,
        v.y / scalar
    );
}

float vec2_dot(Vec2 a, Vec2 b)
{
    return a.x * b.x + a.y * b.y;
}

float vec2_length_squared(Vec2 v)
{
    return vec2_dot(v, v);
}

float vec2_length(Vec2 v)
{
    return sqrtf(vec2_length_squared(v));
}

Vec2 vec2_normalize(Vec2 v)
{
    float length = vec2_length(v);

    if (length <= 0.000001f)
    {
        return vec2_zero();
    }

    return vec2_div(v, length);
}