#include "Game.h"
#include <iostream>
#include <random>
#define DEBUG 
void Game::initWindow()
{
	this->window.create(sf::VideoMode(800, 600), "Game 4", sf::Style::Close | sf::Style::Titlebar);
	this->window.setFramerateLimit(60);
	//this->window.setKeyRepeatEnabled(false);
	
}

void Game::initPlayer()
{
	Object* pl = lvlController->getObject("hero");
	this->player = new Player(pl->rect.left, pl->rect.top);
	//player->setPosition(playerObj.rect.left, playerObj.rect.top);
#ifdef DEBUG
	plshape.setSize({ player->getGlobalBounds().width,player->getGlobalBounds().height });
	plshape.setFillColor(sf::Color::Transparent);
	plshape.setOutlineThickness(1.f);
	hitbox.setSize({ player->getHitBox().width,player->getHitBox().height });
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setOutlineThickness(1.f);
#endif // 

	
}

void Game::initPigs()
{
	//active_enemies = new ActiveEnemies();
	std::vector<Object> pigs_init_vec = lvlController->getObjects("enemy");
	for (Object pig : pigs_init_vec)
	{
		Pigs_vec.push_back(new Pig(pig.rect.left, pig.rect.top));
	}
	pigshape.setSize({ Pigs_vec[0]->getHitBox().width,Pigs_vec[0]->getHitBox().height });
	pigshape.setFillColor(sf::Color::Transparent);
	pigshape.setOutlineColor(sf::Color::Green);
	pigshape.setOutlineThickness(1.f);
	active_enemies = new ActiveEnemies();
	active_enemies->addEnemies(Pigs_vec);

}

void Game::initLevel()
{
	/*this->lvl = new Level;
	lvl->LoadFromFile("maps/jumpking.tmx");*/
	//invisObjects = lvl->GetObjects("invis_walls");
	lvlController = new LevelController();
#ifdef DEBUG
	std::cout << "Controls: WASD SPACE\n";
	std::cout << "Press n to change lvl\n Press Enter to respawn when you'r dead.\n";
	for (Object solidObj : lvlController->solidBounds->getBoundaries())
	{
		solidObj.sprite.setTextureRect(solidObj.rect);
		solidObj.sprite.setColor(sf::Color::Red);
		sf::RectangleShape wall;
		wall.setSize({ float(solidObj.rect.width),float(solidObj.rect.height) });
		wall.setPosition(solidObj.rect.left, solidObj.rect.top);
		wall.setFillColor(sf::Color::Transparent);
		wall.setOutlineColor(sf::Color::Magenta);
		wall.setOutlineThickness(1.f);
		walls.push_back(wall);
		
	}
#endif // DEBUG

	

}

void Game::initView()
{
	view = new sf::View(player->getPosition(), sf::Vector2f(500.f, 350.f));
}

Game::Game()
{
	this->initWindow();
	this->initLevel();
	this->initPlayer();
	this->initPigs();
	
	
	this->initView();
	srand(time(NULL));
}

Game::~Game()
{
	delete this->player;
}

void Game::updatePlayer()
{
	this->player->update();
}

void Game::changeLevel()
{
	lvlController->nextLevel();
	Object* playerObj = lvlController->getObject("hero");
	player->setPosition(playerObj->rect.left, playerObj->rect.top);
	player->setHitBoxPos(playerObj->rect.left + player->getHitBoxOffsetX(), playerObj->rect.top + player->getHitBoxOffsetY());
	active_enemies->clearActiveEnemies();
	std::vector<Object> pigs_init_vec = lvlController->getObjects("enemy");
	active_enemies->addEnemies(pigs_init_vec);
}

void Game::updateView()
{
	/*if (player->getHitBox().left >= view->getCenter().x + view->getSize().x / 2)
		view->setCenter(view->getCenter().x + view->getSize().x, player->getPosition().y);
	else if (player->getHitBox().left < view->getCenter().x - view->getSize().x / 2)
		view->setCenter(view->getCenter().x - view->getSize().x, player->getPosition().y);*/

	view->setCenter(player->getPosition().x, view->getCenter().y);

	if (player->getHitBox().top + player->getHitBox().height <= view->getCenter().y - view->getSize().y / 2)
		view->setCenter(player->getPosition().x, view->getCenter().y - view->getSize().y);
	else if (player->getHitBox().top + player->getHitBox().height >= view->getCenter().y + view->getSize().y / 2)
		view->setCenter(player->getPosition().x, view->getCenter().y + view->getSize().y);
}

void Game::updateCollision()
{
	lvlController->updateCollision(player, active_enemies);
}



void Game::playerAttacks()
{
	for (Unit* pig : active_enemies->getActiveEnemies())
	{
		if (player->getAttackArea().getGlobalBounds().intersects(pig->getHitBox()))
		{
			player->attack(pig);
		}
		if (pig->getAttackArea().getGlobalBounds().intersects(player->getHitBox()))
		{
			pig->attack(player);
		}
	}
	
}

void Game::update()
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
				this->player->resetAttackLock();
			}
			else if (ev.key.code == sf::Keyboard::Enter)
			{
				if (!player->isAlive())
				{
					delete player;
					initPlayer();
				}
			}
			else if (ev.key.code == sf::Keyboard::N)
			{
				changeLevel();
			}
				
		}
			
	}
	
	
	
	this->updatePlayer();
	//std::cout << player->getHitBox().top << "\t\t" << player->getPosition().y << std::endl;
	this->playerAttacks();
	this->updatePigs();
	this->updateCollision();
	this->lvlController->update();
	this->active_enemies->removeDeadEnemies();
	updateView();
#ifdef DEBUG
	plshape.setPosition(player->getPosition());
	hitbox.setPosition(player->getHitBox().left, player->getHitBox().top);
	//pigshape.setPosition(Pigs_vec[0]->getHitBox().left, Pigs_vec[0]->getHitBox().top);
#endif // DEBUG

	
}

void Game::renderPlayer()
{
	this->player->render(this->window);
}

void Game::renderPigs()
{
	for (Unit* pig : active_enemies->getActiveEnemies())
	{
		pig->render(this->window);
	}
}

void Game::updatePigs()
{
	for (Unit* pig : active_enemies->getActiveEnemies())
	{
		pig->update();
	}
}

void Game::render()
{
	this->window.clear();

	//Render game
	
	lvlController->renderCurrentLevel(this->window);
	this->renderPlayer();
	this->renderPigs();
	#ifdef DEBUG
	window.draw(plshape);
	window.draw(hitbox);
	
	
	window.draw(pigshape);
	window.draw(player->getAttackArea());
	#endif
	/*
	active_enemies->getActiveEnemies()[0]->getAttackArea().setFillColor(sf::Color::Red);
	window.draw(active_enemies->getActiveEnemies()[0]->getAttackArea());*/

	for (sf::RectangleShape wall : walls)
	{
		window.draw(wall);
	}
	window.setView(*view);
	this->window.display();
}

const sf::RenderWindow& Game::getWindow() const
{
	
	return this->window;
}
