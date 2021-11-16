#include "Scene.h"
class System
{
    public:
    System(Scene* currentScene) : scene(currentScene) 
    { }
    virtual bool update(float deltaTime) = 0;

    protected:
    Scene* scene;
};


class PlayerInputSystem : public System
{
    public:
    PlayerInputSystem(Scene* currentScene) : System(currentScene) {};
    virtual bool update(float dt) override;
};

class MoveSystem : public System
{
    public:
    MoveSystem(Scene* currentScene) : System(currentScene) {};
    virtual bool update(float dt) override;
};

class ColliderSystem: public System
{
    public:
    ColliderSystem(Scene* currentScene) : System(currentScene) {};
    virtual bool update(float dt) override;
};

class AnimationSystem: public System
{
public:
    AnimationSystem(Scene* currentScene) : System(currentScene) {};
    virtual bool update(float dt) override;
    void runAnimation(AnimationComponent& animation);
};