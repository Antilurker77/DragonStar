// ==================================
//
// button.cpp
//
// ==================================

#include "button.h"

#include "../core/assetManager.h"
#include "../core/settings.h"

Button::Button() {
	
	// Background Setup
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	// Text Setup
	font = assetManager.LoadFont(settings.Font);

	buttonText.setFont(*font);
	buttonText.setCharacterSize(20);
}

bool Button::Update(float secondsPerUpdate, sf::Vector2i mousePos) {
	bool contained = false;

	if (background.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
		contained = true;
		background.setFillColor(sf::Color(255, 255, 255, 255));
		buttonText.setFillColor(sf::Color(0, 0, 0, 255));
	}
	else {
		background.setFillColor(sf::Color(0, 0, 0, 255));
		buttonText.setFillColor(sf::Color(255, 255, 255, 255));
	}

	return contained;
}

void Button::Render(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(buttonText);
}

void Button::SetString(std::string s) {
	buttonText.setString(s);
	calcSize();
}

void Button::SetString(std::string s, unsigned int fontSize) {
	buttonText.setString(s);
	buttonText.setCharacterSize(fontSize);
	calcSize();
}

void Button::SetPosition(sf::Vector2i pos) {
	SetPosition(pos.x, pos.y);
}

void Button::SetPosition(int x, int y) {
	sf::Vector2f size = background.getSize();
	x -= size.x / 2;
	y -= size.y / 2;
	background.setPosition(x, y);
	buttonText.setPosition(x + margin, y + margin - (buttonText.getCharacterSize() / 4));
}

sf::Vector2f Button::GetSize() {
	return background.getSize();
}

void Button::calcSize() {
	auto size = buttonText.getLocalBounds();
	background.setSize(sf::Vector2f(size.width + (margin * 2), size.height + (margin * 2)));
}
