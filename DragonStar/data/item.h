// ==================================
//
// item.h
//
// Base class for all items in the
// game.
//
// ==================================

#pragma once

enum class ItemQuality;

#include <memory>
#include <string>

class Item {
public:

	// Returns the name of the item.
	std::string GetName();

	// Returns the filepath of the item.
	std::string GetIconFilepath();

	// Returns the quality of the item.
	ItemQuality GetItemQuality();

	// Returns the weight of the item.
	int GetWeight();

	// Returns the tier of the item.
	unsigned int GetItemTier();

	// Returns the value of the item.
	virtual unsigned int GetPrice() = 0;

	// Returns whether or not the item is an equipment.
	virtual bool IsEquipment();

	// Returns whether or not the item is an ability scroll.
	virtual bool IsAbilityScroll();

protected:
	std::string name;
	std::string iconFilepath;
	ItemQuality itemQuality{};
	int weight;
	unsigned int tier;
};
