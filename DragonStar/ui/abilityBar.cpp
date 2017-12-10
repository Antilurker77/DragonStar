// ==================================
//
// abilityBar.cpp
//
// ==================================

#include "abilityBar.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../entity/actor.h"

AbilityBar::AbilityBar() {
	barTexture = assetManager.LoadTexture("gfx/ui/hud/hud.png");
	bar.setTexture(*barTexture);
	bar.setTextureRect(sf::IntRect(0, 0, 458, 38));

	font = assetManager.LoadFont(settings.Font);
	abilityTooltip.SetFont(settings.Font);

	hotkeyText[0].setString("A");
	hotkeyText[1].setString("1");
	hotkeyText[2].setString("2");
	hotkeyText[3].setString("3");
	hotkeyText[4].setString("4");
	hotkeyText[5].setString("5");
	hotkeyText[6].setString("6");
	hotkeyText[7].setString("7");
	hotkeyText[8].setString("8");
	hotkeyText[9].setString("9");
	hotkeyText[10].setString("0");
	hotkeyText[11].setString("-");
	hotkeyText[12].setString("Q");

	for (size_t i = 0; i < hotkeyText.size(); i++) {
		hotkeyText[i].setFont(*font);
		hotkeyText[i].setCharacterSize(10);
		hotkeyText[i].setOutlineThickness(1.f);
		//hotkeyText[i].setFillColor(sf::Color(0, 0, 0, 255));

		// set cooldown text
		cooldownText[i].setFont(*font);
		cooldownText[i].setCharacterSize(10);
		cooldownText[i].setOutlineThickness(1.f);
		cooldownText[i].setFillColor(sf::Color(255, 0, 0, 255));
		cooldownText[i].setString("");
	}

	for (size_t i = 0; i < disabledRects.size(); i++) {
		disabledRects[i].setFillColor(sf::Color(0, 0, 0, 0));
		disabledRects[i].setSize(sf::Vector2f(32.f, 32.f));
	}
}

void AbilityBar::SetPosition(int screenWidth, int screenHeight) {
	sf::Vector2f barPosition((screenWidth / 2) - 229.f, screenHeight - 40.f);
	bar.setPosition(barPosition);

	for (size_t i = 0; i < abilityIcons.size(); i++){
		abilityIcons[i].setPosition(barPosition.x + 3.f + (i * 35.f), barPosition.y + 3.f);
		hotkeyText[i].setPosition(barPosition.x + 26.f + (i * 35.f), barPosition.y + 3.f);
		disabledRects[i].setPosition(barPosition.x + 3.f + (i * 35.f), barPosition.y + 3.f);
		cooldownText[i].setPosition(barPosition.x + 4.f + (i * 35.f), barPosition.y + 23.f);
	}

	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void AbilityBar::SetIcons(ActorPtr& player) {
	std::vector<std::string> filepaths = player->GetAbilityIcons();
	iconTextures.fill(nullptr);

	for (size_t i = 0; i < filepaths.size(); i++) {
		if (std::empty(filepaths[i]) == false) {
			iconTextures[i] = assetManager.LoadTexture("gfx/ui/icon/ability/" + filepaths[i]);
			abilityIcons[i].setTexture(*iconTextures[i]);
			if (player->IsAbilityAvailable(i) == false) {
				disabledRects[i].setFillColor(sf::Color(0, 0, 0, 191));
				int cooldown = player->GetAbility(i)->GetCurrentCooldown();
				// cooldown text
				if (cooldown > 0) {
					std::string s;
					if (cooldown > 999) {
						s = std::to_string(cooldown / 100) + "s";
					}
					else {
						// super hacky way to make sure it always shows two digits
						std::string remainder = std::to_string(cooldown % 100);
						if (remainder.length() == 1) {
							remainder = "0" + remainder;
						}

						s = std::to_string(cooldown / 100) + "." + remainder + "s";
					}
					cooldownText[i].setString(s);
				}
				else {
					cooldownText[i].setString("");
				}
			}
			else {
				disabledRects[i].setFillColor(sf::Color(0, 0, 0, 0));
				cooldownText[i].setString("");
			}
		}
	}
}

void AbilityBar::Update(ActorPtr& player, sf::Vector2i mousePos) {
	for (size_t i = 0; i < abilityIcons.size(); i++) {
		if (iconTextures[i] != nullptr && abilityIcons[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
			abilityTooltip.SetAbility(player->GetAbility(i));
			sf::Vector2i tooltipSize = abilityTooltip.GetSize();
			sf::Vector2f barPosition(bar.getGlobalBounds().left, bar.getGlobalBounds().top);
			abilityTooltip.SetPosition(barPosition.x, barPosition.y - 2 - tooltipSize.y, screenWidth, screenHeight);
			displayTooltip = true;
			break;
		}

		displayTooltip = false;
	}
}

void AbilityBar::Render(sf::RenderTarget& window) {
	window.draw(bar);

	if (displayTooltip) {
		abilityTooltip.Render(window);
	}

	for (size_t i = 0; i < abilityIcons.size(); i++) {
		if (iconTextures[i] != nullptr) {
			window.draw(abilityIcons[i]);
			window.draw(disabledRects[i]);
			window.draw(hotkeyText[i]);
			window.draw(cooldownText[i]);
		}
	}
}