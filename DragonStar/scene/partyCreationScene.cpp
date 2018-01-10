// ==================================
//
// partyCreationScene.cpp
//
// ==================================

#include "partyCreationScene.h"

#include "../core/random.h"
#include "../core/settings.h"
#include "../data/id/playerClassID.h"
#include "../data/id/raceID.h"

PartyCreationScene::PartyCreationScene() {

	// button setup
	makePartyPlaceholderButton.SetString("Make Party Placeholder", 24);
	makePartyPlaceholderButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight / 4);

	startGameButton.SetString("Start Game", 24);
	startGameButton.SetPosition(settings.ScreenWidth / 2, settings.ScreenHeight * 0.75);

	backButton.SetString("Back");
	sf::Vector2f buttonSize = backButton.GetSize();
	backButton.SetPosition(4 + buttonSize.x / 2, 4 + buttonSize.y / 2);
}

void PartyCreationScene::ReadInput(sf::RenderWindow& window) {
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

GameState PartyCreationScene::Update(float secondsPerUpdate) {
	GameState gameState = GameState::PARTY_CREATION;
	
	if (makePartyPlaceholderButton.Update(secondsPerUpdate, windowMousePos) && leftClick) {
		makeParty();
	}

	if (startGameButton.Update(secondsPerUpdate, windowMousePos) && leftClick && !party.empty()) {
		gameState = GameState::MAP_SELECT;
	}

	if (backButton.Update(secondsPerUpdate, windowMousePos) && leftClick) {
		gameState = GameState::MAIN_MENU;
	}

	return gameState;
}

void PartyCreationScene::Render(sf::RenderTarget& window, float timeRatio) {
	makePartyPlaceholderButton.Render(window);
	startGameButton.Render(window);
	backButton.Render(window);
}

std::vector<ActorPtr> PartyCreationScene::GetParty() {
	return party;
}

uint64_t PartyCreationScene::GetSeed() {
	uint64_t seed = Random::RandSeed();
	return seed;
}

void PartyCreationScene::makeParty() {
	party.clear();

	// hardcoded test
	party.push_back(ActorPtr(std::make_shared<Player>("Adriathe", RaceID::HUMAN, PlayerClassID::ADVENTURER)));
	party.push_back(ActorPtr(std::make_shared<Player>("Bera", RaceID::HUMAN, PlayerClassID::ADVENTURER, true)));
	party.push_back(ActorPtr(std::make_shared<Player>("Cerruk", RaceID::HUMAN, PlayerClassID::ADVENTURER)));
	party.push_back(ActorPtr(std::make_shared<Player>("Dega", RaceID::HUMAN, PlayerClassID::ADVENTURER, true)));
	party.push_back(ActorPtr(std::make_shared<Player>("Ethandis", RaceID::HUMAN, PlayerClassID::ADVENTURER)));
	party.push_back(ActorPtr(std::make_shared<Player>("Fathe", RaceID::HUMAN, PlayerClassID::ADVENTURER, true)));
}