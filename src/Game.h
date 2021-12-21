#pragma once
#include "SFML/Graphics.hpp"
#include "TextureLoader.h"
#include "Systems.h"
#include "Components.h"
#include "Entity.h"
#include "Map.h"
class Game : public Scene
{
private:
	sf::RenderWindow& window;
	sf::Event ev;
	//this is all temporary just to check if everything is working correctly
	std::unique_ptr<GameMap::Map> map;
	std::unique_ptr<Entity> player;
	std::unique_ptr<SpriteRendererSystem> spriteSystem;
	std::unique_ptr<AnimationSystem> animSystem;
	std::unique_ptr<MoveSystem> moveSystem;
	std::unique_ptr<PhysicsSystem> physicsSystem;
	std::unique_ptr<PlayerInputSystem> inputSystem;
	std::unique_ptr<AnimationStateSystem> animStateSystem;
	/*BoundariesComponent* solidBounds;
	BoundariesComponent* invisBounds;
	BoundariesComponent* stickBounds;*/
	sf::View* view;
	void initWindow();
	void initPlayer();
	void initPigs();
	void initLevel();
	void initView();
public:

	//Functions

Game(sf::RenderWindow& game_window) : Scene(game_window), window(game_window)
{
	this->initWindow();
	this->initLevel();
	this->initPlayer();
	this->initPigs();
	this->initView();
	srand(time(NULL));
}

	//Functions
	void updatePlayer();
	void changeLevel();
	void updateView();
	void updateCollision();
	void playerAttacks();
	bool update(float dt);
	void renderPlayer();
	void renderPigs();
	void updatePigs();
	bool render(float dt);
	const sf::RenderWindow& getWindow() const;
	

};

