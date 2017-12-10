// ==================================
//
// ability.cpp
//
// ==================================

#include "ability.h"

#include "../core/random.h"
#include "../scene/battleScene.h"
#include "../entity/actor.h"
#include "../hex/hexMath.h"
#include "../ui/messageLog.h"

void Ability::SetUser(ActorPtr& user) {
	this->user = user;

	setAbilityOptions();
}

void Ability::SetWorld(BattleScene& battleScene) {
	this->battleScene = &battleScene;
}

bool Ability::IsUsable() {
	if (user == nullptr) {
		return false;
	}
	else {
		// todo: account for resource cost reduction for HP
		// todo: account for status effects like disarm/silence
		if (user->GetCurrentMP() < GetMPCost()) {
			return false;
		}

		if (user->GetCurrentSP() < GetSPCost()) {
			return false;
		}

		if (user->GetCurrentHP() < hpCost) {
			return false;
		}

		if (currentCooldown > 0) {
			return false;
		}

		return true;
	}
}

std::vector<sf::Vector3i> Ability::GetTargetRange() {
	sf::Vector3i center = sf::Vector3i(0, 0, 0);

	if (user != nullptr) {
		center = user->GetHexPosition();
	}

	std::vector<sf::Vector3i> targetRange;
	
	if (!keyTileRange) {
		if (useAttackRange && user != nullptr) {
			targetRange = Hex::FilledHexagon(center, user->GetAttackRange(false));
		}
		else if (range > 0){
			targetRange = Hex::FilledHexagon(center, range);
		}
	}
	else {
		targetRange = Hex::AllHexRotations(center, keyTile + center);
	}

	if (battleScene != nullptr) {
		targetRange = battleScene->GetLineOfSight(center, targetRange, user->IsPlayer(), ignoreBodyBlock, ignoreLineOfSight);
	}

	return targetRange;
}

void Ability::UseAbility(sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	if (user != nullptr && battleScene != nullptr) {
		std::vector<ActorPtr> targets = battleScene->GetAbilityTargets(targetArea, isFriendlyAbility, user->IsPlayer());
		calcCooldown = cooldown; // resets cooldown to the base amount, abilities can change calcCooldown in the execute step
		if (requireTargetsInArea) {
			if (targets.size() > 0) {
				if (usage == UseType::INSTANT) {
					consumeResources();
					execute(targets, cursor, targetArea);
					exhaustUser();
					doubleStrike(targets[0]);
					putOnCooldown();
				}
				else if (usage == UseType::CAST) {
					if (user->IsCastReady()) {
						execute(targets, cursor, targetArea);
						doubleStrike(targets[0]);
						putOnCooldown();
					}
					else {
						consumeResources();
						messageLog.AddMessage(user->GetName() + " begins casting " + name + ".");
						if (isGroundTargeted) {
							user->StartCast(cursor, GetCastTime(true));
						}
						else {
							user->StartCast(targets[0], GetCastTime(true));
						}
					}
				}
			}
		}
		// Does not require targets.
		else {
			if (usage == UseType::INSTANT) {
				consumeResources();
				execute(targets, cursor, targetArea);
				exhaustUser();
				putOnCooldown();
			}
			else if (usage == UseType::CAST) {
				if (user->IsCastReady()) {
					execute(targets, cursor, targetArea);
					putOnCooldown();
				}
				else {
					consumeResources();
					messageLog.AddMessage(user->GetName() + " begins casting " + name + ".");
					user->StartCast(cursor, GetCastTime(true));
				}
			}
		}
	}
}

AbilityID Ability::GetAbilityID() {
	return abilityID;
}

std::string Ability::GetName() {
	return name;
}

std::string Ability::GetIcon() {
	return icon;
}

std::vector<AbilityType> Ability::GetAbilityTypes() {
	return abilityTypes;
}

unsigned int Ability::GetTier() {
	return tier;
}

