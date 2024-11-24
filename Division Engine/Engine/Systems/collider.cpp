#include "collider.h"
#include <cstdlib>
#include <cstdio>

typedef struct
{
	float radius;
}CircleCollider;

Collider* createCircleCollider(float radius)
{
	Collider* allocatedCollider = (Collider*)malloc(sizeof(Collider));
	if (allocatedCollider == nullptr)
	{
		fprintf(stderr, "spherer colider allocation falied\n");
		return nullptr;
	}
	allocatedCollider->type = Circle;
	allocatedCollider->state = (CircleCollider*)malloc(sizeof(CircleCollider));
	auto iState = (CircleCollider*)(allocatedCollider->state);
	if (iState == nullptr)
	{
		fprintf(stderr, "cannot access the internal state for the sphere collider\n");
		return nullptr;
	}
	iState->radius = radius;
	
	return allocatedCollider;

}

float getRadius(Collider* col)
{
	auto colState = (CircleCollider*)col->state;
	return colState->radius;
}

bool cleanCollider(Collider* col)
{
	free(col->state);
	free(col);
	return true;
}

bool isCollidingCircle(Vec2 posA, float radA, Vec2 posB, float radB)
{
	//get the distance
	auto distance = v2Mag(v2Sub(posB, posA));

	return distance <= (radA + radB);
}
