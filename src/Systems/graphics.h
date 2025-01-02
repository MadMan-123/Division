#pragma once
#include "../Core/maths.h"
#include "../definitions.h"


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
static Colour orange = {255,165,0,1};

DIVAPI void initGraphics(GraphicsState* state, int height, int width);
DIVAPI void graphicsCleanUp(GraphicsState* state);
DIVAPI bool drawPixel(GraphicsState* state, Vec2i pos, Colour colour);
DIVAPI void drawLine(GraphicsState* state, Vec2i start, Vec2i end, Colour colour);
DIVAPI void swapBuffers(GraphicsState* state);
DIVAPI void clearBuffer(GraphicsState* state, Colour** buffer, Colour colour);
DIVAPI void clear(GraphicsState* state, Colour colour);
DIVAPI void drawFilledSquare(GraphicsState* GFX, Vec2i pos, int size, Colour colour);
DIVAPI void drawFilledSquare(GraphicsState* GFX, Vec2 pos, Vec2 scale, Colour colour);
DIVAPI void drawWireSquare(GraphicsState* GFX, Vec2 pos, Vec2 scale, Colour colour);
