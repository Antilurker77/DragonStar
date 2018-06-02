// ==================================
//
// equipWindow.cpp
//
// ==================================

#include "equipWindow.h"

#include <iomanip>
#include <sstream>

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/equipment.h"
#include "../data/item.h"
#include "../data/id/category.h"
#include "../data/id/element.h"
#include "../data/id/equipType.h"
#include "../data/id/itemQuality.h"
#include "../entity/actor.h"
#include "../entity/player.h"

EquipWindow::EquipWindow() {
	currentFilter = 0;
	
	// font
	font = assetManager.LoadFont(settings.Font);

	// background
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setOutlineThickness(2.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(settings.ScreenWidth / 2 - (width / 2), settings.ScreenHeight / 2 - (height / 2));
	bgPos.x = background.getGlobalBounds().left;
	bgPos.y = background.getGlobalBounds().top;

	// close button
	sf::Vector2f buttonSize;
	closeButton.SetString("X", 16);
	buttonSize = closeButton.GetSize();
	closeButton.SetPosition(bgPos.x + width + 2 - buttonSize.x / 2, bgPos.y + buttonSize.y / 2 + 2);

	// equipped boxes
	for (size_t i = 0; i < eqBoxes.size(); i++) {
		eqBoxes[i].setFillColor(sf::Color(0, 0, 0, 255));
		eqBoxes[i].setOutlineThickness(1.f);
		eqBoxes[i].setOutlineColor(sf::Color(255, 255, 255, 255));
		eqBoxes[i].setSize(sf::Vector2f(32.f, 32.f));
	}
	eqBoxes[0].setPosition(bgPos.x + 292, bgPos.y + 220);
	eqBoxes[1].setPosition(bgPos.x + 332, bgPos.y + 220);

	eqBoxes[2].setPosition(bgPos.x + 250, bgPos.y + 80);
	eqBoxes[4].setPosition(bgPos.x + 250, bgPos.y + 120);
	eqBoxes[5].setPosition(bgPos.x + 250, bgPos.y + 160);
	eqBoxes[8].setPosition(bgPos.x + 250, bgPos.y + 200);

	eqBoxes[3].setPosition(bgPos.x + 374, bgPos.y + 80);
	eqBoxes[6].setPosition(bgPos.x + 374, bgPos.y + 120);
	eqBoxes[7].setPosition(bgPos.x + 374, bgPos.y + 160);
	eqBoxes[9].setPosition(bgPos.x + 374, bgPos.y + 200);

	// sprites
	for (size_t i = 0; i < eqSprites.size(); i++) {
		eqSprites[i].setScale(2.f, 2.f);
	}
	eqSprites[0].setPosition(bgPos.x + 292, bgPos.y + 220);
	eqSprites[1].setPosition(bgPos.x + 332, bgPos.y + 220);

	eqSprites[2].setPosition(bgPos.x + 250, bgPos.y + 80);
	eqSprites[4].setPosition(bgPos.x + 250, bgPos.y + 120);
	eqSprites[5].setPosition(bgPos.x + 250, bgPos.y + 160);
	eqSprites[8].setPosition(bgPos.x + 250, bgPos.y + 200);

	eqSprites[3].setPosition(bgPos.x + 374, bgPos.y + 80);
	eqSprites[6].setPosition(bgPos.x + 374, bgPos.y + 120);
	eqSprites[7].setPosition(bgPos.x + 374, bgPos.y + 160);
	eqSprites[9].setPosition(bgPos.x + 374, bgPos.y + 200);

	itemCursorSprite.setScale(2.f, 2.f);

	// inventory sort icons
	for (size_t i = 0; i < 10; i++) {
		invSortIcons[i].setPosition(bgPos.x + 500.f + i * 38, bgPos.y + 72.f);
		invSortIcons[i].setScale(2.f, 2.f);
		invSortIcons[i].setColor(sf::Color(128, 128, 128, 255));
	}

	for (size_t i = 10; i < invSortIcons.size(); i++) {
		invSortIcons[i].setPosition(bgPos.x + 500.f + (i - 10) * 38, bgPos.y + 110.f);
		invSortIcons[i].setScale(2.f, 2.f);
		invSortIcons[i].setColor(sf::Color(128, 128, 128, 255));
	}

	invSortIcons[0].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/sword.png"));
	invSortIcons[1].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/axe.png"));
	invSortIcons[2].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/mace.png"));
	invSortIcons[3].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/dagger.png"));
	invSortIcons[4].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/spear.png"));
	invSortIcons[5].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/longbow.png"));
	invSortIcons[6].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/wand.png"));
	invSortIcons[7].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/staff.png"));
	invSortIcons[8].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/shield.png"));
	invSortIcons[9].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/off_hand.png"));
	invSortIcons[10].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/head.png"));
	invSortIcons[11].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/body.png"));
	invSortIcons[12].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/hands.png"));
	invSortIcons[13].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/feet.png"));
	invSortIcons[14].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/neck.png"));
	invSortIcons[15].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/ring.png"));
	invSortIcons[16].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/trinket.png"));


	// inventory boxes
	for (size_t i = 0; i < 10; i++) {
		for (size_t j = 0; j < 10; j++) {
			invBoxes[(i * 10) + j].setFillColor(sf::Color(0, 0, 0, 255));
			invBoxes[(i * 10) + j].setOutlineThickness(1.f);
			invBoxes[(i * 10) + j].setOutlineColor(sf::Color(255, 255, 255, 255));
			invBoxes[(i * 10) + j].setSize(sf::Vector2f(32.f, 32.f));			
			invBoxes[(i * 10) + j].setPosition(bgPos.x + 500.f + j * 38, bgPos.y + 150.f + i * 38);

			invIcons[(i * 10) + j].setPosition(bgPos.x + 500.f + j * 38, bgPos.y + 150.f + i * 38);
			invIcons[(i * 10) + j].setScale(2.f, 2.f);
		}
	}

	// stat text
	hpText.setFont(*font);
	hpText.setCharacterSize(fontSize);
	hpText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 270.f));

	mpText.setFont(*font);
	mpText.setCharacterSize(fontSize);
	mpText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 290.f));

	spText.setFont(*font);
	spText.setCharacterSize(fontSize);
	spText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 310.f));

	strText.setFont(*font);
	strText.setCharacterSize(fontSize);
	strText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 350.f));

	dexText.setFont(*font);
	dexText.setCharacterSize(fontSize);
	dexText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 370.f));

	intText.setFont(*font);
	intText.setCharacterSize(fontSize);
	intText.setPosition(sf::Vector2f(bgPos.x + 350.f, bgPos.y + 350.f));

	wisText.setFont(*font);
	wisText.setCharacterSize(fontSize);
	wisText.setPosition(sf::Vector2f(bgPos.x + 350.f, bgPos.y + 370.f));

	vitText.setFont(*font);
	vitText.setCharacterSize(fontSize);
	vitText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 390.f));

	armorText.setFont(*font);
	armorText.setCharacterSize(fontSize);
	armorText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 430.f));

	blockText.setFont(*font);
	blockText.setCharacterSize(fontSize);
	blockText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 450.f));

	dodgeText.setFont(*font);
	dodgeText.setCharacterSize(fontSize);
	dodgeText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 470.f));

	mainHandText.setFont(*font);
	mainHandText.setCharacterSize(fontSize);
	mainHandText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 510.f));

	offHandText.setFont(*font);
	offHandText.setCharacterSize(fontSize);
	offHandText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 530.f));

	hitText.setFont(*font);
	hitText.setCharacterSize(fontSize);
	hitText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 550.f));

	attackSpeedText.setFont(*font);
	attackSpeedText.setCharacterSize(fontSize);
	attackSpeedText.setPosition(sf::Vector2f(bgPos.x + 260.f, bgPos.y + 570.f));

	critText.setFont(*font);
	critText.setCharacterSize(fontSize);
	critText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 270.f));

	critDamageText.setFont(*font);
	critDamageText.setCharacterSize(fontSize);
	critDamageText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 290.f));

	hasteText.setFont(*font);
	hasteText.setCharacterSize(fontSize);
	hasteText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 310.f));

	doubleStrikeText.setFont(*font);
	doubleStrikeText.setCharacterSize(fontSize);
	doubleStrikeText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 330.f));

	armorPenText.setFont(*font);
	armorPenText.setCharacterSize(fontSize);
	armorPenText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 350.f));

	mpCostReductionText.setFont(*font);
	mpCostReductionText.setCharacterSize(fontSize);
	mpCostReductionText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 390.f));

	spCostReductionText.setFont(*font);
	spCostReductionText.setCharacterSize(fontSize);
	spCostReductionText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 410.f));

	cooldownReductionText.setFont(*font);
	cooldownReductionText.setCharacterSize(fontSize);
	cooldownReductionText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 430.f));

	hpLeechText.setFont(*font);
	hpLeechText.setCharacterSize(fontSize);
	hpLeechText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 470.f));

	mpLeechText.setFont(*font);
	mpLeechText.setCharacterSize(fontSize);
	mpLeechText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 490.f));

	movementSpeedText.setFont(*font);
	movementSpeedText.setCharacterSize(fontSize);
	movementSpeedText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 530.f));

	goldFindText.setFont(*font);
	goldFindText.setCharacterSize(fontSize);
	goldFindText.setPosition(sf::Vector2f(bgPos.x + 10.f, bgPos.y + 550.f));
}

