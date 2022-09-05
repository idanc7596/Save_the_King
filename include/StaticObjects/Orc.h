#pragma once
#include "StaticObjects/StaticObject.h"


class Orc : public StaticObject {
public:
	Orc(const sf::Texture& texture, sf::Vector2f location, float tileSize);

	bool replaceWithKey() const;

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(King& king) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Thief& thief) override;
	void handleCollision(Dwarf& dwarf) override;

private:
	//tell if warrior killed the orc and it has to be replaced with key:
	bool m_replaceWithKey; 
};