#include "StaticObjects/Gift.h"
#include "ResourcesManager.h"

Gift::Gift(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:StaticObject(texture, location, tileSize), m_isActive(false)
{
	m_sprite.scale(0.8f, 0.8f); //design
}

bool Gift::isActive() const
{
	return m_isActive;
}

void Gift::handleCollision(King& /*king*/)
{
	//the king collected the gift:
	ResourcesManager::instance().playSound(Sounds::gift);
	m_isActive = true;
	m_isDisposed = true;
}

void Gift::handleCollision(Mage& /*mage*/)
{
	ResourcesManager::instance().playSound(Sounds::gift);
	m_isActive = true;
	m_isDisposed = true;
}

void Gift::handleCollision(Warrior& /*warrior*/)
{
	ResourcesManager::instance().playSound(Sounds::gift);
	m_isActive = true;
	m_isDisposed = true;
}

void Gift::handleCollision(Thief& /*thief*/)
{
	ResourcesManager::instance().playSound(Sounds::gift);
	m_isActive = true;
	m_isDisposed = true;
}

void Gift::handleCollision(Dwarf& /*dwarf*/)
{
	//dwarf cannot collect a gift, but he can step on it
}
