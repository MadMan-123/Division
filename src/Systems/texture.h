#pragma once
#include "graphics.h"


typedef struct{
	//size data
	Colour** pixelData;
}Texture;

typedef struct{
	size_t maxSize;
	size_t textureCount;
	Texture* textures;
}TextureAtlas;

void createTextureAtlas(TextureAtlas* atlas, size_t atlasBufferTextureCount);
bool getTexture(TextureAtlas* atlas, const char* fileName);


