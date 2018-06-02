// ==================================
//
// enemy.cpp
//
// ==================================

#include "enemy.h"

#include "statMath.h"
#include "../command/abilityCommand.h"
#include "../command/moveCommand.h"
#include "../command/waitCommand.h"
#include "../scene/battleScene.h"
#include "../data/map.h"
#include "../data/statMod.h"
#include "../data/id/abilityID.h"
#include "../data/id/auraID.h"
#include "../data/id/attribute.h"
#include "../data/id/category.h"
#include "../data/id/element.h"
#include "../data/id/equipType.h"
#include "../data/id/statModType.h"
#include "../ui/messageLog.h"

#include <limits>

Enemy::Enemy(EnemyID enemyID, int level, sf::Vector3i spawnPosition) {
	this->enemyInfo = Factory::CreateEnemyInfo(enemyID);
	this->level = level;

	this->texture = assetManager.LoadTexture("gfx/actor/enemy/" + enemyInfo->GetFilepath());
	texture->setSmooth(false);
	sprite.setTexture(*texture);
	sprite.setPosition(0, 0);
	destination = { 0, 0 };

	exhaustion = 0;

	MoveToHex(spawnPosition);

	name = enemyInfo->GetName();

	hpCurrent = GetMaxHP();
	mpCurrent = GetMaxMP();
	spCurrent = GetMaxSP();

	// ability slot set-up
	abilities.push_back(Factory::CreateAbility(AbilityID::Attack)); // slot 0 is always attack
	std::vector<AbilityID> abilityIDs = enemyInfo->GetAbilities();
	for (size_t i = 0; i < abilityIDs.size(); i++) {
		abilities.push_back(Factory::CreateAbility(abilityIDs[i]));
	}
}

CommandPtr Enemy::CalcAICommand(BattleScene& battleScene)
{
	sf::Clock aiClock;
	sf::Time aiTime = sf::Time::Zero;
	std::pair<sf::Vector3i, size_t> idea; // first is cursor position, second is action

	idea = enemyInfo->ExecuteAI(this->getPtr(), battleScene);

	// if cursor is -1, -1, -1, then the enemy failed to find an action and will wait for 0.5s
	if (idea.first == sf::Vector3i(-1, -1, -1)) {
		aiTime = aiClock.restart();
		//messageLog.AddMessage(name + " LV" + std::to_string(level) + " " + std::to_string(aiTime.asSeconds() * 1000.f) + "ms");
		return CommandPtr(std::make_shared<WaitCommand>(50));
	}

	// self targeted abilities
	if (idea.first == GetHexPosition()) {
		return CommandPtr(std::make_shared<AbilityCommand>(idea.second, battleScene, idea.first));
	}

	// the enemy has an idea, path the enemy to the necessary location and use the action

	std::vector<sf::Vector3i> tilesInRange = abilities[idea.second]->GetTargetRange();

	// check if we're already in range
	if (abilities[idea.second]->CanTargetOutsideCursor() == false) {
		for (auto tile : tilesInRange) {
			if (idea.first == tile) {
				aiTime = aiClock.restart();
				//messageLog.AddMessage(name + " LV" + std::to_string(level) + " " + std::to_string(aiTime.asSeconds() * 1000.f) + "ms");
				return CommandPtr(std::make_shared<AbilityCommand>(idea.second, battleScene, idea.first));
			}
		}
	}
	else {
		for (auto tile : tilesInRange) {
			std::vector<sf::Vector3i> aoe = abilities[idea.second]->GetTargetArea(tile);
			if (std::find(aoe.begin(), aoe.end(), idea.first) != aoe.end()) {
				aiTime = aiClock.restart();
				//messageLog.AddMessage(name + " LV" + std::to_string(level) + " " + std::to_string(aiTime.asSeconds() * 1000.f) + "ms");
				return CommandPtr(std::make_shared<AbilityCommand>(idea.second, battleScene, tile));
			}
		}
	}

	// cache the enemy's previous position
	// enemy's position is changed for targeting purposes, this is super-hacky
	sf::Vector3i currentPos = this->GetHexPosition();


	// if not in range, get us to the closest tile
	std::vector<sf::Vector3i> checkableTiles;
	int searchRange = abilities[idea.second]->GetAISearchRange();
	bool ignoreBodyBlock = abilities[idea.second]->IgnoreBodyBlock();
	bool ignoreLineOfSight = abilities[idea.second]->IgnoreLineOfSight();


	// search tiles around the target
	// starting with the outmost ring first for effecientcy
	while (searchRange > 0) {
		std::vector<sf::Vector3i> ring = Hex::HexRing(idea.first, searchRange);

		for (auto tile : ring) {
			if (battleScene.IsTileOccupied(tile) == false && battleScene.IsTileWalkable(tile, enemyInfo->CanFly(), enemyInfo->CanSwim())) {
				// check if enemy can hit target from tile
				if (ignoreLineOfSight == true || battleScene.InLineOfSight(tile, idea.first, false, ignoreBodyBlock)) {
					if (abilities[idea.second]->CanTargetOutsideCursor() == true) {
						this->MoveToHex(tile);
						tilesInRange = abilities[idea.second]->GetTargetRange();					
						for (auto tile2 : tilesInRange) {
							std::vector<sf::Vector3i> aoe = abilities[idea.second]->GetTargetArea(tile2);
							if (std::find(aoe.begin(), aoe.end(), idea.first) != aoe.end()) {
								checkableTiles.push_back(tile);
								break;
							}
						}
					}
					else {
						checkableTiles.push_back(tile);
					}
				}
			}
		}

		if (checkableTiles.size() > 0) {
			searchRange = 0;
		}
		else {
			searchRange--;
		}
	}

	this->MoveToHex(currentPos);
	std::vector<sf::Vector3i> path;
	double fastest = std::numeric_limits<double>::max();

	for (auto tile : checkableTiles) {
		std::vector<sf::Vector3i> testPath = battleScene.Pathfind(this->getPtr(), tile);
		if (testPath.size() > 0) {
			double testCost = battleScene.GetPathCost(getPtr(), testPath);
			if (testCost < fastest) {
				path = testPath;
				fastest = testCost;
			}
		}
	}

	if (path.size() > 0) {
		aiTime = aiClock.restart();
		//messageLog.AddMessage(name + " LV" + std::to_string(level) + " " + std::to_string(aiTime.asSeconds() * 1000.f) + "ms");		
		return CommandPtr(std::make_shared<MoveCommand>(battleScene, path[0]));
	}
	else {
		aiTime = aiClock.restart();
		//messageLog.AddMessage(name + " LV" + std::to_string(level) + " " + std::to_string(aiTime.asSeconds() * 1000.f) + "ms");
		return CommandPtr(std::make_shared<WaitCommand>(100));
	}
}

