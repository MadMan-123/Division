#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "../Core/arena.h"

typedef uint32_t EntityID;

// Archetype definition macro with Arena support
#define DEFINE_ARCHETYPE(name, ...) \
    typedef struct { \
        __VA_ARGS__ \
    } name##Data; \
    \
    typedef struct { \
        uint32_t count; \
        uint32_t capacity; \
        EntityID* entities; \
        Arena componentsArena; \
        name##Data* first_component; /* Points to start of SoA data */ \
    } name##Archetype; \
    \
    DIVAPI bool create##name##Archetype(name##Archetype* archetype, uint32_t max_entities); \
    DIVAPI void destroy##name##Archetype(name##Archetype* archetype); \
    DIVAPI EntityID add##name(name##Archetype* archetype, name##Data components); \
    DIVAPI void remove##name(name##Archetype* archetype, EntityID entity); \
    DIVAPI name##Data get##name##Data(name##Archetype* archetype, EntityID entity);

// Implementation helper macros
#define POPULATE_ARCHETYPE(name) \
    bool create##name##Archetype(name##Archetype* archetype, uint32_t max_entities); \
        archetype->count = 0; \
        archetype->capacity = max_entities; \
        \
        /* Allocate entities array */ \
        archetype->entities = malloc(sizeof(EntityID) * max_entities); \
        if (!archetype->entities) return false; \
        \
        /* Create arena for components */ \
        if (arenaCreate(&archetype->componentsArena, \
                       sizeof(name##Data) * max_entities)) { \
            free(archetype->entities); \
            return false; \
        } \
        \
        archetype->first_component = (name##Data*)archetype->componentsArena.data; \
        return true; \
    } \
    \
    void destroy##name##Archetype(name##Archetype* archetype); \
        free(archetype->entities); \
        arenaDestroy(&archetype->componentsArena); \
    } \
    \
    EntityID add##name(name##Archetype* archetype, name##Data components); \
        if (archetype->count >= archetype->capacity) { \
            return 0; /* Invalid entity ID to indicate failure */ \
        } \
        \
        EntityID entity = generate_entity_id(); \
        archetype->entities[archetype->count] = entity; \
        \
        /* Copy components to arena */ \
        name##Data* comp_ptr = &archetype->first_component[archetype->count]; \
        *comp_ptr = components; \
        \
        archetype->count++; \
        return entity; \
    } \
    \
    void remove##name(name##Archetype* archetype, EntityID entity); \
        for (uint32_t i = 0; i < archetype->count; i++) { \
            if (archetype->entities[i] == entity) { \
                if (i < archetype->count - 1) { \
                    /* Move last entity to removed slot */ \
                    archetype->entities[i] = archetype->entities[archetype->count - 1]; \
                    archetype->first_component[i] = archetype->first_component[archetype->count - 1]; \
                } \
                archetype->count--; \
                return; \
            } \
        } \
    } \
    \
    name##Data get##name##Data(name##Archetype* archetype, EntityID entity);
        for (uint32_t i = 0; i < archetype->count; i++) { \
            if (archetype->entities[i] == entity) { \
                return &archetype->first_component[i]; \
            } \
        } \
        return NULL; \
    }

// Helper function to generate unique entity IDs
static EntityID next_entity_id = 1;
static inline EntityID generate_entity_id(void) {
    return next_entity_id++;
}
