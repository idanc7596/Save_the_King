#pragma once
#include "GameObject.h"

const sf::Vector2f UP(0, -1), DOWN(0, 1), LEFT(-1, 0), RIGHT(1, 0), STAY(0, 0);
const int SPRITE_DIMENSION = 32; //a size of a single square in the sprite sheet

class MovingObject : public GameObject {
public:
	MovingObject(const sf::Texture& texture, sf::Vector2f location, float tileSize);
	virtual ~MovingObject() = default;

	virtual void move(sf::Time deltaTime) = 0;
	void goBack();

	using GameObject::handleCollision;
	virtual void handleCollision(Fire& fire) = 0;
	virtual void handleCollision(Gate& gate) = 0;
	virtual void handleCollision(Key& key) = 0;
	virtual void handleCollision(Orc& orc) = 0;
	virtual void handleCollision(Teleport& teleport) = 0;
	virtual void handleCollision(Throne& throne) = 0;
	virtual void handleCollision(Wall& wall) = 0;

protected:
	float m_speed;
	sf::Vector2f m_direction;
	sf::Vector2f m_prevLoc; //the previos location of moving object, before it moved
	sf::Vector2i m_spriteSheetOffset; //know what square in sprite sheet to draw
};