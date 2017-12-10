// ==================================
//
// formationTooltip.cpp
//
// ==================================

#include "formationTooltip.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/enemyInfo.h"
#include "../data/factory.h"
#include "../data/formation.h"
#include "../scene/mapNode.h"

FormationTooltip::FormationTooltip() {
	// Background Initializtion
	background.setFillColor(sf::Color(0, 0, 0, 192));
	background.setOutlineThickness(1.f);
	background.setOutlineColor(sf::Color(255, 255, 255, 255));

	// Text Initialization
	font = assetManager.LoadFont(settings.Font);

	nameText.setFont(*font);
	nameText.setCharacterSize(nameSize);

	levelText.setFont(*font);
	levelText.setCharacterSize(textSize);

	monsterList.setFont(*font);
	monsterList.setCharacterSize(textSize);
}

void FormationTooltip::Render(sf::RenderTarget& window) {
	window.draw(background);
	window.draw(nameText);
	window.draw(levelText);
	if (!isDomain) {
		window.draw(monsterList);
	}
}

void FormationTooltip::SetMapNode(MapNode& mapNode, bool domain) {
	isDomain = domain;
	Factory factory;
	FormationPtr formation = factory.CreateFormation(mapNode.FormationID);

	// Name Text
	if (isDomain) {
		nameText.setString("#relic " + formation->GetName() + "'s Domain");
	}
	else {
		std::string s;
		if (formation->IsBoss()) {
			s += "#relic ";
		}
		else if (formation->IsUnique()) {
			s += "#unique ";
		}
		else {
			s += "#rare ";
		}
		s += formation->GetName();
		nameText.setString(s);
	}

	// Level Text
	if (isDomain) {
		levelText.setString("Levels " + std::to_string(mapNode.Level) + " - " + std::to_string(mapNode.Level + 3u));
	}
	else {
		levelText.setString("Level " + std::to_string(mapNode.Level));
	}

	// Monster List Text
	monsterList.setString("");
	if (isDomain) {

	}
	else {
		auto enemies = formation->GetEnemySpawns();
		std::string enemyText;
		for (auto e : enemies) {
			std::string s;
			auto ePtr = factory.CreateEnemyInfo(std::get<0>(e));
			if (ePtr->IsBoss()) {
				s += "#relic ";
			}
			else if (ePtr->IsUnique()) {
				s += "#unique ";
			}
			s += "LV " + std::to_string(std::get<1>(e) + mapNode.Level) + "  ";
			s += ePtr->GetName();
			if (ePtr->GetTitle().length() > 0) {
				s += ", " + ePtr->GetTitle();
			}
			s += "\n";
			enemyText += s;
		}
		monsterList.setString(enemyText);
	}

	// Set the size of the background.
	int width = std::max(monsterList.getLocalBounds().width + 6, nameText.getLocalBounds().width + 6);
	if (width < 200) {
		width = 200;
	}

	// extra 2 are for margins
	int height = 4;
	height += nameSize + 4;
	height += textSize + 4;

	if (!isDomain) {
		height += monsterList.getLocalBounds().height + 4;
	}

	background.setSize(sf::Vector2f(width, height));
}

void FormationTooltip::SetPosition(int x, int y) {
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
	levelText.setPosition(x + 2, y + 5 + nameSize);
	monsterList.setPosition(x + 2, y + 9 + nameSize + textSize + textSize);
}

sf::Vector2f FormationTooltip::GetSize() {
	return background.getSize();
}