int Enemy::GetMaxHP() {
	int hp = CalcExpStat(enemyInfo->GetBaseHP(), level);

	double hpd = hp;
	hpd = getStat(hpd, StatModType::HP, false, false);
	double hpMult = getStat(1.0, StatModType::HPMult, true, false);

	hp = std::floor(hpd * hpMult);

	return hp;
}

int Enemy::GetMaxMP() {
	int mp = CalcPercentStat(enemyInfo->GetBaseMP(), level, 0.10);

	double mpd = mp;
	mpd = getStat(mpd, StatModType::MP, false, false);
	double mpMult = getStat(1.0, StatModType::MPMult, true, false);

	mp = std::floor(mpd * mpMult);

	return mp;
}

int Enemy::GetMaxSP() {
	int sp = CalcLinearStat(enemyInfo->GetBaseSP(), level, 1);

	double spd = sp;
	spd = getStat(spd, StatModType::SP, false, false);
	double spMult = getStat(1.0, StatModType::SPMult, true, false);

	sp = std::floor(spd * spMult);

	return sp;
}

double Enemy::GetHPRegen() {
	double hpRegen = getStat(0.0, StatModType::HPRegen, false, false);

	return hpRegen;
}

double Enemy::GetMPRegen() {
	double mpRegen = getStat(1.0, StatModType::MPRegen, false, false);

	return mpRegen;
}

double Enemy::GetSPRegen() {
	double spRegen = getStat(5.0, StatModType::SPRegen, false, false);

	return spRegen;
}

double Enemy::GetHPLeech(EventOptions eventOptions, bool consumeBuffs) {
	double hpLeech = getStat(0.0, StatModType::HPLeech, eventOptions, false, consumeBuffs);

	return hpLeech;
}

