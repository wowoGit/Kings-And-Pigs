#pragma once
#include "SFML/Graphics.hpp"
//#include "Pig.h"
//#include "ActiveEnemies.h"
//#include "InvisibleBoundaries.h"
//#include "SolidBoundaries.h"
//#include "StickBoundaries.h"
//#include "LevelController.h"
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
	std::unique_ptr<Map> map;
	std::unique_ptr<Entity> player;
	std::unique_ptr<SpriteRendererSystem> spriteSystem;
	std::unique_ptr<AnimationSystem> animSystem;
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

