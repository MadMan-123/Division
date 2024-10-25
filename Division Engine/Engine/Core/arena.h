#pragma once

typedef struct{
    void* data;
    size_t size;
    size_t used;
}Arena;

bool arenaCreate(Arena* arena, size_t maxSize);
void* aalloc(Arena* arena, size_t size);
void arenaDestroy(Arena* arena);

