// ==================================
//
// player.ccp
//
// ==================================

#include "player.h"

#include "statMath.h"
#include "../scene/battleScene.h"
#include "../data/abilityScroll.h"
#include "../data/factory.h"
#include "../data/playerClass.h"
#include "../data/race.h"
#include "../data/id/abilityID.h"
#include "../data/id/auraID.h"
#include "../data/id/attribute.h"
#include "../data/id/category.h"
#include "../data/id/creatureType.h"
#include "../data/id/element.h"
#include "../data/id/equipType.h"
#include "../data/id/eventType.h"
#include "../data/id/statModType.h"

#include "../ui/messageLog.h"

Player::Player(std::string n, RaceID raceID, PlayerClassID classID, bool female) {
	name = n;
	race = Factory::CreateRace(raceID);
	playerClass = Factory::CreatePlayerClass(classID);
	isFemale = female;

	if (isFemale) {
		texture = assetManager.LoadTexture(race->GetFilepath() + "/base_f.png");
	}
	else {
		texture = assetManager.LoadTexture(race->GetFilepath() + "/base_m.png");
	}
	texture->setSmooth(false);
	sprite.setTexture(*texture);
	sprite.setPosition(0, 0);
	destination = { 0, 0 };

	exhaustion = 0;

	level = 1;
	exp = 0;

	abilities.resize(12);
	abilities[0] = Factory::CreateAbility(AbilityID::Attack); // 0 is always attack
	abilities[11] = Factory::CreateAbility(race->GetActiveID()); // last slot is racial ability by default

	// Default Linen Armor
	setEquipmentTexture(4);

	hpCurrent = GetMaxHP();
	mpCurrent = GetMaxMP();
	spCurrent = GetMaxSP();
}

void Player::Update(float secondsPerUpdate) {
	Entity::Update(secondsPerUpdate);
	for (size_t i = 0; i < 8; i++) {
		equipmentSprites[i].setPosition(sprite.getPosition());
	}
}

void Player::Draw(sf::RenderTarget& window, float timeRatio) {
	if (IsMoving() == true) {
		sf::Vector2f oldPos = sprite.getPosition();
		sf::Vector2f interlopPos = { oldPos.x + velocityPerUpdate.x * timeRatio, oldPos.y + velocityPerUpdate.y * timeRatio };

		// Don't overshoot target destination.
		if (abs(destination.x - oldPos.x) < abs(velocityPerUpdate.x * timeRatio)) {
			interlopPos.x = destination.x;
		}
		if (abs(destination.y - oldPos.y) < abs(velocityPerUpdate.y * timeRatio)) {
			interlopPos.y = destination.y;
		}
		sprite.setPosition(interlopPos);
		for (size_t i = 0; i < 8; i++) {
			equipmentSprites[i].setPosition(sprite.getPosition());
		}
		if (IsOnScreen(window)) {
			window.draw(sprite);
			for (size_t i = 0; i < 8; i++) {
				if (drawEquip(i)) {
					window.draw(equipmentSprites[i]);
				}
			}
		}
		sprite.setPosition(oldPos);
		for (size_t i = 0; i < 8; i++) {
			equipmentSprites[i].setPosition(sprite.getPosition());
		}
	}
	else {
		if (IsOnScreen(window)) {
			window.draw(sprite);
			for (size_t i = 0; i < 8; i++) {
				if (drawEquip(i)) {
					window.draw(equipmentSprites[i]);
				}
			}
		}
	}
}

void Player::Draw(sf::RenderTarget& window, sf::Vector2f pos, float scale) {
	sf::Vector2f oldPos = sprite.getPosition();
	auto oldScale = sprite.getScale();
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	if (IsOnScreen(window)) {
		window.draw(sprite);
		for (size_t i = 0; i < 8; i++) {
			equipmentSprites[i].setPosition(pos);
			equipmentSprites[i].setScale(scale, scale);
			if (drawEquip(i)) {
				window.draw(equipmentSprites[i]);
			}
			equipmentSprites[i].setPosition(oldPos);
			equipmentSprites[i].setScale(oldScale);
		}
	}
	sprite.setPosition(oldPos);
	sprite.setScale(oldScale);
}

int Player::GetMaxHP() {
	int hp = race->GetBaseHP();
	hp = CalcExpStat(hp, level);

	double hpd = hp;
	hpd = getStat(hpd, StatModType::HP, false, false);
	double hpMult = getStat(1.0, StatModType::HPMult, true, false);

	hp = std::floor(hpd * hpMult);
	return hp;
}

int Player::GetMaxMP() {
	int mp = race->GetBaseMP();
	mp = CalcPercentStat(mp, level, 0.10);

	double mpd = mp;
	mpd = getStat(mpd, StatModType::MP, false, false);
	double mpMult = getStat(1.0, StatModType::MPMult, true, false);

	mp = std::floor(mpd * mpMult);

	return mp;
}

int Player::GetMaxSP() {
	int sp = race->GetBaseSP();
	sp = CalcLinearStat(sp, level, 1);

	double spd = sp;
	spd = getStat(spd, StatModType::SP, false, false);
	double spMult = getStat(1.0, StatModType::SPMult, true, false);

	sp = std::floor(spd * spMult);

	return sp;
}

double Player::GetHPRegen() {
	double hpRegen = getStat(0.0, StatModType::HPRegen, false, false);

	return hpRegen;
}

