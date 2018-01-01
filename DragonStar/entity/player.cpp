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

#include "../ui/messageLog.h"

Player::Player(std::string n, RaceID raceID, PlayerClassID classID, bool female) {
	Factory factory;

	name = n;
	race = factory.CreateRace(raceID);
	playerClass = factory.CreatePlayerClass(classID);
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
	abilities[0] = factory.CreateAbility(AbilityID::ATTACK); // 0 is always attack
	abilities[11] = factory.CreateAbility(race->GetActiveID()); // last slot is racial ability by default

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
	double hpMult = getStat(1.0, StatModType::HP_MULT, true, false);

	hp = std::floor(hpd * hpMult);
	return hp;
}

int Player::GetMaxMP() {
	int mp = race->GetBaseMP();
	mp = CalcPercentStat(mp, level, 0.10);

	double mpd = mp;
	mpd = getStat(mpd, StatModType::MP, false, false);
	double mpMult = getStat(1.0, StatModType::MP_MULT, true, false);

	mp = std::floor(mpd * mpMult);

	return mp;
}

int Player::GetMaxSP() {
	int sp = race->GetBaseSP();
	sp = CalcLinearStat(sp, level, 1);

	double spd = sp;
	spd = getStat(spd, StatModType::SP, false, false);
	double spMult = getStat(1.0, StatModType::SP_MULT, true, false);

	sp = std::floor(spd * spMult);

	return sp;
}

double Player::GetHPRegen() {
	double hpRegen = getStat(0.0, StatModType::HP_REGEN, false, false);

	return hpRegen;
}

double Player::GetMPRegen() {
	double mpRegen = getStat(1.0, StatModType::MP_REGEN, false, false);

	return mpRegen;
}

double Player::GetSPRegen() {
	double spRegen = getStat(5.0, StatModType::SP_REGEN, false, false);

	return spRegen;
}

double Player::GetHPLeech(EventOptions eventOptions, bool consumeBuffs) {
	double hpLeech = getStat(0.0, StatModType::HP_LEECH, eventOptions, false, consumeBuffs);

	return hpLeech;
}

double Player::GetMPLeech(EventOptions eventOptions, bool consumeBuffs) {
	double mpLeech = getStat(0.0, StatModType::MP_LEECH, eventOptions, false, consumeBuffs);

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
			StatModCalc::GetStatModValue(strd, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::STR_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
		}
	}

	// Auras
	getStatModValueFromAuras(strd, StatModType::STR, false, consumeBuffs);
	getStatModValueFromAuras(strd, StatModType::ALL_ATTRIBUTES, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::STR_MULT, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::ALL_ATTRIBUTES_MULT, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(strd, statMods, StatModType::STR, false);
			StatModCalc::GetStatModValue(strd, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::STR_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
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
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::DEX_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
		}
	}

	// Auras
	getStatModValueFromAuras(dexd, StatModType::DEX, false, consumeBuffs);
	getStatModValueFromAuras(dexd, StatModType::ALL_ATTRIBUTES, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::DEX_MULT, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::ALL_ATTRIBUTES_MULT, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::DEX, false);
			StatModCalc::GetStatModValue(dexd, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::DEX_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
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
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::INT_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
		}
	}

	// Auras
	getStatModValueFromAuras(intellegenced, StatModType::INT, false, consumeBuffs);
	getStatModValueFromAuras(intellegenced, StatModType::ALL_ATTRIBUTES, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::INT_MULT, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::ALL_ATTRIBUTES_MULT, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::INT, false);
			StatModCalc::GetStatModValue(intellegenced, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::INT_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
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
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::WIS_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
		}
	}

	// Auras
	getStatModValueFromAuras(wisd, StatModType::WIS, false, consumeBuffs);
	getStatModValueFromAuras(wisd, StatModType::ALL_ATTRIBUTES, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::WIS_MULT, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::ALL_ATTRIBUTES_MULT, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::WIS, false);
			StatModCalc::GetStatModValue(wisd, statMods, StatModType::ALL_ATTRIBUTES, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::WIS_MULT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ALL_ATTRIBUTES_MULT, false);
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
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::WIS_MULT, false);
		}
	}

	// Auras
	getStatModValueFromAuras(vitd, StatModType::VIT, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::VIT_MULT, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(vitd, statMods, StatModType::VIT, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::WIS_MULT, false);
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
	StatModCalc::GetStatModValue(armord, statMods, StatModType::ARMOR, false);
	StatModCalc::GetStatModValue(armorPerLevel, statMods, StatModType::ARMOR_PER_LEVEL, false);
	StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ARMOR_MULT, false);

	// Gear
	for (size_t i = 0; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* equip = (Equipment*)equipment[i].get();
			statMods = equip->GetStatMods();
			StatModCalc::GetStatModValue(armord, statMods, StatModType::ARMOR, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ARMOR_MULT, false);
		}
	}

	// Auras
	getStatModValueFromAuras(armord, StatModType::ARMOR, false, consumeBuffs);
	getStatModValueFromAuras(armorPerLevel, StatModType::ARMOR_PER_LEVEL, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::ARMOR_MULT, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(armord, statMods, StatModType::ARMOR, false);
			StatModCalc::GetStatModValue(armorPerLevel, statMods, StatModType::ARMOR_PER_LEVEL, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::ARMOR_MULT, true);
		}
	}

	armor = std::floor((armord + (armorPerLevel * level)) * multiplier);

	return armor;
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
	range = getStat(range, StatModType::RANGE, eventOptions, false, consumeBuffs);

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

