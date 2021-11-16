#pragma once
#include <string>
#include "InputCommands.h"
#include <SFML/Graphics.hpp>
//ENTITY COMPONENTS 

struct TagComponent
{
    std::string Tag;
    TagComponent() = default;
    TagComponent(TagComponent& other) = default;
    TagComponent(const std::string& tag): Tag(tag)
    {}
};

struct SpriteComponent
{
    sf::Sprite Sprite;
    bool flip; 
    SpriteComponent(sf::Texture& texture, sf::IntRect rect, bool flipped)
    {
        Sprite.setTexture(texture);
        Sprite.setTextureRect(rect);
        flip = flipped;
        
    }
    SpriteComponent() = default;
    SpriteComponent(SpriteComponent& other) = default; 
};

struct AnimationComponent
{
    SpriteComponent spriteComponent;
    float speed;
    sf::IntRect frame;
    bool islooped;
    AnimationComponent(sf::IntRect& rect,SpriteComponent& sprite_comp, bool loop, float anim_speed) : 
    spriteComponent(sprite_comp),frame(rect),islooped(loop), speed(anim_speed) {}
    AnimationComponent(AnimationComponent& other) = default;

};

struct AnimationPool
{
    std::map<TagComponent,AnimationComponent> pool;
    std::string current;
    AnimationPool(std::map<TagComponent,AnimationComponent>& anim_pool) : pool(anim_pool) {};
    AnimationPool(AnimationPool& other) = default;
};

struct MoveComponent
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    MoveComponent(const sf::Vector2f pos, const sf::Vector2f vel, float spd) : position(pos), velocity(vel), speed(spd)
    {}
    MoveComponent() = default;
    MoveComponent(MoveComponent& other) = default;
};

struct HitBoxComponent
{
    sf::FloatRect hitbox;
    HitBoxComponent(const sf::FloatRect box): hitbox(box) {};
    HitBoxComponent() = default;
    HitBoxComponent(HitBoxComponent& other) = default;
};

struct PlayerMoveComponent
{
    MoveCommand* button_W;
    MoveCommand* button_S;
    MoveCommand* button_A;
    MoveCommand* button_D;
    PlayerMoveComponent(MoveComponent& mvcomp)
    {
        button_A = new MoveLeftCommand();
        button_W = new MoveUpCommand();
        button_S = new MoveDownCommand();
        button_D = new MoveRightCommand();
    }
    PlayerMoveComponent(PlayerMoveComponent& other) = default;
    ~PlayerMoveComponent() 
    {
        delete button_W;
        delete button_S;
        delete button_A;
        delete button_D;
    }
    
    void setA(MoveCommand* command)
    {
        if(button_A)
        delete button_A;

        button_A = command;
    }
    void setW(MoveCommand* command)
    {
        if(button_W)
        delete button_W;

        button_W = command;
    }
    void setD(MoveCommand* command)
    {
        if(button_D)
        delete button_D;

        button_D = command;
    }
    void setS(MoveCommand* command)
    {
        if(button_S)
        delete button_S;

        button_S = command;
    }
};

struct CollidableComponent
{
    sf::IntRect body;
    CollidableComponent(sf::IntRect body_param) : body(body_param) {}
    CollidableComponent() = default;
    CollidableComponent(CollidableComponent& other) = default;
};

struct PlayerStateComponent
{
    enum STATE {IDLE = 0, MOVE_LEFT, MOVE_RIGHT, JUMP, FALL, ATTACK};
    STATE p_state;
    PlayerStateComponent() = default; 
    PlayerStateComponent(PlayerStateComponent& state) = default;
};
