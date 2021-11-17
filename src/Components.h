#pragma once
#include <string>
//#include "InputCommands.hpp"
#include <SFML/Graphics.hpp>
//ENTITY COMPONENTS 

struct TagComponent
{
    std::string Tag;
};

struct SpriteComponent
{
    sf::Sprite Sprite;
    bool flip; 
};

struct AnimationComponent
{
    float speed;
    sf::IntRect frame;
    bool islooped;

};

struct AnimationPool
{
    std::map<std::string, sf::IntRect> pool;
    std::string current;
};

struct MoveComponent
{
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
};

struct HitBoxComponent
{
    sf::FloatRect hitbox;
};

//struct PlayerMoveComponent
//{
    //MoveCommand* button_W;
    //MoveCommand* button_S;
    //MoveCommand* button_A;
    //MoveCommand* button_D;
    //PlayerMoveComponent(MoveComponent& mvcomp)
    //{
        //button_A = new MoveLeftCommand();
        //button_W = new MoveUpCommand();
        //button_S = new MoveDownCommand();
        //button_D = new MoveRightCommand();
    //}
    //PlayerMoveComponent(PlayerMoveComponent& other) = default;
    //~PlayerMoveComponent() 
    //{
        //delete button_W;
        //delete button_S;
        //delete button_A;
        //delete button_D;
    //}
    
    //void setA(MoveCommand* command)
    //{
        //if(button_A)
        //delete button_A;

        //button_A = command;
    //}
    //void setW(MoveCommand* command)
    //{
        //if(button_W)
        //delete button_W;

        //button_W = command;
    //}
    //void setD(MoveCommand* command)
    //{
        //if(button_D)
        //delete button_D;

        //button_D = command;
    //}
    //void setS(MoveCommand* command)
    //{
        //if(button_S)
        //delete button_S;

        //button_S = command;
    //}
//};

struct CollidableComponent
{
    sf::IntRect body;
};

struct StateComponent
{
    std::string state;
};
