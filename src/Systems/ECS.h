﻿#pragma once
#include <cstdint>

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



// Component Types
typedef enum {
    	COMPONENT_TRANSFORM = 1 << 0,
    	COMPONENT_RIGIDBODY = 2 << 1,
	COMPONENT_RENDERABLE = 1 << 2
} ComponentType;

typedef struct{
	Arena buffer;
	size_t count;
}Archetype;



typedef struct{
    bool isActive[MAX_ENTITIES];
    // Entity signatures
    uint32_t signatures[MAX_ENTITIES];
    
    
    //TODO: Make true SOA
    // Component arrays (SoA style)
    Transform transforms[MAX_ENTITIES];
    Rigidbody rigidbodies[MAX_ENTITIES];
    Collider colliders[MAX_ENTITIES];
    Renderable renderables[MAX_ENTITIES]; 
    
    uint32_t entityCount;
}ECS;

DIVAPI uint32_t addEntity(ECS* ecs,Transform transform , Rigidbody rigidbody,Renderable renderable,Collider collider);