double Enemy::GetMPLeech(EventOptions eventOptions, bool consumeBuffs) {
	double mpLeech = getStat(0.0, StatModType::MPLeech, eventOptions, false, consumeBuffs);

	return mpLeech;
}

int Enemy::GetSTR(bool consumeBuffs) {
	int str = enemyInfo->GetBaseSTR();
	str = CalcExpStat(str, level);

	double strd = str;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

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

int Enemy::GetDEX(bool consumeBuffs) {
	int dex = enemyInfo->GetBaseDEX();
	dex = CalcExpStat(dex, level);

	double dexd = dex;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

	// Auras
	statMods = getAuraStatMods();
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

int Enemy::GetINT(bool consumeBuffs) {
	int inte = enemyInfo->GetBaseINT();
	inte = CalcExpStat(inte, level);

	double inted = inte;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

	// Auras
	getStatModValueFromAuras(inted, StatModType::INT, false, consumeBuffs);
	getStatModValueFromAuras(inted, StatModType::AllAttributes, false, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::INTMult, true, consumeBuffs);
	getStatModValueFromAuras(multiplier, StatModType::AllAttributesMult, true, consumeBuffs);

	// Ground Effects
	if (battleScene != nullptr) {
		std::vector<AuraPtr> gev = battleScene->GetGroundEffectsAtHex(GetHexPosition(), IsPlayer());
		for (auto ge : gev) {
			statMods = ge->GetStatMods();
			StatModCalc::GetStatModValue(inted, statMods, StatModType::INT, false);
			StatModCalc::GetStatModValue(inted, statMods, StatModType::AllAttributes, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::INTMult, false);
			StatModCalc::GetStatModValue(multiplier, statMods, StatModType::AllAttributesMult, false);
		}
	}

	inte = std::floor(inted * multiplier);

	return inte;
}

int Enemy::GetWIS(bool consumeBuffs) {
	int wis = enemyInfo->GetBaseWIS();
	wis = CalcExpStat(wis, level);

	double wisd = wis;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

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

int Enemy::GetVIT(bool consumeBuffs) {
	int vit = enemyInfo->GetBaseVIT();

	double vitd = vit;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

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

int Enemy::GetArmor(bool consumeBuffs) {
	int armor = CalcExpStat(enemyInfo->GetBaseArmor(), level);

	double armord = armor;
	double armorPerLevel = 0.0;
	double multiplier = 1.0;
	std::vector<StatMod> statMods = {};

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

void Enemy::OnEvent(EventType eventType, ActorPtr& target, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	if (eventType == EventType::Attack) {
		EventOptions eventOptionsLocal;
		eventOptionsLocal.AbilityID = AbilityID::Undefined;
		eventOptionsLocal.AuraID = AuraID::Undefined;
		eventOptionsLocal.Categories = { Category::Damaging };
		eventOptionsLocal.TriggerOnHit = false;

		for (auto au : auras) {
			au->OnEvent(eventType, target, battleScene, eventOptions, eventResult, isOffHand, amount);
		}

		enemyInfo->OnEvent(eventType, getPtr(), target, battleScene, eventOptions, eventResult, isOffHand, amount);

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

		enemyInfo->OnEvent(eventType, getPtr(), target, battleScene, eventOptions, eventResult, isOffHand, amount);
	}
}

bool Enemy::IsDualWielding() {
	if (enemyInfo->GetOffHandAttackType() == EquipType::None) {
		return false;
	}
	else {
		return true;
	}
}

int Enemy::GetAttackSpeed() {
	return enemyInfo->GetAttackSpeed();
}

int Enemy::GetAttackRange(bool consumeBuffs) {
	double attackRange = enemyInfo->GetAttackRange();
	EventOptions eventOptions;
	eventOptions.Categories = GetMainHandCategories();
	eventOptions.Elements = GetMainHandElements();
	attackRange = getStat(attackRange, StatModType::Range, eventOptions, false, consumeBuffs);
	return (int)attackRange;
}

double Enemy::GetMainHandDamage(bool consumeBuffs) {
	Attribute weaponAttribute = getWeaponAttribute(enemyInfo->GetAttackType());
	double damage = 0;

	switch (weaponAttribute) {
	case Attribute::STR:
		damage = GetSTR(consumeBuffs);
		break;
	case Attribute::DEX:
		damage = GetDEX(consumeBuffs);
		break;
	case Attribute::INT:
		damage = GetINT(consumeBuffs);
		break;
	default:
		break;
	}

	// multiply stat by attack mod
	damage *= enemyInfo->GetAttackMod();

	// add base damage
	damage += enemyInfo->GetAttackDamage();

	return damage;
}

EquipType Enemy::GetMainHandEquipType() {
	return enemyInfo->GetAttackType();
}

std::vector<Category> Enemy::GetMainHandCategories() {
	std::vector<Category> categories = {};
	EquipType equipType = enemyInfo->GetAttackType();
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
		break;
	}

	return categories;
}

std::vector<Element> Enemy::GetMainHandElements() {
	return enemyInfo->GetAttackElement();
}

double Enemy::GetOffHandDamage(bool consumeBuffs) {
	Attribute weaponAttribute = getWeaponAttribute(enemyInfo->GetOffHandAttackType());
	double damage = 0;

	switch (weaponAttribute) {
	case Attribute::STR:
		damage = GetSTR(consumeBuffs);
		break;
	case Attribute::DEX:
		damage = GetDEX(consumeBuffs);
		break;
	case Attribute::INT:
		damage = GetINT(consumeBuffs);
		break;
	default:
		break;
	}

	// multiply stat by attack mod
	damage *= enemyInfo->GetOffHandAttackMod();

	// add base damage
	damage += enemyInfo->GetOffHandAttackDamage();

	return damage;
}

EquipType Enemy::GetOffHandEquipType() {
	return enemyInfo->GetOffHandAttackType();
}

std::vector<Category> Enemy::GetOffHandCategories() {
	std::vector<Category> categories = {};
	EquipType equipType = enemyInfo->GetOffHandAttackType();
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
		break;
	}

	return categories;
}

std::vector<Element> Enemy::GetOffHandElements() {
	return enemyInfo->GetOffHandAttackElement();
}

double Enemy::GetDamageDealt(EventOptions eventOptions, bool consumeBuffs) {
	double damageDealt = getStat(1.0, StatModType::Damage, eventOptions, true, consumeBuffs);

	return damageDealt;
}

double Enemy::GetDamageTaken(EventOptions eventOptions, bool consumeBuffs) {
	double damageTaken = getStat(1.0, StatModType::DamageTaken, eventOptions, true, consumeBuffs);

	return damageTaken;
}

double Enemy::GetHealingDealt(EventOptions eventOptions, bool consumeBuffs) {
	double healingDealt = getStat(1.0, StatModType::Healing, eventOptions, true, consumeBuffs);

	return healingDealt;
}

double Enemy::GetHealingTaken(EventOptions eventOptions, bool consumeBuffs) {
	double healingTaken = getStat(1.0, StatModType::HealingTaken, eventOptions, true, consumeBuffs);

	return healingTaken;
}

double Enemy::GetResistance(EventOptions eventOptions, bool consumeBuffs) {
	double resistance = getStat(0.0, StatModType::Resistance, eventOptions, false, consumeBuffs);

	return resistance;
}

double Enemy::GetArmorPen(EventOptions eventOptions, bool consumeBuffs) {
	double armorPen = getStat(0.0, StatModType::ArmorPen, eventOptions, false, consumeBuffs);

	return armorPen;
}

double Enemy::GetResistancePen(EventOptions eventOptions, bool consumeBuffs) {
	double resistPen = getStat(0.0, StatModType::ResistancePen, eventOptions, false, consumeBuffs);

	return resistPen;
}

double Enemy::GetCritChance(EventOptions eventOptions, bool consumeBuffs) {
	double critChance = (double)GetDEX(consumeBuffs) / 1000.0;
	critChance = getStat(critChance, StatModType::CritChance, eventOptions, false, consumeBuffs);

	return critChance;
}

double Enemy::GetCritDamage(EventOptions eventOptions, bool consumeBuffs) {
	double critDamage = (double)GetSTR(consumeBuffs) / 200.0;
	critDamage += 1.25;
	critDamage = getStat(critDamage, StatModType::CritPower, eventOptions, true, consumeBuffs);

	return critDamage;
}

double Enemy::GetCritChanceProtection(EventOptions eventOptions, bool consumeBuffs) {
	double critChanceProtection = getStat(0.0, StatModType::CritChanceProtection, eventOptions, false, consumeBuffs);

	return critChanceProtection;
}

double Enemy::GetCritDamageProtection(EventOptions eventOptions, bool consumeBuffs) {
	double critDamageProtection = getStat(1.0, StatModType::CritPowerProtection, eventOptions, true, consumeBuffs);

	// can't be more than 100% protection
	if (critDamageProtection < 0.0) {
		critDamageProtection = 0.0;
	}

	return critDamageProtection;
}

double Enemy::GetHaste(EventOptions eventOptions, bool consumeBuffs) {
	double haste = getStat(1.0, StatModType::Haste, eventOptions, true, consumeBuffs);

	return haste;
}

double Enemy::GetCastTimeReduction(EventOptions eventOptions, bool consumeBuffs) {
	double castTimeReduction = getStat(0.0, StatModType::CastTimeReduction, eventOptions, false, consumeBuffs);

	return castTimeReduction;
}

double Enemy::GetInstantCast(EventOptions eventOptions, bool consumeBuffs) {
	double instantCast = getStat(0.0, StatModType::Instant, eventOptions, false, consumeBuffs);

	return instantCast;
}

double Enemy::GetRangeIncrease(EventOptions eventOptions, bool consumeBuffs) {
	double range = getStat(0.0, StatModType::Range, eventOptions, false, consumeBuffs);

	return range;
}

double Enemy::GetDoubleStrikeChance(EventOptions eventOptions, bool consumeBuffs) {
	double doubleStrikeChance = getStat(0.0, StatModType::DoubleStrikeChance, eventOptions, false, consumeBuffs);

	return doubleStrikeChance;
}

double Enemy::GetDoubleStrikeDamage(EventOptions eventOptions, bool consumeBuffs) {
	double doubleStrikeDamage = getStat(1.0, StatModType::DoubleStrikeDamage, eventOptions, true, consumeBuffs);

	return doubleStrikeDamage;
}

double Enemy::GetCounterChance(EventOptions eventOptions, bool consumeBuffs) {
	double counterChance = getStat(0.0, StatModType::CounterChance, eventOptions, false, consumeBuffs);

	return counterChance;
}

std::vector<StatMod> Enemy::GetOnHitDamage(EventOptions eventOptions, bool consumeBuffs, bool isOffHand) {
	std::vector<StatMod> statMods;
	std::vector<StatMod> check;

	// EnemyInfo
	check = enemyInfo->GetStatMods();
	for (auto sm : check) {
		if (sm.GetStatModType() == StatModType::OnHitDamage && sm.MatchesCategories(eventOptions.Categories)) {
			statMods.push_back(sm);
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

double Enemy::GetHitChance(EventOptions eventOptions, bool consumeBuffs) {
	double hitChance = getStat(0.9, StatModType::HitChance, eventOptions, false, consumeBuffs);

	return hitChance;
}

double Enemy::GetDodgeChance(EventOptions eventOptions, bool consumeBuffs) {
	double dodgeChance = getStat(0.0, StatModType::DodgeChance, eventOptions, false, consumeBuffs);

	return dodgeChance;
}

double Enemy::GetBlockChance(EventOptions eventOptions, bool consumeBuffs) {
	double blockChance = getStat(0.0, StatModType::BlockChance, eventOptions, false, consumeBuffs);

	return blockChance;
}

double Enemy::GetHPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double hpCostReduction = getStat(0.0, StatModType::HPCostReduction, eventOptions, false, consumeBuffs);

	return hpCostReduction;
}

double Enemy::GetMPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double mpCostReduction = getStat(0.0, StatModType::MPCostReduction, eventOptions, false, consumeBuffs);

	return mpCostReduction;
}

double Enemy::GetSPCostReduction(EventOptions eventOptions, bool consumeBuffs) {
	double spCostReduction = getStat(0.0, StatModType::SPCostReduction, eventOptions, false, consumeBuffs);

	return spCostReduction;
}

double Enemy::GetCooldownReduction(EventOptions eventOptions, bool consumeBuffs) {
	double cdr = getStat(0.0, StatModType::CooldownReduction, eventOptions, false, consumeBuffs);

	return cdr;
}

double Enemy::GetAuraSnapshotPower(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotPower = getStat(1.0, StatModType::AuraSnapshotPower, eventOptions, true, consumeBuffs);

	return auraSnapshotPower;
}

double Enemy::GetAuraSnapshotCritChance(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritChance = getStat(0.0, StatModType::AuraSnapshotCritChance, eventOptions, false, consumeBuffs);

	return auraSnapshotCritChance;
}

double Enemy::GetAuraSnapshotCritPower(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritPower = getStat(1.0, StatModType::AuraSnapshotCritPower, eventOptions, true, consumeBuffs);

	return auraSnapshotCritPower;
}

double Enemy::GetAuraSnapshotResistPen(EventOptions eventOptions, bool consumeBuffs) {
	double auraSnapshotCritPower = getStat(1.0, StatModType::AuraSnapshotCritPower, eventOptions, true, consumeBuffs);

	return auraSnapshotCritPower;
}

double Enemy::GetStunResistance(EventOptions eventOptions, bool consumeBuffs) {
	double stunResistance = getStat(0.0, StatModType::StunResistance, eventOptions, false, consumeBuffs);

	return stunResistance;
}

double Enemy::GetDisarmResistance(EventOptions eventOptions, bool consumeBuffs) {
	double disarmResistance = getStat(0.0, StatModType::DisarmResistance, eventOptions, false, consumeBuffs);

	return disarmResistance;
}

double Enemy::GetSilenceResistance(EventOptions eventOptions, bool consumeBuffs) {
	double silenceResistance = getStat(0.0, StatModType::SilenceResistance, eventOptions, false, consumeBuffs);

	return silenceResistance;
}

double Enemy::GetKnockbackResistance(EventOptions eventOptions, bool consumeBuffs) {
	double knockbackResistance = getStat(0.0, StatModType::KnockbackResistance, eventOptions, false, consumeBuffs);

	return knockbackResistance;
}

double Enemy::GetSnareResistance(EventOptions eventOptions, bool consumeBuffs) {
	double snareResistance = getStat(0.0, StatModType::SlowRootResistance, eventOptions, false, consumeBuffs);

	return snareResistance;
}

double Enemy::GetDeathResistance(EventOptions eventOptions, bool consumeBuffs) {
	double deathResistance = getStat(0.0, StatModType::DeathResistance, eventOptions, false, consumeBuffs);

	return deathResistance;
}

double Enemy::GetGoldFind(bool consumeBuffs) {
	double goldFind = getStat(0.0, StatModType::GoldFind, false, consumeBuffs);

	return goldFind;
}

double Enemy::GetEXPBoost(bool consumeBuffs) {
	double expBoost = getStat(0.0, StatModType::EXPBoost, false, consumeBuffs);

	return expBoost;
}

unsigned int Enemy::GetEXPDrop() {
	return CalcExpStat(enemyInfo->GetBaseEXP(), level);
}

unsigned int Enemy::GetGoldDrop() {
	return CalcPercentStat(enemyInfo->GetBaseGold(), level, 0.10);
}

unsigned int Enemy::GetLootPoints() {
	return enemyInfo->GetLootPoints();
}

int Enemy::GetMoveSpeed() {
	int moveSpeed = enemyInfo->GetBaseMoveSpeed();
	double msMult = getStat(1.0, StatModType::MovementSpeed, false, false);
	return moveSpeed * (1.0 / msMult);
}

bool Enemy::CanFly() {
	return enemyInfo->CanFly();
}

bool Enemy::CanSwim() {
	return enemyInfo->CanSwim();
}

CreatureType Enemy::GetCreatureType() {
	return enemyInfo->GetCreatureType();
}

bool Enemy::IsPlayer() {
	return false;
}

void Enemy::SetAbilitySlotUser() {
	for (size_t i = 0; i < abilities.size(); i++) {
		abilities[i]->SetUser(getPtr());
	}
}

double Enemy::getStat(double initialValue, StatModType statModType, bool isMultiplicative, bool consumeBuffs) {
	EventOptions eo;
	eo.Categories = { Category::None };
	eo.Elements = { Element::None };
	eo.AbilityID = AbilityID::Undefined;
	eo.AuraID = AuraID::Undefined;

	return getStat(initialValue, statModType, eo, isMultiplicative, consumeBuffs);
}

double Enemy::getStat(double initialValue, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs) {
	double stat = initialValue;

	std::vector<StatMod> statMods = {};

	// Enemy Info
	statMods = enemyInfo->GetStatMods();
	StatModCalc::GetStatModValue(stat, statMods, statModType, eventOptions, false);

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