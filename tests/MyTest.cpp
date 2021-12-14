#include "gtest/gtest.h"
#include "Systems.h"
#include <Entity.h>

#define vec2f sf::Vector2f


const std::ostream& operator<<(const std::ostream& os,vec2f& vec)
{
    std::cout << "x = " << vec.x << "; y = " << vec.y << ";\n";
    return os;
}
struct TestScene: public Scene
{
    TestScene(sf::RenderWindow& window_ref): Scene(window_ref) {}
    virtual bool render(float dt) override
    {
        return false;
    }
    virtual bool update(float dt) override
    {
        return false;
    }
};
struct MoveSystemTestCase : public ::testing::Test
{
    virtual void SetUp() override
    {
        test_scene = new TestScene(*null_window);
        reg_ptr = &(test_scene->Reg());
        test_entity = new Entity(reg_ptr->create(), test_scene);
        test_entity->AddComponent<MoveComponent>(vec2f(0.f,0.f), vec2f(0.f,0.f), vec2f(0.f,0.f), vec2f(100.f,100.f));
        move_system = new MoveSystem(test_scene);

    }
    virtual void TearDown() override
    {
        delete test_entity;
        delete test_scene;
    }
    template<typename T>
    T& getComponent(Entity entity)
    {
        auto& result= reg_ptr->get<T>(entity.EntityID);
        return result;
    }
    protected:
    Scene* test_scene;
    //placeholder to create a scene which contains entt::registry
    sf::RenderWindow* null_window = nullptr;
    Entity* test_entity;
    entt::registry* reg_ptr;
    System* move_system;

};


TEST_F(MoveSystemTestCase, PositionZero)
{
    auto& move_component = getComponent<MoveComponent>(*test_entity);

    //Simulating input 
    move_component.current_speed +=move_component.max_speed;

    float predefined_dt = 0.125f;
    vec2f expected_vel = move_component.current_speed * predefined_dt;
    vec2f expected_pos(0.f,0.f);
    expected_pos += expected_vel;
    move_system->update(predefined_dt);
    std::cout<<"Expected position: " << expected_pos;
    std::cout<<"Actual position: " << move_component.position;
    EXPECT_EQ(expected_pos,move_component.position);
}