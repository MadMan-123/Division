#pragma once
#include "../definitions.h"

typedef struct{
    void* data;
    size_t size;
    size_t used;
}Arena;

DIVAPI bool arenaCreate(Arena* arena, size_t maxSize);
DIVAPI void* aalloc(Arena* arena, size_t size);
DIVAPI void arenaDestroy(Arena* arena);