std::vector<Category> Player::GetMainHandCategories() {
	std::vector<Category> categories = { Category::UNARMED };

	if (equipment[0] != nullptr) {
		categories.clear();
		Equipment* equip = (Equipment*)equipment[0].get();
		EquipType equipType = equip->GetEquipType();
		switch (equipType) {
			case EquipType::UNARMED_STR:
			case EquipType::UNARMED_DEX:
			case EquipType::UNARMED_INT:
				categories.push_back(Category::UNARMED);
				break;
			case EquipType::SWORD_1H:
			case EquipType::SWORD_2H:
				categories.push_back(Category::SWORD);
				break;
			case EquipType::AXE_1H:
			case EquipType::AXE_2H:
				categories.push_back(Category::AXE);
				break;
			case EquipType::MACE_1H:
			case EquipType::MACE_2H:
				categories.push_back(Category::MACE);
				break;
			case EquipType::DAGGER:
				categories.push_back(Category::DAGGER);
				break;
			case EquipType::CLAW:
				categories.push_back(Category::CLAW);
				break;
			case EquipType::SPEAR:
				categories.push_back(Category::SPEAR);
				break;
			case EquipType::BOW:
				categories.push_back(Category::BOW);
				break;
			case EquipType::WAND:
				categories.push_back(Category::WAND);
				break;
			case EquipType::STAFF:
				categories.push_back(Category::STAFF);
				break;
			default:
				categories.push_back(Category::UNARMED);
				break;
		}
	}

	return categories;
}

std::vector<Element> Player::GetMainHandElements() {
	std::vector<Element> elements = { Element::PHYSICAL };

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

std::vector<Category> Player::GetOffHandCategories() {
	std::vector<Category> categories = { Category::UNARMED };

	if (equipment[1] != nullptr) {
		categories.clear();
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->IsWeapon()) {
			EquipType equipType = equip->GetEquipType();
			switch (equipType) {
			case EquipType::UNARMED_STR:
			case EquipType::UNARMED_DEX:
			case EquipType::UNARMED_INT:
				categories.push_back(Category::UNARMED);
				break;
			case EquipType::SWORD_1H:
			case EquipType::SWORD_2H:
				categories.push_back(Category::SWORD);
				break;
			case EquipType::AXE_1H:
			case EquipType::AXE_2H:
				categories.push_back(Category::AXE);
				break;
			case EquipType::MACE_1H:
			case EquipType::MACE_2H:
				categories.push_back(Category::MACE);
				break;
			case EquipType::DAGGER:
				categories.push_back(Category::DAGGER);
				break;
			case EquipType::CLAW:
				categories.push_back(Category::CLAW);
				break;
			case EquipType::SPEAR:
				categories.push_back(Category::SPEAR);
				break;
			case EquipType::BOW:
				categories.push_back(Category::BOW);
				break;
			case EquipType::WAND:
				categories.push_back(Category::WAND);
				break;
			case EquipType::STAFF:
				categories.push_back(Category::STAFF);
				break;
			default:
				categories.push_back(Category::UNARMED);
				break;
			}
		}
	}

	return categories;
}

