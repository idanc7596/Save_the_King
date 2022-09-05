#pragma once
#include <SFML/Graphics.hpp>


class Menu {
public:
	Menu(sf::RenderWindow& window);
	void show();
	bool newGameButtonPressed();


private:
	void initButtons();
	void handleEvents();
	void handleClick(sf::Event::MouseButtonEvent& ev);
	void handleHover(sf::Event::MouseMoveEvent& ev);
	void draw();

	sf::RenderWindow& m_window; //a reference to the window from the controller
	sf::Vector2f m_clickPosition;
	sf::Vector2f m_hoverPosition;

	sf::Sprite m_background; 
	sf::Sprite m_newGameButton;
	sf::Sprite m_instructionsButton;
	sf::Sprite m_exitButton;

	sf::Sprite m_instructionsImage;
	sf::Sprite m_instructionsBackButton;

	//indicate if the menu displays the instructions screen
	//or menu screen:
	bool m_instructionsMode; 

};