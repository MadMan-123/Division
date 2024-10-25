#pragma once
#include "../Core/maths.h"

#define GRAVITATIONAL_PULL -9.81f

typedef struct
{
    Vec2 velocity;
    float mass;
}Rigidbody;

//bool physicsUpdate(ECS*  ecs,float dt);