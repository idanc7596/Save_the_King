#pragma once
#include "MovingObjects/Figure.h"

class Mage : public Figure {
public:
	Mage(const sf::Texture& texture, sf::Vector2f location, float tileSize);

	using Figure::handleCollision;
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Dwarf& dwarf) override;
	void handleCollision(Fire& fire) override;
	void handleCollision(Gate& gate) override;
	void handleCollision(Key& key) override;
	void handleCollision(Orc& orc) override;
	void handleCollision(Teleport& teleport) override;
	void handleCollision(Throne& throne) override;

private:

};