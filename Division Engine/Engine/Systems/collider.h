
#pragma once
#include "../Core/maths.h"


typedef enum
{
	Circle,
	Box
} ColliderType;

typedef struct {
	ColliderType type;
	bool isColliding;
	int layer;
	void* state;
} Collider;


Collider* createCircleCollider(float radius);
bool cleanCollider(Collider* col);
bool isCollidingCircle(Vec2 posA, float radA, Vec2 posB, float radB);
float getRadius(Collider* col);
