#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "level.h"
#include "SolidBoundaries.h"
#include "StickBoundaries.h"
#include "InvisibleBoundaries.h"
#include "Player.h"
#include "ActiveEnemies.h"
#include "Box.h"
class LevelController
{
public:
	LevelController();
	void addLevelByPath(std::string levelPath);
	void nextLevel();
	void updateCollision(Unit* player, ActiveEnemies* enemies);
	std::vector<Object> getObjects(std::string objName);
	Object* getObject(std::string objName);
	void update();
	void renderCurrentLevel(sf::RenderWindow& window);
	BoundariesComponent* solidBounds = nullptr;
private:
	//boundaries
	void initItems();
	void itemCollision(Unit* player);
	void loadLevel(std::string levelPath);
	void itemsCollision(Unit* items);
	void clearResources();
	std::vector<Item*> items;
	BoundariesComponent* invisBounds = nullptr;
	BoundariesComponent* stickBounds = nullptr;
	std::vector<std::string> levels;
	Level* currentLevel = nullptr;
	size_t levelCounter;

};

