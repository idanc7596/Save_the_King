#include "StaticObjects/Fire.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

Fire::Fire(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize)
{
	m_sprite.scale(0.8f, 0.8f); //design
}

void Fire::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Fire::handleCollision(King& king)
{
	king.handleCollision(*this);
}

void Fire::handleCollision(Mage& /*mage*/)
{
	//fire disposed by the mage:
	ResourcesManager::instance().playSound(Sounds::mage);
	m_isDisposed = true;
}

void Fire::handleCollision(Warrior& warrior)
{
	warrior.handleCollision(*this);
}

void Fire::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

void Fire::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}