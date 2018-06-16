// ==================================
//
// messageLog.cpp
//
// ==================================

#include "messageLog.h"

#include "../core/assetManager.h"

MessageLog messageLog;

MessageLog::MessageLog() {
	texts.resize(maxMessages);

	// text options
	for (size_t i = 0; i < maxMessages; i++) {
		texts[i].setCharacterSize(12);
		//texts[i].setOutlineThickness(1.f);
	}

	// background options
	background.setFillColor(sf::Color(0, 0, 0, 191));
}

void MessageLog::Update() {

}

void MessageLog::Render(sf::RenderTarget& window) {
	float screenBottom = window.getView().getSize().y;

	background.setPosition(8.f, screenBottom - ((messages.size() - 1) * 14) - 82);
	if (messages.size() > 0) {
		window.draw(background);
	}

	for (size_t i = 0; i < messages.size(); i++) {
		texts[i].setPosition(10.f, screenBottom - ((messages.size() - 1 - i) * 14) - 80);
		window.draw(texts[i]);
	}
	
}

void MessageLog::SetFont(std::string filepath) {
	font = assetManager.LoadFont(filepath);
	for (size_t i = 0; i < maxMessages; i++) {
		texts[i].setFont(*font);
	}
}

void MessageLog::AddMessage(std::string message) {
	messages.push_back(message);

	// remove oldest messages if over cap
	while (messages.size() > maxMessages) {
		messages.pop_front();
	}

	float longestWidth = 0.f;
	for (size_t i = 0; i < messages.size(); i++) {
		texts[i].setString(messages[i]);
		float testWidth = texts[i].getLocalBounds().width;
		if (testWidth > longestWidth) {
			longestWidth = testWidth;
		}
	}
	background.setSize(sf::Vector2f(longestWidth + 4, messages.size() * 14 + 4));
}

void MessageLog::ClearLog() {
	messages.clear();
	
	for (size_t i = 0; i < texts.size(); i++) {
		texts[i].setString("");
	}
}