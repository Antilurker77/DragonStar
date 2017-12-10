// ==================================
//
// messageLog.h
//
// Message log in corner of screen.
// Singleton.
//
// ==================================

#pragma once

#include <deque>
#include <vector>
#include <SFML/Graphics.hpp>

class MessageLog {
public:
	MessageLog();

	void Update();
	void Render(sf::RenderTarget& window);

	// Sets the font that should be used.
	void SetFont(std::string filepath);

	// Adds a message to the log.
	void AddMessage(std::string message);

	// Clears all messages in the log.
	void ClearLog();

private:
	const size_t maxMessages = 16;
	sf::Font* font;
	
	std::deque<std::string> messages;
	std::vector<sf::Text> texts;

	sf::RectangleShape background;
};

extern MessageLog messageLog;
