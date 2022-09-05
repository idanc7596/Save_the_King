#pragma once
#include <SFML/Graphics.hpp>

class InfoBar {
public:
	InfoBar();
	void setLevelNumber(int levelNumber);
	void setTimer(int timer);
	void draw(sf::RenderWindow& window) const;
	bool isPauseButtonPress(sf::Vector2f clickPosition);
	void updatePauseButtonTexture(bool playMode);

private:
	sf::Text m_timerText;
	sf::Text m_levelNumText;
	int m_levelNumber; 
	int m_timer;

	sf::Sprite m_pauseButton;
};