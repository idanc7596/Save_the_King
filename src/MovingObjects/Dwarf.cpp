#include "MovingObjects/Dwarf.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"

Dwarf::Dwarf(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	: MovingObject(texture, location, tileSize), m_initiatedCollision(false)
{
	m_speed = generateSpeed(); 
	m_direction = generateDirection();
}


float Dwarf::generateSpeed()
{
	return MIN_SPEED + rand() % int(MAX_SPEED - MIN_SPEED + 1);
}

//generate a direction that is different from the current direction.
sf::Vector2f Dwarf::generateDirection()
{
	sf::Vector2f direction = m_direction;
	int spriteSheetOffsetY = 0; //for animation

	do {
		int choice = rand() % NUM_OF_DIRECTIONS;
		switch (choice) {
		case 0:
			direction = DOWN;
			spriteSheetOffsetY = 0;
			break;
		case 1:
			direction = LEFT;
			spriteSheetOffsetY = 1;
			break;
		case 2:
			direction = RIGHT;
			spriteSheetOffsetY = 2;
			break;
		case 3:
			direction = UP;
			spriteSheetOffsetY = 3;
			break;
		default:
			break;
		}
	} while (direction == m_direction);

	m_spriteSheetOffset.y = spriteSheetOffsetY;
	return direction;

}

//when a dwarf collides he change his direction to the opposite direction.
void Dwarf::changeDirection()
{
	if (m_direction == DOWN) {
		m_spriteSheetOffset.y += 3;
	}
	else if (m_direction == LEFT) {
		m_spriteSheetOffset.y += 1;
	}
	else if (m_direction == RIGHT) {
		m_spriteSheetOffset.y -= 1;
	}
	else if (m_direction == UP) {
		m_spriteSheetOffset.y -= 3;
	}
	m_direction = -m_direction;
}

void Dwarf::move(sf::Time deltaTime)
{
	//generate new direction every time gap:
	if (m_clock.getElapsedTime().asSeconds() > TIME_GAP) {
		m_direction = generateDirection();
		m_clock.restart();
	}

	//for animation:
	m_spriteSheetOffset.x = (m_spriteSheetOffset.x + 1) % 3; 
	m_sprite.setTextureRect(sf::IntRect(m_spriteSheetOffset.x * SPRITE_DIMENSION,
		m_spriteSheetOffset.y * SPRITE_DIMENSION, SPRITE_DIMENSION, SPRITE_DIMENSION));

	//save previous location for use if dwarf has to go back:
	m_prevLoc = m_sprite.getPosition(); 
	m_sprite.move(m_direction * m_speed * deltaTime.asSeconds());
}

bool Dwarf::initiatedCollision() const
{
	return m_initiatedCollision;
}

void Dwarf::setAsInitiatedCollision(bool initiatedCollision)
{
	m_initiatedCollision = initiatedCollision;
}

void Dwarf::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}

void Dwarf::handleCollision(King& king)
{
	if (m_initiatedCollision) {
		changeDirection();
		goBack();
	}
	else { 
		king.handleCollision(*this);
	}
}

void Dwarf::handleCollision(Mage& mage)
{
	if (m_initiatedCollision) {
		changeDirection();
		goBack();
	}
	else {
		mage.handleCollision(*this);
	}
}

void Dwarf::handleCollision(Warrior& warrior)
{
	if (m_initiatedCollision) {
		changeDirection();
		goBack();
	}
	else {
		warrior.handleCollision(*this);
	}
}

void Dwarf::handleCollision(Thief& thief)
{
	if (m_initiatedCollision) {
		changeDirection();
		goBack();
	}
	else {
		thief.handleCollision(*this);
	}
}

void Dwarf::handleCollision(Dwarf& dwarf)
{
	if (&dwarf == this) {
		return;
	}
	if (m_initiatedCollision) {
		changeDirection();
		goBack();
	}
	else {
		dwarf.handleCollision(*this);
	}
}

void Dwarf::handleCollision(Fire& /*fire*/)
{
	changeDirection();
	goBack();
}

void Dwarf::handleCollision(Gate& /*gate*/)
{
	changeDirection();
	goBack();
}

void Dwarf::handleCollision(Gift& /*gift*/)
{
}

void Dwarf::handleCollision(Key& /*key*/)
{
	changeDirection();
	goBack();
}

void Dwarf::handleCollision(Orc& /*orc*/)
{
	changeDirection();
	goBack();
}

void Dwarf::handleCollision(Teleport& /*teleport*/)
{
	changeDirection();
	goBack();
}

void Dwarf::handleCollision(Throne& /*throne*/)
{
	changeDirection();
	goBack();
}

void Dwarf::handleCollision(Wall& /*wall*/)
{
	changeDirection();
	goBack();
}
