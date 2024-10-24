#include "game.h"
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
	auto GFX = (GraphicsState*)state.graphicsState;

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
