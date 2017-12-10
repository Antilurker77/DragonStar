// ==================================
//
// mainMenuScene.cpp
//
// ==================================

#include "mainMenuScene.h"

#include "../core/assetManager.h"
#include "../core/settings.h"

MainMenuScene::MainMenuScene() {
	font = assetManager.LoadFont(settings.Font);

	titleText.setFont(*font);
	titleText.setCharacterSize(80);
	titleText.setString("Dragon Star");

	authorText.setFont(*font);
	authorText.setCharacterSize(32);
	authorText.setString("By Antilurker77");

	versionText.setFont(*font);
	versionText.setCharacterSize(32);
	versionText.setString("v0.2.2");

	// Button Setup
	newGameButton.SetString("New Game", 36);
}

void MainMenuScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;

	windowMousePos = mouse.getPosition(window);
	leftClick = false;

	while (window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
			}
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			break;
		default:
			break;
		}
	}

}

GameState MainMenuScene::Update(float secondsPerUpdate) {
	GameState gameState = GameState::MAIN_MENU;

	// Position Text
	// Done every frame in case user changes resolution.
	auto textSize = titleText.getLocalBounds();
	titleText.setPosition(settings.ScreenWidth / 2 - textSize.width / 2, settings.ScreenHeight / 5);

	textSize = authorText.getLocalBounds();
	authorText.setPosition(16, settings.ScreenHeight - textSize.height - 16);

	textSize = versionText.getLocalBounds();
	versionText.setPosition(settings.ScreenWidth - textSize.width - 16, settings.ScreenHeight - textSize.height - 24);

	// Position Buttons
	newGameButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 0.4);

	// Check button mouseover and clicks.
	if (newGameButton.Update(secondsPerUpdate, windowMousePos)) {
		if (leftClick) {
			gameState = GameState::PARTY_CREATION;
		}
	}

	return gameState;
}

void MainMenuScene::Render(sf::RenderTarget& window, float timeRatio) {
	window.draw(titleText);
	window.draw(authorText);
	window.draw(versionText);

	newGameButton.Render(window);
}