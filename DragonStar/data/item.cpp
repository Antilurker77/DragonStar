// ==================================
//
// item.cpp
//
// ==================================

#include "item.h"

std::string Item::GetName() {
	return name;
}

std::string Item::GetIconFilepath() {
	return iconFilepath;
}

ItemQuality Item::GetItemQuality() {
	return itemQuality;
}

int Item::GetWeight() {
	return weight;
}

unsigned int Item::GetItemTier() {
	return tier;
}

bool Item::IsEquipment() {
	return false;
}

bool Item::IsAbilityScroll() {
	return false;
}