#pragma once
#include "MovingObjects/MovingObject.h"

const float FIGURE_SPEED = 150;

//class for representing the 4 main figures in the game:
//(king, mage, warrior, thief)
class Figure : public MovingObject {
public:
	Figure(const sf::Texture& texture, sf::Vector2f location, float tileSize);
	virtual ~Figure() = default;
	void move(sf::Time deltaTime) override;
	void setIsControlled(bool isControlled);
	bool isControlled() const;

	void handleCollision(King& king) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Thief& thief) override;
	void handleCollision(Wall& wall) override;


protected:
	bool m_isControlled;
};