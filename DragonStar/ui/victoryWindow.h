// ==================================
//
// victoryWindow.h
//
// Window that shows EXP, gold, and
// equipment from winning a battle.
//
// ==================================

#pragma once

class Actor;
class Item;

#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "itemTooltip.h"
#include "richText.h"

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Item> ItemPtr;

class VictoryWindow {
public:
	VictoryWindow();

	// Initializes the values for the window.
	void Initialize(unsigned int xp, unsigned int gold, std::vector<ItemPtr>& items, std::vector<ActorPtr>& players);

	// Updates the window. Checks to display item tooltips.
	void Update(float secondsPerUpdate, sf::Vector2i mousePos);

	// Renders the window.
	void Render(sf::RenderTarget& window, float timeRatio);

private:
	sf::RectangleShape background;
	sf::Font* font;
	const unsigned int fontSize = 14;

	sfe::RichText expText;
	sfe::RichText goldText;
	sfe::RichText actorXPText;
	std::vector<sfe::RichText> itemText;
	std::vector<sf::Sprite> itemIcons;

	std::vector<ItemPtr> itemsAwared;
	ItemTooltip itemTooltip;
	bool displayItemTooltip;
};