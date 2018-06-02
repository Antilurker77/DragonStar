// ==================================
//
// itemTooltip.cpp
//
// ==================================

#include "itemTooltip.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../core/wordWrap.h"
#include "../data/dataString.h"
#include "../data/item.h"
#include "../data/equipment.h"
#include "../data/id/itemQuality.h"

ItemTooltip::ItemTooltip() {
	// Background Initializtion
	background.setFillColor(sf::Color(0, 0, 0, 192));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	// Text Initialization
	font = assetManager.LoadFont(settings.Font);

	nameText.setFont(*font);
	nameText.setCharacterSize(nameSize);

	typeText.setFont(*font);
	typeText.setCharacterSize(textSize);

	powerText.setFont(*font);
	powerText.setCharacterSize(textSize);

	specialText.setFont(*font);
	specialText.setCharacterSize(textSize);

	affixText.setFont(*font);
	affixText.setCharacterSize(textSize);
}

void ItemTooltip::Render(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(nameText);
	window.draw(typeText);
	window.draw(powerText);
	window.draw(specialText);
	window.draw(affixText);
}

void ItemTooltip::SetItem(ItemPtr& item) {
	isEquipment = item->IsEquipment();
	isScroll = item->IsAbilityScroll();
	
	// converts seconds into string
	auto convertToSec = [](int i) {
		std::string s;
		if (i > 999) {
			s = std::to_string(i / 100) + "s";
		}
		else {
			// super hacky way to make sure it always shows two digits
			std::string remainder = std::to_string(i % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			s = std::to_string(i / 100) + "." + remainder + "s";
		}

		return s;
	};

	// Name Text
	std::string nameString = "";
	switch (item->GetItemQuality()) {
	case ItemQuality::Magical:
		nameString += "#magical ";
		break;
	case ItemQuality::Rare:
		nameString += "#rare ";
		break;
	case ItemQuality::Mythic:
		nameString += "#mythic ";
		break;
	case ItemQuality::Unique:
		nameString += "#unique ";
		break;
	case ItemQuality::Relic:
		nameString += "#relic ";
		break;
	default:
		break;
	}
	nameString += item->GetName();
	nameText.setString(nameString);

	// Type Text
	std::string typeString = "#aaaaaa Tier ";
	typeString += std::to_string(item->GetItemTier());
	typeText.setString(typeString);

	// Power, Special, and Affix Text
	std::string powerString = "";
	std::string specialString = "";
	std::string affixString = "";
	if (isEquipment) {
		Equipment* eq = (Equipment*)item.get();
		if (eq->IsWeapon()) {
			powerString += std::to_string(eq->GetEquipPower()) + " #aaaaaa ";
			powerString += DataString::ElementString(eq->GetAttackElements(), true) + " Damage";
			specialString = convertToSec(eq->GetAttackSpeed()) + " #aaaaaa Attack Speed";
		}
		else {
			powerString += std::to_string(eq->GetEquipPower()) + " #aaaaaa Armor";
		}
		auto sm = eq->GetStatMods();
		for (auto m : sm) {
			affixString += "#66ff66 " + WordWrap::WrapString(DataString::StatModString(m), 30) + "\n";
		}
		auto em = eq->GetExtraAffixStrings();
		for (auto m : em) {
			affixString += "#66ff66 >" + WordWrap::WrapString(m, 30) + "\n";
		}
	}

	// todo: better scroll implimentation
	else if (isScroll) {
		powerString = "Teaches a character this ability.";
	}

	powerText.setString(powerString);
	specialText.setString(specialString);
	affixText.setString(affixString);

	// Set the size of the background.
	int width = std::max(affixText.getLocalBounds().width + 6, nameText.getLocalBounds().width + 6);
	width = std::max((float)width, powerText.getLocalBounds().width + specialText.getLocalBounds().width + 50.f);
	if (width < 250) {
		width = 250;
	}

	// extra 2 are for margins
	int height = 4;
	height += nameSize + 4;
	height += textSize + 4;
	height += textSize + 4;

	if (isEquipment) {
		height += affixText.getLocalBounds().height + 4;
	}

	background.setSize(sf::Vector2f(width, height));
}

void ItemTooltip::SetPosition(int x, int y) {
	int width = background.getSize().x;
	int height = background.getSize().y;

	// keep tooltip on screen
	if (x + width > settings.ScreenWidth) {
		x = settings.ScreenWidth - width - 2;
	}
	if (x - 2 < 0) {
		x = 2;
	}
	if (y + height > settings.ScreenHeight) {
		y = settings.ScreenHeight - height - 2;
	}
	if (y - 2 < 0) {
		y = 2;
	}

	// set positions
	background.setPosition(x, y);
	nameText.setPosition(x + 2, y + 1);
	typeText.setPosition(x + 2, y + 5 + nameSize);
	powerText.setPosition(x + 2, y + 9 + nameSize + textSize);
	specialText.setPosition(x + width - 2 - specialText.getLocalBounds().width, y + 9 + nameSize + textSize);
	affixText.setPosition(x + 2, y + 13 + nameSize + textSize + textSize + textSize);
}

sf::Vector2f ItemTooltip::GetSize() {
	return background.getSize();
}