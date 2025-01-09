#pragma once
#include <cstdint>
#include <cstdio>
#include "renderable.h"
#include "rigidbody.h"
#include "../Core/arena.h"
#include "../Core/maths.h"
#include "collider.h"



#define MAX_ENTITIES 128
//todo: put in own files

typedef struct
{
    	Vec2 position;
    	Vec2 scale;
    	float angle;
}Transform;

typedef struct{
	int current;
	int max;
}Health;

typedef struct{
    	bool isActive[MAX_ENTITIES];
    	// Entity signatures
    	uint32_t signatures[MAX_ENTITIES];
    
    
    	//TODO: Make true SOA
    	// Component arrays (SoA style)
    	Transform transforms[MAX_ENTITIES];
    	Rigidbody rigidbodies[MAX_ENTITIES];
    	Collider* colliders[MAX_ENTITIES];
    	Renderable renderables[MAX_ENTITIES]; 
    	Health healthPools[MAX_ENTITIES];
	uint32_t entityCount;
	char* tags[MAX_ENTITIES]; 
	
}ECS;

//static reference to the current ECS
static ECS* currentECS = NULL;

DIVAPI uint32_t addEntity(ECS* current,Transform transform , Rigidbody rigidbody,Renderable renderable,Collider* collider, Health health);
DIVAPI void setTag(ECS* current, int index, const char* tag);



//ECS
//We need a way for devs to specify a layout of how a SoA should look like
