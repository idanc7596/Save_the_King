#include "Board.h"
#include "macros.h"
#include "MovingObjects/Figure.h"
#include <string>
#include <sstream>

Board::Board() 
	: m_rows(0), m_cols(0), m_timeLimit(NO_TIME_LIMIT)
{	
	m_levelFile.open("Level1.txt");
	//first line in Level1.txt contains the number of levels:
	m_levelFile >> m_numOfLevels; 
}

Board::~Board()
{
	m_levelFile.close();
}

void Board::readLevelFromFile(int levelNum)
{
	m_levelFile.close(); //close the previous level .txt file
	std::string levelFileName = "Level" + std::to_string(levelNum) + ".txt";
	m_levelFile.open(levelFileName); //open the current level .txt file

	//only in Level1.txt there is a blank line between numOfLevels and the level,
	//read it:
	std::string line;
	if (levelNum == 1) {
		std::getline(m_levelFile, line);
		std::getline(m_levelFile, line);
	}
	
	
	//reads level dimensions and time limit (0 = no time limit):
	std::getline(m_levelFile, line);
	std::istringstream stringStream(line);
	stringStream >> m_rows >> m_cols >> m_timeLimit;

	//clear the former level data:
	m_staticObjects.clear(); 
	m_dwarfsInitialLocations.clear();
	m_teleportsPairs.clear();

	float tileSize = getTileEdge(); 

	//read the file chars and build static objects accordingly:
	char c; //current char read from file
	for (int i = 0; i < m_rows; i++) {		
		for (int j = 0; j < m_cols; j++) {
			sf::Vector2f currLocation = calculateLocation(i, j);
			m_levelFile.get(c);
			switch (c) {
			case WALL_CHAR:
				m_staticObjects.push_back(std::make_unique<Wall>
					(ResourcesManager::instance().getTexture(WALL_ID), currLocation, tileSize));
				break;
			case GATE_CHAR:
				m_staticObjects.push_back(std::make_unique<Gate>
					(ResourcesManager::instance().getTexture(GATE_ID), currLocation, tileSize));
				break;
			case FIRE_CHAR:
				m_staticObjects.push_back(std::make_unique<Fire>
					(ResourcesManager::instance().getTexture(FIRE_ID), currLocation, tileSize));
				break;
			case ORC_CHAR:
				m_staticObjects.push_back(std::make_unique<Orc>
					(ResourcesManager::instance().getTexture(ORC_ID), currLocation, tileSize));
				break;
			case KEY_CHAR:
				m_staticObjects.push_back(std::make_unique<Key>
					(ResourcesManager::instance().getTexture(KEY_ID), currLocation, tileSize));
				break;
			case TELEPORT_CHAR:
				m_staticObjects.push_back(std::make_unique<Teleport>
					(ResourcesManager::instance().getTexture(TELEPORT_ID), currLocation, tileSize));
				break;
			case THRONE_CHAR:
				m_staticObjects.push_back(std::make_unique<Throne>
					(ResourcesManager::instance().getTexture(THRONE_ID), currLocation, tileSize));
				break;
			case GIFT_TIME_INCREASE_CHAR:
				m_staticObjects.push_back(std::make_unique<GiftTime>
					(ResourcesManager::instance().getTexture(GIFT_ID), 
						currLocation, tileSize, true)); //true == increase time
				break;
			case GIFT_TIME_DECREASE_CHAR:
				m_staticObjects.push_back(std::make_unique<GiftTime>
					(ResourcesManager::instance().getTexture(GIFT_ID), 
						currLocation, tileSize, false)); //false == decrease time
				break;
			case GIFT_DWARFS_ERASE_CHAR:
				m_staticObjects.push_back(std::make_unique<GiftDwarfs>
					(ResourcesManager::instance().getTexture(GIFT_ID), currLocation, tileSize));
				break;
			//save the initial locations of the moving objects:
			case KING_CHAR:
				m_kingInitialLocation = currLocation;
				break;
			case MAGE_CHAR:
				m_mageInitialLocation = currLocation;
				break;
			case WARRIOR_CHAR:
				m_warriorInitialLocation = currLocation;
				break;
			case THIEF_CHAR:
				m_thiefInitialLocation = currLocation;
				break;
			case DWARF_CHAR:
				m_dwarfsInitialLocations.push_back(currLocation);
				break;
			default:
				break;
			}
		}
		if (i != m_rows-1) { //(don't read '\n' after last line)
			m_levelFile.get(c); //read '\n'
		}
	}

	matchTeleports(); 
	
}

