#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Unit.h"
#include "level.h"
#include "Pig.h"
class ActiveEnemies
{
public:
	void addEnemies(std::vector<Unit*> src);
	void addEnemies(std::vector<Object> src);
	void removeDeadEnemies();
	void clearActiveEnemies();
	std::vector<Unit*>& getActiveEnemies();
private:
	std::vector<Unit*> active_enemies;
};

