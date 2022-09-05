#include "ResourcesManager.h"
#include <iostream>

ResourcesManager::ResourcesManager() {
	initTextures();
	initFonts();
	initSounds();
	initMusics();
}

//for the class to be singleton:
ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager instance;
	return instance;
}

const sf::Texture& ResourcesManager::getTexture(int texId) const
{
	return m_textures[texId];
}

const sf::Font& ResourcesManager::getFont(int fontId) const
{
	return m_fonts[fontId];
}

void ResourcesManager::playSound(int soundId)
{
	m_sounds[soundId].play();
}

void ResourcesManager::playMenuMusic()
{
	m_menuMusic.play();
}

void ResourcesManager::playGameMusic()
{
	m_gameMusic.play();
}

void ResourcesManager::stopMenuMusic()
{
	m_menuMusic.stop();
}

void ResourcesManager::stopGameMusic()
{
	m_gameMusic.stop();	
}

//push back the textures to m_textures vector:
void ResourcesManager::initTextures() {

	sf::Texture kingTex;
	kingTex.loadFromFile("king.png");
	sf::Texture mageTex;
	mageTex.loadFromFile("mage.png");
	sf::Texture warriorTex;
	warriorTex.loadFromFile("warrior.png");
	sf::Texture thiefTex;
	thiefTex.loadFromFile("thief.png");
	sf::Texture thiefWithKeyTex;
	thiefWithKeyTex.loadFromFile("thiefWithKey.png");
	sf::Texture dwarfTex;
	dwarfTex.loadFromFile("dwarf.png");
	sf::Texture wallTex;
	wallTex.loadFromFile("wall.png");
	sf::Texture gateTex;
	gateTex.loadFromFile("gate.png");
	sf::Texture fireTex;
	fireTex.loadFromFile("fire.png");
	sf::Texture orcTex;
	orcTex.loadFromFile("orc.png");
	sf::Texture keyTex;
	keyTex.loadFromFile("key.png");
	sf::Texture teleportTex;
	teleportTex.loadFromFile("teleport.png");
	sf::Texture throneTex;
	throneTex.loadFromFile("throne.png");
	sf::Texture giftTex;
	giftTex.loadFromFile("gift.png"); 
	sf::Texture gameBackgroundTex;
	gameBackgroundTex.loadFromFile("gameBackground.png");
	sf::Texture menuBackgroundTex;
	menuBackgroundTex.loadFromFile("menuBackground.png");
	sf::Texture newGameButtonTex;
	newGameButtonTex.loadFromFile("newGameButton.png");
	sf::Texture instructionsButtonTex;
	instructionsButtonTex.loadFromFile("instructionsButton.png");
	sf::Texture exitButtonTex;
	exitButtonTex.loadFromFile("exitButton.png");
	sf::Texture instructionsImageTex;
	instructionsImageTex.loadFromFile("instructionsImage.png");
	sf::Texture instructionsBackButtonTex;
	instructionsBackButtonTex.loadFromFile("instructionsBackButton.png");
	sf::Texture gameEndTex;
	gameEndTex.loadFromFile("gameEndScreen.png");
	sf::Texture levelSuccessTex;
	levelSuccessTex.loadFromFile("levelSuccessScreen.png");
	sf::Texture levelFailureTex;
	levelFailureTex.loadFromFile("levelFailureScreen.png");
	sf::Texture playTex;
	playTex.loadFromFile("play.png");
	sf::Texture pauseTex;
	pauseTex.loadFromFile("pause.png");

	m_textures.push_back(kingTex);
	m_textures.push_back(mageTex);
	m_textures.push_back(warriorTex);
	m_textures.push_back(thiefTex);
	m_textures.push_back(thiefWithKeyTex);
	m_textures.push_back(dwarfTex);
	m_textures.push_back(wallTex);
	m_textures.push_back(gateTex);
	m_textures.push_back(fireTex);
	m_textures.push_back(orcTex);
	m_textures.push_back(keyTex);
	m_textures.push_back(teleportTex);
	m_textures.push_back(throneTex);
	m_textures.push_back(giftTex);
	m_textures.push_back(gameBackgroundTex);
	m_textures.push_back(menuBackgroundTex);
	m_textures.push_back(newGameButtonTex);
	m_textures.push_back(instructionsButtonTex);
	m_textures.push_back(exitButtonTex);
	m_textures.push_back(instructionsImageTex);
	m_textures.push_back(instructionsBackButtonTex);
	m_textures.push_back(gameEndTex);
	m_textures.push_back(levelSuccessTex);
	m_textures.push_back(levelFailureTex);
	m_textures.push_back(playTex);
	m_textures.push_back(pauseTex);

}

//push back the fonts to m_fonts vector:
void ResourcesManager::initFonts()
{
	sf::Font levelNumFont;
	levelNumFont.loadFromFile("levelNumFont.ttf");
	sf::Font timerFont;
	timerFont.loadFromFile("timerFont.ttf");

	m_fonts.push_back(levelNumFont);
	m_fonts.push_back(timerFont);

}

//push back the sounds to m_sounds vector:
void ResourcesManager::initSounds()
{
	sf::SoundBuffer gateSoundBuffer;
	gateSoundBuffer.loadFromFile("gateSound.wav");
	sf::SoundBuffer giftSoundBuffer;
	giftSoundBuffer.loadFromFile("giftSound.wav");
	sf::SoundBuffer keySoundBuffer;
	keySoundBuffer.loadFromFile("keySound.wav");
	sf::SoundBuffer mageSoundBuffer;
	mageSoundBuffer.loadFromFile("mageSound.wav");
	sf::SoundBuffer swordSoundBuffer;
	swordSoundBuffer.loadFromFile("swordSound.wav");
	sf::SoundBuffer teleportSoundBuffer;
	teleportSoundBuffer.loadFromFile("teleportSound.wav");
	sf::SoundBuffer throneSoundBuffer;
	throneSoundBuffer.loadFromFile("throneSound.wav");
	sf::SoundBuffer timesUpBuffer;
	timesUpBuffer.loadFromFile("timesUpSound.wav");

	m_soundBuffers.push_back(gateSoundBuffer);
	m_soundBuffers.push_back(giftSoundBuffer);
	m_soundBuffers.push_back(keySoundBuffer);
	m_soundBuffers.push_back(mageSoundBuffer);
	m_soundBuffers.push_back(swordSoundBuffer);
	m_soundBuffers.push_back(teleportSoundBuffer);
	m_soundBuffers.push_back(throneSoundBuffer);
	m_soundBuffers.push_back(timesUpBuffer);

	for (int i = 0; i < m_soundBuffers.size(); i++) {
		sf::Sound sound(m_soundBuffers[i]);
		m_sounds.push_back(sound);
	}

	//it was too high :)
	m_sounds[Sounds::mage].setVolume(50.f);
	m_sounds[Sounds::throne].setVolume(50.f);

}

void ResourcesManager::initMusics()
{
	m_menuMusic.openFromFile("menuMusic.wav");
	m_menuMusic.setLoop(true);
	m_menuMusic.setVolume(70.f);

	m_gameMusic.openFromFile("gameMusic.wav");
	m_gameMusic.setLoop(true);
	m_gameMusic.setVolume(25.f);
}