std::vector<Element> Player::GetOffHandElements() {
	std::vector<Element> elements = { Element::PHYSICAL };

	if (equipment[1] != nullptr) {
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->IsWeapon()) {
			elements = equip->GetAttackElements();
		}
	}

	return elements;
}

double Player::GetDamageDealt(EventOptions eventOptions, bool consumeBuffs) {
	double damageDealt = getStat(1.0, StatModType::DAMAGE, eventOptions, true, consumeBuffs);

	return damageDealt;
}

double Player::GetDamageTaken(EventOptions eventOptions, bool consumeBuffs) {
	double damageTaken = getStat(1.0, StatModType::DAMAGE_TAKEN, eventOptions, true, consumeBuffs);

	return damageTaken;
}

double Player::GetHealingDealt(EventOptions eventOptions, bool consumeBuffs) {
	double healingDealt = getStat(1.0, StatModType::HEALING, eventOptions, true, consumeBuffs);

	return healingDealt;
}

double Player::GetHealingTaken(EventOptions eventOptions, bool consumeBuffs) {
	double healingTaken = getStat(1.0, StatModType::HEALING_TAKEN, eventOptions, true, consumeBuffs);

	return healingTaken;
}

double Player::GetResistance(EventOptions eventOptions, bool consumeBuffs) {
	double resistance = getStat(0.0, StatModType::RESISTANCE, eventOptions, false, consumeBuffs);

	return resistance;
}

double Player::GetArmorPen(EventOptions eventOptions, bool consumeBuffs) {
	double armorPen = getStat(0.0, StatModType::ARMOR_PEN, eventOptions, false, consumeBuffs);

	return armorPen;
}

double Player::GetResistancePen(EventOptions eventOptions, bool consumeBuffs) {
	double resistPen = getStat(0.0, StatModType::RESISTANCE_PEN, eventOptions, false, consumeBuffs);

	return resistPen;
}

double Player::GetCritChance(EventOptions eventOptions, bool consumeBuffs) {
	double critChance = (double)GetDEX(consumeBuffs) / 1000.0;
	critChance = getStat(critChance, StatModType::CRIT_CHANCE, eventOptions, false, consumeBuffs);

	return critChance;
}

double Player::GetCritDamage(EventOptions eventOptions, bool consumeBuffs) {
	double critDamage = (double)GetSTR(consumeBuffs) / 200.0;
	critDamage += 1.25;
	critDamage = getStat(critDamage, StatModType::CRIT_DAMAGE, eventOptions, true, consumeBuffs);

	return critDamage;
}

double Player::GetCritChanceProtection(EventOptions eventOptions, bool consumeBuffs) {
	double critChanceProtection = getStat(0.0, StatModType::CRIT_CHANCE_PROTECTION, eventOptions, false, consumeBuffs);

	return critChanceProtection;
}

double Player::GetCritDamageProtection(EventOptions eventOptions, bool consumeBuffs) {
	double critDamageProtection = getStat(1.0, StatModType::CRIT_DAMAGE_PROTECTION, eventOptions, true, consumeBuffs);

	// can't be more than 100% protection
	if (critDamageProtection < 0.0) {
		critDamageProtection = 0.0;
	}

	return critDamageProtection;
}

double Player::GetHaste(EventOptions eventOptions, bool consumeBuffs) {
	double haste = getStat(1.0, StatModType::HASTE, eventOptions, true, consumeBuffs);

	return haste;
}

double Player::GetCastTimeReduction(EventOptions eventOptions, bool consumeBuffs) {
	double castTimeReduction = getStat(0.0, StatModType::CAST_TIME_REDUCTION, eventOptions, false, consumeBuffs);

	return castTimeReduction;
}

double Player::GetInstantCast(EventOptions eventOptions, bool consumeBuffs) {
	double instantCast = getStat(0.0, StatModType::INSTANT, eventOptions, false, consumeBuffs);

	return instantCast;
}

double Player::GetRangeIncrease(EventOptions eventOptions, bool consumeBuffs) {
	double range = getStat(0.0, StatModType::RANGE, eventOptions, false, consumeBuffs);

	return range;
}

double Player::GetDoubleStrikeChance(EventOptions eventOptions, bool consumeBuffs) {
	double doubleStrikeChance = getStat(0.0, StatModType::DOUBLE_STRIKE_CHANCE, eventOptions, false, consumeBuffs);

	return doubleStrikeChance;
}

