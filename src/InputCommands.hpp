#pragma once
#include "Components.h"

struct MoveCommand
{
    virtual bool execute(MoveComponent& cmpnt,PlayerStateComponent& state) = 0;
};


struct MoveRightCommand: public MoveCommand
{
    MoveRightCommand() = default;
    virtual bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.x = comp.speed;
        state.p_state = "MOVE_RIGHT";
    }
};

struct MoveLeftCommand: public MoveCommand
{
    MoveLeftCommand() = default;
    virtual bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.x = -comp.speed;
        state.p_state = "MOVE_LEFT";
    }
};
struct MoveDownCommand: public MoveCommand
{
    MoveDownCommand() = default;
    virtual bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.y = -comp.speed;
        state.p_state = "MOVE_DOWN";
    }
};
struct MoveUpCommand: public MoveCommand
{
    MoveUpCommand() = default;
    virtual bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.y = comp.speed;
        state.p_state = "MOVE_UP";
    }
};

struct IdleCommand: public MoveCommand
{
    IdleCommand() = default;
    virtual bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        state.p_state = "IDLE";
    }
};

