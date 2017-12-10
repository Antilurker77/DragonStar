// ==================================
//
// window.h
//
// Simple class that handles window
// construction for GUI.
//
// ==================================

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Window {
public:
	Window();

	void Draw(sf::RenderTarget& w);

	void AddText(std::string s);
	void ClearText();
	void SetPosition(sf::Vector2f position);
	void SetTextColor(sf::Color c);
	void SetFont(std::string f);
	void SetFontSize(int fs);

	void SetBorderColor(sf::Color c);
	void SetBackgroundColor(sf::Color c);

private:
	sf::RectangleShape window;
	int margin;
	std::vector<sf::Text> textList;
	sf::Font* font;
	sf::Color fontColor;
	int fontSize;

	void calcSize(sf::Text t);
	void setTextPosition();

	
};