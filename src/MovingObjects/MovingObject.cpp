#include "MovingObjects/MovingObject.h"

MovingObject::MovingObject(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: GameObject(texture, location, tileSize), 
	m_speed(0), 
	m_direction(STAY), 
	m_prevLoc(location),
	m_spriteSheetOffset(0, 0)
{
	m_sprite.scale(3, 4); //so every square in the sprite sheet will be in the tile size
	//for animation:
	m_sprite.setTextureRect(sf::IntRect(0, 0, SPRITE_DIMENSION, SPRITE_DIMENSION));
	m_sprite.scale(sf::Vector2f(0.8f, 0.8f)); 
}

//return the moving object to its previous location:
void MovingObject::goBack()
{
	m_sprite.setPosition(m_prevLoc);
}