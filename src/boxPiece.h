#pragma once
#include "Item.h"

class BoxPiece : public Item
{
public:
	BoxPiece(const float x, const float y, std::string boxPiece);
	void initAnimations() override;
	void interact(Unit* player) override;
	void update() override;
	void updatePhysics();
	void move(const float x, const float y);
	void getHitWith(int _dmg) override;
	void render(sf::RenderTarget& render) override;
private:
	std::string pieceNumber;
	float acceleration;
	float gravity;
	float resistance;
	float initYpos;
	sf::Vector2f velocity;
};