double Player::GetMPRegen() {
	double mpRegen = getStat(1.0, StatModType::MPRegen, false, false);

	return mpRegen;
}

double Player::GetSPRegen() {
	double spRegen = getStat(5.0, StatModType::SPRegen, false, false);

	return spRegen;
}

double Player::GetHPLeech(EventOptions eventOptions, bool consumeBuffs) {
	double hpLeech = getStat(0.0, StatModType::HPLeech, eventOptions, false, consumeBuffs);

	return hpLeech;
}

double Player::GetMPLeech(EventOptions eventOptions, bool consumeBuffs) {
	double mpLeech = getStat(0.0, StatModType::MPLeech, eventOptions, false, consumeBuffs);

	return mpLeech;
}

int Player::GetSTR(bool consumeBuffs) {
	int str = race->GetBaseSTR();
	str = CalcExpStat(str, level);

	double strd = str;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};


	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(strd, statMods, StatModType::STR, false);
			StatModCalc::GetStatModValue(strd, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::STRMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	// Auras
	getStatModValueFromAuras(strd, StatModType::STR, false, consumeBuffs);
	getStatModValueFromAuras(strd, StatModType::AllAttributes, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::STRMult, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::AllAttributesMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(strd, statMods, StatModType::STR, false);
			StatModCalc::GetStatModValue(strd, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::STRMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	str = std::floor(strd * multiplier);
	
	return str;
}

int Player::GetDEX(bool consumeBuffs) {
	int dex = race->GetBaseDEX();
	dex = CalcExpStat(dex, level);

	double dexd = dex;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};


	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::DEX, false);
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::DEXMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	// Auras
	getStatModValueFromAuras(dexd, StatModType::DEX, false, consumeBuffs);
	getStatModValueFromAuras(dexd, StatModType::AllAttributes, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::DEXMult, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::AllAttributesMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::DEX, false);
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::DEXMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	dex = std::floor(dexd * multiplier);

	return dex;
}

int Player::GetINT(bool consumeBuffs) {
	int intellegence = race->GetBaseINT();
	intellegence = CalcExpStat(intellegence, level);

	double intellegenced = intellegence;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};


	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::INT, false);
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::INTMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	// Auras
	getStatModValueFromAuras(intellegenced, StatModType::INT, false, consumeBuffs);
	getStatModValueFromAuras(intellegenced, StatModType::AllAttributes, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::INTMult, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::AllAttributesMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::INT, false);
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::INTMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	intellegence = std::floor(intellegenced * multiplier);

	return intellegence;
}

int Player::GetWIS(bool consumeBuffs) {
	int wis = race->GetBaseWIS();
	wis = CalcExpStat(wis, level);

	double wisd = wis;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};


	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::WIS, false);
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::WISMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	// Auras
	getStatModValueFromAuras(wisd, StatModType::WIS, false, consumeBuffs);
	getStatModValueFromAuras(wisd, StatModType::AllAttributes, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::WISMult, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::AllAttributesMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::WIS, false);
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::WISMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	wis = std::floor(wisd * multiplier);

	return wis;
}

int Player::GetVIT(bool consumeBuffs) {
	int vit = race->GetBaseVIT();

	double vitd = vit;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};


	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(vitd, statMods, StatModType::VIT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::VITMult, false);
		}
	}

	// Auras
	getStatModValueFromAuras(vitd, StatModType::VIT, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::VITMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(vitd, statMods, StatModType::VIT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::VITMult, false);
		}
	}

	vit = std::floor(vitd * multiplier);

	return vit;
}

int Player::GetArmor(bool consumeBuffs) {
	int armor = 0;

	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			if (!equip->IsWeapon()) {
				armor += equip->GetEquipPower();
			}
		}
	}

	double armord = armor;
	double armorPerLevel = 0.0;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

	// Race
	statMods = race->GetPassivePerks();
	StatModCalc::GetStatModValue(armord, statMods, StatModType::Armor, false);
	StatModCalc::GetStatModValue(armorPerLevel, statMods, StatModType::ArmorPerLevel, false);
	StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ArmorMult, false);

	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(armord, statMods, StatModType::Armor, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ArmorMult, false);
		}
	}

	// Auras
	getStatModValueFromAuras(armord, StatModType::Armor, false, consumeBuffs);
	getStatModValueFromAuras(armorPerLevel, StatModType::ArmorPerLevel, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::ArmorMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(armord, statMods, StatModType::Armor, false);
			StatModCalc::GetStatModValue(armorPerLevel, statMods, StatModType::ArmorPerLevel, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ArmorMult, true);
		}
	}

	armor = std::floor((armord + (armorPerLevel * level)) * multiplier);

	return armor;
}

