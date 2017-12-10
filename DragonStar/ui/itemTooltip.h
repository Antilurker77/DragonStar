// ==================================
//
// itemTooltip.h
//
// HUD element that displays
// information about a specific
// item.
//
// ==================================

#pragma once

class Item;

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

#include "richText.h"

typedef std::shared_ptr<Item> ItemPtr;

class ItemTooltip {
public:
	ItemTooltip();

	// Renders the tooltip to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the item information to display on the tooltip.
	void SetItem(ItemPtr& item);

	// Sets the position of the tooltip.
	void SetPosition(int x, int y);

	// Returns the size of the tooltip.
	sf::Vector2f GetSize();

private:
	sf::Font* font;
	const unsigned int nameSize = 14;
	const unsigned int textSize = 12;

	sf::RectangleShape background;

	sfe::RichText nameText;
	sfe::RichText typeText;
	sfe::RichText powerText;
	sfe::RichText specialText;
	sfe::RichText affixText;

	bool isEquipment = true;
	bool isScroll = false;
};