//match the teleports to pairs:
void Board::matchTeleports()
{
	//build a vector of pointers that points all the teleports:
	std::vector<Teleport*> teleports;
	for (auto& staticObject : m_staticObjects) {
		if (Teleport* teleport = dynamic_cast<Teleport*>(staticObject.get())) {
			teleports.push_back(teleport);
		}
	}

	//divide the vector to 2 halves, 
	//and match the first one in the first half 
	//to the first one in the second half, 
	//the second one to the second one, etc. 
	std::pair<Teleport*, Teleport*> pair;
	int half = int(teleports.size()) / 2;
	for (int i = 0, j = half; i < half; i++, j++) {
		teleports[i]->setPartner(teleports[j]);
		teleports[j]->setPartner(teleports[i]);
		pair.first = teleports[i];
		pair.second = teleports[j];
		m_teleportsPairs.push_back(pair);
	}

}

//free blocked teleports:
void Board::resetTeleports(const std::vector<std::unique_ptr<Figure>>& figures)
{
	for (auto& pair : m_teleportsPairs) {
		bool isPairBlocked = false;

		//if any figure is still on one of the teleports of this pair,
		//leave this pair as blocked:
		for (auto& figure : figures) {
			if (figure->collidesWith(*(pair.first)) ||
				figure->collidesWith(*(pair.second))) {
				isPairBlocked = true;
				break;
			}
		}

		//if we are here, it means that this pair is not blocked (there isn't any figure 
		//that steps on any of this teleports pair), so we can free it:
		if (isPairBlocked == false) {
			pair.first->setBlocked(false);
			pair.second->setBlocked(false);
		}

	}

}

int Board::getNumOfLevels() const
{
	return m_numOfLevels;
}

//translate (row, col) coordinates to position (in pixels):
sf::Vector2f Board::calculateLocation(int i, int j) const
{
	float tileEdge = getTileEdge();

	float col = j * tileEdge;
	float row = i * tileEdge;

	return sf::Vector2f(col, row);
}


void Board::draw(sf::RenderWindow& window) const
{
	//call draw function of each static object:
	for (auto& staticObject : m_staticObjects) {
		staticObject->draw(window);
	}
}

sf::Vector2f Board::getFigureInitialLocation(int figureId) const
{
	sf::Vector2f location;
	switch (figureId) {
	case KING_ID:
		location = m_kingInitialLocation;
		break;
	case MAGE_ID:
		location = m_mageInitialLocation;
		break;
	case WARRIOR_ID:
		location = m_warriorInitialLocation;
		break;
	case THIEF_ID:
		location = m_thiefInitialLocation;
		break;
	default:
		break;
	}
	return location;
}


const std::vector<sf::Vector2f>& Board::getDwarfsInitialLocations() const
{
	return m_dwarfsInitialLocations;
}

//calculate the tile size (the length of the tile edge, the tiles are squared):
float Board::getTileEdge() const
{
	if (m_rows > 0 && m_cols > 0) {
		return std::min(float(WINDOW_HEIGHT) / m_rows, float(WINDOW_WIDTH) / m_cols);
	}
	return 0;
}

int Board::getTimeLimit() const
{
	return m_timeLimit;
}

int Board::getNumOfStaticObjects() const
{
	return int(m_staticObjects.size());
}

//for controller to get static object:
StaticObject& Board::getStaticObject(int index) const
{
	return *m_staticObjects[index];
}

void Board::update()
{
	//replace disposed orcs with keys:
	for (auto& staticObject : m_staticObjects) {
		if (Orc *orc = dynamic_cast<Orc*>(staticObject.get())) {
			if (orc->replaceWithKey()) {
				m_staticObjects.push_back(std::make_unique<Key>
					(ResourcesManager::instance().getTexture(KEY_ID), 
						orc->getLocation(), getTileEdge()));
			}
		}
	}
	
	//dispose static objects that was marked to be disposed:
	std::erase_if(m_staticObjects, [](const auto& staticObject) {
		return staticObject->isDisposed();
		});
}