double Player::GetDoubleStrikeDamage(EventOptions eventOptions, bool consumeBuffs) {
	double doubleStrikeDamage = getStat(1.0, StatModType::DOUBLE_STRIKE_DAMAGE, eventOptions, true, consumeBuffs);

	return doubleStrikeDamage;
}

double Player::GetCounterChance(EventOptions eventOptions, bool consumeBuffs) {
	double counterChance = getStat(0.0, StatModType::COUNTER_CHANCE, eventOptions, false, consumeBuffs);

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
			if (sm.GetStatModType() == StatModType::ON_HIT_DAMAGE && sm.MatchesCategories(eventOptions.Categories)) {
				statMods.push_back(sm);
			}
		}
	}
	else if (isOffHand && equipment[1] != nullptr) {
		Equipment* weapon = (Equipment*)equipment[1].get();
		check = weapon->GetStatMods();
		for (auto sm : check) {
			if (sm.GetStatModType() == StatModType::ON_HIT_DAMAGE && sm.MatchesCategories(eventOptions.Categories)) {
				statMods.push_back(sm);
			}
		}
	}

	for (size_t i = 2; i < equipment.size(); i++) {
		if (equipment[i] != nullptr) {
			Equipment* eq = (Equipment*)equipment[i].get();
			check = eq->GetStatMods();
			for (auto sm : check) {
				if (sm.GetStatModType() == StatModType::ON_HIT_DAMAGE && sm.MatchesCategories(eventOptions.Categories)) {
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
				if (sm.GetStatModType() == StatModType::ON_HIT_DAMAGE && sm.MatchesCategories(eventOptions.Categories)) {
					statMods.push_back(sm);
				}
			}
		}
	}

	// Auras
	for (size_t i = 0; i < auras.size(); i++) {
		check = auras[i]->GetStatMods();
		for (auto sm : check) {
			if (sm.GetStatModType() == StatModType::ON_HIT_DAMAGE && sm.MatchesCategories(eventOptions.Categories)) {
				statMods.push_back(sm);
				auras[i]->WasUsed(consumeBuffs);
			}
		}
	}

	return statMods;
}

double Player::GetHitChance(EventOptions eventOptions, bool consumeBuffs) {
	double hitChance = getStat(0.9, StatModType::HIT_CHANCE, eventOptions, false, consumeBuffs);

	return hitChance;
}

double Player::GetDodgeChance(EventOptions eventOptions, bool consumeBuffs) {
	double dodgeChance = getStat(0.0, StatModType::DODGE_CHANCE, eventOptions, false, consumeBuffs);

	return dodgeChance;
}

double Player::GetBlockChance(EventOptions eventOptions, bool consumeBuffs) {
	double blockChance = 0.0; // base 0% block chance

	// Need a shield equipped to block things.
	if (equipment[1] != nullptr) {
		Equipment* equip = (Equipment*)equipment[1].get();
		if (equip->GetEquipType() == EquipType::SHIELD || equip->GetEquipType() == EquipType::BUCKLER) {
			blockChance = getStat(0.0, StatModType::BLOCK_CHANCE, eventOptions, false, consumeBuffs);
			blockChance += equip->GetBlockChance();
		}
	}

	return blockChance;
}

double Player::GetHPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double hpCostReduction = getStat(0.0, StatModType::HP_COST_REDUCTION, eventOptions, false, consumeBuffs);

	return hpCostReduction;
}

double Player::GetMPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double mpCostReduction = getStat(0.0, StatModType::MP_COST_REDUCTION, eventOptions, false, consumeBuffs);

	return mpCostReduction;
}

double Player::GetSPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double spCostReduction = getStat(0.0, StatModType::SP_COST_REDUCTION, eventOptions, false, consumeBuffs);

	return spCostReduction;
}

double Player::GetCooldownReduction(EventOptions eventOptions, bool consumeBuffs) {
	double cdr = getStat(0.0, StatModType::COOLDOWN_REDUCTION, eventOptions, false, consumeBuffs);

	return cdr;
}

double Player::GetAuraSnapshotPower(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotPower = getStat(1.0, StatModType::AURA_SNAPSHOT_POWER, eventOptions, true, consumeBuffs);

	return auraSnapshotPower;
}

