#pragma once
#include "Item.h"
#include "SolidBoundaries.h"
#include "boxPiece.h"
class Box : public Item
{
public:
	Box(const float x, const float y);
	void initAnimations() override;
	void interact(Unit* player) override;
	void update() override;
	void getHitWith(int _dmg) override;
	virtual void render(sf::RenderTarget& render) override;
private:
	enum STATE{SOLID,HIT, SHATTERED};
	std::vector<BoxPiece*> shatteredBox;
	SolidBoundaries* solidBox;
	STATE boxState;
};