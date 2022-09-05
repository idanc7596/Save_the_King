#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"
#include "StaticObjects/Teleport.h"

King::King(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: Figure(texture, location, tileSize), m_reachedThrone(false)
{
}

bool King::isReachedThrone() const
{
	return m_reachedThrone;
}

void King::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void King::handleCollision(Dwarf& dwarf)
{
	//if dwarf initiated collision, he has to go back:
	if (dwarf.initiatedCollision()) {
		dwarf.handleCollision(*this);
	}
	else { 
		goBack();
	}
}

void King::handleCollision(Fire& /*fire*/)
{
	goBack();
}


void King::handleCollision(Gate& /*gate*/)
{
	goBack();
}

void King::handleCollision(Key& /*key*/)
{
}

void King::handleCollision(Orc& /*orc*/)
{
	goBack();
}

void King::handleCollision(Teleport& teleport)
{
	if (!teleport.getPartner()->blocked()) {
		ResourcesManager::instance().playSound(Sounds::teleport);
		m_sprite.setPosition(teleport.getPartner()->getLocation());
	}
}

void King::handleCollision(Throne& /*throne*/)
{
	m_reachedThrone = true;
}