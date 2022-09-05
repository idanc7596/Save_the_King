#pragma once
#include "MovingObjects/Figure.h"

class Thief : public Figure {
public:
	Thief(const sf::Texture& texture, sf::Vector2f location, float tileSize);

	bool holdsKey() const;

	using Figure::handleCollision;
	void handleCollision(GameObject& gameObject) override;
	void handleCollision(Dwarf& dwarf) override;
	void handleCollision(Fire& fire) override;
	void handleCollision(Gate& gate) override;
	void handleCollision(Key& key) override;
	void handleCollision(Orc& orc) override;
	void handleCollision(Teleport& teleport) override;
	void handleCollision(Throne& throne) override;

private:
	bool m_holdsKey;
};