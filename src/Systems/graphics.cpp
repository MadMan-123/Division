#include "graphics.h"
#include <stdio.h>
#include <cstdio>
#include <math.h>


void initGraphics(GraphicsState* state, int height, int width)
{
	//check if state is null
	if (state == nullptr)
	{
		fprintf(stderr, "State given is null");
		return;
	}
	//set height and width
	state->height = height;
	state->width = width;

	//allocate memory for buffers
	for (int i = 0; i < 2; ++i)
	{
		//allocate memory for the buffer
		state->buffers[i] = (Colour**)malloc(state->height * sizeof(Colour*));
		if (state->buffers[i] == nullptr)
			continue;
			for (int y = 0; y < state->height; y++)
			{
			
				state->buffers[i][y] = (Colour*)malloc(state->width * sizeof(Colour));
			}
			
	}
	//set the front and back buffer
	state->front = state->buffers[0];
	state->back = state->buffers[1];
	//clear the buffers
	clearBuffer(state, state->back, { 0,0,0,0 });
	clearBuffer(state, state->front, { 0,0,0,0 });
	state->shouldRender = true;
	
}

void graphicsCleanUp(GraphicsState* state)
{
	//free memory
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
	//check if position is out of bounds
	if (pos.x < 0 || pos.x >= state->width || pos.y < 0 || pos.y >= state->height)
	{
		return false; // Out of bounds
	}
	//draw pixel to back buffer by setting the colour
	state->back[pos.y][pos.x] = colour; 

	return true;


}

void drawLine(GraphicsState* state,Vec2i start, Vec2i end, Colour colour)
{
	//Bresenham's line algorithm
	int x0 = (int)start.x;
	int y0 = (int)start.y;
	int x1 = (int)end.x;
	int y1 = (int)end.y;
	
	//calculate the difference
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = x0 < x1 ? 1 : -1;
	int sy = y0 < y1 ? 1 : -1;
	int err = (dx > dy ? dx : -dy) / 2;
	int e2;
	
	//loop through the line
	while (true) {
		drawPixel(state, { x0, y0 }, colour);
		
		//check if we have reached the end
		if (x0 == x1 && y0 == y1) break;
		//calculate the error
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
	//draw a square by drawing lines
	for (int y = 0; y < size; y++)
	{
		drawLine(GFX, { pos.x, pos.y + y }, { pos.x + size - 1, pos.y + y }, colour);
	}
}
void drawFilledSquare(GraphicsState* GFX, Vec2 pos ,Vec2 scale, Colour colour)
{
	//draw a square by drawing lines
	for(int y = 0; y < scale.y; y++)
	{
		for(int x = 0; x < scale.x; x++)
		{
			//draw square
			drawPixel(GFX, { (int)pos.x + x, (int)pos.y + y }, colour);
		}
	}
}

void drawWireSquare(GraphicsState* GFX, Vec2 pos, Vec2 scale, Colour colour)
{
	//draw 4 lines to each corner
	drawLine(GFX,v2Tov2i(pos), v2Tov2i({ pos.x + scale.x, pos.y }), colour);
	drawLine(GFX,v2Tov2i(pos), v2Tov2i({ pos.x, pos.y + scale.y }), colour);
	drawLine(GFX,v2Tov2i({ pos.x + scale.x, pos.y }), v2Tov2i({ pos.x + scale.x, pos.y + scale.y }), colour);
	drawLine(GFX,v2Tov2i({ pos.x, pos.y + scale.y }), v2Tov2i({ pos.x + scale.x, pos.y + scale.y }), colour);
	
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
