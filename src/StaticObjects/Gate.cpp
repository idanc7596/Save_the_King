#include "StaticObjects/Gate.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

Gate::Gate(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize)
{
}

void Gate::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Gate::handleCollision(King& king)
{
	king.handleCollision(*this);
}

void Gate::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

void Gate::handleCollision(Warrior& warrior)
{	
	warrior.handleCollision(*this);
}

void Gate::handleCollision(Thief& thief)
{
	//if thief has a key he opens the gate:
	if (thief.holdsKey()) {
		ResourcesManager::instance().playSound(Sounds::gate);
		m_isDisposed = true;
		thief.handleCollision(*this);
	}
	else {
		thief.handleCollision(*this);
	}
}

void Gate::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}