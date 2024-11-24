#pragma once

typedef struct {
	int x, y;
}Vec2i;

typedef struct {
	float x, y;

	
}Vec2;

Vec2 v2Add(Vec2 a, Vec2 b);
Vec2 v2Sub(Vec2 a, Vec2 b);
Vec2 v2Mul(Vec2 a, float b);
Vec2 v2Mul(Vec2 a, Vec2 b);
float v2Mag(Vec2 a);
float v2Dis(Vec2 a, Vec2 b);
