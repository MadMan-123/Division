#include "graphics.h"
#include <stdio.h>
#include <cstdio>
#include <cmath>
#include <corecrt_malloc.h>


void initGraphics(GraphicsState* state, int height, int width)
{
	if (state == nullptr)
	{
		fprintf(stderr, "State given is null");
		return;
	}
	state->height = height;
	state->width = width;

	for (int i = 0; i < 2; ++i)
	{
		state->buffers[i] = (Colour**)malloc(state->height * sizeof(Colour*));
		if (state->buffers[i] == nullptr)
			continue;

			for (int y = 0; y < state->height; y++)
			{
				state->buffers[i][y] = (Colour*)malloc(state->width * sizeof(Colour));
			}
			
	}
	state->front = state->buffers[0];
	state->back = state->buffers[1];
	clearBuffer(state, state->back, { 0,0,0,0 });
	clearBuffer(state, state->front, { 0,0,0,0 });
	state->shouldRender = true;
	
}

void graphicsCleanUp(GraphicsState* state)
{
	for (int i = 0; i < 2; ++i) 
	{
		for (int y = 0; y < state->height; ++y) 
		{
			free(state->buffers[i][y]);
		}
		free(state->buffers[i]);
	}

}

bool drawPixel(GraphicsState* state,Vec2i pos, Colour colour)
{
	if (pos.x < 0 || pos.x >= state->width || pos.y < 0 || pos.y >= state->height)
	{
		return false; // Out of bounds
	}
	state->back[pos.y][pos.x] = colour; 

	return true;


}

void drawLine(GraphicsState* state,Vec2i start, Vec2i end, Colour colour)
{
	int x0 = (int)start.x;
	int y0 = (int)start.y;
	int x1 = (int)end.x;
	int y1 = (int)end.y;

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;

	while (true) {
		drawPixel(state, { x0, y0 }, colour);

		if (x0 == x1 && y0 == y1) break;

		e2 = err;
		if (e2 > -dx) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dy) {
			err += dx;
			y0 += sy;
		}
	}
}

void drawFilledSquare(GraphicsState* GFX, Vec2i pos, int size, Colour colour)
{
	for (int y = 0; y < size; y++)
	{
		drawLine(GFX, { pos.x, pos.y + y }, { pos.x + size - 1, pos.y + y }, colour);
	}
}
void drawFilledSquare(GraphicsState* GFX, Vec2 pos ,Vec2 scale, Colour colour)
{
	for(int y = 0; y < scale.y; y++)
	{
		for(int x = 0; x < scale.x; x++)
		{
			//draw square
			drawPixel(GFX, { (int)(pos.x + x - (scale.x /2)), (int)(pos.y + y - (scale.y/2))}, colour);
		}
	}
}

void drawCircle(GraphicsState* state, Vec2 pos, float radius, Colour colour) {
	float xpos, ypos, radsqr = radius * radius;
	for (xpos = pos.x - radius; xpos <= pos.x + radius; xpos += 0.1) {
		float dx = xpos - pos.x;
		float xsqr = dx * dx;
		float dy = sqrt(radsqr - xsqr);
		ypos = pos.y + dy;
		drawPixel(state, { (int)xpos, (int)ypos }, colour);
		ypos = pos.y - dy;
		drawPixel(state, { (int)xpos, (int)ypos }, colour);
	}
}



void swapBuffers(GraphicsState* state)
{
	//xor swap
	state->front = (Colour**)((uintptr_t)state->back ^ (uintptr_t)state->front);
	state->back = (Colour**)((uintptr_t)state->front ^ (uintptr_t)state->back);
	state->front = (Colour**)((uintptr_t)state->back ^ (uintptr_t)state->front);


}

void clearBuffer(GraphicsState* state,Colour** buffer, Colour colour)
{
	for (int y = 0; y < state->height; y++)
	{
		for (int x = 0; x < state->width; x++)
			buffer[y][x] = colour;
	}
}

void clear(GraphicsState* state, Colour colour)
{
	clearBuffer(state, state->back, colour);
}
