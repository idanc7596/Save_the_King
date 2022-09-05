#pragma once
#include "StaticObjects/Gift.h"
class Controller;

//range of time amount that increased/decresed:
const int MIN_AMOUNT = 10;
const int MAX_AMOUNT = 30;

class GiftTime : public Gift {
public:
	GiftTime(const sf::Texture& texture, sf::Vector2f location, float tileSize, 
		bool isIncrease);

	void activate(Controller& controller) override;
	
	using Gift::handleCollision;
	void handleCollision(GameObject& gameObject) override;

private:
	int m_amount; //time to increase/decrease

};