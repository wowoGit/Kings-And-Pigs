#pragma once
#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Pig.h"
#include "ActiveEnemies.h"
#include "InvisibleBoundaries.h"
#include "SolidBoundaries.h"
#include "StickBoundaries.h"
#include "LevelController.h"
class Game
{
private:
	sf::RenderWindow window;
	sf::Event ev;

	Unit* player;
	LevelController* lvlController;
	//std::vector<Object> solidObjects;
	//std::vector<Object> invisObjects;

	/*BoundariesComponent* solidBounds;
	BoundariesComponent* invisBounds;
	BoundariesComponent* stickBounds;*/
	sf::RectangleShape plshape;
	sf::RectangleShape pigshape;
	sf::RectangleShape hitbox;
	std::vector<sf::RectangleShape> walls;
	std::vector<Unit*> Pigs_vec;
	ActiveEnemies* active_enemies;
	sf::View* view;
	void initWindow();
	void initPlayer();
	void initPigs();
	void initLevel();
	void initView();
public:

	//Functions


	Game();
	virtual ~Game();

	//Functions
	void updatePlayer();
	void changeLevel();
	void updateView();
	void updateCollision();
	void playerAttacks();
	void update();
	void renderPlayer();
	void renderPigs();
	void updatePigs();
	void render();
	const sf::RenderWindow& getWindow() const;
	

};

