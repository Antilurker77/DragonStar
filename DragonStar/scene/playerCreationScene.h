// ==================================
//
// playerCreationScene.h
//
// Scene where user creates a party
// member.
//
// ==================================

#pragma once

#include "playerLoadout.h"
#include "../core/gameState.h"
#include "../ui/button.h"
#include "../ui/dropdown.h"

class PlayerCreationScene {
public:
	PlayerCreationScene();

	// Reads input from the user and processes events.
	void ReadInput(sf::RenderWindow& window);

	// Update function.
	GameState Update(float secondsPerUpdate);

	// Renders to the screen.
	void Render(sf::RenderTarget& window, float timeRatio);

	// Initializes this scene based on the given loadout.
	void Initialize(PlayerLoadout loadout);

private:

};