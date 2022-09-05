#include "MovingObjects/Mage.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"
#include "StaticObjects/Fire.h"

Mage::Mage(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: Figure(texture, location, tileSize)
{
}

void Mage::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Mage::handleCollision(Dwarf& dwarf)
{
	if (dwarf.initiatedCollision()) {
		dwarf.handleCollision(*this);
	}
	else {
		goBack();
	}
}

void Mage::handleCollision(Fire& /*fire*/)
{
}

void Mage::handleCollision(Gate& /*gate*/)
{
	goBack();
}

void Mage::handleCollision(Key& /*key*/)
{
}

void Mage::handleCollision(Orc& /*orc*/)
{
	goBack();
}

void Mage::handleCollision(Teleport& /*teleport*/)
{
}

void Mage::handleCollision(Throne& /*throne*/)
{
	goBack();
}