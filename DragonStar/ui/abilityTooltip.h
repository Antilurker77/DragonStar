// ==================================
//
// abilityTooltip.h
//
// HUD element that displays
// information about a specific
// ability.
//
// ==================================

#pragma once

class Ability;

#include <SFML\Graphics.hpp>

#include <memory>
#include <string>
#include "richText.h"


typedef std::shared_ptr<Ability> AbilityPtr;

class AbilityTooltip {
public:
	AbilityTooltip();

	// Sets the font.
	void SetFont(std::string filepath);

	// Pulls data from the given ability.
	void SetAbility(AbilityPtr& ability);
	
	// Sets the location of the tooltip. If the tooltip would be off-screen,
	// it is automatically moved to a readable position.
	void SetPosition(int x, int y, int screenWidth, int screenHeight);

	// Sets the location of the tooltip. If the tooltip would be off-screen,
	// it is automatically moved to a readable position.
	void SetPosition(sf::Vector2i pos, int screenWidth, int screenHeight);

	// Returns the size of the tooltip.
	sf::Vector2i GetSize();

	// Draws the tooltip.
	void Render(sf::RenderTarget& window);
private:
	sf::Font* font;
	const unsigned int nameSize = 14;
	const unsigned int textSize = 12;
	
	sf::RectangleShape background;

	bool hideRange = false;
	bool hideCooldown = false;

	std::string name;
	std::string cost;
	std::string range;
	std::string castTime;
	std::string cooldown;
	std::string description;

	sfe::RichText nameText;
	sfe::RichText costText;
	sfe::RichText rangeText;
	sfe::RichText castTimeText;
	sfe::RichText cooldownText;
	sfe::RichText descriptionText;
};