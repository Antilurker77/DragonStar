// ==================================
//
// cursorActorHUD.cpp
//
// ==================================

#include "cursorActorHUD.h"

#include "../core/assetManager.h"
#include "../core/settings.h"
#include "../data/aura.h"

CursorActorHUD::CursorActorHUD() {
	this->font = assetManager.LoadFont(settings.Font);
	hudTexture = assetManager.LoadTexture("gfx/ui/hud/hud.png");

	actorName.setFont(*font);
	actorName.setCharacterSize(characterSize);
	actorName.setOutlineThickness(outlineThickness);
	
	actorLevel.setFont(*font);
	actorLevel.setCharacterSize(characterSize);
	actorLevel.setOutlineThickness(outlineThickness);

	hp.setFont(*font);
	hp.setCharacterSize(characterSize);
	hp.setOutlineThickness(outlineThickness);

	mp.setFont(*font);
	mp.setCharacterSize(characterSize);
	mp.setOutlineThickness(outlineThickness);

	sp.setFont(*font);
	sp.setCharacterSize(characterSize);
	sp.setOutlineThickness(outlineThickness);

	action.setFont(*font);
	action.setCharacterSize(characterSize);
	action.setOutlineThickness(outlineThickness);

	actionCost.setFont(*font);
	actionCost.setCharacterSize(characterSize);
	actionCost.setOutlineThickness(outlineThickness);
}

