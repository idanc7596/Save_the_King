#include "StaticObjects/StaticObject.h"

StaticObject::StaticObject(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:GameObject(texture, location, tileSize), m_isDisposed(false)
{
}

bool StaticObject::isDisposed() const
{
	return m_isDisposed;
}