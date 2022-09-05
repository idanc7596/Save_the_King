#include "StaticObjects/Teleport.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"
#include "ResourcesManager.h"
#include <iostream>

Teleport::Teleport(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize), m_blocked(false), m_partner(nullptr)
{
}

bool Teleport::blocked() const
{
	return m_blocked;
}

//when a figure steps on teleport it is marked as blocked to avoid loops in 
//transitions between teleports, and to avoid another figure to enter a
//teleport while the teleport or its counterpart are blocked by another figure:
void Teleport::setBlocked(bool blocked)
{
	m_blocked = blocked;
}

void Teleport::setPartner(Teleport* partner)
{
	m_partner = partner;
}

Teleport* Teleport::getPartner() const
{
	return m_partner;
}

void Teleport::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Teleport::handleCollision(King& king)
{
	m_blocked = true;
	king.handleCollision(*this);
}

void Teleport::handleCollision(Mage& /*mage*/)
{
	m_blocked = true;
}

void Teleport::handleCollision(Warrior& warrior)
{
	m_blocked = true;
	warrior.handleCollision(*this);
}

void Teleport::handleCollision(Thief& thief)
{
	m_blocked = true;
	thief.handleCollision(*this);
}

void Teleport::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}