// ==================================
//
// equipWindow.h
//
// Window that allows the user to
// equip their characters.
//
// ==================================

#pragma once

class Actor;
class Item;

#include <array>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "itemTooltip.h"
#include "richText.h"

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Item> ItemPtr;

class EquipWindow {
public:
	EquipWindow();

	// Updates the window. Returns false if the window is closed.
	bool Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool rightClick);

	// Renders the window to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the party and inventory reference.
	void Initialize(std::vector<ActorPtr>& p, std::vector<ItemPtr>& i);

	// Refreshes inventory icons.
	void Refresh();

private:

	// UI
	sf::RectangleShape background;
	sf::Font* font;

	const unsigned int fontSize = 14;

	const int width = 1000;
	const int height = 600;
	sf::Vector2f bgPos;

	ItemTooltip itemTooltip;
	bool displayTooltip = false;

	bool itemOnCursor = false;
	size_t itemCursorIndex = 0;
	sf::Sprite itemCursorSprite;

	size_t displayedActor = 0;
	size_t currentFilter = 0;
	std::vector<size_t> displayedItems;

	Button closeButton;
	std::vector<Button> actorButtons;

	std::array<sf::Sprite, 17> invSortIcons;
	std::array<sf::RectangleShape, 100> invBoxes;
	std::array<sf::Sprite, 100> invIcons;

	std::array<sf::RectangleShape, 10> eqBoxes;
	std::array<sf::Sprite, 10> eqSprites;
	std::array<bool, 10> eqSpritesToDraw;

	// Stats
	sfe::RichText hpText;
	sfe::RichText mpText;
	sfe::RichText spText;

	sfe::RichText strText;
	sfe::RichText dexText;
	sfe::RichText intText;
	sfe::RichText wisText;
	sfe::RichText vitText;

	sfe::RichText armorText;
	sfe::RichText blockText;
	sfe::RichText dodgeText;

	sfe::RichText mainHandText;
	sfe::RichText offHandText;
	sfe::RichText hitText;
	sfe::RichText attackSpeedText;

	sfe::RichText critText;
	sfe::RichText critDamageText;
	sfe::RichText hasteText;
	sfe::RichText doubleStrikeText;
	sfe::RichText armorPenText;

	sfe::RichText mpCostReductionText;
	sfe::RichText spCostReductionText;
	sfe::RichText cooldownReductionText;

	sfe::RichText hpLeechText;
	sfe::RichText mpLeechText;

	sfe::RichText movementSpeedText;
	sfe::RichText goldFindText;

	// Data
	std::vector<ActorPtr> players;
	std::vector<ItemPtr>* inventory;
	
	// Sets equipped item icons.
	void setEquippedIcons();

	// Sets which inventory items will be displayed based on the choosen filter.
	void setDisplayedItems(size_t filter);

	// Sets the stat text for the currently displayed actor.
	void setStatTexts();
};
