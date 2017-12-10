// ==================================
//
// mainMenuScene.h
//
// Scene that manages the main menu.
// From here, user can access new
// game, load game, settings, and
// encyclopedia.
//
// ==================================

#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>

#include "../core/gameState.h"
#include "../ui/button.h"

class MainMenuScene {
public:
	MainMenuScene();

	// Reads input.
	void ReadInput(sf::RenderWindow& window);

	// Updates the main scene. Will return different
	// GameState values when it's time to switch
	// scenes.
	GameState Update(float secondsPerUpdate);

	// Renders the main menu.
	void Render(sf::RenderTarget& window, float timeRatio);

private:
	sf::Text titleText;
	sf::Text versionText;
	sf::Text authorText;

	sf::Font* font;

	sf::Vector2i windowMousePos;
	bool leftClick = false;

	// Buttons
	Button newGameButton;
};