void CursorActorHUD::Update(ActorPtr& actor, int screenWidth, int screenHeight) {
	hasAction = false;
	actorName.setString(actor->GetName());
	actorLevel.setString("LV" + std::to_string(actor->GetLevel()));
	hp.setString(std::to_string(actor->GetCurrentHP()) + "/" + std::to_string(actor->GetMaxHP()));
	mp.setString(std::to_string(actor->GetCurrentMP()) + "/" + std::to_string(actor->GetMaxMP()));
	sp.setString(std::to_string(actor->GetCurrentSP()) + "/" + std::to_string(actor->GetMaxSP()));
	action.setString(actor->GetActionName());

	if (action.getString() != "") {
		hasAction = true;
		int exhaustion = actor->GetExhaustion();
		if (exhaustion > 999) {
			actionCost.setString(std::to_string(exhaustion / 100) + "s");
		}
		else {
			// super hacky way to make sure it always shows two digits
			std::string remainder = std::to_string(exhaustion % 100);
			if (remainder.length() == 1) {
				remainder = "0" + remainder;
			}

			actionCost.setString(std::to_string(exhaustion / 100) + "." + remainder + "s");
		}
	}


	std::vector<AuraPtr> buffs = actor->GetBuffAuras();
	std::vector<AuraPtr> debuffs = actor->GetDebuffAuras();

	auraBuffDuration.clear();
	auraBuffIcons.clear();

	auraDebuffDuration.clear();
	auraDebuffIcons.clear();

	hpBarLength = ((double)actor->GetCurrentHP() / (double)actor->GetMaxHP()) * 200;
	mpBarLength = ((double)actor->GetCurrentMP() / (double)actor->GetMaxMP()) * 200;
	spBarLength = ((double)actor->GetCurrentSP() / (double)actor->GetMaxSP()) * 200;

	// c++ doesn't like 0/0
	if (actor->GetLastActionExhaustion() > 0) {
		actionBarLength = ((double)(actor->GetLastActionExhaustion() - actor->GetExhaustion()) / (double)actor->GetLastActionExhaustion()) * 200;
	}
	else {
		actionBarLength = 0;
	}

	// create the vertex array
	hud.clear();
	hud.resize(24 + (buffs.size() * 4) + (debuffs.size() * 4));

	hud.setPrimitiveType(sf::Quads);

	int hudWidth = 296;
	int hudHeight = 66;

	// main hud piece
	sf::Vertex* quad = &hud[0];

	// 0  1
	// 3  2
	quad[0].position = sf::Vector2f(screenWidth - hudWidth - 2, 2);
	quad[1].position = sf::Vector2f(screenWidth - 2, 2);
	quad[2].position = sf::Vector2f(screenWidth - 2, hudHeight + 2);
	quad[3].position = sf::Vector2f(screenWidth - hudWidth - 2, hudHeight + 2);

	quad[0].texCoords = sf::Vector2f(0, 106);
	quad[1].texCoords = sf::Vector2f(hudWidth, 106);
	quad[2].texCoords = sf::Vector2f(hudWidth, 106 + hudHeight);
	quad[3].texCoords = sf::Vector2f(0, 106 + hudHeight);

	// hp bar
	quad = &hud[4];
	quad[0].position = sf::Vector2f(screenWidth - hudWidth - 1 - (hpBarLength - 200), 20);
	quad[1].position = sf::Vector2f(screenWidth - 97, 20);
	quad[2].position = sf::Vector2f(screenWidth - 97, 35);
	quad[3].position = sf::Vector2f(screenWidth - hudWidth - 1 - (hpBarLength - 200), 35);

	quad[0].texCoords = sf::Vector2f(0, 191);
	quad[1].texCoords = sf::Vector2f(hpBarLength, 191);
	quad[2].texCoords = sf::Vector2f(hpBarLength, 205);
	quad[3].texCoords = sf::Vector2f(0, 205);

	// mp bar
	quad = &hud[8];
	quad[0].position = sf::Vector2f(screenWidth - hudWidth - 1 - (mpBarLength - 200), 36);
	quad[1].position = sf::Vector2f(screenWidth - 97, 36);
	quad[2].position = sf::Vector2f(screenWidth - 97, 51);
	quad[3].position = sf::Vector2f(screenWidth - hudWidth - 1 - (mpBarLength - 200), 51);

	quad[0].texCoords = sf::Vector2f(0, 207);
	quad[1].texCoords = sf::Vector2f(mpBarLength, 207);
	quad[2].texCoords = sf::Vector2f(mpBarLength, 221);
	quad[3].texCoords = sf::Vector2f(0, 221);

	// sp bar
	quad = &hud[12];
	quad[0].position = sf::Vector2f(screenWidth - hudWidth - 1 - (spBarLength - 200), 52);
	quad[1].position = sf::Vector2f(screenWidth - 97, 52);
	quad[2].position = sf::Vector2f(screenWidth - 97, 67);
	quad[3].position = sf::Vector2f(screenWidth - hudWidth - 1 - (spBarLength - 200), 67);

	quad[0].texCoords = sf::Vector2f(0, 223);
	quad[1].texCoords = sf::Vector2f(spBarLength, 223);
	quad[2].texCoords = sf::Vector2f(spBarLength, 237);
	quad[3].texCoords = sf::Vector2f(0, 237);

	// only draw action bar if character isn't idle
	if (hasAction) {
		// action bar background
		quad = &hud[16];
		quad[0].position = sf::Vector2f(screenWidth - (hudWidth / 2) - 103, hudHeight + 4);
		quad[1].position = sf::Vector2f(screenWidth - (hudWidth / 2) + 99, hudHeight + 4);
		quad[2].position = sf::Vector2f(screenWidth - (hudWidth / 2) + 99, hudHeight + 22);
		quad[3].position = sf::Vector2f(screenWidth - (hudWidth / 2) - 103, hudHeight + 22);

		quad[0].texCoords = sf::Vector2f(0, 173);
		quad[1].texCoords = sf::Vector2f(202, 173);
		quad[2].texCoords = sf::Vector2f(202, 190);
		quad[3].texCoords = sf::Vector2f(0, 190);

		// action bar
		quad = &hud[20];
		quad[0].position = sf::Vector2f(screenWidth - (hudWidth / 2) - 102, hudHeight + 5);
		quad[1].position = sf::Vector2f(screenWidth - (hudWidth / 2) - 102 + actionBarLength, hudHeight + 5);
		quad[2].position = sf::Vector2f(screenWidth - (hudWidth / 2) - 102 + actionBarLength, hudHeight + 20);
		quad[3].position = sf::Vector2f(screenWidth - (hudWidth / 2) - 102, hudHeight + 20);

		quad[0].texCoords = sf::Vector2f(0, 239);
		quad[1].texCoords = sf::Vector2f(actionBarLength, 239);
		quad[2].texCoords = sf::Vector2f(actionBarLength, 253);
		quad[3].texCoords = sf::Vector2f(0, 253);
	}

	// buffs
	size_t it = 24;

	for (size_t i = 0; i < buffs.size(); i++) {
		quad = &hud[it];

		int x = screenWidth - hudWidth - ((i + 1) * 35) - 2;

		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(x, 4);
		quad[1].position = sf::Vector2f(x + 34, 4);
		quad[2].position = sf::Vector2f(x + 34, 38);
		quad[3].position = sf::Vector2f(x, 38);

		quad[0].texCoords = sf::Vector2f(297, 39);
		quad[1].texCoords = sf::Vector2f(297, 73);
		quad[2].texCoords = sf::Vector2f(331, 73);
		quad[3].texCoords = sf::Vector2f(331, 39);

		// sprite setup
		auraBuffIcons.push_back(sf::Sprite(*assetManager.LoadTexture("gfx/ui/icon/ability/" + buffs[i]->GetIcon())));
		auraBuffIcons[i].setPosition(x + 1, 5);

		// text setup
		auraBuffDuration.push_back(sf::Text());
		auraBuffDuration[i].setFont(*font);
		auraBuffDuration[i].setCharacterSize(characterSize - 2);
		auraBuffDuration[i].setOutlineThickness(outlineThickness);

		if (buffs[i]->IsUnlimitedDuration() == false) {
			int duration = buffs[i]->GetRemainingDuration();
			if (duration > 999) {
				auraBuffDuration[i].setString(std::to_string(duration / 100) + "s");
			}
			else {
				// super hacky way to make sure it always shows two digits
				std::string remainder = std::to_string(duration % 100);
				if (remainder.length() == 1) {
					remainder = "0" + remainder;
				}

				auraBuffDuration[i].setString(std::to_string(duration / 100) + "." + remainder + "s");
			}
		}
		auraBuffDuration[i].setPosition(x + 2, 26);

		it += 4;
	}

	// debuffs
	for (size_t i = 0; i < debuffs.size(); i++) {
		quad = &hud[it];

		int x = screenWidth - hudWidth - ((i + 1) * 35) - 2;

		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(x, 40);
		quad[1].position = sf::Vector2f(x + 34, 40);
		quad[2].position = sf::Vector2f(x + 34, 74);
		quad[3].position = sf::Vector2f(x, 74);

		quad[0].texCoords = sf::Vector2f(297, 74);
		quad[1].texCoords = sf::Vector2f(297, 108);
		quad[2].texCoords = sf::Vector2f(331, 108);
		quad[3].texCoords = sf::Vector2f(331, 74);

		// sprite setup
		auraDebuffIcons.push_back(sf::Sprite(*assetManager.LoadTexture("gfx/ui/icon/ability/" + debuffs[i]->GetIcon())));
		auraDebuffIcons[i].setPosition(x + 1, 41);

		// text setup
		auraDebuffDuration.push_back(sf::Text());
		auraDebuffDuration[i].setFont(*font);
		auraDebuffDuration[i].setCharacterSize(characterSize - 2);
		auraDebuffDuration[i].setOutlineThickness(outlineThickness);

		if (debuffs[i]->IsUnlimitedDuration() == false) {
			int duration = debuffs[i]->GetRemainingDuration();
			if (duration > 999) {
				auraDebuffDuration[i].setString(std::to_string(duration / 100) + "s");
			}
			else {
				// super hacky way to make sure it always shows two digits
				std::string remainder = std::to_string(duration % 100);
				if (remainder.length() == 1) {
					remainder = "0" + remainder;
				}

				auraDebuffDuration[i].setString(std::to_string(duration / 100) + "." + remainder + "s");
			}
		}
		auraDebuffDuration[i].setPosition(x + 2, 60);

		it += 4;
	}

	// text
	actorName.setPosition(screenWidth - hudWidth, 3);
	actorLevel.setPosition(screenWidth - actorLevel.getLocalBounds().width - 70, 3);
	hp.setPosition(screenWidth - hudWidth + (100 - (int)(hp.getLocalBounds().width / 2)), 20);
	mp.setPosition(screenWidth - hudWidth + (100 - (int)(mp.getLocalBounds().width / 2)), 36);
	sp.setPosition(screenWidth - hudWidth + (100 - (int)(sp.getLocalBounds().width / 2)), 52);
	action.setPosition(screenWidth - (hudWidth / 2) - 100, hudHeight + 5);
	actionCost.setPosition(screenWidth - (hudWidth / 2) + 97 - (int)actionCost.getLocalBounds().width, hudHeight + 5);
}

void CursorActorHUD::Render(sf::RenderTarget& w) {
	w.draw(hud, hudTexture);
	w.draw(actorName);
	w.draw(actorLevel);
	w.draw(hp);
	w.draw(mp);
	w.draw(sp);

	if (hasAction) {
		w.draw(action);
		w.draw(actionCost);
	}

	for (size_t i = 0; i < auraBuffIcons.size(); i++) {
		w.draw(auraBuffIcons[i]);
	}
	for (size_t i = 0; i < auraBuffDuration.size(); i++) {
		w.draw(auraBuffDuration[i]);
	}

	for (size_t i = 0; i < auraDebuffIcons.size(); i++) {
		w.draw(auraDebuffIcons[i]);
	}
	for (size_t i = 0; i < auraDebuffDuration.size(); i++) {
		w.draw(auraDebuffDuration[i]);
	}
}