double Player::GetAuraSnapshotCritChance(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritChance = getStat(0.0, StatModType::AURA_SNAPSHOT_CRIT_CHANCE, eventOptions, false, consumeBuffs);

	return auraSnapshotCritChance;
}

double Player::GetAuraSnapshotCritPower(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritPower = getStat(1.0, StatModType::AURA_SNAPSHOT_CRIT_POWER, eventOptions, true, consumeBuffs);

	return auraSnapshotCritPower;
}

double Player::GetAuraSnapshotResistPen(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotResistPen = getStat(0.0, StatModType::AURA_SNAPSHOT_RES_PEN, eventOptions, false, consumeBuffs);

	return auraSnapshotResistPen;
}

double Player::GetStunResistance(EventOptions eventOptions, bool consumeBuffs) {
	double stunResistance = getStat(0.0, StatModType::STUN_RESISTANCE, eventOptions, false, consumeBuffs);

	return stunResistance;
}

double Player::GetDisarmResistance(EventOptions eventOptions, bool consumeBuffs) {
	double disarmResistance = getStat(0.0, StatModType::DISARM_RESISTANCE, eventOptions, false, consumeBuffs);

	return disarmResistance;
}

double Player::GetSilenceResistance(EventOptions eventOptions, bool consumeBuffs) {
	double silenceResistance = getStat(0.0, StatModType::SILENCE_RESISTANCE, eventOptions, false, consumeBuffs);

	return silenceResistance;
}

double Player::GetKnockbackResistance(EventOptions eventOptions, bool consumeBuffs) {
	double knockbackResistance = getStat(0.0, StatModType::KNOCKBACK_RESISTANCE, eventOptions, false, consumeBuffs);

	return knockbackResistance;
}

double Player::GetSnareResistance(EventOptions eventOptions, bool consumeBuffs) {
	double snareResistance = getStat(0.0, StatModType::SLOW_ROOT_RESISTANCE, eventOptions, false, consumeBuffs);

	return snareResistance;
}

double Player::GetDeathResistance(EventOptions eventOptions, bool consumeBuffs) {
	double deathResistance = getStat(0.0, StatModType::DEATH_RESISTANCE, eventOptions, false, consumeBuffs);

	return deathResistance;
}

double Player::GetGoldFind(bool consumeBuffs) {
	double goldFind = getStat(0.0, StatModType::GOLD_FIND, false, consumeBuffs);

	return goldFind;
}

double Player::GetEXPBoost(bool consumeBuffs) {
	double expBoost = getStat(0.0, StatModType::EXP_BOOST, false, consumeBuffs);

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
		{ EquipType::SWORD_1H, EquipType::SWORD_2H, EquipType::AXE_1H, EquipType::AXE_2H, EquipType::MACE_1H, EquipType::MACE_2H, 
		  EquipType::DAGGER, EquipType::SPEAR, EquipType::BOW, EquipType::WAND, EquipType::STAFF }, // Main-Hand 0
		{ EquipType::SWORD_1H, EquipType::AXE_1H, EquipType::MACE_1H, EquipType::DAGGER, EquipType::SHIELD, EquipType::OFF_HAND }, // Off-Hand 1
		{ EquipType::HEAVY_HEAD, EquipType::MED_HEAD, EquipType::LIGHT_HEAD }, // Head 2
		{ EquipType::NECK }, // Neck 3
		{ EquipType::HEAVY_BODY, EquipType::MED_BODY, EquipType::LIGHT_BODY }, // Body 4
		{ EquipType::HEAVY_HANDS, EquipType::MED_HANDS, EquipType::LIGHT_HANDS }, // Hands 5
		{ EquipType::RING }, // Ring 6
		{ EquipType::RING }, // Ring 7
		{ EquipType::HEAVY_FEET, EquipType::MED_FEET, EquipType::LIGHT_FEET, }, // Feet 8
		{ EquipType::TRINKET } // Trinket 9
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
	Factory factory;
	AbilityPtr eq = factory.CreateAbility(learnedAbilities[index]);
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
	double msMult = getStat(1.0, StatModType::MOVEMENT_SPEED, false, false);
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
	return CreatureType::HUMANOID;
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
	eo.Categories = { Category::NONE };
	eo.Elements = { Element::NONE };
	eo.AbilityID = AbilityID::UNDEFINED;
	eo.AuraID = AuraID::UNDEFINED;

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
	AuraID auraID = AuraID::UNDEFINED;

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