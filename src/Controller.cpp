#include "Controller.h"
#include "macros.h"
#include <cstdlib>

Controller::Controller()
	: m_board(),
	m_level(1), m_numOfLevels(m_board.getNumOfLevels()),
	m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
		"Save the King", sf::Style::Close),
	m_gameBackground(ResourcesManager::instance().getTexture(GAME_BACKGROUND_ID)),
	m_menu(m_window),
	m_infoBar(),
	m_controlled(KING_ID),
	m_isTimeLimit(false),
	m_timer(NO_TIME_LIMIT),
	m_playMode(true)
{
	//set the icon of the window titlebar and taskbar:
	sf::Image icon;
	icon.loadFromFile("kingIcon.png");
	m_window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Controller::initLevel()
{
	m_board.readLevelFromFile(m_level);
	
	//clear the data of the former level:
	m_figures.clear();
	m_dwarfs.clear();
	m_clockMovements.restart();
	
	//check if there is time limit:
	m_isTimeLimit = m_board.getTimeLimit() > NO_TIME_LIMIT ? true : false;
	m_timer = m_board.getTimeLimit();
	m_levelClock.restart();
	m_infoBar.setLevelNumber(m_level);

	//for moving objects to be sized as tile size:
	float tileSize = m_board.getTileEdge(); 
	
	//create the 4 main figures of the game:
	m_figures.push_back(std::make_unique<King>
		(ResourcesManager::instance().getTexture(KING_ID), 
			m_board.getFigureInitialLocation(KING_ID), tileSize) );
	m_figures.push_back(std::make_unique<Mage>
		(ResourcesManager::instance().getTexture(MAGE_ID),
			m_board.getFigureInitialLocation(MAGE_ID), tileSize) );
	m_figures.push_back(std::make_unique<Warrior>
		(ResourcesManager::instance().getTexture(WARRIOR_ID),
			m_board.getFigureInitialLocation(WARRIOR_ID), tileSize) );
	m_figures.push_back(std::make_unique<Thief>
		(ResourcesManager::instance().getTexture(THIEF_ID),
			m_board.getFigureInitialLocation(THIEF_ID), tileSize) );
	
	//create the dwarfs:
	for (int i = 0; i < m_board.getDwarfsInitialLocations().size(); i++) {
		m_dwarfs.push_back(std::make_unique<Dwarf>
			(ResourcesManager::instance().getTexture(DWARF_ID),
				m_board.getDwarfsInitialLocations()[i], tileSize));
	}

	//set the king as the first controlled figure:
	m_controlled = KING_ID;
	m_figures[KING_ID]->setIsControlled(true);

}

void Controller::run()
{
	ResourcesManager::instance().playMenuMusic();

	m_window.setFramerateLimit(FPS);
	while (m_window.isOpen()) {

		m_menu.show();

		if (m_menu.newGameButtonPressed()) {
			startGame();
		}

	}
}

bool Controller::isGameOver() const
{
	return m_level > m_numOfLevels;
}

bool Controller::isLevelOver() 
{
	//check if the king reched throne:
	bool kingReachedThrone = dynamic_cast<King*>(m_figures[KING_ID].get())->isReachedThrone();
	//the player didn't succeed to finish the level on time:
	if (m_isTimeLimit && m_timer <= 0) {
		showLevelFailureScreen();
		return true;
	}
	else if (kingReachedThrone) {
		//because at the end of the game we have another congratulations screen:
		if (m_level != m_numOfLevels) { 
			showLevelSuccessScreen();
		}
		m_level++;
		return true;
	}

	return false;
}

//game and level loops:
void Controller::startGame() {

	ResourcesManager::instance().stopMenuMusic();
	ResourcesManager::instance().playGameMusic();

	//game loop:
	while (!isGameOver()) {

		initLevel();

		//level loop:
		while (!isLevelOver()) {
			handleEvents();
			if (m_playMode == true) { //the game is played
				updateTimer();
				updateObjects();
			}
			else { //the game is paused
				m_clockMovements.restart();
				m_levelClock.restart();
			}
			draw();
		}

	}
	showGameEndScreen();
	m_level = 1; //for next round
	
	ResourcesManager::instance().stopGameMusic();
	ResourcesManager::instance().playMenuMusic();

}


void Controller::updateTimer()
{
	//update the timer that displayed in the infoBar every one second:
	if (m_levelClock.getElapsedTime().asSeconds() >= 1) {
		if (m_isTimeLimit) { //if there is time limit count down
			m_timer--;
			//the time is about to end, play sound:
			if (m_timer == 3) {
				ResourcesManager::instance().playSound(Sounds::timesUp);
			}
		}
		else { 
			m_timer++;
		}
		m_levelClock.restart(); //so the level clock will measure the next second
	}

	m_infoBar.setTimer(m_timer);

}

void Controller::handleEvents()
{
	sf::Event ev;
	while (m_window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				m_window.close();
				exit(EXIT_SUCCESS);
			}
			//change controlled figure when 'P' pressed:
			else if (m_playMode == true && ev.key.code == sf::Keyboard::P) {
				m_figures[m_controlled]->setIsControlled(false);
				m_controlled = (m_controlled + 1) % NUM_OF_FIGURES;
				m_figures[m_controlled]->setIsControlled(true);
			}
			break;
		case sf::Event::MouseButtonReleased:
			//to detect pause button pressed:
			m_clickPosition = 
			m_window.mapPixelToCoords({ ev.mouseButton.x, ev.mouseButton.y });
			updatePlayMode();
			break;
		default:
			break;
		}
	}
}