bool EquipWindow::Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool rightClick) {
	displayTooltip = false;

	if (itemOnCursor) {
		itemCursorSprite.setPosition(mousePos.x - 16.f, mousePos.y - 16.f);
		if (leftClick) {
			for (size_t i = 0; i < eqBoxes.size(); i++) {
				if (eqBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
					Player* p = (Player*)players[displayedActor].get();
					p->Equip(*inventory, itemCursorIndex, i);
					setEquippedIcons();
					setDisplayedItems(currentFilter);
					setStatTexts();
					break;
				}
			}
			itemOnCursor = false;
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
				setEquippedIcons();
				setStatTexts();
			}
		}

		// filters
		for (size_t i = 0; i < invSortIcons.size(); i++) {
			if (leftClick && invSortIcons[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				currentFilter = i;
				setDisplayedItems(i);
				break;
			}
		}

		// equipped item tooltips
		for (size_t i = 0; i < eqBoxes.size(); i++) {
			if (eqSpritesToDraw[i] && eqBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				Player* p = (Player*)players[displayedActor].get();
				if (leftClick) {
					p->Unequip(*inventory, i);
					setEquippedIcons();
					setDisplayedItems(currentFilter);
					setStatTexts();
				}
				else {
					itemTooltip.SetItem(p->GetEquipment(i));
					sf::Vector2f tooltipSize = itemTooltip.GetSize();
					itemTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
					displayTooltip = true;
				}
				break;
			}
		}

		// inv tooltips
		for (size_t i = 0; i < displayedItems.size(); i++) {
			if (i < invBoxes.size() && invBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				if (leftClick) {
					itemOnCursor = true;
					itemCursorIndex = displayedItems[i];
					itemCursorSprite.setColor(invIcons[i].getColor());
					itemCursorSprite.setTexture(*invIcons[i].getTexture());
					itemCursorSprite.setPosition(mousePos.x - 16.f, mousePos.y - 16.f);
				}
				else {
					itemTooltip.SetItem(inventory->at(displayedItems[i]));
					sf::Vector2f tooltipSize = itemTooltip.GetSize();
					itemTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
					displayTooltip = true;
				}
				break;
			}
		}
	}
	return true;
}

