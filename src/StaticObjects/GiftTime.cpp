#include "StaticObjects/GiftTime.h"
#include "Controller.h"

GiftTime::GiftTime(const sf::Texture& texture, sf::Vector2f location, float tileSize,
	bool isIncrease) //get a boolean means increase/decrease
	:Gift(texture, location, tileSize)
{
	//generate a random amount of time to increase/decrease
	//(between the range specified:
	m_amount = MIN_AMOUNT + rand() % (MAX_AMOUNT - MIN_AMOUNT + 1);
	if (!isIncrease) { //make the amount negative, if we want to decrease
		m_amount = -m_amount;
	}
}

//activate the gift (tell the controller to increase/decrease its timer):
void GiftTime::activate(Controller& controller)
{
	controller.adjustTimer(m_amount);
}

void GiftTime::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}