void Player::OnEvent(EventType eventType, ActorPtr& target, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	// OnAttack events care about if the attack is a main-hand attack or an off-hand attack.
	// Also triggers on-hit damage stat mods.
	if (eventType == EventType::Attack) {
		EventOptions eventOptionsLocal;
		eventOptionsLocal.AbilityID = AbilityID::Undefined;
		eventOptionsLocal.AuraID = AuraID::Undefined;
		eventOptionsLocal.Categories = { Category::Damaging, Category::SingleTarget };
		eventOptionsLocal.TriggerOnHit = false;

		for (auto au : auras) {
			au->OnEvent(eventType, target, battleScene, eventOptions, eventResult, isOffHand, amount);
		}

		// Off-Hand
		if (isOffHand) {
			if (equipment[1] != nullptr) {
				Equipment* eq = (Equipment*)equipment[1].get();
				if (eq->IsWeapon()) {
					eq->OnEvent(eventType, getPtr(), target, battleScene, eventOptions, eventResult, isOffHand, amount);
				}
			}
		}
		// Main-Hand
		else {
			if (equipment[0] != nullptr) {
				Equipment* eq = (Equipment*)equipment[0].get();
				eq->OnEvent(eventType, getPtr(), target, battleScene, eventOptions, eventResult, isOffHand, amount);
			}
		}

		// Rest of Equipment
		for (size_t i = 2; i < equipment.size(); i++) {
			if (equipment[i] != nullptr) {
				Equipment* eq = (Equipment*)equipment[i].get();
				eq->OnEvent(eventType, getPtr(), target, battleScene, eventOptions, eventResult, isOffHand, amount);
			}
		}

		std::vector<StatMod> statMods;
		statMods = GetOnHitDamage(eventOptions, true, isOffHand);

		for (auto sm : statMods) {
			eventOptionsLocal.Elements = sm.GetOnHitElements();
			EventResult eventResultLocal = Combat::OnHit(getPtr(), target, sm.GetValue(), eventOptionsLocal);
			eventResult.OnAttackValue += eventResultLocal.ResultValue;
		}
	}
	else {
		for (auto au : auras) {
			au->OnEvent(eventType, target, battleScene, eventOptions, eventResult, isOffHand, amount);
		}

		for (size_t i = 0; i < equipment.size(); i++) {
			if (equipment[i] != nullptr) {
				Equipment* eq = (Equipment*)equipment[i].get();
				eq->OnEvent(eventType, getPtr(), target, battleScene, eventOptions, eventResult, isOffHand, amount);
			}
		}
	}
}

bool Player::IsDualWielding() {
	if (equipment[1] == nullptr) {
		return false;
	}

	Equipment* equip = (Equipment*)equipment[1].get();
	if (!equip->IsWeapon()) {
		return false;
	}
	return true;
}

int Player::GetAttackSpeed() {
	int attackSpeedMainHand = 150; // base unarmed speed
	int attackSpeedOffHand = 0;

	if (equipment[0] != nullptr) {
		Equipment* mainHand = (Equipment*)equipment[0].get();
		attackSpeedMainHand = mainHand->GetAttackSpeed();
		
		// If the actor is dual wielding, get the slowest attack speed between the two weapons.
		if (IsDualWielding()) {
			Equipment* offHand = (Equipment*)equipment[1].get();
			attackSpeedOffHand = offHand->GetAttackSpeed();
		}
	}

	return std::max(attackSpeedMainHand, attackSpeedOffHand);
}

int Player::GetAttackRange(bool consumeBuffs) {
	double range = 1; // default unarmed range

	if (equipment[0] != nullptr) {
		Equipment* mainHand = (Equipment*)equipment[0].get();
		range = mainHand->GetAttackRange();
	}

	EventOptions eventOptions;
	eventOptions.Categories = GetMainHandCategories();
	eventOptions.Elements = GetMainHandElements();
	range = getStat(range, StatModType::Range, eventOptions, false, consumeBuffs);

	return (int)range;
}

double Player::GetMainHandDamage(bool consumeBuffs) {
	double damage = 0.0;
	int attribute = 0;
	Attribute weaponAttribute = Attribute::STR;
	double attributeMultiplier = 1.0;

	// Unarmed
	if (equipment[0] == nullptr) {
		damage = CalcExpDoubleValue(22.5, level);
		attributeMultiplier = 0.75;
	}
	// Weapon Damage
	else {
		Equipment* equip = (Equipment*)equipment[0].get();
		damage = equip->GetEquipPower();
		attributeMultiplier = equip->GetAttackMod();
		weaponAttribute = getWeaponAttribute(equip->GetEquipType());
	}

	switch (weaponAttribute) {
	case Attribute::STR:
		attribute = GetSTR(consumeBuffs);
		break;
	case Attribute::DEX:
		attribute = GetDEX(consumeBuffs);
		break;
	case Attribute::INT:
		attribute = GetINT(consumeBuffs);
		break;
	case Attribute::WIS:
		attribute = GetWIS(consumeBuffs);
		break;
	default:
		attribute = 0.0;
		break;
	}

	// add attribute multiplier
	damage += (attribute * attributeMultiplier);

	return damage;
}

EquipType Player::GetMainHandEquipType() {
	if (equipment[0] != nullptr) {
		auto eq = (Equipment*)equipment[0].get();
		return eq->GetEquipType();
	}
	else {
		return EquipType::UnarmedStrength;
	}
}

std::vector<Category> Player::GetMainHandCategories() {
	std::vector<Category> categories = { Category::Unarmed };

	if (equipment[0] != nullptr) {
		categories.clear();
		Equipment* equip = (Equipment*)equipment[0].get();
		EquipType equipType = equip->GetEquipType();
		switch (equipType) {
			case EquipType::UnarmedStrength:
			case EquipType::UnarmedDexterity:
			case EquipType::UnarmedIntelligence:
				categories.push_back(Category::Unarmed);
				break;
			case EquipType::Sword1H:
			case EquipType::Sword2H:
				categories.push_back(Category::Sword);
				break;
			case EquipType::Axe1H:
			case EquipType::Axe2H:
				categories.push_back(Category::Axe);
				break;
			case EquipType::Mace1H:
			case EquipType::Mace2H:
				categories.push_back(Category::Mace);
				break;
			case EquipType::Dagger:
				categories.push_back(Category::Dagger);
				break;
			case EquipType::Claw:
				categories.push_back(Category::Claw);
				break;
			case EquipType::Spear:
				categories.push_back(Category::Spear);
				break;
			case EquipType::Bow:
				categories.push_back(Category::Bow);
				break;
			case EquipType::Wand:
				categories.push_back(Category::Wand);
				break;
			case EquipType::Staff:
				categories.push_back(Category::Staff);
				break;
			default:
				categories.push_back(Category::Unarmed);
				break;
		}
	}

	return categories;
}

