// ==================================
//
// formationTooltip.h
//
// HUD element that displays
// information about a specific
// formation. Domains and map
// selections have diffent displays.
//
// ==================================

#pragma once

class MapNode;

#include <string>

#include <SFML/Graphics.hpp>

#include "richText.h"

class FormationTooltip {
public:
	FormationTooltip();

	// Renders the tooltip to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the map node to pull information from.
	void SetMapNode(MapNode& mapNode, bool domain = false);

	// Sets the position of the tooltip.
	void SetPosition(int x, int y);

	// Returns the size of the tooltip.
	sf::Vector2f GetSize();
private:
	sf::Font* font;
	const unsigned int nameSize = 14;
	const unsigned int textSize = 12;
	bool isDomain = false;

	sf::RectangleShape background;

	sfe::RichText nameText;
	sfe::RichText levelText;
	sfe::RichText monsterList;
};