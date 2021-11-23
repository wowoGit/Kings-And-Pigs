#include "Systems.h"
#include "DebugRenderer.h"
#include "TextureLoader.h"
#include <iostream>
#define DEBUG  



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

bool AnimationSystem::update(float dt) 
{
       entt::registry& entt_reg = scene->Reg();
       auto view = entt_reg.view<AnimationComponent, SpriteComponent>();

        for(auto [entity, animation,sprite] : view.each())
        {
                runAnimation(animation,sprite,dt);
        }

}
void AnimationSystem::runAnimation(AnimationComponent& animation, SpriteComponent& sprite_comp, float dt)
{
        elapsed +=dt;
        if (elapsed < animation.speed)
        {
                return;
        }
        auto textureSize =sprite_comp.Sprite.getTexture()->getSize();
        auto& sprite  = sprite_comp.Sprite;
        auto& frame = animation.frame;
        switch (animation.dir)
        {
        case  ANIMATION_DIRECTION::STANDARD:
                animation.frame.left = (animation.frame.left + animation.frame.width + 20) % textureSize.x;
		sprite.setScale(1.f, 1.f);
		//sprite.setOrigin(0, 0);
                break;
        
        case ANIMATION_DIRECTION::FLIPPED:
                animation.frame.left =  (animation.frame.left + abs(animation.frame.width)+ 20) % textureSize.x; 
		sprite.setScale(-1.f, 1.f);
		//sprite.setOrigin(sprite.getGlobalBounds().width / 1.f, 0);
                break;
        case ANIMATION_DIRECTION::NEUTRAL:
                animation.frame.left =  (animation.frame.left + abs(animation.frame.width)+ 20) % textureSize.x; 
                break;
        }
        sprite.setTextureRect(animation.frame);
        elapsed = 0.0f;



}

bool SpriteRendererSystem::update(float dt) {
       entt::registry& entt_reg = scene->Reg();
       auto view = entt_reg.view<MoveComponent,SpriteComponent>();
       for( auto [entt,pos,sprite] : view.each())
       {
               sprite.Sprite.setPosition(pos.position);
               scene->Wind().draw(sprite.Sprite);
               #ifdef DEBUG
               DebugRenderer::render(sprite.Sprite, DebugType::CENTER, scene->Wind());
               DebugRenderer::render(sprite.Sprite, DebugType::OUTLINE, scene->Wind());
               #endif 
       }
        

        return true;

}


bool AnimationStateSystem::update(float dt) {
       entt::registry& entt_reg = scene->Reg();
       auto view = entt_reg.view<SpriteComponent,AnimationPool,StateComponent, AnimationComponent>();
       for( auto [entt,sprite_comp,pool_comp,state_comp, anim_comp] : view.each())
       {
               auto& pool = pool_comp.pool;
               auto& current_anim = pool_comp.current;
               auto& sprite = sprite_comp.Sprite;
               auto& state = state_comp.state;
               if (pool.find(state) != pool.end() && current_anim != state)
               {
                       current_anim = state;
                       auto& texture = TextureLoader::getTexture(pool_comp.current);
                       sprite_comp.Sprite.setTexture(texture);
                       sprite_comp.Sprite.setTextureRect(pool[current_anim].frame);
                       anim_comp = pool[current_anim];
               }
               
       }
        

        return true;

}