std::vector<Element> Player::GetMainHandElements() {
	std::vector<Element> elements = { Element::Physical };

	if (equipment[0] != nullptr) {
		Equipment* equip = (Equipment*)equipment[0].get();
		elements = equip->GetAttackElements();
	}

	return elements;
}

double Player::GetOffHandDamage(bool consumeBuffs) {
	double damage = 0.0;

	if (equipment[0] != nullptr && equipment[1] != nullptr) {
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->IsWeapon()) {
			int attribute = 0;
			Attribute weaponAttribute = Attribute::STR;
			double attributeMultiplier = 1.0;

			// Unarmed
			if (equipment[0] == nullptr) {
				damage = CalcExpDoubleValue(15.0, level);
				attributeMultiplier = 0.75;
			}
			// Weapon Damage
			else {
				damage = equip->GetEquipPower();
				attributeMultiplier = equip->GetAttackMod();
				weaponAttribute = getWeaponAttribute(equip->GetEquipType());
			}

			switch (weaponAttribute) {
			case Attribute::STR:
				attribute = GetSTR(consumeBuffs);
				break;
			case Attribute::DEX:
				attribute = GetDEX(consumeBuffs);
				break;
			case Attribute::INT:
				attribute = GetINT(consumeBuffs);
				break;
			case Attribute::WIS:
				attribute = GetWIS(consumeBuffs);
				break;
			default:
				attribute = 0.0;
				break;
			}

			// add attribute multiplier
			damage += (attribute * attributeMultiplier);
		}
	}

	return damage;
}

EquipType Player::GetOffHandEquipType() {
	if (equipment[1] != nullptr) {
		auto eq = (Equipment*)equipment[1].get();
		return eq->GetEquipType();
	}
	else {
		return EquipType::None;
	}
}

std::vector<Category> Player::GetOffHandCategories() {
	std::vector<Category> categories = { Category::Unarmed };

	if (equipment[1] != nullptr) {
		categories.clear();
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->IsWeapon()) {
			EquipType equipType = equip->GetEquipType();
			switch (equipType) {
			case EquipType::UnarmedStrength:
			case EquipType::UnarmedDexterity:
			case EquipType::UnarmedIntelligence:
				categories.push_back(Category::Unarmed);
				break;
			case EquipType::Sword1H:
			case EquipType::Sword2H:
				categories.push_back(Category::Sword);
				break;
			case EquipType::Axe1H:
			case EquipType::Axe2H:
				categories.push_back(Category::Axe);
				break;
			case EquipType::Mace1H:
			case EquipType::Mace2H:
				categories.push_back(Category::Mace);
				break;
			case EquipType::Dagger:
				categories.push_back(Category::Dagger);
				break;
			case EquipType::Claw:
				categories.push_back(Category::Claw);
				break;
			case EquipType::Spear:
				categories.push_back(Category::Spear);
				break;
			case EquipType::Bow:
				categories.push_back(Category::Bow);
				break;
			case EquipType::Wand:
				categories.push_back(Category::Wand);
				break;
			case EquipType::Staff:
				categories.push_back(Category::Staff);
				break;
			default:
				categories.push_back(Category::Unarmed);
				break;
			}
		}
	}

	return categories;
}

std::vector<Element> Player::GetOffHandElements() {
	std::vector<Element> elements = { Element::Physical };

	if (equipment[1] != nullptr) {
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->IsWeapon()) {
			elements = equip->GetAttackElements();
		}
	}

	return elements;
}

double Player::GetDamageDealt(EventOptions eventOptions, bool consumeBuffs) {
	double damageDealt = getStat(1.0, StatModType::Damage, eventOptions, true, consumeBuffs);

	return damageDealt;
}

double Player::GetDamageTaken(EventOptions eventOptions, bool consumeBuffs) {
	double damageTaken = getStat(1.0, StatModType::DamageTaken, eventOptions, true, consumeBuffs);

	return damageTaken;
}

double Player::GetHealingDealt(EventOptions eventOptions, bool consumeBuffs) {
	double healingDealt = getStat(1.0, StatModType::Healing, eventOptions, true, consumeBuffs);

	return healingDealt;
}

double Player::GetHealingTaken(EventOptions eventOptions, bool consumeBuffs) {
	double healingTaken = getStat(1.0, StatModType::HealingTaken, eventOptions, true, consumeBuffs);

	return healingTaken;
}

double Player::GetResistance(EventOptions eventOptions, bool consumeBuffs) {
	double resistance = getStat(0.0, StatModType::Resistance, eventOptions, false, consumeBuffs);

	return resistance;
}

double Player::GetArmorPen(EventOptions eventOptions, bool consumeBuffs) {
	double armorPen = getStat(0.0, StatModType::ArmorPen, eventOptions, false, consumeBuffs);

	return armorPen;
}

