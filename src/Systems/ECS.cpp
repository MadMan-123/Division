#include "ECS.h"
#include <cstring>
uint32_t addEntity(ECS* current,Transform transform, Rigidbody rigidbody,Renderable renderable,Collider *collider, Health health)
{
    if(current == NULL) 
    {
        printf("ECS not initialized\n");
        return -1;
    } 
    if(current->entityCount >= MAX_ENTITIES) return -1;
    auto id = current->entityCount;    

    current->colliders[id] = collider;
    current->transforms[id] = transform;
    current->rigidbodies[id] = rigidbody;
    current->renderables[id] = renderable;
    current->healthPools[id] = health;
    current->isActive[id] = true;
    current->entityCount++;
    return id;
}
