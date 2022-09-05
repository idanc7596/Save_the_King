#include "MovingObjects/Figure.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"


Figure::Figure(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: MovingObject(texture, location, tileSize), 
	m_isControlled(false)
{
	m_speed = FIGURE_SPEED;
	m_sprite.setColor(sf::Color(255, 255, 255, 130)); //opacity for uncontrolled figures
}

void Figure::move(sf::Time deltaTime)
{	
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_direction = DOWN;
		//for animation:
		m_spriteSheetOffset.x = (m_spriteSheetOffset.x + 1) % 3;
		m_spriteSheetOffset.y = 0;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_direction = LEFT;
		m_spriteSheetOffset.x = (m_spriteSheetOffset.x + 1) % 3;
		m_spriteSheetOffset.y = 1;
	} 
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_direction = RIGHT;
		m_spriteSheetOffset.x = (m_spriteSheetOffset.x + 1) % 3;
		m_spriteSheetOffset.y = 2;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_direction = UP;
		m_spriteSheetOffset.x = (m_spriteSheetOffset.x + 1) % 3;
		m_spriteSheetOffset.y = 3;
	} 
	else {
		m_direction = STAY;
	}

	//for animation:
	m_sprite.setTextureRect(sf::IntRect(m_spriteSheetOffset.x* SPRITE_DIMENSION,
		m_spriteSheetOffset.y* SPRITE_DIMENSION, SPRITE_DIMENSION, SPRITE_DIMENSION));

	m_prevLoc = m_sprite.getPosition();
	m_sprite.move(m_speed * m_direction * deltaTime.asSeconds());
}

void Figure::setIsControlled(bool isControlled)
{
	m_isControlled = isControlled;
	if (isControlled) {
		//full opacity for controlled figure:
		m_sprite.setColor(sf::Color(255, 255, 255, 255)); 
	}
	else {
		m_sprite.setColor(sf::Color(255, 255, 255, 130));
	}
}

bool Figure::isControlled() const
{
	return m_isControlled;
}

void Figure::handleCollision(King& king)
{
	if (m_isControlled) {
		goBack();
	}
	else {
		king.goBack();
	}
}

void Figure::handleCollision(Mage& mage)
{
	if (m_isControlled) {
		goBack();
	}
	else {
		mage.goBack();
	}
}

void Figure::handleCollision(Warrior& warrior)
{
	if (m_isControlled) {
		goBack();
	}
	else {
		warrior.goBack();
	}
}

void Figure::handleCollision(Thief& thief)
{
	if (m_isControlled) {
		goBack();
	}
	else {
		thief.goBack();
	}
}

void Figure::handleCollision(Wall& /*wall*/)
{
	goBack();
}