double Player::GetResistancePen(EventOptions eventOptions, bool consumeBuffs) {
	double resistPen = getStat(0.0, StatModType::ResistancePen, eventOptions, false, consumeBuffs);

	return resistPen;
}

double Player::GetCritChance(EventOptions eventOptions, bool consumeBuffs) {
	double critChance = (double)GetDEX(consumeBuffs) / 1000.0;
	critChance = getStat(critChance, StatModType::CritChance, eventOptions, false, consumeBuffs);

	return critChance;
}

double Player::GetCritDamage(EventOptions eventOptions, bool consumeBuffs) {
	double critDamage = (double)GetSTR(consumeBuffs) / 200.0;
	critDamage += 1.25;
	critDamage = getStat(critDamage, StatModType::CritPower, eventOptions, true, consumeBuffs);

	return critDamage;
}

double Player::GetCritChanceProtection(EventOptions eventOptions, bool consumeBuffs) {
	double critChanceProtection = getStat(0.0, StatModType::CritChanceProtection, eventOptions, false, consumeBuffs);

	return critChanceProtection;
}

double Player::GetCritDamageProtection(EventOptions eventOptions, bool consumeBuffs) {
	double critDamageProtection = getStat(1.0, StatModType::CritPowerProtection, eventOptions, true, consumeBuffs);

	// can't be more than 100% protection
	if (critDamageProtection < 0.0) {
		critDamageProtection = 0.0;
	}

	return critDamageProtection;
}

double Player::GetHaste(EventOptions eventOptions, bool consumeBuffs) {
	double haste = getStat(1.0, StatModType::Haste, eventOptions, true, consumeBuffs);

	return haste;
}

double Player::GetCastTimeReduction(EventOptions eventOptions, bool consumeBuffs) {
	double castTimeReduction = getStat(0.0, StatModType::CastTimeReduction, eventOptions, false, consumeBuffs);

	return castTimeReduction;
}

double Player::GetInstantCast(EventOptions eventOptions, bool consumeBuffs) {
	double instantCast = getStat(0.0, StatModType::Instant, eventOptions, false, consumeBuffs);

	return instantCast;
}

double Player::GetRangeIncrease(EventOptions eventOptions, bool consumeBuffs) {
	double range = getStat(0.0, StatModType::Range, eventOptions, false, consumeBuffs);

	return range;
}

double Player::GetDoubleStrikeChance(EventOptions eventOptions, bool consumeBuffs) {
	double doubleStrikeChance = getStat(0.0, StatModType::DoubleStrikeChance, eventOptions, false, consumeBuffs);

	return doubleStrikeChance;
}

double Player::GetDoubleStrikeDamage(EventOptions eventOptions, bool consumeBuffs) {
	double doubleStrikeDamage = getStat(1.0, StatModType::DoubleStrikeDamage, eventOptions, true, consumeBuffs);

	return doubleStrikeDamage;
}

double Player::GetCounterChance(EventOptions eventOptions, bool consumeBuffs) {
	double counterChance = getStat(0.0, StatModType::CounterChance, eventOptions, false, consumeBuffs);

	return counterChance;
}

std::vector<StatMod> Player::GetOnHitDamage(EventOptions eventOptions, bool consumeBuffs, bool isOffHand) {
	std::vector<StatMod> statMods;
	std::vector<StatMod> check;

	// Equipment
	if (!isOffHand && equipment[0] != nullptr) {
		Equipment* weapon = (Equipment*)equipment[0].get();
		check = weapon->GetStatMods();
		for (auto sm : check) {
			if (sm.GetStatModType() == StatModType::OnHitDamage && sm.MatchesCategories(eventOptions.Categories)) {
				statMods.push_back(sm);
			}
		}
	}
	else if (isOffHand && equipment[1] != nullptr) {
		Equipment* weapon = (Equipment*)equipment[1].get();
		check = weapon->GetStatMods();
		for (auto sm : check) {
			if (sm.GetStatModType() == StatModType::OnHitDamage && sm.MatchesCategories(eventOptions.Categories)) {
				statMods.push_back(sm);
			}
		}
	}

	for (size_t i = 2; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* eq = (Equipment*)equipment[i].get();
			check = eq->GetStatMods();
			for (auto sm : check) {
				if (sm.GetStatModType() == StatModType::OnHitDamage && sm.MatchesCategories(eventOptions.Categories)) {
					statMods.push_back(sm);
				}
			}
		}
	}

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			check = ge->GetStatMods();
			for (auto sm : check) {
				if (sm.GetStatModType() == StatModType::OnHitDamage && sm.MatchesCategories(eventOptions.Categories)) {
					statMods.push_back(sm);
				}
			}
		}
	}

	// Auras
	for (size_t i = 0; i < auras.size(); i++) {
		check = auras[i]->GetStatMods();
		for (auto sm : check) {
			if (sm.GetStatModType() == StatModType::OnHitDamage && sm.MatchesCategories(eventOptions.Categories)) {
				statMods.push_back(sm);
				auras[i]->WasUsed(consumeBuffs);
			}
		}
	}

	return statMods;
}

double Player::GetHitChance(EventOptions eventOptions, bool consumeBuffs) {
	double hitChance = getStat(0.9, StatModType::HitChance, eventOptions, false, consumeBuffs);

	return hitChance;
}

double Player::GetDodgeChance(EventOptions eventOptions, bool consumeBuffs) {
	double dodgeChance = getStat(0.0, StatModType::DodgeChance, eventOptions, false, consumeBuffs);

	return dodgeChance;
}

