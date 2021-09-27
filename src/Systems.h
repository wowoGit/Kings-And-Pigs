#include "Scene.h"
class System
{
    public:
    System(Scene* currentScene) : scene(currentScene) 
    { }
    virtual bool update(float deltaTime = .0f) = 0;

    protected:
    Scene* scene;
};


class PlayerInputSystem : public System
{
    public:
    virtual bool update(float dt = .0f) override;
};

class MoveSystem : public System
{
    public:
    virtual bool update(float dt = .0f) override;
};
