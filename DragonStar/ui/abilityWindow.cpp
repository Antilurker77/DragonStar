// ==================================
//
// abilityWindow.cpp
//
// ==================================

#include "abilityWindow.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/ability.h"
#include "../data/abilityScroll.h"
#include "../data/item.h"
#include "../data/id/itemQuality.h"
#include "../entity/actor.h"
#include "../entity/player.h"

AbilityWindow::AbilityWindow() {
	// font
	font = assetManager.LoadFont(settings.Font);
	sf::Vector2f buttonSize;
	abilityTooltip.SetFont(settings.Font);

	// background
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setOutlineThickness(2.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(settings.ScreenWidth / 2 - (width / 2), settings.ScreenHeight / 2 - (height / 2));
	bgPos.x = background.getGlobalBounds().left;
	bgPos.y = background.getGlobalBounds().top;

	// close button
	closeButton.SetString("X", 16);
	buttonSize = closeButton.GetSize();
	closeButton.SetPosition(bgPos.x + width + 2 - buttonSize.x / 2, bgPos.y + buttonSize.y / 2 + 2);

	// equipped ability boxes
	for (size_t i = 0; i < eqBoxes.size(); i++) {
		eqBoxes[i].setFillColor(sf::Color(0, 0, 0, 255));
		eqBoxes[i].setOutlineThickness(1.f);
		eqBoxes[i].setOutlineColor(sf::Color(255, 255, 255, 255));
		eqBoxes[i].setSize(sf::Vector2f(32.f, 32.f));
		eqBoxes[i].setPosition(bgPos.x + 30.f + i * 38, bgPos.y + 50.f);

		eqSprites[i].setPosition(bgPos.x + 30.f + i * 38, bgPos.y + 50.f);
	}

	// learned ability boxes
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			learnedBoxes[(i * 10) + j].setFillColor(sf::Color(0, 0, 0, 255));
			learnedBoxes[(i * 10) + j].setOutlineThickness(1.f);
			learnedBoxes[(i * 10) + j].setOutlineColor(sf::Color(255, 255, 255, 255));
			learnedBoxes[(i * 10) + j].setSize(sf::Vector2f(32.f, 32.f));
			learnedBoxes[(i * 10) + j].setPosition(bgPos.x + 30.f + j * 38, bgPos.y + 100.f + i * 38);

			learnedIcons[(i * 10) + j].setPosition(bgPos.x + 30.f + j * 38, bgPos.y + 100.f + i * 38);
		}
	}

	// inventory boxes
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			invBoxes[(i * 10) + j].setFillColor(sf::Color(0, 0, 0, 255));
			invBoxes[(i * 10) + j].setOutlineThickness(1.f);
			invBoxes[(i * 10) + j].setOutlineColor(sf::Color(255, 255, 255, 255));
			invBoxes[(i * 10) + j].setSize(sf::Vector2f(32.f, 32.f));
			invBoxes[(i * 10) + j].setPosition(bgPos.x + 450.f + j * 38, bgPos.y + 100.f + i * 38);

			invIcons[(i * 10) + j].setPosition(bgPos.x + 450.f + j * 38, bgPos.y + 100.f + i * 38);
			invIcons[(i * 10) + j].setScale(2.f, 2.f);
		}
	}
}

