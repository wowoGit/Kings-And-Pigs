#include "LevelController.h"

LevelController::LevelController()
{
	levelCounter = 0;
	addLevelByPath("../maps/lvl1.tmx");
	addLevelByPath("../maps/lvl2.tmx");
	loadLevel(levels[levelCounter]);
	
	
}

void LevelController::addLevelByPath(std::string levelPath)
{
	levels.push_back(levelPath);
}
void LevelController::updateCollision(Unit* player, ActiveEnemies* enemies)
{
	this->solidBounds->handleCollisionWith(player);
	this->stickBounds->handleCollisionWith(player);
	for (Unit* enemy : enemies->getActiveEnemies())
	{
		this->invisBounds->handleCollisionWith(enemy);
	}
	itemCollision(player);
}
void LevelController::nextLevel()
{
	
	levelCounter++;
	if (levelCounter > levels.size() - 1 )
	{
		levelCounter = 0;
	}
	loadLevel(levels[levelCounter]);
}

std::vector<Object> LevelController::getObjects(std::string objName)
{
	return currentLevel->GetObjects(objName);
}

Object* LevelController::getObject(std::string objName)
{
	return currentLevel->GetObject(objName);
}

void LevelController::update()
{
	for (Item* item : items)
	{
		item->update();
		
	}
}

void LevelController::renderCurrentLevel(sf::RenderWindow& window)
{
	if (currentLevel == nullptr)
		return;

	currentLevel->Draw(window);
	for (Item* item : items)
	{
		item->render(window);
	}
}

void LevelController::initItems()
{
	Object* itemObj = getObject("box");
	if(itemObj)
	items.push_back(new Box(itemObj->rect.left, itemObj->rect.top));
}

void LevelController::itemCollision(Unit* player)
{
	for (Item* item : items)
	{
		if (player->getHitBox().intersects(item->getHitBox()))
		{
			//item->getHitWith(10);
			item->interact(player);
			
		}
		if (player->getAttackArea().getGlobalBounds().intersects(item->getHitBox()))
		{
			Player* castedPlayer = static_cast<Player*>(player);
			castedPlayer->attack(item);
		}
		//std::cout << player->getPosition().x << "\t" << player->getPosition().y << "\t" <<item->getPosition().x << "\t" << item->getPosition().y << std::endl;
	}
}

void LevelController::loadLevel(std::string levelPath)
{
	clearResources();
	currentLevel = new Level();
	currentLevel->LoadFromFile(levelPath);
	solidBounds = new SolidBoundaries();
	invisBounds = new InvisibleBoundaries();
	stickBounds = new StickBoundaries();
	solidBounds->initBoundaries(getObjects("solid"));
	invisBounds->initBoundaries(getObjects("invis_walls"));
	stickBounds->initBoundaries(getObjects("wood_solid"));
	initItems();
}

void LevelController::itemsCollision(Unit* player)
{
	items.front()->interact(player);
}

void LevelController::clearResources()
{
	delete solidBounds;
	delete stickBounds;
	delete invisBounds;
	delete currentLevel;
	for (Item* item : items)
	{
		delete item;
	}
	items.erase(items.begin(), items.end());
}
