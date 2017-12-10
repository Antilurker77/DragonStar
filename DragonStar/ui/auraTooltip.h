// ==================================
//
// auraTooltip.h
//
// HUD element that displays
// information about a specific
// aura.
//
// ==================================

#pragma once

class Aura;

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>

#include "richText.h"

typedef std::shared_ptr<Aura> AuraPtr;

class AuraTooltip {
public:
	AuraTooltip();

	// Renders the tooltip to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the aura refernce for the tooltip.
	void SetAura(AuraPtr& aura);

	// Sets the position of the tooltip.
	void SetPosition(int x, int y);

	// Returns the size of the tooltip.
	sf::Vector2f GetSize();

private:
	sf::Font* font;
	const unsigned int nameSize = 14;
	const unsigned int textSize = 12;

	sf::RectangleShape background;

	AuraPtr aura;

	sfe::RichText nameStackSourceText;
	sfe::RichText durationText;
	sfe::RichText descriptionText;
};