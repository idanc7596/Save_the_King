#include "GameObject.h"
#include <iostream>

GameObject::GameObject(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: m_location(location)
{
	m_sprite.setPosition(location);
	m_sprite.setTexture(texture);
	//adjust the sprite size to the tile size:
	sf::Vector2f scaleFactors = sf::Vector2f(float(tileSize) / m_sprite.getGlobalBounds().width,
		float(tileSize) / m_sprite.getGlobalBounds().height);
	m_sprite.setScale(scaleFactors);
	
}

void GameObject::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::Vector2f GameObject::getLocation() const
{
	return m_sprite.getPosition();
}

bool GameObject::collidesWith(const GameObject& other) const 
{
	//self collision is not interesting:
	if (&other == this) {
		return false;
	}
	return m_sprite.getGlobalBounds().intersects(other.m_sprite.getGlobalBounds());
}