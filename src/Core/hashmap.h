#pragma once
#include "arena.h"


//Thank you Jacob Sorber for your video on hash tables in C

#define MAX_NAME 256

typedef struct{
	char name[MAX_NAME];
	void* data;
}Pair;

typedef struct{
	size_t mapSize;
	Pair* pairs;
	Arena* arena;
}HashMap;


bool createHashMap(HashMap* map, size_t mapSize);
unsigned int hash(char* name,size_t mapSize);
void printMap(HashMap* map);
bool insertMap(HashMap* map);
void cleanMap(HashMap* map);