void Controller::updatePlayMode()
{
	//switch between play/pause modes when pause button is clicked:
	if (m_infoBar.isPauseButtonPress(m_clickPosition)) {
		if (m_playMode == true) {
			m_playMode = false;
			m_infoBar.updatePauseButtonTexture(false);
		}
		else {
			m_playMode = true;
			m_infoBar.updatePauseButtonTexture(true);
		}
	}
}

void Controller::updateObjects()
{
	//delta time for movements:
	const sf::Time deltaTime = m_clockMovements.restart();

	m_figures[m_controlled]->move(deltaTime);
	m_board.resetTeleports(m_figures); //to free blocked teleports
	handleCollisions(*m_figures[m_controlled]);
	activateGifts();

	for (auto& dwarf : m_dwarfs) {
		dwarf->move(deltaTime);
		dwarf->setAsInitiatedCollision(true); //to know who initiated a collision
		handleCollisions(*dwarf);
		dwarf->setAsInitiatedCollision(false);
	}

	m_board.update(); //dispose static objects etc.

}

void Controller::activateGifts()
{
	for (int i = 0; i < m_board.getNumOfStaticObjects(); i++) {
		if (Gift* gift = dynamic_cast<Gift*>(&m_board.getStaticObject(i))) {
			if (gift->isActive()) {
				gift->activate(*this);
			}
		}
	}
}

void Controller::handleCollisions(MovingObject& movingObject)
{
	//collisions with figures:
	for (auto& figure : m_figures) {
		if (movingObject.collidesWith(*figure)) {
			movingObject.handleCollision(*figure);
		}
	}
	
	//collisions with dwarfs:
	for (auto& dwarf : m_dwarfs) {
		if (movingObject.collidesWith(*dwarf)) {
			movingObject.handleCollision(*dwarf);
		}
	}
	
	//collisions with static objects:
	for (int i = 0; i < m_board.getNumOfStaticObjects(); i++) {
		if (movingObject.collidesWith(m_board.getStaticObject(i))) {
			movingObject.handleCollision(m_board.getStaticObject(i));
		}
	}
	
}

void Controller::draw()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_gameBackground);
	m_board.draw(m_window);
	m_infoBar.draw(m_window);
	for (auto& figure : m_figures) {
		figure->draw(m_window);
	}
	for (auto& dwarf : m_dwarfs) {
		dwarf->draw(m_window);
	}
	m_window.display();
}

//called when time gift was collected:
void Controller::adjustTimer(int amount)
{
	m_timer += amount;
}

//called when dwarfs gift was collected:
void Controller::eraseDwarfs()
{
	m_dwarfs.clear();
}

//three functions for displaying messages screens for 2 seconds:
void Controller::showGameEndScreen()
{
	m_levelClock.restart();

	m_gameEndScreen.setTexture(ResourcesManager::instance().getTexture(GAME_END_ID));

	while (m_levelClock.getElapsedTime().asSeconds() < MESSAGE_SCREEN_TIME) {
		m_window.clear();
		m_window.draw(m_gameEndScreen);
		m_window.display();
	}
}

void Controller::showLevelSuccessScreen()
{
	m_levelClock.restart();

	m_levelSuccessScreen.setTexture(ResourcesManager::instance().getTexture(LEVEL_SUCCESS_ID));

	while (m_levelClock.getElapsedTime().asSeconds() < MESSAGE_SCREEN_TIME) {
		m_window.clear();
		m_window.draw(m_levelSuccessScreen);
		m_window.display();
	}
}

void Controller::showLevelFailureScreen()
{
	m_levelClock.restart();

	m_levelFailureScreen.setTexture(ResourcesManager::instance().getTexture(LEVEL_FAILURE_ID));

	while (m_levelClock.getElapsedTime().asSeconds() < MESSAGE_SCREEN_TIME) {
		m_window.clear();
		m_window.draw(m_levelFailureScreen);
		m_window.display();
	}
}