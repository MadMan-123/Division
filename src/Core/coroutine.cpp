#include "coroutine.h"







void addCoroutine(Coroutine* co) 
{
	co->next = coroutineHead;
	coroutineHead = co;
}

void removeFinishedCoroutines() 
{
	Coroutine** current = &coroutineHead;
	while (*current) 
	{
		if ((*current)->active == 0) 
		{
			Coroutine* toRemove = *current;
			*current = (*current)->next;
			free(toRemove); // Assuming dynamic allocation
		} 
		else 
		{
			current = &(*current)->next;
		}
	}
}

void updateCoroutines(float dt) 
{
	Coroutine* current = coroutineHead;
	while (current) 
	{
		if (current->waitTime > 0) 
		{
			current->waitTime -= dt;
			if (current->waitTime <= 0 && current->active) 
			{
				// Resume coroutine
				longjmp(current->env, 1); 
			}
		}
		current = current->next;
	}
}

void wait(Coroutine* co, float ms)
{
	co->waitTime = ms;
	if (!setjmp(co->env)) return;
}

Coroutine* createCoroutine()
{
	//allocate coroutine
	Coroutine* co = (Coroutine*)malloc(sizeof(Coroutine));
	//add coroutine to linked list
	addCoroutine(co);

	return co;
}

void startCoroutine(Coroutine* co, void (*func)(Coroutine* co))
{
	if(co->active) return;
	co->active = 1;
	func(co);
}
