#pragma once

struct PlatformState
{
	void* internalState;
	void* graphicsState;
};

bool platformStart(PlatformState* state, const char* name, int width, int height);
bool platformUpdate(PlatformState* state);
void platformCleanUp(PlatformState* state);
double platformGetAbsoluteTime();
void platformSleep(unsigned long long ms);

void* platformAlloc(size_t bytes);