bool AbilityWindow::Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool rightClick) {
	displayAbilityTooltip = false;
	displayItemTooltip = false;

	if (abilityOnCursor) {
		abilityCursorSprite.setPosition(mousePos.x - 16.f, mousePos.y - 16.f);
		if (leftClick) {
			for (size_t i = 0; i < eqBoxes.size(); i++) {
				if (eqBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
					Player* p = (Player*)players[displayedActor].get();
					p->EquipAbility(abilityCursorIndex, i + 1);
					setEquippedAndKnownIcons();
					break;
				}
			}
			abilityOnCursor = false;
		}
	}
	else {
		// close button
		if (closeButton.Update(secondsPerUpdate, mousePos) && leftClick) {
			return false;
		}

		// actor buttons
		for (size_t i = 0; i < actorButtons.size(); i++) {
			if (actorButtons[i].Update(secondsPerUpdate, mousePos) && leftClick) {
				displayedActor = i;
				setEquippedAndKnownIcons();
				setInventoryIcons();
			}
		}

		// equipped abilities
		for (size_t i = 0; i < eqBoxes.size(); i++) {
			if (eqSpritesToDraw[i] && eqBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				Player* p = (Player*)players[displayedActor].get();
				if (leftClick) {
					p->UnequipAbility(i + 1);
					setEquippedAndKnownIcons();
				}
				else {
					p->SetAbilitySlotUser();
					abilityTooltip.SetAbility(p->GetAbility(i + 1));
					sf::Vector2i tooltipSize = abilityTooltip.GetSize();
					sf::Vector2i tooltipPos(mousePos.x, mousePos.y - tooltipSize.y);
					abilityTooltip.SetPosition(tooltipPos, settings.ScreenWidth, settings.ScreenHeight);
					displayAbilityTooltip = true;
				}
				break;
			}
		}

		// learned abilities
		for (size_t i = 0; i < learnedAbilities.size(); i++) {
			if (learnedBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				Player* p = (Player*)players[displayedActor].get();
				if (leftClick) {
					abilityOnCursor = true;
					abilityCursorIndex = i;
					abilityCursorSprite.setTexture(*learnedIcons[i].getTexture());
					abilityCursorSprite.setPosition(mousePos.x - 16.f, mousePos.y - 16.f);
				}
				else {
					AbilityPtr a = Factory::CreateAbility(learnedAbilities[i]);
					a->SetUser(players[displayedActor]);
					abilityTooltip.SetAbility(a);
					sf::Vector2i tooltipSize = abilityTooltip.GetSize();
					sf::Vector2i tooltipPos(mousePos.x, mousePos.y - tooltipSize.y);
					abilityTooltip.SetPosition(tooltipPos, settings.ScreenWidth, settings.ScreenHeight);
					displayAbilityTooltip = true;
				}
				break;
			}
		}

		// inventory
		for (size_t i = 0; i < displayedItems.size(); i++) {
			if (i < invBoxes.size() && invBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				Player* p = (Player*)players[displayedActor].get();
				if (rightClick && p->IsLearnable(inventory->at(displayedItems[i]))) {
					p->LearnAbility(*inventory, displayedItems[i]);
					setEquippedAndKnownIcons();
					setInventoryIcons();
				}
				else {
					auto s = (AbilityScroll*)inventory->at(displayedItems[i]).get();
					AbilityPtr a = Factory::CreateAbility(s->GetAbilityID());
					a->SetUser(players[displayedActor]);
					abilityTooltip.SetAbility(a);

					itemTooltip.SetItem(inventory->at(displayedItems[i]));
					sf::Vector2f tooltipSize = itemTooltip.GetSize();
					itemTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
					displayItemTooltip = true;

					sf::Vector2i tooltipSize2 = abilityTooltip.GetSize();
					sf::Vector2i tooltipPos(mousePos.x - tooltipSize2.x, mousePos.y - tooltipSize.y);
					abilityTooltip.SetPosition(tooltipPos, settings.ScreenWidth, settings.ScreenHeight);
					displayAbilityTooltip = true;
				}
				break;
			}
		}
	}

	return true;
}