void EquipWindow::Render(sf::RenderTarget& window) {
	window.draw(background);
	closeButton.Render(window);

	players[displayedActor]->Draw(window, sf::Vector2f(bgPos.x + 264, bgPos.y + 84), 2.f);

	for (auto b : actorButtons) {
		b.Render(window);
	}

	for (auto eb : eqBoxes) {
		window.draw(eb);
	}

	for (size_t i = 0; i < eqSprites.size(); i++) {
		if (eqSpritesToDraw[i]) {
			window.draw(eqSprites[i]);
		}
	}

	for (size_t i = 0; i < invSortIcons.size(); i++) {
		window.draw(invSortIcons[i]);
	}

	for (size_t i = 0; i < 100; i++) {
		window.draw(invBoxes[i]);
	}

	// Stat Texts
	window.draw(hpText);
	window.draw(mpText);
	window.draw(spText);

	window.draw(strText);
	window.draw(dexText);
	window.draw(intText);
	window.draw(wisText);
	window.draw(vitText);

	window.draw(armorText);
	window.draw(blockText);
	window.draw(dodgeText);

	window.draw(mainHandText);
	window.draw(offHandText);
	window.draw(hitText);
	window.draw(attackSpeedText);

	window.draw(critText);
	window.draw(critDamageText);
	window.draw(hasteText);
	window.draw(doubleStrikeText);
	window.draw(armorPenText);

	window.draw(mpCostReductionText);
	window.draw(spCostReductionText);
	window.draw(cooldownReductionText);

	window.draw(hpLeechText);
	window.draw(mpLeechText);

	window.draw(movementSpeedText);
	window.draw(goldFindText);

	// Inventory and Item on Cursor
	for (size_t i = 0; i < displayedItems.size(); i++) {
		if (i < invIcons.size()) {
			if (itemOnCursor && displayedItems[i] == itemCursorIndex) {
				window.draw(itemCursorSprite);
			}
			else {
				window.draw(invIcons[i]);
			}
		}
	}

	// Tooltip
	if (displayTooltip) {
		itemTooltip.Render(window);
	}
}

