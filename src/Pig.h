#pragma once
#include "Unit.h"
class Pig : public Unit
{
public:
    Pig(const int _x, const int _y);
    void initAnimations() override;
    void update() override;
    void getHitWith(int _dmg) override;
    void move(const float x, const float y) override;
    void generateDirection();
    void setAnimationOnState();
    void calculateState();
    void resetAttackLock() override;
    void attack(Unit* target) override;
    sf::Clock DirGenerationTimer;
    sf::Clock attackCooldownTimer;
private:
    sf::Vector2f velocity;
    float VelocityXMax = 1.f;
    float VelocityYMax = 0.f;
    float attackCoolDown = 3.f;
    float moveSpeed = 1.f;
    int moveDirection;
    float movementCooldown = 2.f;
    enum STATE {IDLE, RUN_LEFT, RUN_RIGHT,ATTACK,HIT,DEAD};
    STATE pigState;

};

