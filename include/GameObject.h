#pragma once
#include <SFML/Graphics.hpp>

class King;
class Mage;
class Warrior;
class Thief;
class Dwarf;
class Fire;
class Gate;
class Key;
class Orc;
class Teleport;
class Throne;
class Wall;
class Gift;
class GiftDwarfs;
class GiftTime;
#include "ResourcesManager.h"


class GameObject {
public:
	GameObject(const sf::Texture& texture, sf::Vector2f location, float tileSize);
	virtual ~GameObject() = default;

	void draw(sf::RenderWindow& window) const;
	sf::Vector2f getLocation() const;
	bool collidesWith(const GameObject& other) const;

	virtual void handleCollision(GameObject& gameObject) = 0;
	virtual void handleCollision(King& king) = 0;
	virtual void handleCollision(Mage& mage) = 0;
	virtual void handleCollision(Warrior& warrior) = 0;
	virtual void handleCollision(Thief& thief) = 0;
	virtual void handleCollision(Dwarf& dwarf) = 0;

protected:
	sf::Sprite m_sprite;
	sf::Vector2f m_location;

};