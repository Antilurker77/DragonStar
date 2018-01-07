// ==================================
//
// dropdown.h
//
// HUD widget for dropdown menus.
//
// ==================================

#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

template <typename T>
class Dropdown {
public:
	Dropdown();

	// Updates the menu. Returns true if the widget is currently open.
	bool Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool scrollUp, bool scrollDown);

	// Draws the widget to the screen.
	void Render(sf::RenderTarget& window);

	// Removes all items from the dropdown widget.
	void ClearOptions();

	// Adds an item to the dropdown widget.
	void AddOption(std::string name, T value);

	// Sets the length of the option box.
	void SetLength(unsigned int l);

	// Sets the position for the dropdown box.
	void SetPosition(int x, int y);

	// Returns the value of the selected option.
	T GetSelectedValue();

private:
	std::vector<std::pair<std::string, T>> options;

	bool isOpen = false;
	size_t selected = 0;
	size_t top = 0;
	size_t maxVisible = 8;
	size_t optionsToDraw = 0;
	std::vector<sf::Text> optionTexts;
	std::vector<sf::RectangleShape> optionBGs;

	sf::Font* font;
	const unsigned int fontSize = 12;
	unsigned int length = 120;
	const unsigned int height = 20;

	sf::RectangleShape selectedBG;
	sf::RectangleShape arrowBG;
	sf::Text selectedText;

	sf::RectangleShape scrollBG;
	sf::RectangleShape scrollBar;

	// Sets the texts to be displayed.
	void setTexts();

	// Updates the scroll bar.
	void updateScrollBar();
};

// ==========================================================

template <typename T>
Dropdown<T>::Dropdown() {
	font = assetManager.LoadFont(settings.Font);

	selectedBG.setFillColor(sf::Color(0, 0, 0, 255));
	selectedBG.setOutlineThickness(1.f);
	selectedBG.setOutlineColor(sf::Color(255, 255, 255, 255));
	selectedBG.setSize(sf::Vector2f(length, height));

	arrowBG.setFillColor(sf::Color(0, 0, 0, 255));
	arrowBG.setOutlineThickness(1.f);
	arrowBG.setOutlineColor(sf::Color(255, 255, 255, 255));
	arrowBG.setSize(sf::Vector2f(height, height)); // square

	selectedText.setCharacterSize(fontSize);
	selectedText.setFont(*font);

	for (size_t i = 0; i < maxVisible; i++) {
		sf::RectangleShape rect;
		rect.setFillColor(sf::Color(0, 0, 0, 255));
		rect.setOutlineThickness(1.f);
		rect.setOutlineColor(sf::Color(255, 255, 255, 255));
		rect.setSize(sf::Vector2f(length, height));
		optionBGs.push_back(rect);

		sf::Text t;
		t.setCharacterSize(fontSize);
		t.setFont(*font);
		optionTexts.push_back(t);
	}

	scrollBG.setFillColor(sf::Color(0, 0, 0, 255));
	scrollBG.setOutlineThickness(1.f);
	scrollBG.setOutlineColor(sf::Color(255, 255, 255, 255));
	scrollBG.setSize(sf::Vector2f(height, (height + 1) * maxVisible - 1));

	scrollBar.setFillColor(sf::Color(191, 191, 191, 255));
}

template <typename T>
bool Dropdown<T>::Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool scrollUp, bool scrollDown) {
	sf::Vector2f mousePosFloat(mousePos.x, mousePos.y);

	if (isOpen) {
		if (scrollUp) {
			if (top > 0) {
				top--;
				setTexts();
			}
		}
		else if (scrollDown) {
			if (top + maxVisible < options.size()) {
				top++;
				setTexts();
			}
		}
		
		bool searching = true;
		for (size_t i = 0; i < optionsToDraw; i++) {
			if (searching && optionBGs[i].getGlobalBounds().contains(mousePosFloat)) {
				optionBGs[i].setFillColor(sf::Color(255, 255, 255, 255));
				optionTexts[i].setFillColor(sf::Color(0, 0, 0, 255));
				if (leftClick) {
					selected = i + top;
					setTexts();
				}
				searching = false;
			}
			else {
				optionBGs[i].setFillColor(sf::Color(0, 0, 0, 255));
				optionTexts[i].setFillColor(sf::Color(255, 255, 255, 255));
			}
		}
		
		if (leftClick) {
			isOpen = false;
			for (size_t i = 0; i < optionsToDraw; i++) {
				optionBGs[i].setFillColor(sf::Color(0, 0, 0, 255));
				optionTexts[i].setFillColor(sf::Color(255, 255, 255, 255));
			}
		}
	}
	else {
		if (leftClick && (selectedBG.getGlobalBounds().contains(mousePosFloat) || arrowBG.getGlobalBounds().contains(mousePosFloat))) {
			isOpen = true;
			setTexts();
		}
	}

	return isOpen;
}

template <typename T>
void Dropdown<T>::Render(sf::RenderTarget& window) {
	window.draw(selectedBG);
	window.draw(selectedText);
	window.draw(arrowBG);

	if (isOpen) {
		if (options.size() > optionsToDraw) {
			window.draw(scrollBG);
			window.draw(scrollBar);
		}
		for (size_t i = 0; i < optionsToDraw; i++) {
			window.draw(optionBGs[i]);
			window.draw(optionTexts[i]);
		}
	}
}

template <typename T>
void Dropdown<T>::ClearOptions() {
	options.clear();
	selected = 0;
	top = 0;
	optionsToDraw = 0;
}

template <typename T>
void Dropdown<T>::AddOption(std::string name, T value) {
	options.push_back(std::pair<std::string, T>(name, value));

	// set as default selected if this is the first option being added
	if (options.size() == 1) {
		selectedText.setString(name);
	}
}

template <typename T>
void Dropdown<T>::SetLength(unsigned int l) {
	length = l;

	selectedBG.setSize(sf::Vector2f(length, height));

	for (size_t i = 0; i < optionBGs.size(); i++) {
		optionBGs[i].setSize(sf::Vector2f(length, height));
	}
}

template <typename T>
void Dropdown<T>::SetPosition(int x, int y) {
	selectedBG.setPosition(x, y);
	arrowBG.setPosition(x + length + 1, y);
	selectedText.setPosition(x + 3, y + 3);

	scrollBG.setPosition(x + length + 1, y + height + 1);

	for (size_t i = 0; i < optionBGs.size(); i++) {
		optionBGs[i].setPosition(x, y + ((height + 1) * (i + 1)));
		optionTexts[i].setPosition(x + 3, y + 3 + ((height + 1) * (i + 1)));
	}
}

template <typename T>
T Dropdown<T>::GetSelectedValue() {
	return options.at(selected).second;
}

template <typename T>
void Dropdown<T>::setTexts() {
	selectedText.setString(options[selected].first);
	
	optionsToDraw = 0;
	for (size_t i = top; i < top + maxVisible; i++) {
		if (i < options.size()) {
			optionTexts[optionsToDraw].setString(options[i].first);
			optionsToDraw++;
		}
	}

	updateScrollBar();
}

template <typename T>
void Dropdown<T>::updateScrollBar() {
	int maxSize = (height + 1) * maxVisible - 1 - 4;

	int h = (double)maxVisible / (double)options.size() * (double)maxSize;
	int w = height - 4;

	sf::Vector2f pos(arrowBG.getPosition());
	pos.x += 2.f;
	pos.y += (float)top / (float)options.size() * (float)maxSize;
	pos.y += height + 3.f;

	scrollBar.setSize(sf::Vector2f(w, h));
	scrollBar.setPosition(pos);
}