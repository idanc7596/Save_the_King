#include "MovingObjects/Warrior.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"
#include "StaticObjects/Orc.h"
#include "StaticObjects/Teleport.h"

Warrior::Warrior(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: Figure(texture, location, tileSize)
{
}

void Warrior::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Warrior::handleCollision(Dwarf& dwarf)
{
	if (dwarf.initiatedCollision()) {
		dwarf.handleCollision(*this);
	}
	else {
		goBack();
	}
}

void Warrior::handleCollision(Fire& /*fire*/)
{
	goBack();
}

void Warrior::handleCollision(Gate& /*gate*/)
{
	goBack();
}

void Warrior::handleCollision(Key& /*key*/)
{
}

void Warrior::handleCollision(Orc& /*orc*/)
{
}

void Warrior::handleCollision(Teleport& teleport)
{
	if (!teleport.getPartner()->blocked()) {
		ResourcesManager::instance().playSound(Sounds::teleport);
		m_sprite.setPosition(teleport.getPartner()->getLocation());
	}
}

void Warrior::handleCollision(Throne& /*throne*/)
{
	goBack();
}