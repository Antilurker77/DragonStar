// ==================================
//
// auraTooltip.cpp
//
// ==================================

#include "auraTooltip.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/aura.h"
#include "../entity/actor.h"

AuraTooltip::AuraTooltip() {
	font = assetManager.LoadFont(settings.Font);

	// Background Initialization
	background.setFillColor(sf::Color(0, 0, 0, 192));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color::White);

	// Text Initialization
	nameStackSourceText.setFont(*font);
	nameStackSourceText.setCharacterSize(nameSize);

	durationText.setFont(*font);
	durationText.setCharacterSize(textSize);

	descriptionText.setFont(*font);
	descriptionText.setCharacterSize(textSize);
}

void AuraTooltip::Render(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(nameStackSourceText);
	window.draw(durationText);
	window.draw(descriptionText);
}

void AuraTooltip::SetAura(AuraPtr& aura) {

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

	// Name, Stack Count, and Source
	std::string nameStackSource;
	nameStackSource += aura->GetName();
	int stackCount = aura->GetStackCount();
	if (stackCount > 1) {
		nameStackSource += " x" + std::to_string(stackCount);
	}
	nameStackSource += " [" + aura->GetUser()->GetName() + "]";
	nameStackSourceText.setString(nameStackSource);

	// Duration
	if (aura->IsUnlimitedDuration()) {
		durationText.setString("#aaaaaa No Duration");
	}
	else {
		durationText.setString(convertToSec(aura->GetRemainingDuration()) + " Duration");
	}

	// Description
	descriptionText.setString(aura->GetDescription());

	// Set the size of the background.
	int width = std::max(descriptionText.getLocalBounds().width + 6, nameStackSourceText.getLocalBounds().width + 6);
	if (width < 200) {
		width = 200;
	}

	// extra 2 are for margins
	int height = 4;
	height += nameSize + 4;
	height += textSize + 4;
	height += descriptionText.getLocalBounds().height + 4;

	background.setSize(sf::Vector2f(width, height));
}

void AuraTooltip::SetPosition(int x, int y) {
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
	nameStackSourceText.setPosition(x + 2, y + 1);
	durationText.setPosition(x + 2, y + 5 + nameSize);
	descriptionText.setPosition(x + 2, y + 9 + nameSize + textSize);
}

sf::Vector2f AuraTooltip::GetSize() {
	return background.getSize();
}