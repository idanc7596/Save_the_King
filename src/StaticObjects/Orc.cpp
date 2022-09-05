#include "StaticObjects/Orc.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

Orc::Orc(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize), m_replaceWithKey(false)
{
}

bool Orc::replaceWithKey() const
{
	return m_replaceWithKey;
}

void Orc::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Orc::handleCollision(King& king)
{
	king.handleCollision(*this);
}

void Orc::handleCollision(Mage& mage)
{
	mage.handleCollision(*this);
}

void Orc::handleCollision(Warrior& /*warrior*/)
{
	//warrior killed the orc:
	ResourcesManager::instance().playSound(Sounds::sword);
	m_isDisposed = true;
	m_replaceWithKey = true; 
}

void Orc::handleCollision(Thief& thief)
{
	thief.handleCollision(*this);
}

void Orc::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}