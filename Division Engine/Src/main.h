#pragma once
#include "../Engine/game.h"

#include <Windows.h>

#define MAX_ALIENS 10
#define MAX_BULLETS 20
#define MAX_BARRIERS 10

class SpaceInvaders : public Game
{
public:
    virtual bool start() override;
    virtual bool update(float dt) override;
    virtual bool render(float dt) override;
    virtual bool physics(float dt) override;
private:
    uint32_t player;
    uint32_t aliens[MAX_ALIENS];
    uint32_t bullets[MAX_BULLETS];
    uint32_t barriers[MAX_BARRIERS];
    float force = 100;
};