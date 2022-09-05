#include "InfoBar.h"
#include "ResourcesManager.h"
#include "macros.h"

InfoBar::InfoBar()
	:m_levelNumber(1), m_timer(NO_TIME_LIMIT)
{
	//design texts:
	m_levelNumText.setFont(ResourcesManager::instance().getFont(Fonts::levelNum));
	m_levelNumText.setCharacterSize(40);
	m_levelNumText.setFillColor(sf::Color::White);
	m_levelNumText.setPosition(13.f, 8.f);

	m_timerText.setFont(ResourcesManager::instance().getFont(Fonts::timer));
	m_timerText.setCharacterSize(50);
	m_timerText.setFillColor(sf::Color::Red);
	m_timerText.setString("00:00"); //for text width to be relevant
	m_timerText.setPosition(float(WINDOW_WIDTH-17.f-m_timerText.getGlobalBounds().width),
		0.f);

	//design pause button:
	m_pauseButton.setTexture(ResourcesManager::instance().getTexture(PAUSE_ID));
	m_pauseButton.setPosition(
		float(WINDOW_WIDTH - 40.f - 
			m_timerText.getGlobalBounds().width-m_pauseButton.getGlobalBounds().width),
		20.f);
}

void InfoBar::setLevelNumber(int levelNumber)
{
	m_levelNumber = levelNumber;
	m_levelNumText.setString("Level " + std::to_string(m_levelNumber));
}

void InfoBar::setTimer(int timer)
{
	m_timer = timer;
	//print the timer in this format: mm:ss
	m_timerText.setString((m_timer/60 < 10 ? "0" : "") + std::to_string(m_timer/60) +
		":" + (m_timer%60 < 10 ? "0" : "") + std::to_string(m_timer%60));
}

void InfoBar::draw(sf::RenderWindow& window) const
{
	window.draw(m_levelNumText);
	window.draw(m_timerText);
	window.draw(m_pauseButton);
}

//to inform the controller if pause button was pressed:
bool InfoBar::isPauseButtonPress(sf::Vector2f clickPosition)
{
	return m_pauseButton.getGlobalBounds().contains(clickPosition);
}

//change the textures of the pause button according to the current 
//play mode (pause/play):
void InfoBar::updatePauseButtonTexture(bool playMode)
{
	if (playMode == true) {
		m_pauseButton.setTexture(ResourcesManager::instance().getTexture(PAUSE_ID));
	}
	else {
		m_pauseButton.setTexture(ResourcesManager::instance().getTexture(PLAY_ID));
	}
}
