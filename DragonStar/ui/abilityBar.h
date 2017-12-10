// ==================================
//
// abilityBar.h
//
// HUD element that shows the
// abilities of a given actor.
//
// ==================================

#pragma once

class Actor;

#include <array>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "abilityTooltip.h"

typedef std::shared_ptr<Actor> ActorPtr;

class AbilityBar {
public:
	AbilityBar();

	// Updates the position for the ability bar based on screen size.
	void SetPosition(int screenWidth, int screenHeight);

	// Updates the icons based on the given player.
	void SetIcons(ActorPtr& player);

	// Update function. Determines if there's an ability tooltip to show.
	void Update(ActorPtr& player, sf::Vector2i mousePos);

	// Draws the bar to the screen.
	void Render(sf::RenderTarget& window);

private:
	sf::Sprite bar;
	sf::Texture* barTexture;
	sf::Font* font;

	std::array<sf::Sprite, 13> abilityIcons;
	std::array<sf::Texture*, 13> iconTextures;
	std::array<sf::Text, 13> hotkeyText;
	std::array<sf::RectangleShape, 13> disabledRects;
	std::array<sf::Text, 13> cooldownText;

	AbilityTooltip abilityTooltip;
	bool displayTooltip = false;

	int screenWidth;
	int screenHeight;
};
