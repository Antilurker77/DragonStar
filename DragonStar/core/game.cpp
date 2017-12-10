// ==================================
//
// game.cpp
//
// ==================================

#include "game.h"

Settings settings;

// FPS
const sf::Time Game::timePerFrame = sf::seconds(1.f / 60.f);

Game::Game() :
	window(sf::VideoMode(settings.ScreenWidth, settings.ScreenHeight), "Dragon Star v0.2.2"),
	camera(sf::Vector2f(0, 0), sf::Vector2f(settings.ScreenWidth, settings.ScreenHeight)),
	uiView(sf::Vector2f(settings.ScreenWidth / 2, settings.ScreenHeight / 2), sf::Vector2f(settings.ScreenWidth, settings.ScreenHeight))
{
	
	camera.SetZoom(1.f);
	
	battleScene.SetCamera(&camera);

	if (settings.Fullscreen) {
		window.create(sf::VideoMode(settings.ScreenWidth, settings.ScreenHeight), "Dragon Star v0.2.2", sf::Style::Fullscreen);
	}

	// VSync
	window.setVerticalSyncEnabled(settings.EnableVSync);

	// Debug Window
	fpsWindow.SetFont(settings.Font);
}


// Main game loop. Will update at a fixed rate and render as often as possible.
void Game::Run(){
	sf::Clock clock;
	sf::Time timeSinceUpdate = sf::Time::Zero;
	float timeRatio = 0.f;
	float secondsPerUpdate = timePerFrame.asSeconds() / 1.f;

	while (window.isOpen()){
		sf::Time elapsedTime = clock.restart();
		timeSinceUpdate += elapsedTime;
		timeRatio = 0.f;

		while (timeSinceUpdate > timePerFrame){
			timeSinceUpdate -= timePerFrame;
			processInput();
			update(secondsPerUpdate);
		}

		timeRatio = timeSinceUpdate.asSeconds() / timePerFrame.asSeconds();
		render(timeRatio);
		displayFPS(elapsedTime);

	}
}

void Game::processInput(){
	switch (gameState) {
	case GameState::MAIN_MENU:
		mainMenuScene.ReadInput(window);
		break;
	case GameState::PARTY_CREATION:
		partyCreationScene.ReadInput(window);
		break;
	case GameState::MAP_SELECT:
		mapSelectScene.ReadInput(window);
		break;
	case GameState::BATTLE:
		battleScene.ReadInput(window);
		break;
	default:
		break;
	}
}

void Game::update(float secondsPerUpdate){
	//world.Update(secondsPerUpdate);
	//ui.Update(screenWidth, screenHeight);
	//camera.Update(secondsPerUpdate);
	/*
	// Stress test for pushing CPU.
	int test2 = 0;
	for (int i = 0; i < 6750000; i++){
		test2 = 33 * test2 + i;
	}
	*/
	switch (gameState) {
	case GameState::MAIN_MENU:
		gameState = mainMenuScene.Update(secondsPerUpdate);
		break;
	case GameState::PARTY_CREATION:
		gameState = partyCreationScene.Update(secondsPerUpdate);

		// transition from party creation to map select
		if (gameState == GameState::MAP_SELECT) {
			mapSelectScene.SetSeed(partyCreationScene.GetSeed());
			mapSelectScene.SetParty(partyCreationScene.GetParty());
			mapSelectScene.SetClickBuffer(0.05f);
		}
		break;
	case GameState::MAP_SELECT:
		gameState = mapSelectScene.Update(secondsPerUpdate);

		// transition from map selection to battle
		if (gameState == GameState::BATTLE) {
			battleScene.Initialize(mapSelectScene.GetParty(), mapSelectScene.GetSelectedMapNode());
		}
		break;
	case GameState::BATTLE:
		gameState = battleScene.Update(secondsPerUpdate);

		// transistion from battle back to map selection
		if (gameState == GameState::MAP_SELECT) {
			mapSelectScene.CompleteMap(battleScene.GetItemsAwarded(), battleScene.GetGoldAwared());
			mapSelectScene.SetClickBuffer(0.4f);
		}

		break;
	default:
		break;
	}

	camera.Update(secondsPerUpdate);
}

void Game::render(float timeRatio){	
	window.clear();

	camera.Interpolate(timeRatio);
	window.setView(camera.GetCamera());

	//// Draw the world and world UI elements.
	//world.Render(window, timeRatio);
	//ui.WorldRender(window);

	//// Draw the screen UI.
	//window.setView(uiView);
	//ui.Render(window);

	// World
	switch (gameState) {
	case GameState::BATTLE:
		battleScene.RenderWorld(window, timeRatio);
		break;
	default:
		break;
	}

	// UI
	window.setView(uiView);

	switch (gameState) {
	case GameState::MAIN_MENU:
		mainMenuScene.Render(window, timeRatio);
		break;
	case GameState::PARTY_CREATION:
		partyCreationScene.Render(window, timeRatio);
		break;
	case GameState::MAP_SELECT:
		mapSelectScene.Render(window, timeRatio);
		break;
	case GameState::BATTLE:
		battleScene.RenderUI(window, timeRatio);
		break;
	default:
		break;
	}

	fpsWindow.Draw(window);
	window.display();
}

void Game::displayFPS(sf::Time& t) {
	fpsUpdateTime += t;
	numberOfFrames++;

	if (fpsUpdateTime >= sf::seconds(1.f)) {
		fpsWindow.ClearText();
		fpsWindow.AddText("FPS: " + std::to_string(numberOfFrames));
		fpsWindow.AddText("Frame Time: " + std::to_string(1000.f / numberOfFrames));

		numberOfFrames = 0;
		fpsUpdateTime -= sf::seconds(1.f);
	}
}