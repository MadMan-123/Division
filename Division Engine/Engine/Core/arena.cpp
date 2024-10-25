#include "arena.h"

#include <cstdlib>

bool arenaCreate(Arena* arena, size_t maxSize)
{
    arena->size = maxSize;
    arena->used = 0;
    arena->data = malloc(arena->size);
    return (arena->data == nullptr);
}

void* aalloc(Arena* arena, size_t size)
{
    if(arena->used + size > arena->size) return nullptr;
    void* ptr = (char*)(arena->data) + arena->used;
    arena->used += size;
    return ptr;
}

void arenaDestroy(Arena* arena)
{
    free(arena->data);
    arena->data = nullptr;
    
}