double Player::GetBlockChance(EventOptions eventOptions, bool consumeBuffs) {
	double blockChance = 0.0; // base 0% block chance

	// Need a shield equipped to block things.
	if (equipment[1] != nullptr) {
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->GetEquipType() == EquipType::Shield || equip->GetEquipType() == EquipType::Buckler) {
			blockChance = getStat(0.0, StatModType::BlockChance, eventOptions, false, consumeBuffs);
			blockChance += equip->GetBlockChance();
		}
	}

	return blockChance;
}

double Player::GetHPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double hpCostReduction = getStat(0.0, StatModType::HPCostReduction, eventOptions, false, consumeBuffs);

	return hpCostReduction;
}

double Player::GetMPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double mpCostReduction = getStat(0.0, StatModType::MPCostReduction, eventOptions, false, consumeBuffs);

	return mpCostReduction;
}

double Player::GetSPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double spCostReduction = getStat(0.0, StatModType::SPCostReduction, eventOptions, false, consumeBuffs);

	return spCostReduction;
}

double Player::GetCooldownReduction(EventOptions eventOptions, bool consumeBuffs) {
	double cdr = getStat(0.0, StatModType::CooldownReduction, eventOptions, false, consumeBuffs);

	return cdr;
}

double Player::GetAuraSnapshotPower(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotPower = getStat(1.0, StatModType::AuraSnapshotPower, eventOptions, true, consumeBuffs);

	return auraSnapshotPower;
}

double Player::GetAuraSnapshotCritChance(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritChance = getStat(0.0, StatModType::AuraSnapshotCritChance, eventOptions, false, consumeBuffs);

	return auraSnapshotCritChance;
}

double Player::GetAuraSnapshotCritPower(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritPower = getStat(1.0, StatModType::AuraSnapshotCritPower, eventOptions, true, consumeBuffs);

	return auraSnapshotCritPower;
}

double Player::GetAuraSnapshotResistPen(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotResistPen = getStat(0.0, StatModType::AuraSnapshotResPen, eventOptions, false, consumeBuffs);

	return auraSnapshotResistPen;
}

double Player::GetStunResistance(EventOptions eventOptions, bool consumeBuffs) {
	double stunResistance = getStat(0.0, StatModType::StunResistance, eventOptions, false, consumeBuffs);

	return stunResistance;
}

double Player::GetDisarmResistance(EventOptions eventOptions, bool consumeBuffs) {
	double disarmResistance = getStat(0.0, StatModType::DisarmResistance, eventOptions, false, consumeBuffs);

	return disarmResistance;
}

double Player::GetSilenceResistance(EventOptions eventOptions, bool consumeBuffs) {
	double silenceResistance = getStat(0.0, StatModType::SilenceResistance, eventOptions, false, consumeBuffs);

	return silenceResistance;
}

double Player::GetKnockbackResistance(EventOptions eventOptions, bool consumeBuffs) {
	double knockbackResistance = getStat(0.0, StatModType::KnockbackResistance, eventOptions, false, consumeBuffs);

	return knockbackResistance;
}

double Player::GetSnareResistance(EventOptions eventOptions, bool consumeBuffs) {
	double snareResistance = getStat(0.0, StatModType::SlowRootResistance, eventOptions, false, consumeBuffs);

	return snareResistance;
}

double Player::GetDeathResistance(EventOptions eventOptions, bool consumeBuffs) {
	double deathResistance = getStat(0.0, StatModType::DeathResistance, eventOptions, false, consumeBuffs);

	return deathResistance;
}

double Player::GetGoldFind(bool consumeBuffs) {
	double goldFind = getStat(0.0, StatModType::GoldFind, false, consumeBuffs);

	return goldFind;
}

double Player::GetEXPBoost(bool consumeBuffs) {
	double expBoost = getStat(0.0, StatModType::EXPBoost, false, consumeBuffs);

	return expBoost;
}

bool Player::GrantEXP(unsigned int xp){
	bool didLevel = false;
	exp += xp * (1.0 + GetEXPBoost(true));
	unsigned int expToNextLevel = CalcExpStat(300u, level);
	while (exp > expToNextLevel) {
		exp -= expToNextLevel;
		level++;
		didLevel = true;
		expToNextLevel = CalcExpStat(300u, level);
	}
	return didLevel;
}

unsigned int Player::GetEXP(){
	return exp;
}

