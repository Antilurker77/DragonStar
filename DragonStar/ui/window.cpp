// ==================================
//
// window.cpp
//
// ==================================

#include "window.h"

#include "../core/assetManager.h"

// Sets defualt values for the window. Must include a reference to the font to be used.
Window::Window(){

	// Default position.
	window.setPosition(sf::Vector2f(2, 2));

	// Default size.
	window.setSize(sf::Vector2f(8, 8));

	// Default fill color.
	window.setFillColor(sf::Color(0, 0, 0, 192));

	// Default borders.
	window.setOutlineThickness(-2.f);
	window.setOutlineColor(sf::Color(255, 255, 255));

	// Default font size.
	fontSize = 14;

	// Margin for text.
	margin = 16;

	// Default font color.
	fontColor = sf::Color(255, 255, 255);
}

// Adds text to the window. Each text object is printed on a seperate line.
void Window::AddText(std::string s){
	sf::Text text;
	text.setString(s);	
	text.setFont(*font);
	text.setCharacterSize(fontSize);
	text.setFillColor(fontColor);
	text.setOutlineColor(fontColor);
	textList.push_back(text);
	calcSize(text);
}

// Removes all text from a window.
void Window::ClearText(){
	textList.clear();
}

// Sets the window's position.
void Window::SetPosition(sf::Vector2f position){
	window.setPosition(position);
}

// Sets the window's font.
void Window::SetFont(std::string f){
	font = assetManager.LoadFont(f);
}

// Draws the window.
void Window::Draw(sf::RenderTarget& w){
	w.draw(window);

	for (sf::Text text : textList){
		w.draw(text);
	}
}

// Calculates the smallest possible size for the window.
void Window::calcSize(sf::Text t){
	sf::Vector2f windowSize;
	float textWidth = t.getLocalBounds().width;

	windowSize = window.getSize();


	// find the longest text
	if (textWidth + margin > windowSize.x){
		windowSize.x = textWidth + margin; // extra 16 is for margins
	}

	windowSize.y = textList.size() * (fontSize + 2) + margin; // 2 pixels between lines, extra 8 is for margins

	window.setSize(windowSize);
	setTextPosition();
}

// Calculates where each line of text should be drawn.
void Window::setTextPosition(){
	sf::Vector2f windowPosition = window.getPosition();
	for (size_t i = 0; i < textList.size(); i++){
		textList[i].setPosition(sf::Vector2f(windowPosition.x + margin / 2, windowPosition.y + i * (fontSize + 2) + margin / 2));
	}
}