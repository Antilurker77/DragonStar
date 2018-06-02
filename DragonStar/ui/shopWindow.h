// ==================================
//
// shopWindow.h
//
// Window that allows the user to
// craft new equipment or buy new
// abilities.
//
// ==================================

#pragma once

class Actor;
class Item;

enum class EquipmentID;
enum class StatModType;

#include <array>
#include <memory>
#include <vector>

#include <SFML/Graphics.hpp>

#include "button.h"
#include "dropdown.h"
#include "itemTooltip.h"
#include "richText.h"

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Item> ItemPtr;

enum class ShopTab {
	Crafting,
	Ability
};

class ShopWindow {
public:
	ShopWindow();
	
	// Updates the window. Returns false if the window is closed.
	bool Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool rightClick, bool scrollUp, bool scrollDown);

	// Renders the window to the screen.
	void Render(sf::RenderTarget& window);

	// Sets the party and inventory reference.
	void Initialize(std::vector<ActorPtr>& p, std::vector<ItemPtr>& i, unsigned int& g);

	// Updates gold display and highest available tier.
	void Refresh(unsigned int tier);

private:

	// UI
	sf::RectangleShape background;
	sf::Font* font;

	const unsigned int fontSize = 14;

	const int width = 920;
	const int height = 600;
	sf::Vector2f bgPos;

	Button craftButton;
	Button abilityButton;

	sf::RectangleShape goldBackground;
	sf::Sprite goldSprite;
	sf::Text goldText;

	ItemTooltip itemTooltip;
	bool displayTooltip = false;

	Button closeButton;

	ShopTab currentTab = ShopTab::Crafting;

	// Crafting
	sfe::RichText tierText;
	sfe::RichText baseItemText;
	sfe::RichText affixText;
	sfe::RichText craftCostText;

	Dropdown<unsigned int> tierDropdown;
	Dropdown<EquipmentID> baseItemDropdown;
	Dropdown<StatModType> affixDropdown;

	bool isDropdownOpen = false;
	bool isTierDropdownOpen = false;
	bool isBaseItemDropdownOpen = false;
	bool isAffixDropdownOpen = false;

	Button craftItemsButton;

	std::array<sf::RectangleShape, 6> craftedBoxes;
	std::array<sf::Sprite, 6> craftedIcons;
	std::array<sf::Text, 6> craftedPriceText;
	std::array<sf::Sprite, 6> craftedGoldSprite;

	unsigned int selectedTier = 1u;
	EquipmentID selecedID{};
	StatModType selectedAffix{};

	// Abilities

	// Data
	std::vector<ActorPtr> players;
	std::vector<ItemPtr>* inventory;
	unsigned int* gold;

	std::array<ItemPtr, 6> craftedItems;
	const unsigned int craftCost = 10u;

	// Crafts items based on the choosen tier, base item type, and affix.
	void craftItems();

	// Updates the base item selection.
	void updateBaseItemDropdown();

	// Updates the affix list based on the item selection.
	void updateAffixDropdown();

	// Attempts to purchase the selected item.
	void purchaseItem(size_t index);
};
