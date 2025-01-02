
#pragma once
#include "../Core/maths.h"
#include <stdint.h>
//TODO: Define.h needed


#define FNCPTR(name,type,...) type (*name)(__VA_ARGS__)

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
	FNCPTR(
			response,
			void,
			uint32_t self,
			uint32_t other,
			void* ecs
				
	);

} Collider;


DIVAPI Collider* createCircleCollider(float radius);
DIVAPI Collider* createBoxCollider(Vec2 scale);
DIVAPI bool cleanCollider(Collider* col);
DIVAPI bool isCircleColliding(Vec2 posA, float radA, Vec2 posB, float radB);
DIVAPI bool isBoxColliding(Vec2 posA, Vec2 scaleA, Vec2 posB, Vec2 scaleB);
DIVAPI float getRadius(Collider* col);
DIVAPI Vec2 getScale(Collider* col);
DIVAPI bool setBoxScale(Collider* col, Vec2 scale);

