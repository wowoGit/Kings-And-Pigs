#include "Game.h"
#include <iostream>
#include <random>
#define DEBUG 
void Game::initWindow()
{
	//this->window.setKeyRepeatEnabled(false);
	
}

void Game::initPlayer()
{
	player = std::make_unique<Entity>(Scene::Reg().create(), this);
	auto& texture = TextureLoader::loadFromFile("Sprites/king/Idle.png", "IDLE");
	auto& texture1 = TextureLoader::loadFromFile("Sprites/king/Run.png", "RUN_RIGHT");
	sf::IntRect rect(0,0,78,58);
	sf::Sprite sprite(texture,rect);
	std::map<std::string,sf::IntRect> animation_pool {{"IDLE", rect},{"RUN_RIGHT", rect}};

	player->AddComponent<MoveComponent>(sf::Vector2f(100,100), sf::Vector2f());
	player->AddComponent<SpriteComponent>(sprite,true);
	player->AddComponent<AnimationComponent>(.1f,rect,false);
	player->AddComponent<StateComponent>("IDLE");
	player->AddComponent<AnimationPool>(animation_pool,"IDLE");

	spriteSystem = std::make_unique<SpriteRendererSystem>(this);
	animStateSystem = std::make_unique<AnimationStateSystem>(this);
	animSystem = std::make_unique<AnimationSystem>(this);
	
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
			else if (ev.key.code == sf::Keyboard::N)
			{
				auto& state = player->getComponent<StateComponent>();
				state.state = "IDLE";
			}
			else if (ev.key.code == sf::Keyboard::M)
			{
				auto& state = player->getComponent<StateComponent>();
				state.state = "RUN_RIGHT";
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
