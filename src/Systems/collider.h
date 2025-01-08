
#pragma once
#include "../Core/maths.h"
#include <stdint.h>



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
	void (*response)(uint32_t self, uint32_t other);
} Collider;


DIVAPI Collider* createCircleCollider(float radius);
DIVAPI Collider* createBoxCollider(Vec2 scale);
DIVAPI bool cleanCollider(Collider* col);
DIVAPI bool isCircleColliding(Vec2 posA, float radA, Vec2 posB, float radB);
DIVAPI bool isBoxColliding(Vec2 posA, Vec2 scaleA, Vec2 posB, Vec2 scaleB);
DIVAPI float getRadius(Collider* col);
DIVAPI Vec2 getScale(Collider* col);
DIVAPI bool setBoxScale(Collider* col, Vec2 scale);

