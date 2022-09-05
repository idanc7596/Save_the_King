#include "StaticObjects/Wall.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

Wall::Wall(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize)
{
}

void Wall::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Wall::handleCollision(King& king)
{
	king.handleCollision(*this);
}

void Wall::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

void Wall::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}

void Wall::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

void Wall::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}