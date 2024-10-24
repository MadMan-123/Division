#pragma once
#include "maths.h"


typedef struct {
	int r, g, b, a;
}Colour;

typedef struct {
	//frame buffers
	Colour** buffers[2];
	Colour** back;
	Colour** front;
	int height, width;
	bool shouldRender;
}GraphicsState;

static Colour red = { 255,0,0,255 };
static Colour white = { 255,255,255,255 };
static Colour black = { 0,0,0,255 };
static Colour green = { 0,255,0,255 };
static Colour blue = { 0,0,255,255 };
static Colour transparent = { 0,0,0,0 };


void initGraphics(GraphicsState* state, int height, int width);
void graphicsCleanUp(GraphicsState* state);
bool drawPixel(GraphicsState* state, Vec2i pos, Colour colour);
void drawLine(GraphicsState* state, Vec2i start, Vec2i end, Colour colour);
void swapBuffers(GraphicsState* state);
void clearBuffer(GraphicsState* state, Colour** buffer, Colour colour);
void clear(GraphicsState* state, Colour colour);
void drawFilledSquare(GraphicsState* GFX, Vec2i pos, int size, Colour colour);