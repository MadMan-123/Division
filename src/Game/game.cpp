
#include "../../include/division.h"
#include <iostream>
#include <string>



Game::Game()
{

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
		double current = platformGetAbsoluteTime();
		const float dt = (float)(current - last);
		last = current;

		if (!platformUpdate(&pState))
		{
			shouldRun = false;
		}

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


		
		// Swap buffers here, after all rendering is done
		


	}

	shouldRun = false;
	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		cleanCollider(&ecs.colliders[i]);
	}	
	graphicsCleanUp(gState);
	platformCleanUp(&pState);
	
	return false;
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

	gameRun();
	//program success
	return 0;

}

bool Game::physicsUpdate(float dt)
{

	if(!physics(dt))
	{
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
    			Vec2 posA = ecs.transforms[i].position;
    			Vec2 posB = ecs.transforms[j].position;
    			Collider* colA = &ecs.colliders[i];
    			Collider* colB = &ecs.colliders[j];

    			if ((i == j || colA->layer != colB->layer )) continue;
					
    			bool isColliding = isBoxColliding(posA, getScale(colA), posB, getScale(colB));
    			colA->isColliding = isColliding;
    			if(isColliding && &ecs != nullptr)
				colA->response(i,j,&ecs);
			//colB->isColliding = isColliding;


    		}

    	//draw each collider			col = isColliding ? green : red;
    	Colour col = ecs.colliders[i].isColliding ? green : red;
    	drawWireSquare(gState, ecs.transforms[i].position, getScale(&ecs.colliders[i]), col);	
    }
	
	return true; 
}
