#pragma once
#include "Components.h"

struct MoveCommand
{
    virtual bool execute(MoveComponent& cmpnt,PlayerStateComponent& state) = 0;
};


struct MoveRightCommand: public MoveCommand
{
    MoveRightCommand() = default;
    bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.x = comp.speed;
        state.p_state = PlayerStateComponent::MOVE_RIGHT;
    }
};

struct MoveLeftCommand: public MoveCommand
{
    MoveLeftCommand() = default;
    bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.x = -comp.speed;
        state.p_state = PlayerStateComponent::MOVE_LEFT;
    }
};
struct MoveDownCommand: public MoveCommand
{
    MoveDownCommand() = default;
    bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.y = -comp.speed;
        state.p_state = PlayerStateComponent::FALL;
    }
};
struct MoveUpCommand: public MoveCommand
{
    MoveUpCommand() = default;
    bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        comp.velocity.y = comp.speed;
        state.p_state = PlayerStateComponent::JUMP;
    }
};

struct IdleCommand: public MoveCommand
{
    IdleCommand() = default;
    bool execute(MoveComponent& comp,PlayerStateComponent& state) override
    {
        state.p_state = PlayerStateComponent::IDLE;
    }
};