bool Player::Equip(std::vector<ItemPtr>& inventory, size_t index, size_t slot) {
	std::vector<std::vector<EquipType>> validTypesInSlot = {
		{ EquipType::Sword1H, EquipType::Sword2H, EquipType::Axe1H, EquipType::Axe2H, EquipType::Mace1H, EquipType::Mace2H, 
		  EquipType::Dagger, EquipType::Spear, EquipType::Bow, EquipType::Wand, EquipType::Staff }, // Main-Hand 0
		{ EquipType::Sword1H, EquipType::Axe1H, EquipType::Mace1H, EquipType::Dagger, EquipType::Shield, EquipType::OffHand }, // Off-Hand 1
		{ EquipType::HeavyHead, EquipType::MedHead, EquipType::LightHead }, // Head 2
		{ EquipType::Neck }, // Neck 3
		{ EquipType::HeavyBody, EquipType::MedBody, EquipType::LightBody }, // Body 4
		{ EquipType::HeavyHands, EquipType::MedHands, EquipType::LightHands }, // Hands 5
		{ EquipType::Ring }, // Ring 6
		{ EquipType::Ring }, // Ring 7
		{ EquipType::HeavyFeet, EquipType::MedFeet, EquipType::LightFeet, }, // Feet 8
		{ EquipType::Trinket } // Trinket 9
	};
	
	if (inventory[index]->IsEquipment()) {
		Equipment* eq = (Equipment*)inventory[index].get();
		EquipType equipType = eq->GetEquipType();
		bool twoHanded = eq->IsTwoHanded();

		// proper slot
		if (std::find(validTypesInSlot[slot].begin(), validTypesInSlot[slot].end(), equipType) != validTypesInSlot[slot].end()) {
			// class can equip
			if (playerClass != nullptr && playerClass->CanEquip(equipType)) {
				// if slot is empty
				if (equipment[slot] == nullptr) {
					// unequip item in off-hand slot if two-handed
					if (twoHanded && equipment[1] != nullptr) {
						inventory.push_back(equipment[1]);
						equipment[1] = nullptr;
						equipment[0] = std::move(inventory[index]);
						std::swap(inventory[index], inventory.back());
						inventory.pop_back();
						setEquipmentTexture(0);
						FullHeal();
						return true;
					}
					// cant equip anything in off-hand if wielding two-handed weapon
					if (slot == 1 && equipment[0] != nullptr) {
						auto mh = (Equipment*)equipment[0].get();
						if (mh->IsTwoHanded()) {
							return false;
						}
					}
					// if main-hand slot is empty put weapon in main hand slot
					if (slot == 1 && equipment[0] == nullptr && eq->IsWeapon()) {
						equipment[0] = std::move(inventory[index]);
						std::swap(inventory[index], inventory.back());
						inventory.pop_back();
						setEquipmentTexture(0);
						FullHeal();
						return true;
					}
					equipment[slot] = std::move(inventory[index]);
					std::swap(inventory[index], inventory.back());
					inventory.pop_back();
					setEquipmentTexture(slot);
					FullHeal();
					return true;
				}
				else {
					// unequip item in off-hand slot if two-handed
					if (twoHanded && equipment[1] != nullptr) {
						inventory.push_back(equipment[1]);
						equipment[1] = nullptr;
						inventory.push_back(equipment[0]);
						equipment[0] = std::move(inventory[index]);
						std::swap(inventory[index], inventory.back());
						inventory.pop_back();
						setEquipmentTexture(0);
						FullHeal();
						return true;
					}
					inventory.push_back(equipment[slot]);
					equipment[slot] = std::move(inventory[index]);
					std::swap(inventory[index], inventory.back());
					inventory.pop_back();
					setEquipmentTexture(slot);
					FullHeal();
					return true;
				}
			}
		}

		return false;
	}
}

void Player::Unequip(std::vector<ItemPtr>& inventory, size_t slot) {
	if (equipment[slot] != nullptr) {
		inventory.push_back(equipment[slot]);
		equipment[slot].reset();
		setEquipmentTexture(slot);
		FullHeal();
	}
}

ItemPtr Player::GetEquipment(size_t slot) {
	ItemPtr i = nullptr;
	try {
		i = equipment.at(slot);
	}
	catch (std::out_of_range& e){

	}
	return i;
}

std::array<ItemPtr, 10u> Player::GetAllEquipment() {
	return equipment;
}

std::vector<AbilityID> Player::GetLearnedAbilities() {
	return learnedAbilities;
}

std::vector<AbilityType> Player::GetLearnableAbilityTypes() {
	return playerClass->GetAbilityTypes();
}

bool Player::IsLearnable(ItemPtr& scroll) {
	if (scroll->IsAbilityScroll()) {
		auto s = (AbilityScroll*)scroll.get();
		if (playerClass->CanLearn(s->GetAbilityTypes(), s->GetItemTier())) {
			// check for duplicates
			if (std::find(learnedAbilities.begin(), learnedAbilities.end(), s->GetAbilityID()) != learnedAbilities.end()) {
				return false;
			}
			for (size_t i = 0; i < abilities.size(); i++) {
				if (abilities[i] != nullptr && abilities[i]->GetAbilityID() == s->GetAbilityID()) {
					return false;
				}
			}
			return true;
		}
	}

	return false;
}

void Player::LearnAbility(std::vector<ItemPtr>& inventory, size_t index) {
	if (IsLearnable(inventory[index])) {
		auto s = (AbilityScroll*)inventory[index].get();
		learnedAbilities.push_back(s->GetAbilityID());
		inventory.erase(inventory.begin() + index);
	}
}

void Player::EquipAbility(size_t index, size_t slot) {
	AbilityPtr eq = Factory::CreateAbility(learnedAbilities[index]);
	AbilityPtr replaced = nullptr;
	
	try {
		replaced = abilities.at(slot);		
	}
	catch (std::out_of_range& e) {

	}

	if (replaced != nullptr) {
		AbilityID id = replaced->GetAbilityID();
		learnedAbilities.push_back(id);
		abilities[slot] = eq;
		std::swap(learnedAbilities[index], learnedAbilities.back());
		learnedAbilities.pop_back();
	}
	else {
		abilities[slot] = eq;
		learnedAbilities.erase(learnedAbilities.begin() + index);
	}
}

