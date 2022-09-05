#pragma once
#include <memory>
#include "StaticObjects/StaticObject.h"

class Teleport : public StaticObject {
public:
	Teleport(const sf::Texture& texture, sf::Vector2f location, float tileSize);

	bool blocked() const;
	void setBlocked(bool blocked);
	void setPartner(Teleport *partner);
	Teleport* getPartner() const;

	void handleCollision(GameObject& gameObject) override;
	void handleCollision(King& king) override;
	void handleCollision(Mage& mage) override;
	void handleCollision(Warrior& warrior) override;
	void handleCollision(Thief& thief) override;
	void handleCollision(Dwarf& dwarf) override;

private:
	bool m_blocked; //to mark if teleport is blocked
	Teleport* m_partner; //the partner of this teleport

};