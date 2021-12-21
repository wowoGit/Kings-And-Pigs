#include "EntityFactory.h"




void EntityFactory::createHero(const Tmx::Object& obj) {
    
	Entity player(scene->Reg().create(),scene);
	auto& texture_idle = TextureLoader::loadFromFile("Sprites/king/Idle.png", "IDLE");
	auto& texture_run = TextureLoader::loadFromFile("Sprites/king/Run.png", "RUN_LEFT");
	auto& texture_jump = TextureLoader::loadFromFile("Sprites/king/Jump.png", "JUMP");
	auto& texture_run_copy_ref = TextureLoader::bindTexOnMultAnim("RUN_RIGHT", texture_run);
	sf::IntRect rect(0,0,58,58);
	sf::Sprite sprite(texture_idle,rect);
	sprite.setPosition(100.f,100.f);
	sprite.setOrigin(sf::Vector2f{58 / 2, 58 / 2});
	auto runLeftAnim = createAnimation(rect, ANIMATION_DIRECTION::FLIPPED, .1f, true);
	auto runRightAnim = createAnimation(rect, ANIMATION_DIRECTION::STANDARD, .1f, true);
	auto idleAnim = createAnimation(rect, ANIMATION_DIRECTION::NEUTRAL, .1f, true);
	auto jumpAnim = createAnimation(rect, ANIMATION_DIRECTION::NEUTRAL, .1f, true);
	std::map<std::string,AnimationComponent> animation_pool {{"IDLE", idleAnim},
															{"RUN_RIGHT", runRightAnim},
															{"RUN_LEFT", runLeftAnim},
															{"JUMP", jumpAnim}};
	player.AddComponent<MoveComponent>(sf::Vector2f(100,100), sf::Vector2f(0,0),sf::Vector2f(0.f,0.f), sf::Vector2f(100.f,50.f));
	player.AddComponent<PhysicsComponent>(0.85f,1.5f);
	player.AddComponent<SpriteComponent>(sprite);
	player.AddComponent<PlayerTag>(false);
	player.AddComponent<AnimationComponent>(.1f, ANIMATION_DIRECTION::STANDARD,rect, true);
	player.AddComponent<StateComponent>("IDLE");
	player.AddComponent<AnimationPool>(animation_pool,"IDLE");
}

void EntityFactory::createMapObjects(const std::vector<Tmx::Object>& object_vec) {
    
	for(const auto& obj : object_vec)
	{
		// if object.name == "blalala" generate a corresponding entity with a set of components
	}
}

void EntityFactory::createMapTiles(const std::vector<GameMap::map_layer>& layer_vec) {
    
	for (const auto& layer : layer_vec)
	{
		for( const auto& tile : layer.tiles)
		{
			switch(tile.type)
			{
				case GameMap::TileType::SOLID:
					//generate SOLID tile with a set of components...
					break;
				//...
			}
		}
	}
}
