#pragma once
#include "../../include/division.h"
#include <cstdio>
#include <setjmp.h>
#include <unistd.h>


typedef struct Coroutine {
	jmp_buf env;
	float waitTime;
	int active;
	struct Coroutine* next; // Linked list for active coroutines
} Coroutine;

static Coroutine* coroutineHead = NULL;

DIVAPI void addCoroutine(Coroutine* co);
DIVAPI void removeFinishedCoroutines();
DIVAPI void updateCoroutines(float dt);
DIVAPI void wait(Coroutine* co, float ms);
DIVAPI Coroutine* createCoroutine();


DIVAPI void startCoroutine(Coroutine* co, void (*func)(Coroutine* co));
