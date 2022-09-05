#pragma once
#include <vector>
#include <memory>
#include <fstream>
#include "StaticObjects/StaticObject.h"
#include "ResourcesManager.h"
#include "StaticObjects/Fire.h"
#include "StaticObjects/Gate.h"
#include "StaticObjects/Gift.h"
#include "StaticObjects/GiftDwarfs.h"
#include "StaticObjects/GiftTime.h"
#include "StaticObjects/Key.h"
#include "StaticObjects/Orc.h"
#include "StaticObjects/Teleport.h"
#include "StaticObjects/Throne.h"
#include "StaticObjects/Wall.h"
class Figure;

//characters of the input file:
const char KING_CHAR = 'K',
MAGE_CHAR = 'M',
WARRIOR_CHAR = 'W',
THIEF_CHAR = 'T',
DWARF_CHAR = '^',
EMPTY_CHAR = ' ',
WALL_CHAR = '=',
GATE_CHAR = '#',
FIRE_CHAR = '*',
ORC_CHAR = '!',
KEY_CHAR = 'F',
TELEPORT_CHAR = 'X',
THRONE_CHAR = '@',
GIFT_TIME_INCREASE_CHAR = 'I',
GIFT_TIME_DECREASE_CHAR = 'D',
GIFT_DWARFS_ERASE_CHAR = 'E';

class Board {
public:
	Board();
	~Board();
	void readLevelFromFile(int levelNum);
	int getNumOfLevels() const;
	void draw(sf::RenderWindow& window) const;

	sf::Vector2f getFigureInitialLocation(int figureId) const;
	const std::vector<sf::Vector2f>& getDwarfsInitialLocations() const;
	float getTileEdge() const;
	int getTimeLimit() const;
	int getNumOfStaticObjects() const;
	StaticObject& getStaticObject(int index) const;  
	void update();
	void resetTeleports(const std::vector<std::unique_ptr<Figure>>& figures);


private:
	sf::Vector2f calculateLocation(int i, int j) const;
	void matchTeleports();	

	std::ifstream m_levelFile; //input file of the level
	int m_numOfLevels;
	sf::Vector2f m_kingInitialLocation;
	sf::Vector2f m_mageInitialLocation;
	sf::Vector2f m_warriorInitialLocation;
	sf::Vector2f m_thiefInitialLocation;
	std::vector<sf::Vector2f> m_dwarfsInitialLocations;
	
	//holds the teleports matched in pairs:
	std::vector<std::pair<Teleport*, Teleport*>> m_teleportsPairs;

	//vector of game static objects:
	std::vector<std::unique_ptr<StaticObject>> m_staticObjects;
	int m_rows;
	int m_cols;
	int m_timeLimit; //if no time limit - 0, otherwise time limit in seconds

};