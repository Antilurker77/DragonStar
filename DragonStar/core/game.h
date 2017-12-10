// ==================================
//
// game.h
//
// Handles main game loop.
//
// ==================================

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include "camera.h"
#include "gameState.h"
#include "settings.h"
#include "../scene/battleScene.h"
#include "../scene/mainMenuScene.h"
#include "../scene/mapSelectScene.h"
#include "../scene/partyCreationScene.h"
#include "../ui/window.h"

#include <Windows.h>


class Game {
public:
	Game();
	void Run();

private:
	void processInput();
	void update(float secondsPerUpdate);
	void render(float timeRatio);
	void displayFPS(sf::Time& t);
	
	//---------------

	sf::RenderWindow window;
	Camera camera;
	sf::View uiView;
	static const sf::Time timePerFrame;

	// Scenes
	GameState gameState = GameState::MAIN_MENU;

	MainMenuScene mainMenuScene;
	PartyCreationScene partyCreationScene;
	MapSelectScene mapSelectScene;
	BattleScene battleScene;
	

	// Debug Text
	Window fpsWindow;
	sf::Time fpsUpdateTime;
	size_t numberOfFrames;
};