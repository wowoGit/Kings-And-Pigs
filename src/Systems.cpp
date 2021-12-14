#include "Systems.h"
#include "DebugRenderer.h"
#include "TextureLoader.h"
#include <iostream>
#define DEBUG  




bool MoveSystem::update(float dt) 
{
        entt::registry& entt_reg = scene->Reg();
        auto view = entt_reg.view<MoveComponent>();

        for(auto [entity, mc] : view.each())
        {
                mc.velocity += mc.current_speed * dt;
                mc.position +=mc.velocity;
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
               sprite.Sprite.move(pos.velocity);
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



//bool AnimationStateSystem::update(float dt) {
       //entt::registry& entt_reg = scene->Reg();
       //auto view = entt_reg.view<SpriteComponent,AnimationPool,StateComponent, AnimationComponent>();
       //for( auto [entt,sprite_comp,pool_comp,state_comp, anim_comp] : view.each())
       //{
               //auto& pool = pool_comp.pool;
               //auto& current_anim = pool_comp.current;
               //auto& sprite = sprite_comp.Sprite;
               //auto& state = state_comp.state;
               //if (pool.find(state) != pool.end() && current_anim != state)
               //{
                       //current_anim = state;
                       //auto& texture = TextureLoader::getTexture(pool_comp.current);
                       //sprite_comp.Sprite.setTexture(texture);
                       //sprite_comp.Sprite.setTextureRect(pool[current_anim].frame);
                       //anim_comp = pool[current_anim];
               //}
               
       //}
        

        //return true;

//}

bool PlayerInputSystem::update(float dt) {
       entt::registry& entt_reg = scene->Reg();
       //This is a temporary version to test the physics
        auto view = entt_reg.view<PlayerTag, MoveComponent, StateComponent>();
        auto player = view.front();
        auto& mc =  entt_reg.get<MoveComponent>(player);
        auto& state =  entt_reg.get<StateComponent>(player);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {
                mc.current_speed.y += -mc.max_speed.y;
                state.state = "JUMP";
                
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
                mc.current_speed.x = -mc.max_speed.x;
                state.state = "RUN_LEFT";
                
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
                mc.current_speed.x = mc.max_speed.x;
                state.state = "RUN_RIGHT";
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
                mc.current_speed.y += mc.max_speed.y;
                state.state = "RUN_RIGHT";
        }
        else
        {

                mc.current_speed = sf::Vector2f(0.f,0.f);
                state.state = "IDLE";
        }
        
        return true;

}

bool PhysicsSystem::update(float dt)
{
       entt::registry& entt_reg = scene->Reg();
       auto view = entt_reg.view<MoveComponent, PhysicsComponent,SpriteComponent>();

       for(auto [entity,mc,pc,sc] : view.each())
       {
               mc.velocity.y += pc.gravity;

               if(abs(mc.velocity.y) > 20.f)
               {
                       mc.velocity.y = mc.max_speed.y * ((mc.velocity.y > 0) ? 1.f: -1.f);
               }

               mc.velocity *=pc.resistance;
               if(abs(mc.velocity.y) < 1.f)
               mc.velocity.y = 0;
               if(abs(mc.velocity.x) < 1.f)
               mc.velocity.x = 0;
               if (mc.position.y >= 900)
               mc.position.y = 900;
               sc.Sprite.setPosition(mc.position);


       }


}