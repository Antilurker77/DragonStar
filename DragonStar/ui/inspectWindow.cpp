// ==================================
//
// inspectWindow.cpp
//
// ==================================

#include "inspectWindow.h"

#include "../core/combat.h"
#include "../core/settings.h"
#include "../data/factory.h"
#include "../data/id/category.h"
#include "../data/id/element.h"
#include "../entity/actor.h"

InspectWindow::InspectWindow() {
	font = assetManager.LoadFont(settings.Font);

	// sets up background
	background.setOutlineThickness(2.f);
	background.setOutlineColor(sf::Color::White);
	background.setFillColor(sf::Color(0, 0, 0, 255));
	background.setSize(sf::Vector2f(width, height));

	sf::Vector2f pos;
	pos.x = (settings.ScreenWidth / 2) - (width / 2);
	pos.y = (settings.ScreenHeight / 2) - (height / 2);
	background.setPosition(pos);

	// 3px of margin for text
	pos.x += 3.f;
	pos.y += 3.f;

	// Texture Loading
	hudTexture = assetManager.LoadTexture("gfx/ui/hud/hud.png");

	resistanceIconTextures[0] = assetManager.LoadTexture("gfx/ui/icon/small_icon/physical.png");
	resistanceIconTextures[1] = assetManager.LoadTexture("gfx/ui/icon/small_icon/arcane.png");
	resistanceIconTextures[2] = assetManager.LoadTexture("gfx/ui/icon/small_icon/fire.png");
	resistanceIconTextures[3] = assetManager.LoadTexture("gfx/ui/icon/small_icon/ice.png");
	resistanceIconTextures[4] = assetManager.LoadTexture("gfx/ui/icon/small_icon/lightning.png");
	resistanceIconTextures[5] = assetManager.LoadTexture("gfx/ui/icon/small_icon/poison.png");
	resistanceIconTextures[6] = assetManager.LoadTexture("gfx/ui/icon/small_icon/water.png");
	resistanceIconTextures[7] = assetManager.LoadTexture("gfx/ui/icon/small_icon/wind.png");
	resistanceIconTextures[8] = assetManager.LoadTexture("gfx/ui/icon/small_icon/earth.png");
	resistanceIconTextures[9] = assetManager.LoadTexture("gfx/ui/icon/small_icon/mind.png");
	resistanceIconTextures[10] = assetManager.LoadTexture("gfx/ui/icon/small_icon/light.png");
	resistanceIconTextures[11] = assetManager.LoadTexture("gfx/ui/icon/small_icon/dark.png");
	resistanceIconTextures[12] = assetManager.LoadTexture("gfx/ui/icon/small_icon/astral.png");

	// Text Initialization
	nameText.setFont(*font);
	nameText.setCharacterSize(fontSize);
	nameText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 12.f));

	levelText.setFont(*font);
	levelText.setCharacterSize(fontSize);
	levelText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 46.f));

	hpText.setFont(*font);
	hpText.setCharacterSize(fontSize);
	hpText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 66.f));

	mpText.setFont(*font);
	mpText.setCharacterSize(fontSize);
	mpText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 86.f));

	spText.setFont(*font);
	spText.setCharacterSize(fontSize);
	spText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 106.f));

	strText.setFont(*font);
	strText.setCharacterSize(fontSize);
	strText.setPosition(sf::Vector2f(pos.x + 340.f, pos.y + 46.f));

	dexText.setFont(*font);
	dexText.setCharacterSize(fontSize);
	dexText.setPosition(sf::Vector2f(pos.x + 340.f, pos.y + 66.f));

	intText.setFont(*font);
	intText.setCharacterSize(fontSize);
	intText.setPosition(sf::Vector2f(pos.x + 340.f, pos.y + 86.f));

	wisText.setFont(*font);
	wisText.setCharacterSize(fontSize);
	wisText.setPosition(sf::Vector2f(pos.x + 340.f, pos.y + 106.f));

	vitText.setFont(*font);
	vitText.setCharacterSize(fontSize);
	vitText.setPosition(sf::Vector2f(pos.x + 520.f, pos.y + 46.f));

	msText.setFont(*font);
	msText.setCharacterSize(fontSize);
	msText.setPosition(sf::Vector2f(pos.x + 520.f, pos.y + 66.f));

	actionText.setFont(*font);
	actionText.setCharacterSize(fontSize);
	actionText.setPosition(sf::Vector2f(pos.x + 520.f, pos.y + 86.f));

	exhaustionText.setFont(*font);
	exhaustionText.setCharacterSize(fontSize);
	exhaustionText.setPosition(sf::Vector2f(pos.x + 520.f, pos.y + 106.f));

	mainHandDamageText.setFont(*font);
	mainHandDamageText.setCharacterSize(fontSize);
	mainHandDamageText.setPosition(sf::Vector2f(pos.x + 200.f, pos.y + 146.f));

	attackSpeedText.setFont(*font);
	attackSpeedText.setCharacterSize(fontSize);
	attackSpeedText.setPosition(sf::Vector2f(pos.x + 200.f, pos.y + 166.f));

	hitChanceText.setFont(*font);
	hitChanceText.setCharacterSize(fontSize);
	hitChanceText.setPosition(sf::Vector2f(pos.x + 200.f, pos.y + 186.f));

	criticalStrikeChanceText.setFont(*font);
	criticalStrikeChanceText.setCharacterSize(fontSize);
	criticalStrikeChanceText.setPosition(sf::Vector2f(pos.x + 200.f, pos.y + 206.f));

	offHandDamageText.setFont(*font);
	offHandDamageText.setCharacterSize(fontSize);
	offHandDamageText.setPosition(sf::Vector2f(pos.x + 440.f, pos.y + 146.f));

	attackRangeText.setFont(*font);
	attackRangeText.setCharacterSize(fontSize);
	attackRangeText.setPosition(sf::Vector2f(pos.x + 440.f, pos.y + 166.f));

	doubleStrikeChanceText.setFont(*font);
	doubleStrikeChanceText.setCharacterSize(fontSize);
	doubleStrikeChanceText.setPosition(sf::Vector2f(pos.x + 440.f, pos.y + 186.f));

	hasteText.setFont(*font);
	hasteText.setCharacterSize(fontSize);
	hasteText.setPosition(sf::Vector2f(pos.x + 440.f, pos.y + 206.f));

	armorText.setFont(*font);
	armorText.setCharacterSize(fontSize);
	armorText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 246.f));

	evadeChanceText.setFont(*font);
	evadeChanceText.setCharacterSize(fontSize);
	evadeChanceText.setPosition(sf::Vector2f(pos.x + 340.f, pos.y + 246.f));

	blockChanceText.setFont(*font);
	blockChanceText.setCharacterSize(fontSize);
	blockChanceText.setPosition(sf::Vector2f(pos.x + 520.f, pos.y + 246.f));

	bonusText.setFont(*font);
	bonusText.setCharacterSize(fontSize);
	bonusText.setString("#aaaaaa Bonuses");
	bonusText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 286.f));

	statusEffectText.setFont(*font);
	statusEffectText.setCharacterSize(fontSize);
	statusEffectText.setString("#aaaaaa Status Effects");
	statusEffectText.setPosition(sf::Vector2f(pos.x + 160.f, pos.y + 495.f));

	resistanceText.setFont(*font);
	resistanceText.setCharacterSize(fontSize);
	resistanceText.setString("#aaaaaa Resistances");
	resistanceText.setPosition(sf::Vector2f(pos.x + 12.f, pos.y + 160.f));

	for (size_t i = 0; i < resistanceTextValues.size(); i++){
		resistanceTextValues[i].setFont(*font);
		resistanceTextValues[i].setCharacterSize(fontSize);
		resistanceTextValues[i].setPosition(sf::Vector2f(pos.x + 50.f, pos.y + 178.f + (i * 30.f)));
	}

	// Sprite Initialization
	for (size_t i = 0; i < resistanceIcons.size(); i++) {
		resistanceIcons[i].setTexture(*resistanceIconTextures[i]);
		resistanceIcons[i].setPosition(sf::Vector2f(pos.x + 12.f, pos.y + 180.f + (i * 30.f)));
	}
}

