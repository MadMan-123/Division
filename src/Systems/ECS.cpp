#include "ECS.h"
#include <cstring>
uint32_t addEntity(ECS* current,Transform transform, Rigidbody rigidbody,Renderable renderable,Collider *collider, Health health)
{
	//Check if the ECS is initialized
    if(current == NULL) 
    {
        printf("ECS not initialized\n");
        return -1;
    } 
	//Check if the entity count is at the maximum
    if(current->entityCount >= MAX_ENTITIES) return -1;
    auto id = current->entityCount;    
	//Set the entity signature
    current->colliders[id] = collider;
    current->transforms[id] = transform;
    current->rigidbodies[id] = rigidbody;
    current->renderables[id] = renderable;
    current->healthPools[id] = health;
    current->isActive[id] = true;
    current->entityCount++;
    return id;
}



void setTag(ECS* current, int index, const char* tag)
{
	//Check if the ECS is initialized
	if(current == NULL || index > MAX_ENTITIES)
	{
		printf("ECS NOT INITIALISED");
		return;
	}
	//set the tag as so we can free it later
	current->tags[index] = (char*)malloc(strlen(tag) + 1);
	strcpy(current->tags[index], tag);

}
