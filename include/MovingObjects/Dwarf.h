#pragma once
#include "MovingObjects/MovingObject.h"

const float MIN_SPEED = 40;
const float MAX_SPEED = 110;
const float TIME_GAP = 5; //change direction every time gap
const int NUM_OF_DIRECTIONS = 4;

class Dwarf : public MovingObject {
public:
	Dwarf(const sf::Texture& texture, sf::Vector2f location, float tileSize);
	void move(sf::Time deltaTime) override;
	bool initiatedCollision() const;
	void setAsInitiatedCollision(bool initiatedCollision);

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(King& king) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Thief& thief) override;
	void handleCollision(Dwarf& dwarf) override;
	void handleCollision(Fire& fire) override;
	void handleCollision(Gate& gate) override;
	void handleCollision(Gift& gift);
	void handleCollision(Key& key) override;
	void handleCollision(Orc& orc) override;
	void handleCollision(Teleport& teleport) override;
	void handleCollision(Throne& throne) override;
	void handleCollision(Wall& wall) override;

private:
	float generateSpeed();
	sf::Vector2f generateDirection();
	void changeDirection();

	sf::Clock m_clock; //for direction change
	bool m_initiatedCollision; //if dwarf initiated collision he has to go back

};