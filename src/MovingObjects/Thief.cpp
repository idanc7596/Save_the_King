#include "MovingObjects/Thief.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Dwarf.h"
#include "StaticObjects/Key.h"
#include "StaticObjects/Gate.h"
#include "StaticObjects/Teleport.h"
#include "ResourcesManager.h"
#include <iostream>

Thief::Thief(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: Figure(texture, location, tileSize), m_holdsKey(false)
{
}

bool Thief::holdsKey() const
{
	return m_holdsKey;
}

void Thief::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Thief::handleCollision(Dwarf& dwarf)
{
	if (dwarf.initiatedCollision()) {
		dwarf.handleCollision(*this);
	}
	else {
		goBack();
	}
}

void Thief::handleCollision(Fire& /*fire*/)
{
	goBack();
}

void Thief::handleCollision(Gate& gate)
{
	if (gate.isDisposed()) {
		m_holdsKey = false; //because thief used his key to open this gate
		m_sprite.setTexture(ResourcesManager::instance().getTexture(THIEF_ID));
	}
	else { //thief didn't open the gate:
		goBack();
	}
}

void Thief::handleCollision(Key& key)
{
	if (key.isDisposed()) {
		m_holdsKey = true; //thief collected this key
		m_sprite.setTexture(ResourcesManager::instance().getTexture(THIEF_WITH_KEY_ID));
	}
}

void Thief::handleCollision(Orc& /*orc*/)
{
	goBack();
}

void Thief::handleCollision(Teleport& teleport)
{
	if (!teleport.getPartner()->blocked()) {
		ResourcesManager::instance().playSound(Sounds::teleport);
		m_sprite.setPosition(teleport.getPartner()->getLocation());
	}
}

void Thief::handleCollision(Throne& /*throne*/)
{
	goBack();
}