	
#include "../../include/division.h"
#include <iostream>
#include <string>

#define ECS_TAG_SIZE 10
Game::Game()
{	


	for(int i = 0; i < MAX_ENTITIES; i++)
	{

		ecs.tags[i] = nullptr;	
	
	}
	if (!platformStart(&pState, name,width,height))
	{
		fprintf(stderr, "Cannot start platform state\n");
	}

	initGraphics((GraphicsState*)pState.graphicsState,height,width);
}

bool Game::gameRun()
{
	
	double last = platformGetAbsoluteTime();
	gState = (GraphicsState*)pState.graphicsState;

	while (shouldRun)
	{
		double frameStartTime = platformGetAbsoluteTime();
	
		double current = platformGetAbsoluteTime();
		const float dt = (float)(current - last);
		last = current;

		if (!platformUpdate(&pState))
		{
			shouldRun = false;
		}
		
		updateCoroutines(dt);
		


		if (!update(dt))
		{
			shouldRun = false;
		}

		physicsUpdate(dt);
		
		swapBuffers(gState);

		clear(gState, transparent);

		gState->shouldRender = render(dt);

		if (!gState->shouldRender)
		{
			shouldRun = false;
		}
		removeFinishedCoroutines();
	
		// Lock the frame rate to targetFPS
		double frameEndTime = platformGetAbsoluteTime();
		double frameDuration = frameEndTime - frameStartTime;	
		if (frameDuration < targetFrameTime)
		{
			platformSleep(targetFrameTime - frameDuration);
		}
	}

	shouldRun = false;
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		if(ecs.tags[i] != nullptr)
		{
			printf("%s\n", ecs.tags[i]);
			char* tag = ecs.tags[i];
			free(tag);
	
		}
		cleanCollider(ecs.colliders[i]);
		
		
	}	
	graphicsCleanUp(gState);
	platformCleanUp(&pState);

	//destroy the ECS
	
	return true;
}


int Game::run()
{
	//check game state
	if (shouldRun == false)
	{
		fprintf(stderr, "The Game State is incorrect should run is false, returning -1\n");
		//program faliure
		return -1;
	}


	
	if(!start())
	{
		return -1; 
	}

	bool result = gameRun();
	return result ? 0 : -1;

}

bool Game::physicsUpdate(float dt)
{
	
	if(!physics(dt))
	{
		return false;
	}
    for(int i = 0; i < ecs.entityCount; i++)
    {
       	if(!ecs.isActive[i])continue;
		
       	//update position
       	ecs.transforms[i].position =
           	v2Sub(
               	v2Add(
                   	ecs.transforms[i].position,
                   	v2Mul(ecs.rigidbodies[i].velocity,dt)),
               	{0,GRAVITATIONAL_PULL * dt}
               	);
    	for (int j = 0; j < ecs.entityCount; j++)
    	{
    		if (!ecs.isActive[j]) continue;
			if (i == j) continue;

    		Vec2 posA = ecs.transforms[i].position;
    		Vec2 posB = ecs.transforms[j].position;
    		Collider* colA = ecs.colliders[i];
    		Collider* colB = ecs.colliders[j];

    		if (colA->layer != colB->layer ) continue;
			
    		bool isColliding = isBoxColliding(posA, getScale(colA), posB, getScale(colB));
    			
			colA->isColliding = isColliding;
			//colB->isColliding = isColliding;


			if(isColliding)
			{
	
				void(*response)(uint32_t, uint32_t) = colA->response;
    			
				if(response != NULL)
				{

				//printf("Response function address: %p\n", (void*)response);
					//printf("%s:%i collided with %s:%i\n\n", ecs.tags[i],i,ecs.tags[j],j);*/
    				
					//check if address is corrupted
					if((uintptr_t)response == 0xbaadf00dbaadf00d) 
					{
    						fprintf(stderr,"Warning: Detected freed/corrupted response function\n");
    						continue;
    					}

					colA->response((uint32_t)i,(uint32_t)j);
				}
	
				/*if(colB->response != NULL) 
				{
					colB->response((uint32_t)j, (uint32_t)i);  // Note the reversed order for B
				}*/
			}
		}
    

   	}
	
	return true; 
}
