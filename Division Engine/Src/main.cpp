#include "main.h"


bool SpaceInvaders::start() 
{
	Transform transform = {0};
	transform.scale  = {10,10};
	Rigidbody rb = {0};
	Renderable renderable = {red};
	Collider* playerCollider = createBoxCollider(transform.scale);
	
	playerCollider->layer = 0;
	
	//player
	transform.position = {width /2.0f, height - 10.0f};
	player = addEntity(&ecs, transform, rb, renderable,*playerCollider);
	renderable = {green};
	for(int i = 0; i < MAX_ALIENS; i++)
	{
		transform.position = {transform.scale.x * 2.5f *  i + 10, 10.0f};
		aliens[i] = addEntity(&ecs, transform, rb, renderable, *playerCollider);
	}
	renderable.colour = red;
	transform.scale = { 10,5 };
	renderable.colour = white;
	Collider* barrierCollider = createBoxCollider(transform.scale);
	for (int i = 0; i < MAX_BARRIERS; i++)
	{
		transform.position = { transform.scale.x * 2.5f * i + 10, height - 20.0f };
		barriers[i] = addEntity(&ecs, transform, rb, renderable, *barrierCollider);

	}
	

		
	renderable.colour = {100,0,50,255};
	transform.scale = {5,5};
	Collider* bulletCollider = createBoxCollider(transform.scale);
	for(int i = 0; i < MAX_BULLETS; i++)
	{
		bullets[i] = addEntity(&ecs, transform, rb, renderable, *bulletCollider);
		ecs.isActive[bullets[i]] = false;
	}
		
	return true;
}

bool SpaceInvaders::update(float dt) 
{
	
	if(isInputPressed('A'))
	{
		ecs.transforms[player].position.x -= 100 * dt;
	}
	else if(isInputPressed('D'))
	{
		ecs.transforms[player].position.x += 100 * dt;
	}

	if(isInputPressed('E'))
	{
		for(int i = 0; i < MAX_BULLETS; i++)
		{
			uint32_t currentBullet = bullets[i];
			if(ecs.isActive[currentBullet])
				continue;

			ecs.isActive[currentBullet] = true;
			ecs.transforms[currentBullet].position = ecs.transforms[player].position;
			ecs.rigidbodies[currentBullet].velocity.y -= force;
			printf("Bullet Spawned\n ");
			break;
		}
	}
	
	//for each bullet
	for(int i = 0 ; i < MAX_BULLETS;i++)
	{
		if(!ecs.isActive[bullets[i]])
			continue;

		if(ecs.transforms[bullets[i]].position.y < 0)
		{
			ecs.transforms[bullets[i]].position.y = 0;
			ecs.rigidbodies[bullets[i]].velocity.y = 0;
			ecs.isActive[bullets[i]] = false;
		}
	}

	return true;

}


bool SpaceInvaders::physics(float dt) 
{
	return true;
}

bool SpaceInvaders::render(float dt) 
{
	auto GFX = (GraphicsState*)pState.graphicsState;

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





int main()
{
	SpaceInvaders game;

	return game.run();
}


//Big ass TODO list
//todo:
//	1. Arena Structure x
//	2. Make ECS system x
//	3. rewrite engine with arenas
//	4. basic collision 
//	5. input system x