int Ability::GetRange() {
	int result = 0;
	if (keyTileRange) {
		result = aiSearchRange;
	}
	else {
		if (useAttackRange) {
			if (user != nullptr) {
				result = user->GetAttackRange(false);
			}
			else {
				result = 1;
			}
		}
		else {
			result = range;
		}
	}

	if (user != nullptr) {
		result += user->GetRangeIncrease(abilityOptions, false);
	}

	return result;
}

bool Ability::IsSpell() {
	return std::find(categories.begin(), categories.end(), Category::SPELL) != categories.end();
}

int Ability::GetAISearchRange() {
	if (useAttackRange && user != nullptr) {
		return user->GetAttackRange(false);
	}
	else {
		return aiSearchRange;
	}
}

bool Ability::CanTargetOutsideCursor() {
	return targetOutsideCursor;
}

bool Ability::IgnoreBodyBlock() {
	return ignoreBodyBlock;
}

bool Ability::IgnoreLineOfSight() {
	return ignoreLineOfSight;
}

bool Ability::IsFriendly() {
	return isFriendlyAbility;
}

bool Ability::IsCasted() {
	return usage == UseType::CAST;
}

int Ability::GetCastTime(bool consumeBuffs) {
	int time = 0;

	if (user != nullptr) {
		double haste = user->GetHaste(abilityOptions, consumeBuffs);
		double flatReduction = user->GetCastTimeReduction(abilityOptions, consumeBuffs);

		if (isAttack) {
			time = user->GetAttackSpeed() * attackSpeedMultipler;
		}
		else {
			time = castTime;
		}

		return (time - flatReduction) * (1.0 / haste);
	}
	else {
		if (isAttack) {
			return -100 * attackSpeedMultipler; // negative flag for tooltips
		}
		else {
			return castTime;
		}
	}
	 
}

int Ability::GetMPCost() {
	// todo: resource cost reduction
	return mpCost;
}

int Ability::GetSPCost() {
	// todo: resource cost reduction
	return spCost;
}

int Ability::GetCooldown() {
	if (user != nullptr) {
		return cooldown * (1.0 - user->GetCooldownReduction(abilityOptions, false));
	}
	else {
		return cooldown;
	}
}

int Ability::GetCurrentCooldown() {
	return currentCooldown;
}

void Ability::DecrementCooldown() {
	if (currentCooldown > 0) {
		currentCooldown--;
	}
}

void Ability::ResetCooldown() {
	currentCooldown = 0;
}

std::string Ability::GetDescription() {
	return "No description.";
}

void Ability::setAttackDefault() {
	canDodge = true;
	canBlock = true;
	canCounter = true;
	canCrit = true;
	canDoubleStrike = true;
	canIncreaseRange = true; // mostly for bows
	isAttack = true;
	isGroundTargeted = false;
	ignoreBodyBlock = false;
	ignoreLineOfSight = false;
	requireTargetsInArea = true;
	useAttackRange = true;

	usage = UseType::INSTANT;
}

void Ability::setHarmfulSpellDefault() {
	canBlock = false;
	canCounter = false;
	canCrit = true;
	canDodge = false;
	canDoubleStrike = false;
	canIncreaseRange = true;
	isAttack = false;
	isGroundTargeted = false;
	ignoreBodyBlock = false;
	ignoreLineOfSight = false;
	requireTargetsInArea = true;
	useAttackRange = false;
}

void Ability::setHelpfulSpellDefault() {
	canBlock = false;
	canCounter = false;
	canCrit = true;
	canDodge = false;
	canDoubleStrike = false;
	canIncreaseRange = true;
	isAttack = false;
	isFriendlyAbility = true;
	isGroundTargeted = false;
	ignoreBodyBlock = true;
	ignoreLineOfSight = false;
	requireTargetsInArea = true;
	useAttackRange = false;
}

