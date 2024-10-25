#include "../Engine/game.h"

#include <Windows.h>

class SpaceInvaders : public Game
{
public:
	bool start() override
	{
		Transform transform = {0};
		transform.scale  = {10,10};
		Rigidbody rb = {0};
		for(int i = 0; i < 10; i++)
		{
			transform.position.x = rand() % 100;
			transform.position.y = rand() % 100;

			
			addEntity(&ecs,transform,rb);
		}
		return true;
	}

	bool update(float dt) override
	{
		

		//mouse
		if(isInputPressed(1))
		{
			for(int i = 0; i < 10; i++)
			{
				ecs.rigidbodies[i].velocity = {
					(float)(rand() % 10),
					(float)(rand() % 10)
				};
			}
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
					red
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