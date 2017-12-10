// ==================================
//
// cursorActorHUD.h
//
// HUD that appears in upper-right
// corner when cursor is on an actor.
//
// ==================================

#pragma once

#include <memory>
#include <string>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../entity/actor.h"

class CursorActorHUD {
public:
	CursorActorHUD();

	// Configures all the sprites and text to display actor data.
	void Update(ActorPtr& actor, int screenWidth, int screenHeight);

	// Renders the HUD element in the upper-right corner.
	void Render(sf::RenderTarget& window);
private:
	const int characterSize = 12;
	const float outlineThickness = 1.f;
	
	sf::Texture* hudTexture;
	sf::Font* font;
	
	sf::VertexArray hud;

	sf::Text actorName;
	sf::Text actorLevel;

	sf::Text hp;
	int hpBarLength;

	sf::Text mp;
	int mpBarLength;

	sf::Text sp;
	int spBarLength;

	bool hasAction = false;
	sf::Text action;
	sf::Text actionCost;
	int actionBarLength;

	std::vector<sf::Sprite> auraBuffIcons;
	std::vector<sf::Text> auraBuffDuration;

	std::vector<sf::Sprite> auraDebuffIcons;
	std::vector<sf::Text> auraDebuffDuration;
};
