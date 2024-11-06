#pragma once
#include "Core/maths.h"
#include "Core/arena.h"
#include "Core/platform.h"
#include "Systems/graphics.h"
#include "Systems/input.h"
#include "Systems/collider.h"
#include <cstdio>

#include "Systems/rigidbody.h"
#include "Systems/ECS.h"

class Game
{
public:
	virtual ~Game() = default;
	int run();
	virtual bool start() = 0;
	virtual bool update(float dt) = 0;
	virtual bool render(float dt) = 0;
	virtual bool physics(float dt) = 0;
	int width = 256, height = 256;
	const char* name = "Test bed";

	
	ECS ecs;
	
	Game();
private:
	bool gameRun();
	bool physicsUpdate(float dt);
	bool shouldRun = true;
protected:
	PlatformState pState;
	GraphicsState* gState;

	// Clock
};
