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

#include <array>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "playerLoadout.h"
#include "../core/gameState.h"
#include "../entity/player.h"
#include "../ui/button.h"
#include "../ui/richText.h"

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

	// Returns the the party's starting gold.
	unsigned int GetStartingGold();

	// Returns the master seed used to start the current game.
	uint64_t GetSeed();

	// Returns the selected Player Loadout.
	PlayerLoadout GetSelectedPlayerLoadout();

	// Sets the text showing each player's name, race, and class.
	// Sets buttons to either Create or Edit
	void SetPlayerTextAndButtons();

private:
	// Party Data
	std::vector<ActorPtr> party;
	std::array<PlayerLoadout, 6> loadouts;
	unsigned int startingGold = 0u;

	// UI
	sf::Vector2i windowMousePos;
	bool leftClick = false;

	Button startGameButton;
	Button backButton;
	//Button makePartyPlaceholderButton; // placeholder button for creating a party
	Button placeholderA;
	Button placeholderB;

	std::array<sfe::RichText, 6> playerText;
	std::array<Button, 6> playerCreationButtons;
	size_t selectedPlayer = 0u;
	const unsigned int playerButtonSize = 18u;

	// Creates the party from the loadouts.
	void makeParty();

	// Creates test party A.
	void testPartyA();

	// Creates test party B.
	void testPartyB();
};
