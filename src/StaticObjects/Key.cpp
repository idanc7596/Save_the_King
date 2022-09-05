#include "StaticObjects/Key.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

Key::Key(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize)
{
	m_sprite.scale(0.8f, 0.8f); //design
}

void Key::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Key::handleCollision(King& /*king*/)
{
}

void Key::handleCollision(Mage& /*mage*/)
{
}

void Key::handleCollision(Warrior& /*warrior*/)
{
}

void Key::handleCollision(Thief& thief)
{
	//a thief cannot collect another key if he always has one:
	if (thief.holdsKey()) { 
		//ignore
	}
	else {
		ResourcesManager::instance().playSound(Sounds::key);
		m_isDisposed = true;
		thief.handleCollision(*this);
	}
}

void Key::handleCollision(Dwarf& dwarf)
{
	dwarf.handleCollision(*this);
}