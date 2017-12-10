// ==================================
//
// statmod.cpp
//
// ==================================

#include "statMod.h"

#include <algorithm>

StatMod::StatMod(StatModType statMod, double value) {
	this->statModType = statMod;
	this->value = value;
	this->categories = { Category::ANY };
	this->elements = { Element::NONE };

	this->ability = AbilityID::UNDEFINED;
	this->aura = AuraID::UNDEFINED;
	this->onHitElements = { Element::NONE };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Category> categories) {
	this->statModType = statMod;
	this->value = value;
	this->categories = categories;
	this->elements = { Element::NONE };

	this->ability = AbilityID::UNDEFINED;
	this->aura = AuraID::UNDEFINED;
	this->onHitElements = { Element::NONE };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Category> categories, std::vector<Element> element){
	this->statModType = statMod;
	this->value = value;
	this->categories = categories;
	this->elements = element;

	this->ability = AbilityID::UNDEFINED;
	this->aura = AuraID::UNDEFINED;
	this->onHitElements = { Element::NONE };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, std::vector<Category> categories) {
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->categories = categories;
	this->elements = { Element::NONE };

	this->ability = AbilityID::UNDEFINED;
	this->aura = AuraID::UNDEFINED;
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, std::vector<Category> categories, std::vector<Element> element){
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->categories = categories;
	this->elements = element;

	this->ability = AbilityID::UNDEFINED;
	this->aura = AuraID::UNDEFINED;
}

StatMod::StatMod(StatModType statMod, double value, AbilityID ability){
	this->statModType = statMod;
	this->value = value;
	this->ability = ability;
	this->aura = AuraID::UNDEFINED;

	this->categories = { Category::NONE };
	this->elements = { Element::NONE };
	this->onHitElements = { Element::NONE };
}

StatMod::StatMod(StatModType statMod, double value, AuraID aura) {
	this->statModType = statMod;
	this->value = value;
	this->ability = AbilityID::UNDEFINED;
	this->aura = aura;

	this->categories = { Category::NONE };
	this->elements = { Element::NONE };
	this->onHitElements = { Element::NONE };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, AbilityID ability){
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->ability = ability;

	this->categories = { Category::NONE };
	this->elements = { Element::NONE };
}

StatMod::StatMod(StatModType statMod, double value, std::vector<Element> onHitElements, AuraID aura) {
	this->statModType = statMod;
	this->value = value;
	this->onHitElements = onHitElements;
	this->ability = AbilityID::UNDEFINED;
	this->aura = aura;

	this->categories = { Category::NONE };
	this->elements = { Element::NONE };
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
	if (std::find(categories.begin(), categories.end(), Category::ANY) != categories.end()) {
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
			if (eventOptions.AbilityID != AbilityID::UNDEFINED && statMods[i].GetAbility() == eventOptions.AbilityID) {
				if (isMultiplicative) {
					value *= statMods[i].GetValue() + 1.0;
				}
				else {
					value += statMods[i].GetValue();
				}
			}
			else if (eventOptions.AuraID != AuraID::UNDEFINED && statMods[i].GetAura() == eventOptions.AuraID) {
				if (isMultiplicative) {
					value *= statMods[i].GetValue() + 1.0;
				}
				else {
					value += statMods[i].GetValue();
				}
			}
			// if statMod is not for a specific ability or aura
			else if (statMods[i].GetAbility() == AbilityID::UNDEFINED && statMods[i].GetAura() == AuraID::UNDEFINED) {
				if (statMods[i].MatchesCategories(eventOptions.Categories)) {
					if (statMods[i].GetElements()[0] == Element::NONE) {
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
		StatModType::HP_MULT,
		StatModType::HP_LEECH,
		StatModType::MP_MULT,
		StatModType::MP_LEECH,
		StatModType::SP_MULT,
		StatModType::SP_LEECH,
		StatModType::STR_MULT,
		StatModType::DEX_MULT,
		StatModType::INT_MULT,
		StatModType::WIS_MULT,
		StatModType::ALL_ATTRIBUTES_MULT,
		StatModType::VIT_MULT,
		StatModType::ARMOR_MULT,
		StatModType::DAMAGE,
		StatModType::DAMAGE_TAKEN,
		StatModType::HEALING,
		StatModType::HEALING_TAKEN,
		StatModType::RESISTANCE,
		StatModType::ARMOR_PEN,
		StatModType::RESISTANCE_PEN,
		StatModType::CRIT_CHANCE,
		StatModType::CRIT_DAMAGE,
		StatModType::CRIT_CHANCE_PROTECTION,
		StatModType::CRIT_DAMAGE_PROTECTION,
		StatModType::HASTE,
		StatModType::DOUBLE_STRIKE_CHANCE,
		StatModType::DOUBLE_STRIKE_DAMAGE,
		StatModType::COUNTER_CHANCE,
		StatModType::HIT_CHANCE,
		StatModType::DODGE_CHANCE,
		StatModType::BLOCK_CHANCE,
		StatModType::HP_COST_REDUCTION,
		StatModType::MP_COST_REDUCTION,
		StatModType::SP_COST_REDUCTION,
		StatModType::COOLDOWN_REDUCTION,
		StatModType::STUN_RESISTANCE,
		StatModType::DISARM_RESISTANCE,
		StatModType::SILENCE_RESISTANCE,
		StatModType::KNOCKBACK_RESISTANCE,
		StatModType::SLOW_ROOT_RESISTANCE,
		StatModType::DEATH_RESISTANCE,
		StatModType::MOVEMENT_SPEED,
		StatModType::GOLD_FIND,
		StatModType::EXP_BOOST
	};

	if (std::find(percentBoosts.begin(), percentBoosts.end(), statModType) != percentBoosts.end()) {
		return true;
	}

	return false;
}

bool StatModCalc::IsDecimal(StatModType statModType) {
	std::vector<StatModType> decimalBoosts{
		StatModType::HP_REGEN,
		StatModType::MP_REGEN,
		StatModType::SP_REGEN
	};

	if (std::find(decimalBoosts.begin(), decimalBoosts.end(), statModType) != decimalBoosts.end()) {
		return true;
	}

	return false;
}