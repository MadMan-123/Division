#include <stdio.h>

#include "maths.h"


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
