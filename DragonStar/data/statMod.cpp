// ==================================
//
// statmod.cpp
//
// ==================================

#include "statMod.h"

#include <algorithm>

#include "id/abilityID.h"
#include "id/auraID.h"
#include "id/category.h"
#include "id/element.h"
#include "id/statModType.h"

StatMod::StatMod(StatModType statMod, double value) {
	this->statModType = statMod;
	this->value = value;
	this->categories = { Category::Any };
	this->elements = { Element::None };

	this->ability = AbilityID::Undefined;
	this->aura = AuraID::Undefined;
	this->onHitElements = { Element::None };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Category> categories) {
	this->statModType = statMod;
	this->value = value;
	this->categories = categories;
	this->elements = { Element::None };

	this->ability = AbilityID::Undefined;
	this->aura = AuraID::Undefined;
	this->onHitElements = { Element::None };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Category> categories, std::vector<Element> element){
	this->statModType = statMod;
	this->value = value;
	this->categories = categories;
	this->elements = element;

	this->ability = AbilityID::Undefined;
	this->aura = AuraID::Undefined;
	this->onHitElements = { Element::None };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, std::vector<Category> categories) {
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->categories = categories;
	this->elements = { Element::None };

	this->ability = AbilityID::Undefined;
	this->aura = AuraID::Undefined;
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, std::vector<Category> categories, std::vector<Element> element){
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->categories = categories;
	this->elements = element;

	this->ability = AbilityID::Undefined;
	this->aura = AuraID::Undefined;
}

StatMod::StatMod(StatModType statMod, double value, AbilityID ability){
	this->statModType = statMod;
	this->value = value;
	this->ability = ability;
	this->aura = AuraID::Undefined;

	this->categories = { Category::None };
	this->elements = { Element::None };
	this->onHitElements = { Element::None };
}

StatMod::StatMod(StatModType statMod, double value, AuraID aura) {
	this->statModType = statMod;
	this->value = value;
	this->ability = AbilityID::Undefined;
	this->aura = aura;

	this->categories = { Category::None };
	this->elements = { Element::None };
	this->onHitElements = { Element::None };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, AbilityID ability){
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->ability = ability;

	this->categories = { Category::None };
	this->elements = { Element::None };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, AuraID aura) {
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->ability = AbilityID::Undefined;
	this->aura = aura;

	this->categories = { Category::None };
	this->elements = { Element::None };
}

StatMod::StatMod(StatMod& copy, int multiplier) {
	this->statModType = copy.GetStatModType();
	this->value = copy.GetValue() * multiplier;
	this->onHitElements = copy.GetOnHitElements();
	this->ability = copy.GetAbility();
	this->aura = copy.GetAura();

	this->categories = copy.GetCategories();
	this->elements = copy.GetElements();
}

std::vector<Category> StatMod::GetCategories(){
	return categories;
}

std::vector<Element> StatMod::GetElements() {
	return elements;
}

AbilityID StatMod::GetAbility(){
	return ability;
}

AuraID StatMod::GetAura() {
	return aura;
}

StatModType StatMod::GetStatModType(){
	return statModType;
}

double StatMod::GetValue(){
	return value;
}

std::vector<Element> StatMod::GetOnHitElements(){
	return onHitElements;
}

bool StatMod::MatchesCategories(std::vector<Category> testCategories) {
	bool match = false;

	// check if categories contains Category::ANY, if true than statmod will apply
	if (std::find(categories.begin(), categories.end(), Category::Any) != categories.end()) {
		match = true;
	}
	else {
		std::sort(categories.begin(), categories.end());
		std::sort(testCategories.begin(), testCategories.end());
		match = std::includes(testCategories.begin(), testCategories.end(), categories.begin(), categories.end()); // must match all the categories to apply
	}

	return match;
}

void StatModCalc::GetStatModValue(double& value, std::vector<StatMod>& statMods, StatModType statModType, bool isMultiplicative) {
	for (size_t i = 0; i < statMods.size(); i++) {
		if (statMods[i].GetStatModType() == statModType) {
			if (isMultiplicative) {
				value *= statMods[i].GetValue() + 1.0;
			}
			else {
				value += statMods[i].GetValue();
			}
		}
	}
}

