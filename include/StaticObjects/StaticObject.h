#pragma once
#include "GameObject.h"

class StaticObject : public GameObject {
public:
	StaticObject(const sf::Texture& texture, sf::Vector2f location, float tileSize);
	virtual ~StaticObject() = default;

	bool isDisposed() const;

protected:
	bool m_isDisposed; //mark a static object as one that has to be disposed
};