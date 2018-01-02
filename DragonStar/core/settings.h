// ==================================
//
// gameState.h
//
// Struct that holds user settings.
//
// ==================================

#pragma once

#include <SFML/Window.hpp>

struct BattleKeys {
	sf::Keyboard::Key Wait = sf::Keyboard::Q;
	sf::Keyboard::Key Attack = sf::Keyboard::A;
	sf::Keyboard::Key Ability1 = sf::Keyboard::Num1;
	sf::Keyboard::Key Ability2 = sf::Keyboard::Num2;
	sf::Keyboard::Key Ability3 = sf::Keyboard::Num3;
	sf::Keyboard::Key Ability4 = sf::Keyboard::Num4;
	sf::Keyboard::Key Ability5 = sf::Keyboard::Num5;
	sf::Keyboard::Key Ability6 = sf::Keyboard::Num6;
	sf::Keyboard::Key Ability7 = sf::Keyboard::Num7;
	sf::Keyboard::Key Ability8 = sf::Keyboard::Num8;
	sf::Keyboard::Key Ability9 = sf::Keyboard::Num9;
	sf::Keyboard::Key Ability10 = sf::Keyboard::Num0;
	sf::Keyboard::Key AbilityRacial = sf::Keyboard::Dash;
	sf::Keyboard::Key DebugVictory = sf::Keyboard::H;
};

struct Settings {
	// Window Size Settings
	int ScreenWidth = 1280;
	int ScreenHeight = 720;

	bool EnableVSync = true;
	bool Fullscreen = false;

	// Font Settings
	std::string Font = "gfx/ui/font/DroidSansMono.ttf";

	// Keybinds
	BattleKeys BattleKeybinds;

};

extern Settings settings;