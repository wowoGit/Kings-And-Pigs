#pragma once
#include "Components.h"

struct MoveCommand
{
    virtual bool execute(MoveComponent& cmpnt) = 0;
};


struct MoveRightCommand: public MoveCommand
{
    MoveRightCommand() = default;
    bool execute(MoveComponent& comp) override
    {
        comp.velocity.x = comp.speed;
    }
};

struct MoveLeftCommand: public MoveCommand
{
    MoveLeftCommand() = default;
    bool execute(MoveComponent& comp) override
    {
        comp.velocity.x = -comp.speed;
    }
};
struct MoveDownCommand: public MoveCommand
{
    MoveDownCommand() = default;
    bool execute(MoveComponent& comp) override
    {
        comp.velocity.y = -comp.speed;
    }
};
struct MoveUpCommand: public MoveCommand
{
    MoveUpCommand() = default;
    bool execute(MoveComponent& comp) override
    {
        comp.velocity.y = comp.speed;
    }
};


