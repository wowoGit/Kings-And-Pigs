#include "gtest/gtest.h"
#include "Systems.h"
#include <Entity.h>
#define vec2f sf::Vector2f

//GLOBAL VARS


struct TestScene: public Scene
{
    TestScene(sf::RenderWindow* window_ref): Scene(*window_ref) {}
    virtual bool render(float dt) override
    {
        return false;
    }
    virtual bool update(float dt) override
    {
        return false;
    }
};


class ECSEnvironment : public testing::Environment
{
    public:
    ~ECSEnvironment() override {};

    inline static Scene* scene = nullptr;
    void SetUp() override {
        sf::RenderWindow* wind = nullptr;
        scene = new TestScene(wind);
    }

    void TearDown() override {
        delete scene;
    }
};

int main()
{
    testing::InitGoogleTest();
    testing::AddGlobalTestEnvironment(new ECSEnvironment);
    return RUN_ALL_TESTS();
}

const std::ostream& operator<<(const std::ostream& os,vec2f& vec)
{
    std::cout << "x = " << vec.x << "; y = " << vec.y << ";\n";
    return os;
}
struct MoveSystemTestCase : public ::testing::Test
{
    virtual void SetUp() override
    {
        reg_ptr = &(ECSEnvironment::scene->Reg());
        test_entity = new Entity(reg_ptr->create(), ECSEnvironment::scene);
        test_entity->AddComponent<SpriteComponent>(sf::Sprite());
        move_system = new MoveSystem(ECSEnvironment::scene);

    }
    virtual void TearDown() override
    {
        reg_ptr->destroy(test_entity->EntityID);
        delete test_entity;
    }
    template<typename T>
    T& getComponent(Entity entity)
    {
        auto& result= reg_ptr->get<T>(entity.EntityID);
        return result;
    }
    protected:
    Entity* test_entity;
    entt::registry* reg_ptr;
    System* move_system;

};


TEST_F(MoveSystemTestCase, VelocityPositive)
{
    //Starting values
    test_entity->AddComponent<MoveComponent>(
    vec2f(0.f,0.f), // position
    vec2f(0.f,0.f), // velocity
    vec2f(0.f,0.f), // current speed
    vec2f(100.f,100.f)); // max speed
    auto& move_component = getComponent<MoveComponent>(*test_entity);

    //Simulating user input 
    move_component.current_speed +=move_component.max_speed;
    //Frame length
    float predefined_dt = 0.125f;
    //Expected values calculation 
    vec2f expected_vel = move_component.current_speed * predefined_dt;
    vec2f expected_pos(0.f,0.f);
    expected_pos +=expected_vel;
    move_system->update(predefined_dt);
    
    //Comparision
    std::cout<<"Expected position: " << expected_pos;
    std::cout<<"Actual position: " << move_component.position;
    EXPECT_EQ(expected_pos,move_component.position);
    reg_ptr->remove<MoveComponent>(test_entity->EntityID);
}


TEST_F(MoveSystemTestCase, VelocityZero)
{
    //Starting values
    test_entity->AddComponent<MoveComponent>(
    vec2f(0.f,0.f), // position
    vec2f(0.f,0.f), // velocity
    vec2f(0.f,0.f), // current speed
    vec2f(100.f,100.f)); // max speed

    auto& move_component = getComponent<MoveComponent>(*test_entity);

    //Frame length
    float predefined_dt = 0.125f;
    //Expected values calculation 
    vec2f expected_vel = move_component.current_speed * predefined_dt;
    vec2f expected_pos(0.f,0.f);
    expected_pos += expected_vel;
    //Tested function 
    move_system->update(predefined_dt);
    //Comparision
    std::cout<<"Expected position: " << expected_pos;
    std::cout<<"Actual position: " << move_component.position;
    EXPECT_EQ(expected_pos,move_component.position);
    reg_ptr->remove<MoveComponent>(test_entity->EntityID);
}

TEST_F(MoveSystemTestCase, VelocityNegative)
{
    //Starting values
    test_entity->AddComponent<MoveComponent>(
    vec2f(0.f,0.f), // position
    vec2f(0.f,0.f), // velocity
    vec2f(0.f,0.f), // current speed
    vec2f(-100.f,-100.f)); // max speed

    auto& move_component = getComponent<MoveComponent>(*test_entity);
    //Simulating user input 
    move_component.current_speed +=move_component.max_speed;

    //Frame length
    float predefined_dt = 0.125f;
    //Expected values
    vec2f expected_vel = move_component.current_speed * predefined_dt;
    vec2f expected_pos(0.f,0.f);
    expected_pos += expected_vel;
    //Tested functon
    move_system->update(predefined_dt);
    //Comparison
    std::cout<<"Expected position: " << expected_pos;
    std::cout<<"Actual position: " << move_component.position;
    EXPECT_EQ(expected_pos,move_component.position);
    reg_ptr->remove<MoveComponent>(test_entity->EntityID);
}