void InspectWindow::SetActor(ActorPtr& actor) {
	this->actor = actor;

	sf::Vector2f pos = background.getPosition();

	// Set Up Event Option
	EventOptions eventOptions;
	eventOptions.Categories = { Category::Any };
	eventOptions.Elements = { Element::None };

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

	nameText.setString(actor->GetName());

	levelText.setString("#aaaaaa Level #default " + std::to_string(actor->GetLevel()));
	hpText.setString("#aaaaaa HP #default " + std::to_string(actor->GetCurrentHP()) + "/" + std::to_string(actor->GetMaxHP()));
	mpText.setString("#aaaaaa MP #default " + std::to_string(actor->GetCurrentMP()) + "/" + std::to_string(actor->GetMaxMP()));
	spText.setString("#aaaaaa SP #default " + std::to_string(actor->GetCurrentSP()) + "/" + std::to_string(actor->GetMaxSP()));

	strText.setString("#aaaaaa STR #default " + std::to_string(actor->GetSTR(false)));
	dexText.setString("#aaaaaa DEX #default " + std::to_string(actor->GetDEX(false)));
	intText.setString("#aaaaaa INT #default " + std::to_string(actor->GetINT(false)));
	wisText.setString("#aaaaaa WIS #default " + std::to_string(actor->GetWIS(false)));

	vitText.setString("#aaaaaa VIT #default " + std::to_string(actor->GetVIT(false)));
	msText.setString("#aaaaaa Movement Speed #default " + convertToSec(actor->GetMoveSpeed()));
	actionText.setString("#aaaaaa Action #default " + actor->GetActionName());
	exhaustionText.setString("#aaaaaa Exhaustion #default " + convertToSec(actor->GetExhaustion()));

	// Weapon Damage
	mainHandDamageText.setString("#aaaaaa Main-Hand Damage #default " + std::to_string((int)std::floor(actor->GetMainHandDamage(false))));
	attackSpeedText.setString("#aaaaaa Attack Speed #default " + convertToSec(actor->GetAttackSpeed()));
	double hitChance = actor->GetHitChance(eventOptions, false);
	hitChance = std::round(hitChance * 100);
	hitChanceText.setString("#aaaaaa Hit Chance #default " + std::to_string((int)hitChance) + "%");
	double criticalStrikeChance = actor->GetCritChance(eventOptions, false);
	criticalStrikeChance = std::round(criticalStrikeChance * 100);
	criticalStrikeChanceText.setString("#aaaaaa Critical Strike Chance #default " + std::to_string((int)criticalStrikeChance) + "%");

	if (actor->IsDualWielding()) {
		offHandDamageText.setString("#aaaaaa Off-Hand Damage #default " + std::to_string((int)std::floor(actor->GetOffHandDamage(false))));
	}
	attackRangeText.setString("#aaaaaa Attack Range #default " + std::to_string(actor->GetAttackRange(false)));
	double doubleStrikeChance = actor->GetDoubleStrikeChance(eventOptions, false);
	doubleStrikeChance = std::round(doubleStrikeChance * 100);
	doubleStrikeChanceText.setString("#aaaaaa Double Strike Chance #default " + std::to_string((int)doubleStrikeChance) + "%");
	double haste = actor->GetHaste(eventOptions, false);
	haste = std::round(haste * 100 - 100);
	hasteText.setString("#aaaaaa Haste #default " + std::to_string((int)haste) + "%");

	// Defenses
	armorText.setString("#aaaaaa Armor #default " + std::to_string((int)std::floor(actor->GetArmor(false))));
	double evadeChance = actor->GetDodgeChance(eventOptions, false);
	evadeChance = std::round(evadeChance * 100);
	evadeChanceText.setString("#aaaaaa Evade Chance #default " + std::to_string((int)evadeChance) + "%");
	double blockChance = actor->GetBlockChance(eventOptions, false);
	blockChance = std::round(blockChance * 100);
	blockChanceText.setString("#aaaaaa Block Chance #default " + std::to_string((int)blockChance) + "%");

	// Get Resistances
	std::array<Element, 13> elements = {
		Element::Physical,
		Element::Arcane,
		Element::Fire,
		Element::Ice,
		Element::Lightning,
		Element::Poison,
		Element::Water,
		Element::Wind,
		Element::Earth,
		Element::Mind,
		Element::Light,
		Element::Dark,
		Element::Astral
	};
	for (size_t i = 0; i < elements.size(); i++) {
		eventOptions.Elements = { elements[i] };
		double resistance = actor->GetResistance(eventOptions, false);
		resistance = std::round(resistance * 100);
		resistanceTextValues[i].setString(std::to_string((int)resistance) + "%");
	}
	eventOptions.Elements = { Element::None };

	// Auras
	buffs = actor->GetBuffAuras();
	debuffs = actor->GetDebuffAuras();

	auraIcons.clear();
	auraIcons.resize((buffs.size() * 4) + (debuffs.size() * 4));
	auraIcons.setPrimitiveType(sf::Quads);

	size_t it = 0;

	auraBuffDuration.clear();
	auraBuffIcons.clear();

	auraDebuffDuration.clear();
	auraDebuffIcons.clear();


	for (size_t i = 0; i < buffs.size(); i++) {
		sf::Vertex* quad = &auraIcons[it];

		int x = pos.x + 162 + (i * 35);
		int y = pos.y + 520;

		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(x, y);
		quad[1].position = sf::Vector2f(x + 34, y);
		quad[2].position = sf::Vector2f(x + 34, y + 34);
		quad[3].position = sf::Vector2f(x, y + 34);

		quad[0].texCoords = sf::Vector2f(297, 39);
		quad[1].texCoords = sf::Vector2f(297, 73);
		quad[2].texCoords = sf::Vector2f(331, 73);
		quad[3].texCoords = sf::Vector2f(331, 39);

		// sprite setup
		auraBuffIcons.push_back(sf::Sprite(*assetManager.LoadTexture("gfx/ui/icon/ability/" + buffs[i]->GetIcon())));
		auraBuffIcons[i].setPosition(x + 1, y + 1);

		// text setup
		auraBuffDuration.push_back(sf::Text());
		auraBuffDuration[i].setFont(*font);
		auraBuffDuration[i].setCharacterSize(fontSize - 4);
		auraBuffDuration[i].setOutlineThickness(outlineThickness);

		if (buffs[i]->IsUnlimitedDuration() == false) {
			auraBuffDuration[i].setString(convertToSec(buffs[i]->GetRemainingDuration()));
		}
		auraBuffDuration[i].setPosition(x + 2, y + 21);

		it += 4;
	}

	// debuffs
	for (size_t i = 0; i < debuffs.size(); i++) {
		sf::Vertex* quad = &auraIcons[it];

		int x = pos.x + 162 + (i * 35);
		int y = pos.y + 556;

		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(x, y);
		quad[1].position = sf::Vector2f(x + 34, y);
		quad[2].position = sf::Vector2f(x + 34, y + 34);
		quad[3].position = sf::Vector2f(x, y + 34);

		quad[0].texCoords = sf::Vector2f(297, 74);
		quad[1].texCoords = sf::Vector2f(297, 108);
		quad[2].texCoords = sf::Vector2f(331, 108);
		quad[3].texCoords = sf::Vector2f(331, 74);

		// sprite setup
		auraDebuffIcons.push_back(sf::Sprite(*assetManager.LoadTexture("gfx/ui/icon/ability/" + debuffs[i]->GetIcon())));
		auraDebuffIcons[i].setPosition(x + 1, y + 1);

		// text setup
		auraDebuffDuration.push_back(sf::Text());
		auraDebuffDuration[i].setFont(*font);
		auraDebuffDuration[i].setCharacterSize(fontSize - 4);
		auraDebuffDuration[i].setOutlineThickness(outlineThickness);

		if (debuffs[i]->IsUnlimitedDuration() == false) {
			auraDebuffDuration[i].setString(convertToSec(debuffs[i]->GetRemainingDuration()));
		}
		auraDebuffDuration[i].setPosition(x + 2, y + 21);

		it += 4;
	}
}

