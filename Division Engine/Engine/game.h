#pragma once
#include "maths.h"
#include "platform.h"
#include "graphics.h"
#include <cstdio>

class Game
{
public:
	int run();
	virtual bool start() = 0;
	virtual bool update(float dt) = 0;
	virtual bool render(float dt) = 0;
	int width = 512, height = 256;
	const char* name = "Test bed";

	
	Game();
private:
	bool gameRun();
	bool shouldRun = true;
protected:
	PlatformState state;


	// Clock
};