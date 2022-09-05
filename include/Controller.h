#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Board.h"
#include "Menu.h"
#include "InfoBar.h"
#include "MovingObjects/MovingObject.h"
#include "MovingObjects/Figure.h"
#include "MovingObjects/King.h"
#include "MovingObjects/Mage.h"
#include "MovingObjects/Warrior.h"
#include "MovingObjects/Thief.h"
#include "MovingObjects/Dwarf.h"

const unsigned int FPS = 20; 
const int NUM_OF_FIGURES = 4;
//time for displaying the level up, time's up and congratulations messages:
const int MESSAGE_SCREEN_TIME = 2; 

class Controller {
public:
	Controller();

	void run(); 
	void adjustTimer(int amount); 
	void eraseDwarfs();


private:
	bool isGameOver() const;
	bool isLevelOver();
	void initLevel();
	void startGame();
	void updateTimer();
	void handleEvents();
	void updateObjects();
	void activateGifts();
	void draw();
	void showGameEndScreen();
	void showLevelSuccessScreen();
	void showLevelFailureScreen();
	void updatePlayMode();

	void handleCollisions(MovingObject &movingObject);
	

	sf::RenderWindow m_window;
	Menu m_menu;
	InfoBar m_infoBar;
	Board m_board;
	std::vector<std::unique_ptr<Figure>> m_figures;
	int m_controlled; //for current controlled figure
	std::vector<std::unique_ptr<Dwarf>> m_dwarfs;
	
	int m_level;
	int m_numOfLevels;
	bool m_playMode; //play / pause
	sf::Vector2f m_clickPosition;
	sf::Clock m_clockMovements; //for delta time movements
	
	bool m_isTimeLimit;
	int m_timer; //in seconds
	sf::Clock m_levelClock; //count seconds from level beginning

	sf::Sprite m_gameBackground;
	sf::Sprite m_gameEndScreen; //congratulations screen
	sf::Sprite m_levelSuccessScreen; //level up screen
	sf::Sprite m_levelFailureScreen; //time's up screen

};