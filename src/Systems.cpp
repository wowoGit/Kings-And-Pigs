#include "Systems.h"
#include "Components.h"



bool PlayerInputSystem::update(float dt) 
{
        //POSSIBLY RELOCATE TO BASE CLASS CONSTRUCTOR
        entt::registry& entt_reg = scene->Reg();
        auto& wind = scene->Wind();
        
        auto view = entt_reg.view<PlayerMoveComponent, MoveComponent>();
        auto player_entity = view.front();

        // get PlayerMoveComponent
        for(auto [player, player_mc, mc] : view.each())
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
                player_mc.button_A->execute(mc);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
                player_mc.button_W->execute(mc);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
                player_mc.button_S->execute(mc);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
                player_mc.button_D->execute(mc);
        }
        
        
}

bool MoveSystem::update(float dt) 
{
        entt::registry& entt_reg = scene->Reg();
        auto& wind = scene->Wind();
        auto view = entt_reg.view<MoveComponent>();

        for(auto [entity, mc] : view.each())
        {
                mc.position += mc.velocity * dt;
                mc.velocity *= .0f;
        }

}