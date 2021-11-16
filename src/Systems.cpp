#include "Systems.h"



bool PlayerInputSystem::update(float dt) 
{
        //POSSIBLY RELOCATE TO BASE CLASS CONSTRUCTOR
        //entt::registry& entt_reg = scene->Reg();

        //auto view = entt_reg.view<PlayerMoveComponent, MoveComponent, PlayerStateComponent>();
        //auto player_entity = view.front();

        //// get PlayerMoveComponent
        //for(auto [player, player_mc, mc, sc] : view.each())
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        //{
                //player_mc.button_A->execute(mc,sc);
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        //{
                //player_mc.button_W->execute(mc,sc);
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        //{
                //player_mc.button_S->execute(mc,sc);
        //}
        //else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        //{
                //player_mc.button_D->execute(mc,sc);
        //}
        
        return true;
}

bool MoveSystem::update(float dt) 
{
        entt::registry& entt_reg = scene->Reg();
        auto view = entt_reg.view<MoveComponent>();

        for(auto [entity, mc] : view.each())
        {
                mc.position += mc.velocity * dt;
                mc.velocity *= .0f;
        }

        return true;
}
// TO DO
bool ColliderSystem::update(float dt)
{
        entt::registry& entt_reg = scene->Reg();
        auto view_units= entt_reg.view<HitBoxComponent, TagComponent>();
        auto view_boundaries = entt_reg.view<CollidableComponent, TagComponent>();
        
        for(auto [entity,body,name] : view_units.each())
        {
                if(name.Tag.compare("player") == 0)
                {
                        
                }
                for(auto [collidable_body_entity,collidable_body,collidable_body_name] : view_boundaries.each())
                {
                        
                }
        }
        return true;
} 

//bool AnimationSystem::update(float dt) 
//{
       //entt::registry& entt_reg = scene->Reg();
       //auto view = entt_reg.view<AnimationPool, PlayerStateComponent>();
       //auto player_entity = view.front();

       //auto [pool,state] = view.get<AnimationPool,PlayerStateComponent>(player_entity);

        //pool.current = state.p_state;



//}
void AnimationSystem::runAnimation(AnimationComponent& animation, SpriteComponent& sprite_comp)
{
        auto textureSize =sprite_comp.Sprite.getTexture()->getSize();
        auto& sprite  = sprite_comp.Sprite;
        auto& frame = animation.frame;

        sprite.setTextureRect(frame);
        if(sprite_comp.flip)
        {
                frame.left -= frame.width;
                if(frame.left  <= frame.width) {
                        if(animation.islooped) 
                        {
                                frame.left = textureSize.x - frame.width;
                        }
                        else
                        {
                                frame.left = 0;
                        }
                        
                        
                }
        }
        else
        {
                frame.left += frame.width;
                if(frame.left >= textureSize.x-frame.width)
                {
                        if(animation.islooped)
                        {
                                frame.left = 0;
                        }
                        else
                        {
                                frame.left = textureSize.x - frame.width;
                        }
                }
        }

}

bool SpriteRendererSystem::update(float dt)
{
       entt::registry& entt_reg = scene->Reg();
       auto view = entt_reg.view<MoveComponent,SpriteComponent>();
       for( auto [entt,pos,sprite] : view.each())
       {
               sprite.Sprite.setPosition(pos.position);
               scene->Wind().draw(sprite.Sprite);
       }
        

        return true;

}




