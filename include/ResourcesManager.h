#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

//constants & enums for accessing the resources vectors:
const int KING_ID = 0,
MAGE_ID = 1,
WARRIOR_ID = 2,
THIEF_ID = 3,
THIEF_WITH_KEY_ID = 4,
DWARF_ID = 5,
WALL_ID = 6,
GATE_ID = 7,
FIRE_ID = 8,
ORC_ID = 9,
KEY_ID = 10,
TELEPORT_ID = 11,
THRONE_ID = 12,
GIFT_ID = 13,
GAME_BACKGROUND_ID = 14,
MENU_BACKGROUND_ID = 15,
NEW_GAME_BUTTON_ID = 16,
INSTRUCTIONS_BUTTON_ID = 17,
EXIT_BUTTON_ID = 18,
INSTRUCTIONS_IMAGE_ID = 19,
INSTRUCTIONS_BACK_BUTTON_ID = 20,
GAME_END_ID = 21,
LEVEL_SUCCESS_ID = 22,
LEVEL_FAILURE_ID = 23,
PLAY_ID = 24,
PAUSE_ID = 25;

enum Sounds {
	gate,
	gift,
	key,	
	mage,
	sword,
	teleport,
	throne,
	timesUp
};

enum Fonts {
	levelNum,
	timer
};


//This class is a singleton. It saves all the heavy resources files 
//(textures, fonts, sounds)
class ResourcesManager {
public:
	~ResourcesManager() = default;
	static ResourcesManager& instance();

	const sf::Texture& getTexture(int texId) const;
	const sf::Font& getFont(int fontId) const;
	void playSound(int soundId);
	void playMenuMusic();
	void playGameMusic();
	void stopMenuMusic();
	void stopGameMusic();

private:
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = default;
	ResourcesManager& operator=(const ResourcesManager&) = default;

	void initTextures();
	void initFonts();
	void initSounds();
	void initMusics();

	std::vector<sf::Texture> m_textures;
	std::vector<sf::Font> m_fonts;
	std::vector<sf::SoundBuffer> m_soundBuffers;
	std::vector<sf::Sound> m_sounds;
	sf::Music m_menuMusic;
	sf::Music m_gameMusic;

};