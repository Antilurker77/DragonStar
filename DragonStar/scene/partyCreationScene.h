// ==================================
//
// partyCreationScene.h
//
// Scene that where the user creates
// their party.
//
// Currently hard-coded / disabled
// for testing.
//
// ==================================

#pragma once

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "../core/gameState.h"
#include "../entity/player.h"
#include "../ui/button.h"

class PartyCreationScene {
public:
	PartyCreationScene();

	// Reads input from the user and processes events.
	void ReadInput(sf::RenderWindow& window);

	// Update function.
	GameState Update(float secondsPerUpdate);

	// Renders to the screen.
	void Render(sf::RenderTarget& window, float timeRatio);

	// Returns the player's party. Used for scene transitions.
	std::vector<ActorPtr> GetParty();

	// Returns the master seed used to start the current game.
	uint64_t GetSeed();

private:
	// Party Data
	std::vector<ActorPtr> party;

	// UI
	sf::Vector2i windowMousePos;
	bool leftClick = false;

	Button startGameButton;
	Button backButton;
	Button makePartyPlaceholderButton; // placeholder button for creating a party

	// Creates a party. Placeholder.
	void makeParty();
};
