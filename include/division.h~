#pragma once
#include "Engine/Core/maths.h"
#include "Engine/Core/arena.h"
#include "Engine/Core/platform.h"
#include "Engine/Systems/graphics.h"
#include "Engine/Systems/input.h"
#include "Engine/Systems/collider.h"
#include <cstdio>

#include "Engine/Systems/rigidbody.h"
#include "Engine/Systems/ECS.h"
#include "Engine/definitions.h"

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

	
	ECS ecs;
	
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