void StatModCalc::GetStatModValue(double& value, std::vector<StatMod>& statMods, StatModType statModType, EventOptions& eventOptions, bool isMultiplicative) {
	for (size_t i = 0; i < statMods.size(); i++) {
		if (statMods[i].GetStatModType() == statModType) {
			if (eventOptions.AbilityID != AbilityID::Undefined && statMods[i].GetAbility() == eventOptions.AbilityID) {
				if (isMultiplicative) {
					value *= statMods[i].GetValue() + 1.0;
				}
				else {
					value += statMods[i].GetValue();
				}
			}
			else if (eventOptions.AuraID != AuraID::Undefined && statMods[i].GetAura() == eventOptions.AuraID) {
				if (isMultiplicative) {
					value *= statMods[i].GetValue() + 1.0;
				}
				else {
					value += statMods[i].GetValue();
				}
			}
			// if statMod is not for a specific ability or aura
			else if (statMods[i].GetAbility() == AbilityID::Undefined && statMods[i].GetAura() == AuraID::Undefined) {
				if (statMods[i].MatchesCategories(eventOptions.Categories)) {
					if (statMods[i].GetElements()[0] == Element::None) {
						if (isMultiplicative) {
							value *= statMods[i].GetValue() + 1.0;
						}
						else {
							value += statMods[i].GetValue();
						}
					}
					// if statMod has element requirement
					else {
						double matches = 0.0;
						std::vector<Element> statModElements = statMods[i].GetElements();
						for (size_t j = 0; j < eventOptions.Elements.size(); j++) {
							if (std::find(statModElements.begin(), statModElements.end(), eventOptions.Elements[j]) != statModElements.end()) {
								matches++;
							}
						}
						double elementMultiplier = matches / eventOptions.Elements.size(); // if only some of the elements match, the value is partially applied
						if (isMultiplicative) {
							value *= statMods[i].GetValue() * elementMultiplier + 1.0;
						}
						else {
							value += statMods[i].GetValue() * elementMultiplier;
						}
					}
				}
			}
		}
	}
}

bool StatModCalc::IsPercent(StatModType statModType) {
	std::vector<StatModType> percentBoosts{
		StatModType::HPMult,
		StatModType::HPLeech,
		StatModType::MPMult,
		StatModType::MPLeech,
		StatModType::SPMult,
		StatModType::SPLeech,
		StatModType::STRMult,
		StatModType::DEXMult,
		StatModType::INTMult,
		StatModType::WISMult,
		StatModType::AllAttributesMult,
		StatModType::VITMult,
		StatModType::ArmorMult,
		StatModType::Damage,
		StatModType::DamageTaken,
		StatModType::Healing,
		StatModType::HealingTaken,
		StatModType::Resistance,
		StatModType::ArmorPen,
		StatModType::ResistancePen,
		StatModType::CritChance,
		StatModType::CritPower,
		StatModType::CritChanceProtection,
		StatModType::CritPowerProtection,
		StatModType::Haste,
		StatModType::DoubleStrikeChance,
		StatModType::DoubleStrikeDamage,
		StatModType::CounterChance,
		StatModType::HitChance,
		StatModType::DodgeChance,
		StatModType::BlockChance,
		StatModType::HPCostReduction,
		StatModType::MPCostReduction,
		StatModType::SPCostReduction,
		StatModType::CooldownReduction,
		StatModType::StunResistance,
		StatModType::DisarmResistance,
		StatModType::SilenceResistance,
		StatModType::KnockbackResistance,
		StatModType::SlowRootResistance,
		StatModType::DeathResistance,
		StatModType::MovementSpeed,
		StatModType::GoldFind,
		StatModType::EXPBoost
	};

	if (std::find(percentBoosts.begin(), percentBoosts.end(), statModType) != percentBoosts.end()) {
		return true;
	}

	return false;
}

bool StatModCalc::IsDecimal(StatModType statModType) {
	std::vector<StatModType> decimalBoosts{
		StatModType::HPRegen,
		StatModType::MPRegen,
		StatModType::SPRegen
	};

	if (std::find(decimalBoosts.begin(), decimalBoosts.end(), statModType) != decimalBoosts.end()) {
		return true;
	}

	return false;
}