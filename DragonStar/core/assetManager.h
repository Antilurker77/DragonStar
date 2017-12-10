// ==================================
//
// assetManager.h
//
// Manages game assets via maps. Must
// be cleared manually.
//
// ==================================

#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class AssetManager {
public:
	AssetManager();
	sf::Image* LoadImage(std::string filepath);
	sf::Texture* LoadTexture(std::string filePath);
	sf::Font* LoadFont(std::string filePath);
	sf::SoundBuffer* LoadSoundBuffer(std::string filePath);
private:
	std::map<std::string, sf::Image> imageMap;
	std::map<std::string, sf::Texture> textureMap;
	std::map<std::string, sf::Font> fontMap;
	std::map<std::string, sf::SoundBuffer> soundBufferMap;

	void loadDefaultAssets();
	std::string loadDefault(std::string filePath);
};

extern AssetManager assetManager;