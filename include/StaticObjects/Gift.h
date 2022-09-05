#pragma once
#include "StaticObjects/StaticObject.h"
class Controller;

class Gift : public StaticObject {
public:
	Gift(const sf::Texture& texture, sf::Vector2f location, float tileSize);
	bool isActive() const;

	virtual void activate(Controller& controller) = 0;

	void handleCollision(King& king) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Thief& thief) override;
	void handleCollision(Dwarf& dwarf) override;


protected:
	//if one of the figures collected the gift, the gift is marked as activated:
	bool m_isActive; 
};