void Ability::setAbilityOptions() {
	abilityOptions.AbilityID = abilityID;
	abilityOptions.AllowedWeaponTypes = usableWeapons;
	abilityOptions.BonusCritChance = bonusCrit;
	abilityOptions.BonusCritDamage = bonusCritDmg;
	abilityOptions.BonusDoubleStrikeChance = bonusDoubleStrike;
	abilityOptions.BonusHitChance = bonusHit;
	abilityOptions.BonusLifeLeech = bonusLifeLeech;
	abilityOptions.BonusManaLeech = bonusManaLeech;
	abilityOptions.BonusStaminaLeech = bonusStaminaLeech;
	abilityOptions.CanBlock = canBlock;
	abilityOptions.CanCounter = canCounter;
	abilityOptions.CanCrit = canCrit;
	abilityOptions.CanDodge = canDodge;
	abilityOptions.CanDoubleStrike = canDoubleStrike;
	abilityOptions.Categories = categories;
	abilityOptions.Elements = elements;
	abilityOptions.EventName = name;
}

void Ability::consumeResources() {
	// todo: get resource cost reduction
	user->SpendResource(Attribute::HP, hpCost);
	user->SpendResource(Attribute::MP, mpCost);
	user->SpendResource(Attribute::SP, spCost);
}

void Ability::exhaustUser() {
	int time = 0;
	double haste = user->GetHaste(abilityOptions, true);
	double flatReduction = user->GetCastTimeReduction(abilityOptions, true);

	if (isAttack) {
		time = user->GetAttackSpeed() * attackSpeedMultipler;
	}
	else {
		time = castTime;
	}

	user->Wait((time - flatReduction) * (1.0 / haste));
}

void Ability::putOnCooldown() {
	currentCooldown = calcCooldown * (1.0 - user->GetCooldownReduction(abilityOptions, true));
	//messageLog.AddMessage(name + " CD: " + std::to_string(currentCooldown));
	if (currentCooldown < 0) {
		currentCooldown = 0;
	}
}

void Ability::rotateArea(sf::Vector3i cursor, std::vector<sf::Vector3i>& area) {
	if (user != nullptr) {
		for (size_t i = 0; i < area.size(); i++) {
			area[i] = Hex::OffsetHex(area[i], user->GetHexPosition());
		}
	}

	//area = Hex::RotateHex(user->GetHexPosition(), cursor, area);
	std::vector<sf::Vector3i> targetArea = Hex::AllHexRotations(user->GetHexPosition(), keyTile + user->GetHexPosition());
	for (int i = 0; i < 6; i++) {
		if (cursor == targetArea[i]) {
			area = Hex::RotateHex(user->GetHexPosition(), cursor, area, i);
			break;
		}
	}

	if (battleScene != nullptr) {
		area = battleScene->GetLineOfSight(user->GetHexPosition(), area, user->IsAlive(), areaIgnoreBodyBlock, areaIgnoreLineOfSight);
	}
}

bool Ability::doubleStrike(ActorPtr& target) {
	if (canDoubleStrike) {
		EventResult eventResult;
		double doubleStrikeChance = bonusDoubleStrike;
		eventResult.DidDoubleStrike = doubleStrikeChance > 0.0 && doubleStrikeChance >= Random::RandDouble(0.0, 1.0);

		// Double strikes can't trigger additional double strikes.
		if (eventResult.DidDoubleStrike) {
			EventOptions dsEventOptions;
			dsEventOptions.CanBlock = true;
			dsEventOptions.CanCounter = true;
			dsEventOptions.CanCrit = true;
			dsEventOptions.CanDodge = true;
			dsEventOptions.CanDoubleStrike = false;
			dsEventOptions.EventName = "double strike";

			const double doubleStrikeDamage = 1.0;

			Combat::WeaponAttack(user, target, doubleStrikeDamage, false, dsEventOptions);
			Combat::WeaponAttack(user, target, doubleStrikeDamage * offHandBasicMultiplier, true, dsEventOptions);

			return true;
		}
	}
	return false;
}
