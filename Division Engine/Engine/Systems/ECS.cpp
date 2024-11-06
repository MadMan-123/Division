#include "ECS.h"

uint32_t addEntity(ECS* ecs, Transform transform, Rigidbody rigidbody,Renderable renderable,Collider collider)
{
    if(ecs->entityCount >= MAX_ENTITIES) return -1;
    uint32_t id = ecs->entityCount;
    ecs->transforms[id] = transform;
    ecs->rigidbodies[id] = rigidbody;
    ecs->renderables[id] = renderable;
    ecs->colliders[id] = collider;
    ecs->isActive[id] = true;
    ecs->entityCount++;
    return id;
}
