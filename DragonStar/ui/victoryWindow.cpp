// ==================================
//
// victoryWindow.cpp
//
// ==================================

#include "victoryWindow.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/id/itemQuality.h"
#include "../entity/player.h"

VictoryWindow::VictoryWindow() {
	font = assetManager.LoadFont(settings.Font);
	
	background.setFillColor(sf::Color(0, 0, 0, 196));
	background.setOutlineThickness(2.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	// Text Initializtion
	expText.setFont(*font);
	expText.setCharacterSize(fontSize);

	goldText.setFont(*font);
	goldText.setCharacterSize(fontSize);

	actorXPText.setFont(*font);
	actorXPText.setCharacterSize(fontSize);
}

void VictoryWindow::Initialize(unsigned int xp, unsigned int gold, std::vector<ItemPtr>& items, std::vector<ActorPtr>& players) {
	expText.setString("#aaaaaa EXP #default " + std::to_string(xp));
	goldText.setString("#aaaaaa Gold #default " + std::to_string(gold));
	itemText.clear();
	itemIcons.clear();
	itemsAwared = items;

	std::string actorText;
	for (auto a : players) {
		std::string s;
		s += a->GetName();
		s += " #aaaaaa LV#default " + std::to_string(a->GetLevel());
		while (s.length() < 40) {
			s += " ";
		}
		s += std::to_string(a->GetEXP()) + "/" + std::to_string(a->GetEXPToNextLevel());
		s += "\n";
		actorText += s;
	}
	actorXPText.setString(actorText);

	for (auto e : items) {
		std::string s;

		sf::Texture* t = assetManager.LoadTexture("gfx/ui/icon/small_icon/" + e->GetIconFilepath());
		sf::Sprite icon;
		icon.setTexture(*t);

		switch (e->GetItemQuality()) {
		case ItemQuality::Magical:
			s += "#magical ";
			icon.setColor(sf::Color(30, 255, 0, 255));
			break;
		case ItemQuality::Rare:
			s += "#rare ";
			icon.setColor(sf::Color(0, 110, 220, 255));
			break;
		case ItemQuality::Mythic:
			s += "#mythic ";
			icon.setColor(sf::Color(165, 55, 240, 255));
			break;
		case ItemQuality::Unique:
			s += "#unique ";
			icon.setColor(sf::Color(255, 130, 0, 255));
			break;
		case ItemQuality::Relic:
			s += "#relic ";
			icon.setColor(sf::Color(230, 0, 0, 255));
			break;
		default:
			icon.setColor(sf::Color(255, 255, 255, 255));
			break;
		}
		s += e->GetName();

		sfe::RichText rt;
		rt.setFont(*font);
		rt.setCharacterSize(fontSize);
		rt.setString(s);

		itemText.push_back(rt);

		itemIcons.push_back(icon);
	}

	// Determine size of window and position of text.
	sf::Vector2f pos;
	sf::Vector2f size;

	size.x = std::max(actorXPText.getLocalBounds().width + 12.f, 200.f);
	size.y = fontSize + 20.f + actorXPText.getLocalBounds().height;

	if (itemText.size() > 0) {
		size.y += 14.f;
	}

	for (auto i : itemText) {
		size.y += fontSize + 2.f;
	}

	pos.x = std::round(settings.ScreenWidth / 2 - (size.x / 2));
	pos.y = std::round(settings.ScreenHeight / 2 - (size.y / 2));

	background.setPosition(pos);
	background.setSize(size);

	expText.setPosition(pos.x + 4.f + (std::round(size.x * 0.10f)), pos.y + 6.f);
	goldText.setPosition(pos.x + 4.f + (std::round(size.x * 0.55f)), pos.y + 6.f);
	actorXPText.setPosition(pos.x + 6.f, pos.y + 12.f + fontSize + fontSize);

	for (size_t i = 0; i < itemText.size(); i++) {
		itemText[i].setPosition(pos.x + 6.f + 18.f, actorXPText.getGlobalBounds().height + actorXPText.getGlobalBounds().top  + i * (fontSize + 2));
		itemIcons[i].setPosition(pos.x + 6.f, actorXPText.getGlobalBounds().height + actorXPText.getGlobalBounds().top + i * (fontSize + 2));
	}
}

void VictoryWindow::Update(float secondsPerUpdate, sf::Vector2i mousePos) {
	displayItemTooltip = false;
	
	for (size_t i = 0; i < itemText.size(); i++) {
		if (itemText[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
			itemTooltip.SetItem(itemsAwared[i]);
			sf::Vector2f tooltipSize = itemTooltip.GetSize();
			itemTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
			displayItemTooltip = true;
			break;
		}
	}

	for (size_t i = 0; i < itemIcons.size(); i++) {
		if (itemIcons[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
			itemTooltip.SetItem(itemsAwared[i]);
			sf::Vector2f tooltipSize = itemTooltip.GetSize();
			itemTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
			displayItemTooltip = true;
			break;
		}
	}
}

void VictoryWindow::Render(sf::RenderTarget& window, float timeRatio) {
	window.draw(background);
	window.draw(expText);
	window.draw(goldText);
	window.draw(actorXPText);
	for (size_t i = 0; i < itemText.size(); i++) {
		window.draw(itemIcons[i]);
		window.draw(itemText[i]);
	}
	if (displayItemTooltip) {
		itemTooltip.Render(window);
	}
}