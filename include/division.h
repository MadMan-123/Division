#pragma once
#include "../src/Core/maths.h"
#include "../src/Core/arena.h"
#include "../src/Core/platform.h"
#include "../src/Systems/graphics.h"
#include "../src/Systems/input.h"
#include "../src/Systems/collider.h"
#include "../src/Core/coroutine.h"
#include <cstdio>
#include <cstdlib>
#include <stdio.h>

#include "../src/Systems/rigidbody.h"
#include "../src/Systems/ECS.h"
#include "../src/definitions.h"

class Game
{
public:
	virtual ~Game() = default;
	DIVAPI int run();
	DIVAPI virtual bool start() = 0;
	DIVAPI virtual bool update(float dt) = 0;
	DIVAPI virtual bool render(float dt) = 0;
	DIVAPI virtual bool physics(float dt) = 0;
	int width = 384, height = 384;
	const char* name = "Test bed";
	const int targetFPS = 60;	
	const double targetFrameTime = 1.0 / targetFPS;
	

	bool shouldRun = true;
	DIVAPI Game();
private:
	bool gameRun();
	bool physicsUpdate(float dt);
protected:
	PlatformState pState;
	GraphicsState* gState;
	ECS ecs = {0};	
	// Clock
};
