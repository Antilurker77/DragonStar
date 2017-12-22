// ==================================
//
// abilityWindow.h
//
// Window that allows the user to
// change their abilities.
//
// ==================================

#pragma once

class Actor;
class Item;

#include <array>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "abilityTooltip.h"
#include "button.h"
#include "itemTooltip.h"
#include "../data/id.h"

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Item> ItemPtr;

class AbilityWindow {
public:
	AbilityWindow();

	// Updates the window. Returns false if the window is closed.
	bool Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool rightClick);

	// Renders the window to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the party and inventory reference.
	void Initialize(std::vector<ActorPtr>& p, std::vector<ItemPtr>& i);

	// Refreshes displayed items.
	void Refresh();

private:
	// UI
	sf::RectangleShape background;
	sf::Font* font;

	const unsigned int fontSize = 14;

	const int width = 850;
	const int height = 500;
	sf::Vector2f bgPos;

	ItemTooltip itemTooltip;
	bool displayItemTooltip = false;

	AbilityTooltip abilityTooltip;
	bool displayAbilityTooltip = false;

	bool abilityOnCursor = false;
	size_t abilityCursorIndex = 0;
	sf::Sprite abilityCursorSprite;

	size_t displayedActor = 0;
	size_t currentFilter = 0;
	std::vector<size_t> displayedItems;

	Button closeButton;
	std::vector<Button> actorButtons;

	std::array<sf::RectangleShape, 100> invBoxes;
	std::array<sf::Sprite, 100> invIcons;

	std::array<sf::RectangleShape, 100> learnedBoxes;
	std::array<sf::Sprite, 100> learnedIcons;
	std::vector<AbilityID> learnedAbilities;

	std::array<sf::RectangleShape, 10> eqBoxes;
	std::array<sf::Sprite, 10> eqSprites;
	std::array<bool, 10> eqSpritesToDraw;

	// Data
	std::vector<ActorPtr> players;
	std::vector<ItemPtr>* inventory;

	// Sets the icons for equipped and known abilities.
	void setEquippedAndKnownIcons();

	// Sets inventory icons.
	void setInventoryIcons();
};