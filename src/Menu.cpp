#include "Menu.h"
#include "ResourcesManager.h"
#include "macros.h"

Menu::Menu(sf::RenderWindow& window) 
	: m_window(window),
	m_clickPosition(sf::Vector2f(0, 0)),
	m_hoverPosition(sf::Vector2f(0, 0)),
	m_instructionsMode(false)
{
	m_background.setTexture(ResourcesManager::instance().getTexture(MENU_BACKGROUND_ID));
	m_instructionsImage.setTexture(
		ResourcesManager::instance().getTexture(INSTRUCTIONS_IMAGE_ID));
	initButtons();
}

void Menu::initButtons()
{
	m_newGameButton.setTexture(ResourcesManager::instance().getTexture(NEW_GAME_BUTTON_ID));
	m_newGameButton.setOrigin(sf::Vector2f(m_newGameButton.getTexture()->getSize() / 2u));
	m_newGameButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f));

	m_instructionsButton.setTexture(ResourcesManager::instance().getTexture(INSTRUCTIONS_BUTTON_ID));
	m_instructionsButton.setOrigin(sf::Vector2f(m_instructionsButton.getTexture()->getSize() / 2u));
	m_instructionsButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f,
		WINDOW_HEIGHT / 2.f + m_newGameButton.getGlobalBounds().height + 20.f));

	m_exitButton.setTexture(ResourcesManager::instance().getTexture(EXIT_BUTTON_ID));
	m_exitButton.setOrigin(sf::Vector2f(m_exitButton.getTexture()->getSize() / 2u));
	m_exitButton.setPosition(sf::Vector2f(WINDOW_WIDTH / 2.f,
		WINDOW_HEIGHT / 2.f + 2 * (m_newGameButton.getGlobalBounds().height + 20.f)));

	m_instructionsBackButton.setTexture(ResourcesManager::instance().getTexture(INSTRUCTIONS_BACK_BUTTON_ID));
	m_instructionsBackButton.setOrigin(sf::Vector2f(m_instructionsBackButton.getTexture()->getSize() / 2u));
	m_instructionsBackButton.setPosition(sf::Vector2f(100, 100));
}

//called from the controller:
void Menu::show()
{
	handleEvents();
	draw();
}


void Menu::handleEvents()
{
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				m_window.close();
			}
			break;
		case sf::Event::MouseButtonReleased:
			handleClick(ev.mouseButton);
			break;
		case sf::Event::MouseMoved:
			handleHover(ev.mouseMove);
			break;
		default:
			break;
		}
	}
}

//check if any button was pressed and act accordingly:
void Menu::handleClick(sf::Event::MouseButtonEvent& ev)
{
	m_clickPosition = m_window.mapPixelToCoords({ ev.x, ev.y });
	if (m_exitButton.getGlobalBounds().contains(m_clickPosition)) {
		m_window.close();
	}
	else if (m_instructionsButton.getGlobalBounds().contains(m_clickPosition)) {
		m_instructionsMode = true;
	} 
	else if (m_instructionsBackButton.getGlobalBounds().contains(m_clickPosition)) {
		m_instructionsMode = false;
	}

}

//to enlarge the buttons when they are hovered:
void Menu::handleHover(sf::Event::MouseMoveEvent& ev)
{
	m_hoverPosition = m_window.mapPixelToCoords({ ev.x, ev.y });

	m_newGameButton.getGlobalBounds().contains(m_hoverPosition) ?
		m_newGameButton.setScale(sf::Vector2f(1.1f, 1.1f)) 
		: m_newGameButton.setScale(sf::Vector2f(1, 1));
	
	m_instructionsButton.getGlobalBounds().contains(m_hoverPosition) ? 
		m_instructionsButton.setScale(sf::Vector2f(1.1f, 1.1f))
		: m_instructionsButton.setScale(sf::Vector2f(1, 1));

	m_exitButton.getGlobalBounds().contains(m_hoverPosition) ?
		m_exitButton.setScale(sf::Vector2f(1.1f, 1.1f)) 
		: m_exitButton.setScale(sf::Vector2f(1, 1));

	m_instructionsBackButton.getGlobalBounds().contains(m_hoverPosition) ?
		m_instructionsBackButton.setScale(sf::Vector2f(1.1f, 1.1f))
		: m_instructionsBackButton.setScale(sf::Vector2f(1, 1));

}

//called from the controller, to check if we have to start the game:
bool Menu::newGameButtonPressed() 
{
	bool newGameButtonPressed = m_newGameButton.getGlobalBounds().contains(m_clickPosition);
	m_clickPosition = sf::Vector2f(0, 0); //to avoid automatic click in the next round
	return newGameButtonPressed;
}

void Menu::draw() 
{
	m_window.clear();
	if (m_instructionsMode) { //draw instructions 
		m_window.draw(m_instructionsImage);
		m_window.draw(m_instructionsBackButton);
	}
	else { //draw menu
		m_window.draw(m_background);
		m_window.draw(m_newGameButton);
		m_window.draw(m_instructionsButton);
		m_window.draw(m_exitButton);
	}
	m_window.display();
}