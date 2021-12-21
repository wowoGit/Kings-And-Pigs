#include "EntityFactory.h"




void EntityFactory::createHero(const Tmx::Object& obj) {
    
	Entity player(scene->Reg().create(),scene);
	const auto& texture_idle = TextureLoader::loadFromFile("Sprites/king/Idle.png", "IDLE");
	const auto& texture_run = TextureLoader::loadFromFile("Sprites/king/Run.png", "RUN_LEFT");
	const auto& texture_jump = TextureLoader::loadFromFile("Sprites/king/Jump.png", "JUMP");
	//auto& texture_run_copy_ref = TextureLoader::bindTexOnMultAnim("RUN_RIGHT", texture_run);
	sf::IntRect rect(0,0,58,58);
	sf::Sprite sprite(texture_idle,rect);
	sprite.setPosition(100.f,100.f);
	sprite.setOrigin(sf::Vector2f{58 / 2, 58 / 2});
	auto runLeftAnim = createAnimation(rect, ANIMATION_DIRECTION::FLIPPED, .1f, true);
	auto runRightAnim = createAnimation(rect, ANIMATION_DIRECTION::STANDARD, .1f, true);
	auto idleAnim = createAnimation(rect, ANIMATION_DIRECTION::NEUTRAL, .1f, true);
	auto jumpAnim = createAnimation(rect, ANIMATION_DIRECTION::NEUTRAL, .1f, true);
	std::map<std::string,AnimationComponent> animation_pool {{"IDLE", idleAnim},
															{"RUN_LEFT", runLeftAnim},
															{"JUMP", jumpAnim}};
	player.AddComponent<MoveComponent>(sf::Vector2f(100,100), sf::Vector2f(0,0),sf::Vector2f(0.f,0.f), sf::Vector2f(100.f,50.f));
	player.AddComponent<PhysicsComponent>(0.85f,1.5f);
	player.AddComponent<SpriteComponent>(sprite);
	player.AddComponent<PlayerTag>(false);
	player.AddComponent<AnimationComponent>(.1f, ANIMATION_DIRECTION::STANDARD,rect, true);
	player.AddComponent<StateComponent>("IDLE");
	player.AddComponent<AnimationPool>(animation_pool,"IDLE");
	entity_vec.push_back(player);
}

void EntityFactory::createMapObjects(std::vector<Tmx::Object> object_vec) {
    
	for(const auto& obj : object_vec)
	{
		if(obj.GetName() == "hero")
		{
			createHero(obj);
		}
	// if object.name == "blalala" generate a corresponding entity with a set of components
	}
}

void EntityFactory::createMapTiles(std::vector<GameMap::map_layer> layer_vec) {
	
	auto& reg = scene->Reg();
	for (const auto& layer : layer_vec)
	{
		for( const auto& tile : layer.tiles)
		{
			sf::Sprite tile_sprite(tile.texture_ref,tile.rect);
			tile_sprite.setPosition(tile.sprite_pos);
			Entity ent(reg.create(), scene);
			ent.AddComponent<SpriteComponent>(tile_sprite);
			switch(tile.type)
			{
				case GameMap::TileType::SOLID:
					sf::IntRect collidableBody(tile.rect);
					collidableBody.left = tile.sprite_pos.x;
					collidableBody.top = tile.sprite_pos.y;
					ent.AddComponent<CollidableComponent>(collidableBody);
					break;
				//...
			}
			entity_vec.push_back(ent);
		}
	}
}
