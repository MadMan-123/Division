#include "../Engine/game.h"

#include <Windows.h>

#define MAX_ALIENS 10
#define MAX_BULLETS 20
#define MAX_BARRIERS 10

class SpaceInvaders : public Game
{
private:
	uint32_t player;
	uint32_t aliens[MAX_ALIENS];
	uint32_t bullets[MAX_BULLETS];
	uint32_t barriers[MAX_BARRIERS];
public:
	bool start() override
	{
		Transform transform = {0};
		transform.scale  = {10,10};
		Rigidbody rb = {0};
		Renderable renderable = {red};
	
		//player
		transform.position = {width /2.0f, height - 10.0f};
		player = addEntity(&ecs, transform, rb, renderable);
		renderable = {green};
		for(int i = 0; i < MAX_ALIENS; i++)
		{
			transform.position = {transform.scale.x * 2.5f *  i + 10, 10.0f};
			aliens[i] = addEntity(&ecs, transform, rb, renderable);
		}
		renderable.colour = red;
		transform.scale = {10,5};
		renderable.colour = white;
		for(int i = 0; i < MAX_BARRIERS; i++)
		{
			transform.position = {transform.scale.x * 2.5f * i + 10, height - 20.0f};
			barriers[i] = addEntity(&ecs, transform, rb, renderable);
		}
		
		renderable.colour = {100,0,50,255};
		transform.scale = {5,5};
		for(int i = 0; i < MAX_BULLETS; i++)
		{
			bullets[i] = addEntity(&ecs, transform, rb, renderable);
		    ecs.isActive[bullets[i]] = false;
		}
		
		return true;
	}

	bool update(float dt) override
	{
	
		if(isInputPressed('A'))
		{
			ecs.transforms[player].position.x -= 100 * dt;
		}
		else if(isInputPressed('D'))
		{
			ecs.transforms[player].position.x += 100 * dt;
		}
	

		



		return true;

	}

	bool physics(float dt) override
	{
		return true;
	}

	bool render(float dt) override
	{
		auto GFX = (GraphicsState*)state.graphicsState;

		//draw all the entities
		for(int i = 0; i < ecs.entityCount; i++)
		{
			if(ecs.isActive[i])
			{
				drawFilledSquare(
					GFX,
					ecs.transforms[i].position,
					ecs.transforms[i].scale,
					ecs.renderables[i].colour
					);
				
			}
		}
		return true;

	}

};



int main()
{
	SpaceInvaders game;

	return game.run();
}


//Big ass TODO list
//todo:
//	1. Arena Structure x
//	2. Make ECS system 
//	3. rewrite engine with arenas
//	4. basic collision
//	5. input system