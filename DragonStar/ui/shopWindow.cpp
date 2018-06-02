// ==================================
//
// shopWindow.cpp
//
// ==================================

#include "shopWindow.h"

#include <iomanip>
#include <sstream>

#include "../core/assetManager.h"
#include "../core/random.h"
#include "../core/settings.h"
#include "../data/dataString.h"
#include "../data/equipment.h"
#include "../data/factory.h"
#include "../data/item.h"
#include "../data/id/equipmentID.h"
#include "../data/id/itemQuality.h"
#include "../entity/actor.h"
#include "../entity/player.h"

ShopWindow::ShopWindow() {
	// font
	font = assetManager.LoadFont(settings.Font);

	// background
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setOutlineThickness(2.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));
	background.setSize(sf::Vector2f(width, height));
	background.setPosition(settings.ScreenWidth / 2 - (width / 2) + 80, settings.ScreenHeight / 2 - (height / 2));
	bgPos.x = background.getGlobalBounds().left;
	bgPos.y = background.getGlobalBounds().top;

	// close button
	sf::Vector2f buttonSize;
	closeButton.SetString("X", 16);
	buttonSize = closeButton.GetSize();
	closeButton.SetPosition(bgPos.x + width + 2 - buttonSize.x / 2, bgPos.y + buttonSize.y / 2 + 2);

	// side buttons
	craftButton.SetString("Buy Equipment");
	buttonSize = craftButton.GetSize();
	craftButton.SetPosition(bgPos.x - buttonSize.x / 2 - 10, bgPos.y + buttonSize.y / 2 + 1);

	abilityButton.SetString("Buy Abilities");
	buttonSize = abilityButton.GetSize();
	abilityButton.SetPosition(bgPos.x - buttonSize.x / 2 - 10, bgPos.y + buttonSize.y + buttonSize.y / 2 + 10 + 1);

	// 185 52
	sf::Vector2f goldBGPos;
	goldBackground.setFillColor(sf::Color(0, 0, 0, 255));
	goldBackground.setOutlineThickness(1.f);
	goldBackground.setOutlineColor(sf::Color(255, 255, 255, 255));
	goldBackground.setSize(sf::Vector2f(185.f, 24.f));
	goldBackground.setPosition(bgPos.x - 184 - 12, bgPos.y + (52 * 2) + (52 / 2) + 30 + 1);
	goldBGPos.x = goldBackground.getGlobalBounds().left;
	goldBGPos.y = goldBackground.getGlobalBounds().top;

	goldSprite.setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/gold.png"));
	goldSprite.setPosition(goldBGPos.x + 2.f, goldBGPos.y + 5.f);

	goldText.setFont(*font);
	goldText.setCharacterSize(14);
	goldText.setPosition(goldBGPos.x + 2.f + 16.f + 2.f, goldBGPos.y + 4.f);
	goldText.setString("12345678900");

	// Crafting Side
	tierText.setFont(*font);
	tierText.setCharacterSize(fontSize);
	tierText.setString("#aaaaaa Tier");
	tierText.setPosition(bgPos.x + 100.f, bgPos.y + 100.f);

	baseItemText.setFont(*font);
	baseItemText.setCharacterSize(fontSize);
	baseItemText.setString("#aaaaaa Base Item");
	baseItemText.setPosition(bgPos.x + 200.f, bgPos.y + 100.f);

	affixText.setFont(*font);
	affixText.setCharacterSize(fontSize);
	affixText.setString("#aaaaaa Affix");
	affixText.setPosition(bgPos.x + 100.f, bgPos.y + 250.f);

	craftCostText.setFont(*font);
	craftCostText.setCharacterSize(fontSize);
	craftCostText.setString("#aaaaaa Costs #default " + std::to_string(craftCost));
	craftCostText.setPosition(bgPos.x + 160.f, bgPos.y + 400.f);

	craftItemsButton.SetString("Craft Items", fontSize);
	craftItemsButton.SetPosition(bgPos.x + 190, bgPos.y + 450);

	for (size_t i = 0; i < craftedBoxes.size(); i++) {
		craftedBoxes[i].setFillColor(sf::Color(0, 0, 0, 255));
		craftedBoxes[i].setOutlineThickness(1.f);
		craftedBoxes[i].setOutlineColor(sf::Color(255, 255, 255, 255));
		craftedBoxes[i].setSize(sf::Vector2f(32.f, 32.f));
		
		craftedIcons[i].setScale(2.f, 2.f);

		craftedPriceText[i].setFont(*font);
		craftedPriceText[i].setCharacterSize(fontSize);

		craftedGoldSprite[i].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/gold.png"));
	}
	craftedBoxes[0].setPosition(bgPos.x + 450.f, bgPos.y + 200.f);
	craftedIcons[0].setPosition(bgPos.x + 450.f, bgPos.y + 200.f);
	craftedPriceText[0].setPosition(bgPos.x + 463.f, bgPos.y + 234.f);
	craftedGoldSprite[0].setPosition(bgPos.x + 445.f, bgPos.y + 235.f);

	craftedBoxes[1].setPosition(bgPos.x + 600.f, bgPos.y + 200.f);
	craftedIcons[1].setPosition(bgPos.x + 600.f, bgPos.y + 200.f);
	craftedPriceText[1].setPosition(bgPos.x + 613.f, bgPos.y + 234.f);
	craftedGoldSprite[1].setPosition(bgPos.x + 595.f, bgPos.y + 235.f);

	craftedBoxes[2].setPosition(bgPos.x + 750.f, bgPos.y + 200.f);
	craftedIcons[2].setPosition(bgPos.x + 750.f, bgPos.y + 200.f);
	craftedPriceText[2].setPosition(bgPos.x + 763.f, bgPos.y + 234.f);
	craftedGoldSprite[2].setPosition(bgPos.x + 745.f, bgPos.y + 235.f);

	craftedBoxes[3].setPosition(bgPos.x + 450.f, bgPos.y + 350.f);
	craftedIcons[3].setPosition(bgPos.x + 450.f, bgPos.y + 350.f);
	craftedPriceText[3].setPosition(bgPos.x + 463.f, bgPos.y + 384.f);
	craftedGoldSprite[3].setPosition(bgPos.x + 445.f, bgPos.y + 385.f);

	craftedBoxes[4].setPosition(bgPos.x + 600.f, bgPos.y + 350.f);
	craftedIcons[4].setPosition(bgPos.x + 600.f, bgPos.y + 350.f);
	craftedPriceText[4].setPosition(bgPos.x + 613.f, bgPos.y + 384.f);
	craftedGoldSprite[4].setPosition(bgPos.x + 595.f, bgPos.y + 385.f);

	craftedBoxes[5].setPosition(bgPos.x + 750.f, bgPos.y + 350.f);
	craftedIcons[5].setPosition(bgPos.x + 750.f, bgPos.y + 350.f);
	craftedPriceText[5].setPosition(bgPos.x + 763.f, bgPos.y + 384.f);
	craftedGoldSprite[5].setPosition(bgPos.x + 745.f, bgPos.y + 385.f);

	tierDropdown.SetLength(30);
	tierDropdown.SetPosition(bgPos.x + 100.f, bgPos.y + 120.f);

	baseItemDropdown.SetLength(150);
	baseItemDropdown.SetPosition(bgPos.x + 200.f, bgPos.y + 120.f);

	affixDropdown.SetLength(200);
	affixDropdown.SetPosition(bgPos.x + 100.f, bgPos.y + 270.f);
}

