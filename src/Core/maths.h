#pragma once
#include "../definitions.h"

typedef struct {
	int x, y;
}Vec2i;

typedef struct {
	float x, y;
}Vec2;

DIVAPI Vec2 v2Add(Vec2 a, Vec2 b);
DIVAPI Vec2 v2Sub(Vec2 a, Vec2 b);
DIVAPI Vec2 v2Mul(Vec2 a, float b);
DIVAPI Vec2 v2Mul(Vec2 a, Vec2 b);
DIVAPI float v2Mag(Vec2 a);
DIVAPI float v2Dis(Vec2 a, Vec2 b);
DIVAPI Vec2i v2Tov2i(Vec2 a);
DIVAPI Vec2 v2iTov2(Vec2i a);
DIVAPI Vec2 v2Div(Vec2 a, float b);