void EquipWindow::Initialize(std::vector<ActorPtr>& p, std::vector<ItemPtr>& i) {
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

	setEquippedIcons();
	setDisplayedItems(0);
	setStatTexts();
}

void EquipWindow::Refresh() {
	setDisplayedItems(currentFilter);
}

void EquipWindow::setEquippedIcons() {
	Player* p = (Player*)players[displayedActor].get();
	auto equipment = p->GetAllEquipment();

	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			sf::Texture* texture = assetManager.LoadTexture("gfx/ui/icon/small_icon/" + equipment[i]->GetIconFilepath());
			eqSprites[i].setTexture(*texture);
			eqSpritesToDraw[i] = true;

			switch (equipment[i]->GetItemQuality()) {
			case ItemQuality::Magical:
				eqSprites[i].setColor(sf::Color(30, 255, 0, 255));
				break;
			case ItemQuality::Rare:
				eqSprites[i].setColor(sf::Color(0, 110, 220, 255));
				break;
			case ItemQuality::Mythic:
				eqSprites[i].setColor(sf::Color(165, 55, 240, 255));
				break;
			case ItemQuality::Unique:
				eqSprites[i].setColor(sf::Color(255, 130, 0, 255));
				break;
			case ItemQuality::Relic:
				eqSprites[i].setColor(sf::Color(230, 0, 0, 255));
				break;
			default:
				eqSprites[i].setColor(sf::Color(255, 255, 255, 255));
				break;
			}
		}
		else {
			eqSpritesToDraw[i] = false;
		}
	}
}

