// ==================================
//
// hpBarManager.h
//
// Manager object that displays HP
// bars for actors on the battle
// scene.
//
// ==================================

#pragma once

#include <memory>

#include <SFML\Graphics.hpp>

class Actor;

typedef std::shared_ptr<Actor> ActorPtr;

class HPBarManager {
public:
	HPBarManager();

	// Updates the length and positions of HP bars.
	void Update(std::vector<ActorPtr>& actorList);

	// Renders the HP bars to the screen.
	void Render(sf::RenderTarget& window);

private:
	sf::Texture* uiTexture;
	sf::VertexArray hpBars;
};
