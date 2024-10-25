#pragma once
#include <cstdint>

#include "rigidbody.h"
#include "../Core/arena.h"
#include "../Core/maths.h"


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
    COMPONENT_RIGIDBODY = 1 << 1,
    COMPONENT_RENDERABLE = 1 << 2
} ComponentType;



typedef struct{
    bool isActive[MAX_ENTITIES];
    // Entity signatures
    uint32_t signatures[MAX_ENTITIES];
    
    // Component arrays (SoA style)
    Transform transforms[MAX_ENTITIES];
    Rigidbody rigidbodies[MAX_ENTITIES];
    
    
    uint32_t entityCount;
}ECS;

uint32_t addEntity(ECS* ecs,Transform transform , Rigidbody rigidbody);