void InspectWindow::Update(sf::Vector2i mousePos) {
	displayAuraTooltip = false;

	for (size_t i = 0; i < auraBuffIcons.size(); i++) {
		if (auraBuffIcons[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
			auraTooltip.SetAura(buffs[i]);
			sf::Vector2f tooltipSize = auraTooltip.GetSize();
			auraTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
			displayAuraTooltip = true;
			break;
		}
	}

	if (displayAuraTooltip == false) {
		for (size_t i = 0; i < auraDebuffIcons.size(); i++) {
			if (auraDebuffIcons[i].getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y))) {
				auraTooltip.SetAura(debuffs[i]);
				sf::Vector2f tooltipSize = auraTooltip.GetSize();
				auraTooltip.SetPosition(mousePos.x, mousePos.y - tooltipSize.y);
				displayAuraTooltip = true;
				break;
			}
		}
	}
}

void InspectWindow::Render(sf::RenderTarget& window) {
	sf::Vector2f pos = background.getPosition();
	
	window.draw(background);

	window.draw(nameText);
	window.draw(levelText);
	window.draw(hpText);
	window.draw(mpText);
	window.draw(spText);

	window.draw(strText);
	window.draw(dexText);
	window.draw(intText);
	window.draw(wisText);

	window.draw(vitText);
	window.draw(msText);
	window.draw(actionText);
	window.draw(exhaustionText);

	window.draw(mainHandDamageText);
	window.draw(attackSpeedText);
	window.draw(hitChanceText);
	window.draw(criticalStrikeChanceText);

	if (actor->IsDualWielding()) {
		window.draw(offHandDamageText);
	}
	window.draw(attackRangeText);
	window.draw(doubleStrikeChanceText);
	window.draw(hasteText);

	window.draw(armorText);
	window.draw(evadeChanceText);
	window.draw(blockChanceText);

	window.draw(bonusText);
	window.draw(statusEffectText);

	// resistances
	window.draw(resistanceText);
	for (size_t i = 0; i < resistanceIcons.size(); i++) {
		window.draw(resistanceIcons[i]);
		window.draw(resistanceTextValues[i]);
	}

	// auras
	window.draw(auraIcons, hudTexture);

	for (size_t i = 0; i < auraBuffIcons.size(); i++) {
		window.draw(auraBuffIcons[i]);
	}
	for (size_t i = 0; i < auraBuffDuration.size(); i++) {
		window.draw(auraBuffDuration[i]);
	}

	for (size_t i = 0; i < auraDebuffIcons.size(); i++) {
		window.draw(auraDebuffIcons[i]);
	}
	for (size_t i = 0; i < auraDebuffDuration.size(); i++) {
		window.draw(auraDebuffDuration[i]);
	}

	// Actor Sprite
	if (actor->IsPlayer()) {
		actor->Draw(window, sf::Vector2f(pos.x + 67.f - 64.f, pos.y + 67.f - 32.f), 2.f);
	}
	else {
		actor->Draw(window, sf::Vector2f(pos.x + 52.f, pos.y + 52.f), 2.f);
	}

	// Aura Tooltip
	if (displayAuraTooltip) {
		auraTooltip.Render(window);
	}
}