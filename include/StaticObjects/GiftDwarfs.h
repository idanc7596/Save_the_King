#pragma once
#include "StaticObjects/Gift.h"
class Controller;

class GiftDwarfs : public Gift {
public:
	GiftDwarfs(const sf::Texture& texture, sf::Vector2f location, float tileSize);

	void activate(Controller& controller) override;

	using Gift::handleCollision;
	void handleCollision(GameObject& gameObject) override;

private:

};