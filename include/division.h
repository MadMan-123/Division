#pragma once
#include "../src/Core/maths.h"
#include "../src/Core/arena.h"
#include "../src/Core/platform.h"
#include "../src/Systems/graphics.h"
#include "../src/Systems/input.h"
#include "../src/Systems/collider.h"
#include <cstdio>

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
	int width = 256, height = 256;
	const char* name = "Test bed";

	
	ECS ecs = {0};
	
	DIVAPI Game();
private:
	bool gameRun();
	bool physicsUpdate(float dt);
	bool shouldRun = true;
protected:
	PlatformState pState;
	GraphicsState* gState;

	// Clock
};
