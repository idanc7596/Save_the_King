#include "StaticObjects/GiftDwarfs.h"
#include "Controller.h"

GiftDwarfs::GiftDwarfs(const sf::Texture& texture, sf::Vector2f location, float tileSize)
	:Gift(texture, location, tileSize)
{
}

//activate the gift (tell controller to erase the dwarfs):
void GiftDwarfs::activate(Controller& controller)
{
	controller.eraseDwarfs();
}

void GiftDwarfs::handleCollision(GameObject& gameObject)
{
	gameObject.handleCollision(*this);
}