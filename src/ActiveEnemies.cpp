#include "ActiveEnemies.h"

void ActiveEnemies::addEnemies(std::vector<Unit*> src)
{
	for (Unit* enemy : src)
	{
		active_enemies.push_back(enemy);
	}
}
void ActiveEnemies::addEnemies(std::vector<Object> src)
{
	for (Object enemy : src)
	{
		Unit* piggie = new Pig(enemy.rect.left, enemy.rect.top);
		active_enemies.push_back(piggie);
	}
}

void ActiveEnemies::removeDeadEnemies()
{
	size_t position = 0;
	for (Unit* enemy : active_enemies)
	{
		
		if (!enemy->isAlive())
		{
			if (enemy->currentAnimationIsOver())
			{
				Unit* tmp = enemy;
				active_enemies.erase(active_enemies.begin() + position);
				delete tmp;
			}
		}
		position++;
	}
}

void ActiveEnemies::clearActiveEnemies()
{
	for (Unit* enemy : active_enemies)
	{
		delete enemy;
	}
	active_enemies.erase(active_enemies.begin(), active_enemies.end());
}

std::vector<Unit*>& ActiveEnemies::getActiveEnemies()
{
	return active_enemies;
}
