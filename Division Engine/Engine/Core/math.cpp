#include <stdio.h>

#include "maths.h"
#include <cmath>


Vec2 v2Add(Vec2 a, Vec2 b)
{
    return { a.x + b.x, a.y + b.y };
}


Vec2 v2Sub(Vec2 a, Vec2 b)
{
    return { a.x - b.x, a.y - b.y };
}


Vec2 v2Mul(Vec2 a, float b)
{
    return {a.x * b, a.y * b };
}


Vec2 v2Mul(Vec2 a, Vec2 b)
{
    return { a.x * b.x, a.y * b.y };
}

float v2Mag(Vec2 a)
{
    return sqrt(pow(a.x, 2) + pow(a.y, 2));
}

float v2Dis(Vec2 a, Vec2 b)
{
    return  (v2Mag(v2Sub(b, a)));
}
