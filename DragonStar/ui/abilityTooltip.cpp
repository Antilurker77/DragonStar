// ==================================
//
// abilityTooltip.cpp
//
// ==================================

#pragma once

#include "abilityTooltip.h"
#include "../core/assetManager.h"
#include "../data/ability.h"

AbilityTooltip::AbilityTooltip() {
	nameText.setCharacterSize(nameSize);
	costText.setCharacterSize(textSize);
	rangeText.setCharacterSize(textSize);
	castTimeText.setCharacterSize(textSize);
	cooldownText.setCharacterSize(textSize);
	descriptionText.setCharacterSize(textSize);

	background.setFillColor(sf::Color(0, 0, 0, 192));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));
}

void AbilityTooltip::SetFont(std::string filepath) {
	font = assetManager.LoadFont(filepath);

	nameText.setFont(*font);
	costText.setFont(*font);
	rangeText.setFont(*font);
	castTimeText.setFont(*font);
	cooldownText.setFont(*font);
	descriptionText.setFont(*font);
}

void AbilityTooltip::SetAbility(AbilityPtr& ability) {
	name = "";
	cost = "";
	range = "";
	castTime = "";
	cooldown = "";
	description = "";

	hideRange = false;
	hideCooldown = false;

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

	if (ability->IsSpell()) {
		name = "#spell ";
	}
	else {
		name = "#skill ";
	}
	name += ability->GetName();

	// Ability Cost
	int hpCost = 0;

	int mpCost = ability->GetMPCost();
	if (mpCost > 0) {
		if (hpCost > 0) {
			cost += " ";
		}
		cost += "#spell " + std::to_string(mpCost) + " MP";
	}
	int spCost = ability->GetSPCost();
	if (spCost > 0) {
		if (mpCost > 0) {
			cost += " ";
		}
		cost += "#skill " + std::to_string(spCost) + " SP";
	}

	if (cost == "") {
		cost = "#888888 No Cost";
	}

	// Range
	int abilRange = ability->GetRange();
	if (abilRange < 1) {
		hideRange = true;
	}
	else {
		range = "Range " + std::to_string(abilRange);
		if (ability->IgnoreBodyBlock() == false) {
			range += "P";
		}
	}
	

	// Cast Time
	int abilCastTime = ability->GetCastTime();
	if (abilCastTime < 0) {
		castTime = std::to_string(abilCastTime * -1) + "% Attack Speed";
	}
	else {
		castTime = convertToSec(abilCastTime);
	}

	if (ability->IsCasted()) {
		castTime += " Cast";
	}
	else {
		castTime += " Instant";
	}

	// Cooldown
	int abilCooldown = ability->GetCooldown();
	if (abilCooldown > 0) {
		cooldown = convertToSec(ability->GetCooldown()) + " Cooldown";
	}
	else {
		hideCooldown = true;
	}

	// Description
	description = ability->GetDescription();

	nameText.setString(name);
	costText.setString(cost);
	rangeText.setString(range);
	castTimeText.setString(castTime);
	cooldownText.setString(cooldown);
	descriptionText.setString(description);
}

void AbilityTooltip::SetPosition(int x, int y, int screenWidth, int screenHeight) {
	
	// first figure out how big the background box should be
	int width = descriptionText.getLocalBounds().width + 6;
	if (width < 200) {
		width = 200;
	}

	// extra 2 are for margins
	int height = 4;
	height += nameSize + 4;
	height += textSize + 4;
	height += textSize + 4;
	height += descriptionText.getLocalBounds().height + 4;

	background.setSize(sf::Vector2f(width, height));

	// keep tooltip on screen
	if (x + width > screenWidth) {
		x = screenWidth - width - 2;
	}
	if (y + height > screenHeight) {
		y = screenHeight - height - 2;
	}
	if (x - 2 < 0) {
		x = 2;
	}
	if (y - 2 < 0) {
		y = 2;
	}

	// set positions
	background.setPosition(x, y);
	nameText.setPosition(x + 2, y + 1);
	costText.setPosition(x + 2, y + 5 + nameSize);
	rangeText.setPosition(x + width - rangeText.getLocalBounds().width - 4, y + 5 + nameSize);
	castTimeText.setPosition(x + 2, y + 9 + nameSize + textSize);
	cooldownText.setPosition(x + width - cooldownText.getLocalBounds().width - 4, y + 9 + nameSize + textSize);
	descriptionText.setPosition(x + 2 , y + 13 + nameSize + textSize + textSize);

}

void AbilityTooltip::SetPosition(sf::Vector2i pos, int screenWidth, int screenHeight) {
	this->SetPosition(pos.x, pos.y, screenWidth, screenHeight);
}

sf::Vector2i AbilityTooltip::GetSize() {
	return sf::Vector2i(background.getLocalBounds().width, background.getLocalBounds().height);
}

void AbilityTooltip::Render(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(nameText);
	window.draw(costText);
	if (!hideRange) {
		window.draw(rangeText);
	}
	window.draw(castTimeText);
	if (!hideCooldown) {
		window.draw(cooldownText);
	}
	window.draw(descriptionText);
}