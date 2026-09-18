//
// Created by tdragon on 9/8/26.
//

#ifndef PARTICLESIMULATOR_VEC2_H
#define PARTICLESIMULATOR_VEC2_H

typedef struct
{
    float x;
    float y;
} Vec2;

Vec2 vec2_create(float x, float y);

Vec2 vec2_zero(void);

Vec2 vec2_add(Vec2 a, Vec2 b);

Vec2 vec2_sub(Vec2 a, Vec2 b);

Vec2 vec2_mul(Vec2 v, float scalar);

Vec2 vec2_div(Vec2 v, float scalar);

float vec2_dot(Vec2 a, Vec2 b);

float vec2_length_squared(Vec2 v);

float vec2_length(Vec2 v);

Vec2 vec2_normalize(Vec2 v);

#endif //PARTICLESIMULATOR_VEC2_H
