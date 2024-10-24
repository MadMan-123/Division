#include "../Engine/game.h"

#include <Windows.h>

class SpaceInvaders : public Game
{
public:
	bool start() override
	{

		return true;
	}

	bool update(float dt) override
	{
		if (GetAsyncKeyState('W') & 0x8000)
		{
			pos.y -= speed * dt;
		}
		if (GetAsyncKeyState('S') & 0x8000)
			pos.y += speed * dt;
		
		if (GetAsyncKeyState('D') & 0x8000)
			pos.x += speed * dt;

		if (GetAsyncKeyState('A') & 0x8000)
			pos.x -= speed * dt;

		if (pos.y + 50 > floor)
			pos.y = floor - 50;



		return true;

	}


	bool render(float dt) override
	{
		auto GFX = (GraphicsState*)state.graphicsState;
		//draw square at pos
		drawFilledSquare(GFX, {(int)pos.x,(int)pos.y}, 50, green);
		for (int i = 0; i < 10; i++)
			drawLine(GFX, { 0, floor + i }, { width, floor + i }, red);
		


		return true;

	}

private:
	Vec2 pos{ 10,10 };
	int floor = height - 10;
	float speed = 100.0f;
};



int main()
{
	SpaceInvaders game;

	return game.run();
}


//Big ass TODO list
//todo:
//	1. Arena Structure
//	2. Make ECS system
//	3. rewrite engine with arenas
//	4. basic collision