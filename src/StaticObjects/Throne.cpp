#include "StaticObjects/Throne.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

Throne::Throne(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize)
{
}

void Throne::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Throne::handleCollision(King& king)
{
	//king reached throne:
	ResourcesManager::instance().playSound(Sounds::throne);
	king.handleCollision(*this);
}

void Throne::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

void Throne::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}

void Throne::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

void Throne::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}