void Player::UnequipAbility(size_t slot) {
	AbilityPtr replaced = nullptr;
	
	try {
		replaced = abilities.at(slot);
	}
	catch (std::out_of_range& e) {

	}

	if (replaced != nullptr) {
		AbilityID id = abilities.at(slot)->GetAbilityID();
		learnedAbilities.push_back(id);
		abilities[slot] = nullptr;
	}
}

bool Player::IsFemale() {
	return isFemale;
}

unsigned int Player::GetEXPToNextLevel() {
	return CalcExpStat(300u, level);
}

// Returns the player's movespeed.
int Player::GetMoveSpeed(){
	int moveSpeed = 50;
	double msMult = getStat(1.0, StatModType::MovementSpeed, false, false);
	return moveSpeed * (1.0 / msMult);
}

// Returns true if the player can fly.
bool Player::CanFly(){
	return race->CanFly();
}

// Returns true if the player can swim.
bool Player::CanSwim(){
	return race->CanSwim();
}

// Returns Humanoid creature type for all players.
CreatureType Player::GetCreatureType(){
	return CreatureType::Humanoid;
}

bool Player::IsPlayer() {
	return true;
}

void Player::SetAbilitySlotUser() {
	for (size_t i = 0; i < abilities.size(); i++) {
		if (abilities[i] != nullptr) {
			abilities[i]->SetUser(getPtr());
		}
	}
}

double Player::getStat(double initialValue, StatModType statModType, bool isMultiplicative, bool consumeBuffs) {
	EventOptions eo;
	eo.Categories = { Category::None };
	eo.Elements = { Element::None };
	eo.AbilityID = AbilityID::Undefined;
	eo.AuraID = AuraID::Undefined;

	return getStat(initialValue, statModType, eo, isMultiplicative, consumeBuffs);
}

double Player::getStat(double initialValue, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs) {
	double stat = initialValue;

	std::vector<StatMod> statMods = {};

	// Race
	statMods = race->GetPassivePerks();
	StatModCalc::GetStatModValue(stat, statMods, statModType, eventOptions, false);

	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(stat, statMods, statModType, eventOptions, false);
		}
	}


	// Auras
	getStatModValueFromAuras(stat, statModType, eventOptions, isMultiplicative, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(stat, statMods, statModType, eventOptions, isMultiplicative);
		}
	}

	return stat;
}

AuraID Player::getWeaponOnHitAura(bool isOffHand) {
	AuraID auraID = AuraID::Undefined;

	if (!isOffHand && equipment[0] != nullptr) {
		Equipment* weapon = (Equipment*)equipment[0].get();
		auraID = weapon->GetOnHitAura();
	}
	else if (isOffHand && equipment[1] != nullptr) {
		Equipment* weapon = (Equipment*)equipment[1].get();
		auraID = weapon->GetOnHitAura();
	}

	return auraID;
}

void Player::setEquipmentTexture(size_t slot) {
	size_t textureSlot = 0;
	std::string file = "";
	switch (slot) {
	case 0:
		textureSlot = 6;
		file = "weapon";
		break;
	case 1:
		textureSlot = 7;
		file = "weapon";
		break;
	case 2:
		textureSlot = 4;
		file = "head";
		break;
	case 4:
		textureSlot = 1;
		if (isFemale) {
			file = "armor_f";
		}
		else {
			file = "armor_m";
		}
		break;
	case 5:
		textureSlot = 5;
		file = "hands";
		break;
	case 8:
		textureSlot = 0;
		file = "feet";
		break;
	default:
		textureSlot = 100;
		break;
	}

	if (textureSlot < 8 && equipment[slot] != nullptr) {
		Equipment* equip = (Equipment*)equipment[slot].get();
		equipmentTextures[textureSlot] = assetManager.LoadTexture(race->GetFilepath() + "/" + file + "/" + equip->GetTextureFilepath());
		equipmentTextures[textureSlot]->setSmooth(false);
		equipmentSprites[textureSlot].setTexture(*equipmentTextures[textureSlot]);

		// reverse texture for offhand slot
		if (textureSlot == 7) {
			auto size = equipmentTextures[textureSlot]->getSize();
			sf::IntRect rect(size.x, 0, (int)size.x * -1, size.y);
			equipmentSprites[textureSlot].setTextureRect(rect);
		}
	}
	else if (textureSlot == 1 && equipment[4] == nullptr) {
		if (isFemale) {
			equipmentTextures[1] = assetManager.LoadTexture(race->GetFilepath() + "/armor_f/linen.png");
		}
		else {
			equipmentTextures[1] = assetManager.LoadTexture(race->GetFilepath() + "/armor_m/linen.png");
		}
		equipmentTextures[1]->setSmooth(false);
		equipmentSprites[1].setTexture(*equipmentTextures[1]);
	}
}

bool Player::drawEquip(size_t index) {
	size_t test = 0;
	switch (index) {
	// Feet
	case 0:
		test = 8;
		break;
	// Body
	case 1:
		test = 4;
		break;
	// Neck
	case 2:
		test = 3;
		break;
	// Hair
	case 3:
		test = 4;
		break;
	// Head
	case 4:
		test = 2;
		break;
	// Hands
	case 5:
		test = 5;
		break;
	// Main-Hand
	case 6:
		test = 0;
		break;
	// Off-Hand
	case 7:
		test = 1;
		break;
	default:
		break;
	}

	if (test == 4) {
		return true;
	}
	if (equipment[test] != nullptr) {
		return true;
	}
	return false;
}