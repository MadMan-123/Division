﻿#pragma once
#include "../Core/maths.h"
#include "../definitions.h"

#define GRAVITATIONAL_PULL 0.0f

typedef struct
{
    Vec2 velocity;
    float mass;
}Rigidbody;

//bool physicsUpdate(ECS*  ecs,float dt);