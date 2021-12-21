#include "Game.h"
#include "EntityFactory.h"
#include <iostream>
#include <random>
#include "functions.hpp"
void Game::initWindow()
{
	//this->window.setKeyRepeatEnabled(false);
	
}

void Game::initPlayer()
{
	map = std::make_unique<GameMap::Map>("maps/lvl1.tmx");
	EntityFactory factory(this);
	factory.createMapTiles(map->getMapLayers());
	factory.createMapObjects(map->getObjects());
	spriteSystem = std::make_unique<SpriteRendererSystem>(this);
	animStateSystem = std::make_unique<AnimationStateSystem>(this);
	animSystem = std::make_unique<AnimationSystem>(this);
	moveSystem = std::make_unique<MoveSystem>(this);
	physicsSystem = std::make_unique<PhysicsSystem>(this);
	inputSystem = std::make_unique<PlayerInputSystem>(this);
	
}

void Game::initPigs()
{
	//active_enemies = new ActiveEnemies();
}

void Game::initLevel()
{
	/*this->lvl = new Level;
	lvl->LoadFromFile("maps/jumpking.tmx");*/
	//invisObjects = lvl->GetObjects("invis_walls");
	//lvlController = new LevelController();
#ifdef DEBUG
	//std::cout << "Controls: WASD SPACE\n";
	//std::cout << "Press n to change lvl\n Press Enter to respawn when you'r dead.\n";
	//for (Object solidObj : lvlController->solidBounds->getBoundaries())
	//{
		//solidObj.sprite.setTextureRect(solidObj.rect);
		//solidObj.sprite.setColor(sf::Color::Red);
		//sf::RectangleShape wall;
		//wall.setSize({ float(solidObj.rect.width),float(solidObj.rect.height) });
		//wall.setPosition(solidObj.rect.left, solidObj.rect.top);
		//wall.setFillColor(sf::Color::Transparent);
		//wall.setOutlineColor(sf::Color::Magenta);
		//wall.setOutlineThickness(1.f);
		//walls.push_back(wall);
		
	//}
#endif // DEBUG

	

}

void Game::initView()
{
	//auto& pos = player->getComponent<MoveComponent>().position;
	//view = new sf::View(pos, sf::Vector2f(500.f, 350.f));
}


void Game::updatePlayer()
{
}

void Game::changeLevel()
{
	//lvlController->nextLevel();
	//Object* playerObj = lvlController->getObject("hero");
	//player->setPosition(playerObj->rect.left, playerObj->rect.top);
	//player->setHitBoxPos(playerObj->rect.left + player->getHitBoxOffsetX(), playerObj->rect.top + player->getHitBoxOffsetY());
	//active_enemies->clearActiveEnemies();
	//std::vector<Object> pigs_init_vec = lvlController->getObjects("enemy");
	//active_enemies->addEnemies(pigs_init_vec);
}

void Game::updateView()
{
	/*if (player->getHitBox().left >= view->getCenter().x + view->getSize().x / 2)
		view->setCenter(view->getCenter().x + view->getSize().x, player->getPosition().y);
	else if (player->getHitBox().left < view->getCenter().x - view->getSize().x / 2)
		view->setCenter(view->getCenter().x - view->getSize().x, player->getPosition().y);*/
	//auto& pos = player->getComponent<MoveComponent>();
	//view->setCenter(pos.position.x, view->getCenter().y);
	

	//if (player->getHitBox().top + player->getHitBox().height <= view->getCenter().y - view->getSize().y / 2)
		//view->setCenter(player->getPosition().x, view->getCenter().y - view->getSize().y);
//	else if (player->getHitBox().top + player->getHitBox().height >= view->getCenter().y + view->getSize().y / 2)
		//view->setCenter(player->getPosition().x, view->getCenter().y + view->getSize().y);
}

void Game::updateCollision()
{
	//lvlController->updateCollision(player, active_enemies);
}



void Game::playerAttacks()
{
	//for (Unit* pig : active_enemies->getActiveEnemies())
	//{
		//if (player->getAttackArea().getGlobalBounds().intersects(pig->getHitBox()))
		//{
			//player->attack(pig);
		//}
		//if (pig->getAttackArea().getGlobalBounds().intersects(player->getHitBox()))
		//{
			//pig->attack(player);
		//}
	//}
	
}

bool Game::update(float dt)
{
	inputSystem->update(dt);
	moveSystem->update(dt);
	physicsSystem->update(dt);
	//Polling window events
	while (this->window.pollEvent(this->ev))
	{
		if (this->ev.type == sf::Event::Closed)
			this->window.close();
		else if (this->ev.type == sf::Event::KeyReleased)// �����-�������
		{
			if (ev.key.code == sf::Keyboard::Space)
			{
			//	this->player->resetAttackLock();
			}
			else if (ev.key.code == sf::Keyboard::Enter)
			{
				//if (!player->isAlive())
				//{
					//delete player;
					//initPlayer();
				//}
			}
		}
			
	}
	
	
	
	//this->updatePlayer();
	////std::cout << player->getHitBox().top << "\t\t" << player->getPosition().y << std::endl;
	//this->playerAttacks();
	//this->updatePigs();
	//this->updateCollision();
	//this->lvlController->update();
	//this->active_enemies->removeDeadEnemies();
	//updateView();
//#ifdef DEBUG
	//plshape.setPosition(player->getPosition());
	//hitbox.setPosition(player->getHitBox().left, player->getHitBox().top);
	////pigshape.setPosition(Pigs_vec[0]->getHitBox().left, Pigs_vec[0]->getHitBox().top);
//#endif // DEBUG

	return true;
}

void Game::renderPlayer()
{
	//this->player->render(this->window);
}

void Game::renderPigs()
{
	//for (Unit* pig : active_enemies->getActiveEnemies())
	//{
		//pig->render(this->window);
	//}
}

void Game::updatePigs()
{
	//for (Unit* pig : active_enemies->getActiveEnemies())
	//{
		//pig->update();
	//}
}

bool Game::render(float dt)
{
	this->window.clear();
	animSystem->update(dt);
	animStateSystem->update(102);
	spriteSystem->update(0.f);
	window.display();
	//Render game
	
	//lvlController->renderCurrentLevel(this->window);
	//this->renderPlayer();
	//this->renderPigs();
	//#ifdef DEBUG
	//window.draw(plshape);
	//window.draw(hitbox);
	
	
	//window.draw(pigshape);
	//window.draw(player->getAttackArea());
	//#endif
	/*
	active_enemies->getActiveEnemies()[0]->getAttackArea().setFillColor(sf::Color::Red);
	window.draw(active_enemies->getActiveEnemies()[0]->getAttackArea());*/

	//for (sf::RectangleShape wall : walls)
	//{
		//window.draw(wall);
	//}
	//window.setView(*view);
	//this->window.display();
	return true;
}

const sf::RenderWindow& Game::getWindow() const
{
	
	return this->window;
}