bool ShopWindow::Update(float secondsPerUpdate, sf::Vector2i mousePos, bool leftClick, bool rightClick, bool scrollUp, bool scrollDown) {
	displayTooltip = false;

	// Switch to Item Crafting
	if (craftButton.Update(secondsPerUpdate, mousePos) && leftClick) {
		currentTab = ShopTab::Crafting;
	}

	// Switch to Ability Shop
	if (abilityButton.Update(secondsPerUpdate, mousePos) && leftClick) {
		currentTab = ShopTab::Ability;
		isDropdownOpen = false;
		isTierDropdownOpen = false;
		isBaseItemDropdownOpen = false;
		isAffixDropdownOpen = false;
	}

	// close button
	if (closeButton.Update(secondsPerUpdate, mousePos) && leftClick) {
		return false;
	}

	if (currentTab == ShopTab::Crafting) {				
		if (!isDropdownOpen) {
			if (craftItemsButton.Update(secondsPerUpdate, mousePos) && leftClick) {
				if (*gold >= craftCost) {
					craftItems();
					*gold -= craftCost;
					goldText.setString(std::to_string(*gold));
				}
			}

			// item tooltips and purchasing items
			for (size_t i = 0; i < craftedBoxes.size(); i++) {
				if (craftedItems[i] != nullptr && craftedBoxes[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
					if (rightClick){
						purchaseItem(i);
					}
					else {
						itemTooltip.SetItem(craftedItems[i]);
						sf::Vector2f tooltipSize = itemTooltip.GetSize();
						itemTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
						displayTooltip = true;
					}
				}
			}
		}

		if (isTierDropdownOpen || !isDropdownOpen) {
			isTierDropdownOpen = tierDropdown.Update(secondsPerUpdate, mousePos, leftClick, scrollUp, scrollDown);
			isDropdownOpen = isTierDropdownOpen;

			unsigned int checkTier = tierDropdown.GetSelectedValue();
			if (checkTier != selectedTier) {
				selectedTier = checkTier;
				updateBaseItemDropdown();
				leftClick = false; // stops accidently opening another dropdown when closed
			}
		}

		if (isBaseItemDropdownOpen || !isDropdownOpen) {
			isBaseItemDropdownOpen = baseItemDropdown.Update(secondsPerUpdate, mousePos, leftClick, scrollUp, scrollDown);
			isDropdownOpen = isBaseItemDropdownOpen;

			EquipmentID checkID = baseItemDropdown.GetSelectedValue();
			if (checkID != selecedID) {
				selecedID = checkID;
				updateAffixDropdown();
				leftClick = false; // stops accidently opening another dropdown when closed
			}
		}

		if (isAffixDropdownOpen || !isDropdownOpen) {
			isAffixDropdownOpen = affixDropdown.Update(secondsPerUpdate, mousePos, leftClick, scrollUp, scrollDown);
			isDropdownOpen = isAffixDropdownOpen;

			StatModType checkAffix = affixDropdown.GetSelectedValue();
			if (checkAffix != selectedAffix) {
				selectedAffix = checkAffix;
				leftClick = false; // stops accidently opening another dropdown when closed
			}
		}
	}
	else if (currentTab == ShopTab::Ability) {

	}

	return true;
}

void ShopWindow::Render(sf::RenderTarget& window) {
	window.draw(background);
	closeButton.Render(window);

	// Side Buttons and Gold
	craftButton.Render(window);
	abilityButton.Render(window);
	window.draw(goldBackground);
	window.draw(goldSprite);
	window.draw(goldText);

	if (currentTab == ShopTab::Crafting) {
		window.draw(tierText);
		window.draw(baseItemText);
		window.draw(affixText);
		window.draw(craftCostText);
		craftItemsButton.Render(window);

		// dropdown menus rendered bottom up
		affixDropdown.Render(window);
		tierDropdown.Render(window);
		baseItemDropdown.Render(window);

		for (size_t i = 0; i < craftedBoxes.size(); i++) {
			window.draw(craftedBoxes[i]);
			if (craftedItems[i] != nullptr) {
				window.draw(craftedIcons[i]);
				window.draw(craftedGoldSprite[i]);
				window.draw(craftedPriceText[i]);
			}
		}
	}
	else if (currentTab == ShopTab::Ability) {

	}

	// Tooltip
	if (displayTooltip) {
		itemTooltip.Render(window);
	}
}

void ShopWindow::Initialize(std::vector<ActorPtr>& p, std::vector<ItemPtr>& i, unsigned int& g) {
	players = p;
	inventory = &i;
	gold = &g;

	tierDropdown.AddOption("1", 1u);
	updateBaseItemDropdown();
	updateAffixDropdown();
}

void ShopWindow::Refresh(unsigned int tier) {
	goldText.setString(std::to_string(*gold));

	if (tier > 6) {
		tier = 6;
	}

	tierDropdown.ClearOptions();
	for (size_t i = 1; i <= tier; i++) {
		tierDropdown.AddOption(std::to_string(i), i);
	}
}

void ShopWindow::craftItems() {
	craftedItems.fill(nullptr);

	for (size_t i = 0; i < craftedItems.size(); i++) {
		ItemPtr item;
		bool generating = true;

		craftedIcons[i].setColor(sf::Color(0, 110, 220, 255));

		ItemQuality rarity = ItemQuality::Rare;
		int roll = Random::RandInt(1, 6);
		if (roll == 1) {
			rarity = ItemQuality::Magical;
			craftedIcons[i].setColor(sf::Color(30, 255, 0, 255));
		}
		else if (roll == 6) {
			rarity = ItemQuality::Mythic;
			craftedIcons[i].setColor(sf::Color(165, 55, 240, 255));
		}

		while (generating) {
			item = Factory::CreateEquipment(selecedID);
			Equipment* eq = (Equipment*)item.get();
			eq->RollStatMods(rarity, Random::RandSeed());

			if (eq->HasStatModType(selectedAffix)) {
				generating = false;
			}
		}
		craftedItems[i] = item;
		craftedIcons[i].setTexture(*assetManager.LoadTexture("gfx/ui/icon/small_icon/" + item->GetIconFilepath()));
		craftedPriceText[i].setString(std::to_string(item->GetPrice()));
	}
}

void ShopWindow::updateBaseItemDropdown() {
	baseItemDropdown.ClearOptions();

	switch (selectedTier) {
	case 1:
		baseItemDropdown.AddOption("Iron Sword", EquipmentID::IronSword);
		baseItemDropdown.AddOption("Iron Greatsword", EquipmentID::IronGreatsword);
		baseItemDropdown.AddOption("Iron Axe", EquipmentID::IronAxe);
		baseItemDropdown.AddOption("Iron Greataxe", EquipmentID::IronGreataxe);
		baseItemDropdown.AddOption("Iron Mace", EquipmentID::IronMace);
		baseItemDropdown.AddOption("Iron Greatmace", EquipmentID::IronGreatmace);
		baseItemDropdown.AddOption("Iron Dagger", EquipmentID::IronDagger);
		baseItemDropdown.AddOption("Iron Spear", EquipmentID::IronSpear);
		baseItemDropdown.AddOption("Longbow", EquipmentID::Longbow);
		baseItemDropdown.AddOption("Wooden Wand", EquipmentID::WoodenWand);
		baseItemDropdown.AddOption("Wooden Staff", EquipmentID::WoodenStaff);
		baseItemDropdown.AddOption("Iron Shield", EquipmentID::IronShield);
		baseItemDropdown.AddOption("Iron Buckler", EquipmentID::IronBuckler);
		baseItemDropdown.AddOption("Power Orb", EquipmentID::PowerOrb);
		baseItemDropdown.AddOption("Silk Hat", EquipmentID::SilkHat);
		baseItemDropdown.AddOption("Silk Robes", EquipmentID::SilkRobes);
		baseItemDropdown.AddOption("Silk Gloves", EquipmentID::SilkGloves);
		baseItemDropdown.AddOption("Silk Shoes", EquipmentID::SilkShoes);
		baseItemDropdown.AddOption("Leather Helmet", EquipmentID::LeatherHelmet);
		baseItemDropdown.AddOption("Leather Armor", EquipmentID::LeatherArmor);
		baseItemDropdown.AddOption("Leather Gloves", EquipmentID::LeatherGloves);
		baseItemDropdown.AddOption("Leather Boots", EquipmentID::LeatherBoots);
		baseItemDropdown.AddOption("Iron Helm", EquipmentID::IronHelm);
		baseItemDropdown.AddOption("Iron Armor", EquipmentID::IronArmor);
		baseItemDropdown.AddOption("Iron Gauntlets", EquipmentID::IronGauntlets);
		baseItemDropdown.AddOption("Iron Greaves", EquipmentID::IronGreaves);
		baseItemDropdown.AddOption("Silver Necklace", EquipmentID::SilverNecklace);
		baseItemDropdown.AddOption("Silver Ring", EquipmentID::SilverRing);
		break;
	case 2:
		baseItemDropdown.AddOption("Silver Necklace", EquipmentID::SilverNecklace);
		baseItemDropdown.AddOption("Silver Ring", EquipmentID::SilverRing);
		break;
	case 3:
		baseItemDropdown.AddOption("Gold Necklace", EquipmentID::GoldNecklace);
		baseItemDropdown.AddOption("Gold Ring", EquipmentID::GoldRing);
		break;
	case 4:
		baseItemDropdown.AddOption("Gold Necklace", EquipmentID::GoldNecklace);
		baseItemDropdown.AddOption("Gold Ring", EquipmentID::GoldRing);
		break;
	case 5:
		baseItemDropdown.AddOption("Dragonite Necklace", EquipmentID::DragoniteNecklace);
		baseItemDropdown.AddOption("Dragonite Ring", EquipmentID::DragoniteRing);
		break;
	case 6:
		baseItemDropdown.AddOption("Dragonite Necklace", EquipmentID::DragoniteNecklace);
		baseItemDropdown.AddOption("Dragonite Ring", EquipmentID::DragoniteRing);
		break;
	default:
		baseItemDropdown.AddOption("Silver Ring", EquipmentID::SilverRing);
		break;
	}
}

void ShopWindow::updateAffixDropdown() {
	affixDropdown.ClearOptions();
	
	ItemPtr testItem = Factory::CreateEquipment(selecedID);
	Equipment* eq = (Equipment*)testItem.get();
	auto affixes = eq->GetPossibleCraftMods();

	for (auto a : affixes) {
		affixDropdown.AddOption(DataString::StatModTypeString(a), a);
	}
}

void ShopWindow::purchaseItem(size_t index) {
	if (craftedItems[index] != nullptr) {
		auto price = craftedItems[index]->GetPrice();
		if (*gold >= price) {
			*gold -= price;
			inventory->push_back(craftedItems[index]);
			craftedItems[index].reset();
			goldText.setString(std::to_string(*gold));
		}
	}
}