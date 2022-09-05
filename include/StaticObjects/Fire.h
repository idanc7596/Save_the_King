#pragma once
#include "StaticObjects/StaticObject.h"

class Fire : public StaticObject {
public:
	Fire(const sf::Texture& texture, sf::Vector2f location, float tileSize);

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(King& king) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Thief& thief) override;
	void handleCollision(Dwarf& dwarf) override;

private:
};