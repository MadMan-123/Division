
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
Collider* createBoxCollider(Vec2 scale);
bool cleanCollider(Collider* col);
bool isCircleColliding(Vec2 posA, float radA, Vec2 posB, float radB);
bool isBoxColliding(Vec2 posA, Vec2 scaleA, Vec2 posB, Vec2 scaleB);
float getRadius(Collider* col);
Vec2 getScale(Collider* col);
bool setBoxScale(Collider* col, Vec2 scale);

