#include "../game.h"
#include <iostream>
#include <string>



Game::Game()
{
	if (!platformStart(&state, name,width,height))
	{
		fprintf(stderr, "Cannot start platform state");
	}
	initGraphics((GraphicsState*)state.graphicsState,height,width);

}

bool Game::gameRun()
{
	double last = platformGetAbsoluteTime();
	GFX = (GraphicsState*)state.graphicsState;

	while (shouldRun)
	{
		double current = platformGetAbsoluteTime();
		const float dt = (float)(current - last);
		last = current;

		if (!platformUpdate(&state))
		{
			shouldRun = false;
		}

		if (!update(dt))
		{
			shouldRun = false;
		}

		physicsUpdate(dt);
		
		swapBuffers(GFX);

		clear(GFX, transparent);

		GFX->shouldRender = render(dt);

		if (!GFX->shouldRender)
		{
			shouldRun = false;
		}


		
		// Swap buffers here, after all rendering is done
		


	}

	shouldRun = false;
	
	graphicsCleanUp(GFX);
	platformCleanUp(&state);

	for (int i = 0; i < MAX_ENTITIES; i++)
	{
		cleanCollider(&ecs.colliders[i]);
	}
	
	return false;
}


int Game::run()
{
	//check game state
	if (shouldRun == false)
	{
		fprintf(stderr, "The Game State is incorrect should run is false, returning -1");
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

	if(!physics(dt)){}
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
					
			bool isColliding = isCollidingCircle(posA, getRadius(colA), posB, getRadius(colB));
			colA->isColliding = isColliding;
			//colB->isColliding = isColliding;


		}

		//draw each collider			col = isColliding ? green : red;
		Colour col = ecs.colliders[i].isColliding ? green : red;

		drawCircle(GFX, ecs.transforms[i].position, getRadius(&ecs.colliders[i]), col);
    }
	
	return true; 
}