void EquipWindow::setDisplayedItems(size_t filter) {
	std::vector<EquipType> typesToShow;
	displayedItems.clear();

	switch (filter) {
	case 0:
		typesToShow.push_back(EquipType::SWORD_1H);
		typesToShow.push_back(EquipType::SWORD_2H);
		break;
	case 1:
		typesToShow.push_back(EquipType::AXE_1H);
		typesToShow.push_back(EquipType::AXE_2H);
		break;
	case 2:
		typesToShow.push_back(EquipType::MACE_1H);
		typesToShow.push_back(EquipType::MACE_2H);
		break;
	case 3:
		typesToShow.push_back(EquipType::DAGGER);
		break;
	case 4:
		typesToShow.push_back(EquipType::SPEAR);
		break;
	case 5:
		typesToShow.push_back(EquipType::BOW);
		break;
	case 6:
		typesToShow.push_back(EquipType::WAND);
		break;
	case 7:
		typesToShow.push_back(EquipType::STAFF);
		break;
	case 8:
		typesToShow.push_back(EquipType::SHIELD);
		typesToShow.push_back(EquipType::BUCKLER);
		break;
	case 9:
		typesToShow.push_back(EquipType::OFF_HAND);
		break;
	case 10:
		typesToShow.push_back(EquipType::HEAVY_HEAD);
		typesToShow.push_back(EquipType::MED_HEAD);
		typesToShow.push_back(EquipType::LIGHT_HEAD);
		break;
	case 11:
		typesToShow.push_back(EquipType::HEAVY_BODY);
		typesToShow.push_back(EquipType::MED_BODY);
		typesToShow.push_back(EquipType::LIGHT_BODY);
		break;
	case 12:
		typesToShow.push_back(EquipType::HEAVY_HANDS);
		typesToShow.push_back(EquipType::MED_HANDS);
		typesToShow.push_back(EquipType::LIGHT_HANDS);
		break;
	case 13:
		typesToShow.push_back(EquipType::HEAVY_FEET);
		typesToShow.push_back(EquipType::MED_FEET);
		typesToShow.push_back(EquipType::LIGHT_FEET);
		break;
	case 14:
		typesToShow.push_back(EquipType::NECK);
		break;
	case 15:
		typesToShow.push_back(EquipType::RING);
		break;
	case 16:
		typesToShow.push_back(EquipType::TRINKET);
		break;
	default:
		break;
	}

	// set sort sprite color
	for (size_t i = 0; i < invSortIcons.size(); i++) {
		invSortIcons[i].setColor(sf::Color(128, 128, 128, 255));
	}
	invSortIcons[filter].setColor(sf::Color(255, 255, 255, 255));

	// set displayed items
	for (size_t i = 0; i < inventory->size(); i++) {
		if (inventory->at(i)->IsEquipment()) {
			Equipment* eq = (Equipment*)inventory->at(i).get();
			EquipType test = eq->GetEquipType();
			if (std::find(typesToShow.begin(), typesToShow.end(), test) != typesToShow.end()) {
				displayedItems.push_back(i);
			}
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

void EquipWindow::setStatTexts() {
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

	// rounds to decimal point
	auto convertToDec = [](double d, int decimals) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(decimals) << d;
		return ss.str();
	};
	
	// Generic EventOptions for polling stats.
	EventOptions eventOptions;
	eventOptions.Categories = { Category::ANY };
	eventOptions.Elements = { Element::NONE };

	std::string s = "";

	// HP
	s = "#aaaaaa HP #default  " + std::to_string(players[displayedActor]->GetMaxHP()) + " (+" + convertToDec(players[displayedActor]->GetHPRegen(), 1) + "/s)";
	hpText.setString(s);

	// MP
	s = "#aaaaaa MP #default  " + std::to_string(players[displayedActor]->GetMaxMP()) + " (+" + convertToDec(players[displayedActor]->GetMPRegen(), 1) + "/s)";
	mpText.setString(s);

	// SP
	s = "#aaaaaa SP #default  " + std::to_string(players[displayedActor]->GetMaxSP()) + " (+" + convertToDec(players[displayedActor]->GetSPRegen(), 1) + "/s)";
	spText.setString(s);

	// STR
	s = "#aaaaaa STR #default " + std::to_string(players[displayedActor]->GetSTR(false));
	strText.setString(s);

	// DEX
	s = "#aaaaaa DEX #default " + std::to_string(players[displayedActor]->GetDEX(false));
	dexText.setString(s);

	// INT
	s = "#aaaaaa INT #default " + std::to_string(players[displayedActor]->GetINT(false));
	intText.setString(s);

	// WIS
	s = "#aaaaaa WIS #default " + std::to_string(players[displayedActor]->GetWIS(false));
	wisText.setString(s);

	// VIT
	s = "#aaaaaa VIT #default " + std::to_string(players[displayedActor]->GetVIT(false));
	vitText.setString(s);

	// Armor
	s = "#aaaaaa Armor #default " + std::to_string((int)std::floor(players[displayedActor]->GetArmor(false)));
	armorText.setString(s);
	
	// Dodge
	double dodgeChance = players[displayedActor]->GetDodgeChance(eventOptions, false);
	dodgeChance = std::round(dodgeChance * 100);
	s = "#aaaaaa Evade Chance #default " + std::to_string((int)dodgeChance) + "%";
	dodgeText.setString(s);

	// Block
	double blockChance = players[displayedActor]->GetBlockChance(eventOptions, false);
	blockChance = std::round(blockChance * 100);
	s = "#aaaaaa Block Chance #default " + std::to_string((int)blockChance) + "%";
	blockText.setString(s);

	// Main Hand Damage
	s = "#aaaaaa Main Hand Damage #default " + std::to_string((int)players[displayedActor]->GetMainHandDamage(false));
	mainHandText.setString(s);

	// Off Hand Damage
	s = "#aaaaaa Off-Hand Damage #default " + std::to_string((int)players[displayedActor]->GetOffHandDamage(false));
	offHandText.setString(s);

	// Hit Chance
	double hitChance = players[displayedActor]->GetHitChance(eventOptions, false);
	hitChance = std::round(hitChance * 100);
	s = "#aaaaaa Hit Chance #default " + std::to_string((int)hitChance) + "%";
	hitText.setString(s);

	// Attack Speed
	int attackSpeed = players[displayedActor]->GetAttackSpeed();
	s = "#aaaaaa Attack Speed #default " + convertToSec(attackSpeed);
	attackSpeedText.setString(s);

	// Crit Chance
	double critChance = players[displayedActor]->GetCritChance(eventOptions, false);
	critChance = std::round(critChance * 100);
	s = "#aaaaaa Critical Strike Chance #default " + std::to_string((int)critChance) + "%";
	critText.setString(s);

	// Crit Damage
	double critDamage = players[displayedActor]->GetCritDamage(eventOptions, false);
	critDamage = std::round(critDamage * 100);
	s = "#aaaaaa Critical Strike Damage #default " + std::to_string((int)critDamage) + "%";
	critDamageText.setString(s);

	// Haste
	double haste = players[displayedActor]->GetHaste(eventOptions, false);
	haste = std::round((haste - 1.0) * 100);
	s = "#aaaaaa Haste #default " + std::to_string((int)haste) + "%";
	hasteText.setString(s);

	// Double Strike Chance
	double doubleStrikeChance = players[displayedActor]->GetDoubleStrikeChance(eventOptions, false);
	doubleStrikeChance = std::round(doubleStrikeChance * 100);
	s = "#aaaaaa Double Strike Chance #default " + std::to_string((int)doubleStrikeChance) + "%";
	doubleStrikeText.setString(s);

	// Armor Penetration
	double armorPen = players[displayedActor]->GetArmorPen(eventOptions, false);
	armorPen = std::round(armorPen * 100);
	s = "#aaaaaa Armor Penetration #default " + std::to_string((int)armorPen) + "%";
	armorPenText.setString(s);

	// MP Cost Reduction
	double mpCostReduction = players[displayedActor]->GetMPCostReduction(eventOptions, false);
	mpCostReduction = std::round(mpCostReduction * 100);
	s = "#aaaaaa MP Cost Reduction #default " + std::to_string((int)mpCostReduction) + "%";
	mpCostReductionText.setString(s);

	// SP Cost Reduction
	double spCostReduction = players[displayedActor]->GetSPCostReduction(eventOptions, false);
	spCostReduction = std::round(spCostReduction * 100);
	s = "#aaaaaa SP Cost Reduction #default " + std::to_string((int)spCostReduction) + "%";
	spCostReductionText.setString(s);

	// Cooldown Reduction
	double cooldownReduction = players[displayedActor]->GetCooldownReduction(eventOptions, false);
	cooldownReduction = std::round(cooldownReduction * 100);
	s = "#aaaaaa Cooldown Reduction #default " + std::to_string((int)cooldownReduction) + "%";
	cooldownReductionText.setString(s);

	// HP Leech
	double hpLeech = players[displayedActor]->GetHPLeech(eventOptions, false);
	hpLeech = std::round(hpLeech * 100);
	s = "#aaaaaa Life Leech #default " + std::to_string((int)hpLeech) + "%";
	hpLeechText.setString(s);

	// MP Leech
	double mpLeech = players[displayedActor]->GetMPLeech(eventOptions, false);
	mpLeech = std::round(mpLeech * 100);
	s = "#aaaaaa Mana Leech #default " + std::to_string((int)mpLeech) + "%";
	mpLeechText.setString(s);

	// Movement Speed
	int movementSpeed = players[displayedActor]->GetMoveSpeed();
	s = "#aaaaaa Movement Speed #default " + convertToSec(movementSpeed);
	movementSpeedText.setString(s);

	// Gold Find
	double goldFind = players[displayedActor]->GetGoldFind(false);
	goldFind = std::round(goldFind * 100);
	s = "#aaaaaa Gold Find #default " + std::to_string((int)goldFind) + "%";
	goldFindText.setString(s);
}