void AbilityWindow::Render(sf::RenderTarget& window) {
	window.draw(background);
	closeButton.Render(window);

	// actor buttons
	for (auto b : actorButtons) {
		b.Render(window);
	}

	// equipped ability boxes
	for (auto eb : eqBoxes) {
		window.draw(eb);
	}

	for (size_t i = 0; i < eqSprites.size(); i++) {
		if (eqSpritesToDraw[i]) {
			window.draw(eqSprites[i]);
		}
	}

	// inventory boxes
	for (size_t i = 0; i < invBoxes.size(); i++) {
		window.draw(invBoxes[i]);
	}

	for (size_t i = 0; i < displayedItems.size(); i++) {
		if (i < invIcons.size()) {
			window.draw(invIcons[i]);
		}
	}

	// learned ability boxes
	for (size_t i = 0; i < learnedBoxes.size(); i++) {
		window.draw(learnedBoxes[i]);
	}
	for (size_t i = 0; i < learnedAbilities.size(); i++) {
		if (i < learnedIcons.size()) {
			if (abilityOnCursor && i == abilityCursorIndex) {
				window.draw(abilityCursorSprite);
			}
			else {
				window.draw(learnedIcons[i]);
			}
		}
	}

	// item tooltip
	if (displayItemTooltip) {
		itemTooltip.Render(window);
	}

	// ability tooltip
	if (displayAbilityTooltip) {
		abilityTooltip.Render(window);
	}
}

void AbilityWindow::Initialize(std::vector<ActorPtr>& p, std::vector<ItemPtr>& i) {
	players = p;
	inventory = &i;
	actorButtons.clear();

	for (size_t i = 0; i < players.size(); i++) {
		Button b;
		b.SetString(players[i]->GetName(), 14);
		sf::Vector2f size = b.GetSize();
		b.SetPosition(bgPos.x + 120 * i + size.x / 2, bgPos.y - size.y / 2 - 2);
		actorButtons.push_back(b);
	}

	setEquippedAndKnownIcons();
	setInventoryIcons();
}

void AbilityWindow::Refresh() {
	setInventoryIcons();
}

void AbilityWindow::setEquippedAndKnownIcons() {
	Player* p = (Player*)players[displayedActor].get();
	std::vector<std::string> filepaths = p->GetAbilityIcons();
	learnedAbilities = p->GetLearnedAbilities();

	for (size_t i = 1; i < 11; i++) {
		if (std::empty(filepaths[i]) == false) {
			eqSprites[i - 1].setTexture(*assetManager.LoadTexture("gfx/ui/icon/ability/" + filepaths[i]));
			eqSpritesToDraw[i - 1] = true;
		}
		else {
			eqSpritesToDraw[i - 1] = false;
		}
	}

	for (size_t i = 0; i < learnedAbilities.size(); i++) {
		AbilityPtr a = Factory::CreateAbility(learnedAbilities[i]);
		learnedIcons[i].setTexture(*assetManager.LoadTexture("gfx/ui/icon/ability/" + a->GetIcon()));
	}
}

void AbilityWindow::setInventoryIcons() {
	Player* p = (Player*)players[displayedActor].get();
	displayedItems.clear();

	for (size_t i = 0; i < inventory->size(); i++){
		if (p->IsLearnable(inventory->at(i))) {
			displayedItems.push_back(i);
		}
	}

	// set sprites
	for (size_t i = 0; i < displayedItems.size(); i++) {
		if (i < invIcons.size()) {
			std::string fp = "gfx/ui/icon/small_icon/" + inventory->at(displayedItems[i])->GetIconFilepath();
			invIcons[i].setTexture(*assetManager.LoadTexture(fp));

			switch (inventory->at(displayedItems[i])->GetItemQuality()) {
			case ItemQuality::Magical:
				invIcons[i].setColor(sf::Color(30, 255, 0, 255));
				break;
			case ItemQuality::Rare:
				invIcons[i].setColor(sf::Color(0, 110, 220, 255));
				break;
			case ItemQuality::Mythic:
				invIcons[i].setColor(sf::Color(165, 55, 240, 255));
				break;
			case ItemQuality::Unique:
				invIcons[i].setColor(sf::Color(255, 130, 0, 255));
				break;
			case ItemQuality::Relic:
				invIcons[i].setColor(sf::Color(230, 0, 0, 255));
				break;
			default:
				invIcons[i].setColor(sf::Color(255, 255, 255, 255));
				break;
			}
		}
	}
}