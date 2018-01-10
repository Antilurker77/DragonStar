// ==================================
//
// idString.cpp
//
// ==================================

#include "dataString.h"

#include <unordered_map>
#include <iomanip>
#include <sstream>

#include "id/category.h"
#include "id/element.h"
#include "id/statModType.h"

std::string DataString::ElementString(std::vector<Element>& elements, bool capitalize) {
	std::unordered_map<Element, std::string> elementStrings;
	std::string s = "";

	if (elements[0] == Element::NONE) {
		return s;
	}

	// init text
	elementStrings[Element::NONRESISTABLE] = "unresistable";
	elementStrings[Element::PHYSICAL] = "physical";
	elementStrings[Element::ARCANE] = "arcane";
	elementStrings[Element::FIRE] = "fire";
	elementStrings[Element::ICE] = "ice";
	elementStrings[Element::LIGHTNING] = "lightning";
	elementStrings[Element::POISON] = "poison";
	elementStrings[Element::WATER] = "water";
	elementStrings[Element::WIND] = "wind";
	elementStrings[Element::EARTH] = "earth";
	elementStrings[Element::MIND] = "mind";
	elementStrings[Element::LIGHT] = "light";
	elementStrings[Element::DARK] = "dark";
	elementStrings[Element::ASTRAL] = "astral";
	elementStrings[Element::SPIRIT] = "spirit";
	elementStrings[Element::DIVINE_HEAL] = "divine";
	elementStrings[Element::NATURE_HEAL] = "natural";

	size_t elementSize = elements.size();
	for (size_t i = 0; i < elementSize; i++) {
		std::string add = elementStrings[elements[i]];
		if (capitalize) {
			add[0] = toupper(add[0]);
		}

		// final and
		if (i == elementSize - 2) {
			add += " and ";
		}
		else if (i != elementSize - 1) {
			add += ", ";
		}
		s += add;
	}

	return s;
}

std::string DataString::StatModString(StatMod& statMod) {
	std::unordered_map<StatModType, std::string> modTypeStrings;
	std::string s;
	bool isPercent = false;
	bool isDecimal = false;

	modTypeStrings[StatModType::HP] = "Maximum HP";
	modTypeStrings[StatModType::HP_MULT] = "Maximum HP";
	modTypeStrings[StatModType::HP_REGEN] = "HP per Sec";
	modTypeStrings[StatModType::HP_LEECH] = "Life Leech";
	modTypeStrings[StatModType::MP] = "Maximum MP";
	modTypeStrings[StatModType::MP_MULT] = "Maximum MP";
	modTypeStrings[StatModType::MP_REGEN] = "MP per Sec";
	modTypeStrings[StatModType::MP_LEECH] = "Mana Leech";
	modTypeStrings[StatModType::SP] = "Maximum SP";
	modTypeStrings[StatModType::SP_MULT] = "Maximum SP";
	modTypeStrings[StatModType::SP_REGEN] = "SP per Sec";
	modTypeStrings[StatModType::SP_LEECH] = "Stamina Leech";
	modTypeStrings[StatModType::STR] = "Strength";
	modTypeStrings[StatModType::STR_MULT] = "Strength";
	modTypeStrings[StatModType::DEX] = "Dexterity";
	modTypeStrings[StatModType::DEX_MULT] = "Dexterity";
	modTypeStrings[StatModType::INT] = "Intelligence";
	modTypeStrings[StatModType::INT_MULT] = "Intelligence";
	modTypeStrings[StatModType::WIS] = "Wisdom";
	modTypeStrings[StatModType::WIS_MULT] = "Wisdom";
	modTypeStrings[StatModType::ALL_ATTRIBUTES] = "All Attributes";
	modTypeStrings[StatModType::ALL_ATTRIBUTES_MULT] = "All Attributes";
	modTypeStrings[StatModType::VIT] = "Vitality";
	modTypeStrings[StatModType::VIT_MULT] = "Vitality";
	modTypeStrings[StatModType::ARMOR] = "Armor";
	modTypeStrings[StatModType::ARMOR_MULT] = "Armor";
	modTypeStrings[StatModType::ARMOR_PER_LEVEL] = "Armor Per Level";
	modTypeStrings[StatModType::DAMAGE] = "Damage";
	modTypeStrings[StatModType::DAMAGE_TAKEN] = "Damage Taken";
	modTypeStrings[StatModType::HEALING] = "Healing";
	modTypeStrings[StatModType::HEALING_TAKEN] = "Healing Received";
	modTypeStrings[StatModType::RESISTANCE] = "Resistance";
	modTypeStrings[StatModType::ARMOR_PEN] = "Armor Penetration";
	modTypeStrings[StatModType::RESISTANCE_PEN] = "Resistance Penetration";
	modTypeStrings[StatModType::CRIT_CHANCE] = "Critical Strike Chance";
	modTypeStrings[StatModType::CRIT_DAMAGE] = "Critical Strike Damage";
	modTypeStrings[StatModType::CRIT_CHANCE_PROTECTION] = "Reduced Chance to be Critically Struck";
	modTypeStrings[StatModType::CRIT_DAMAGE_PROTECTION] = "Reduced Damage from Critical Strikes";
	modTypeStrings[StatModType::HASTE] = "Haste";
	modTypeStrings[StatModType::CAST_TIME_REDUCTION] = "Cast Time Reduction";
	modTypeStrings[StatModType::INSTANT] = "Instant Cast";
	modTypeStrings[StatModType::RANGE] = "Range";
	modTypeStrings[StatModType::DOUBLE_STRIKE_CHANCE] = "Double Strike Chance";
	modTypeStrings[StatModType::DOUBLE_STRIKE_DAMAGE] = "Double Strike Damage";
	modTypeStrings[StatModType::COUNTER_CHANCE] = "Counter Chance";
	modTypeStrings[StatModType::ON_HIT_DAMAGE] = "Damage on Hit";
	modTypeStrings[StatModType::ON_HIT_HEALING] = "Life on Hit";
	modTypeStrings[StatModType::HIT_CHANCE] = "Hit Chance";
	modTypeStrings[StatModType::DODGE_CHANCE] = "Dodge Chance";
	modTypeStrings[StatModType::BLOCK_CHANCE] = "Block Chance";
	modTypeStrings[StatModType::HP_COST_REDUCTION] = "HP Cost Reduction";
	modTypeStrings[StatModType::MP_COST_REDUCTION] = "MP Cost Reduction";
	modTypeStrings[StatModType::SP_COST_REDUCTION] = "SP Cost Reduction";
	modTypeStrings[StatModType::COOLDOWN_REDUCTION] = "Cooldown Reduction";
	modTypeStrings[StatModType::STUN_RESISTANCE] = "Stun Resistance";
	modTypeStrings[StatModType::DISARM_RESISTANCE] = "Disarm Resistance";
	modTypeStrings[StatModType::SILENCE_RESISTANCE] = "Silence Resistance";
	modTypeStrings[StatModType::KNOCKBACK_RESISTANCE] = "Knockback Resistance";
	modTypeStrings[StatModType::SLOW_ROOT_RESISTANCE] = "Snare Resistance";
	modTypeStrings[StatModType::DEATH_RESISTANCE] = "Death Resistance";
	modTypeStrings[StatModType::MOVEMENT_SPEED] = "Movement Speed";
	modTypeStrings[StatModType::GOLD_FIND] = "Gold Find";
	modTypeStrings[StatModType::EXP_BOOST] = "EXP Gained";

	double value = statMod.GetValue();
	if (value < 0) {
		s += "-";
	}
	else {
		s += "+";
	}

	if (StatModCalc::IsPercent(statMod.GetStatModType())) {
		value = std::round(value * 1000) / 10;
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << value;
		s += ss.str() + "% ";
	}
	else if (StatModCalc::IsDecimal(statMod.GetStatModType())) {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(1) << value;
		s += ss.str() + " ";
	}
	else {
		std::stringstream ss;
		ss << std::fixed << std::setprecision(0) << value;
		s += ss.str() + " ";
	}

	std::string onHitElementText = DataString::ElementString(statMod.GetOnHitElements(), true);
	if (onHitElementText.length() > 0) {
		s += onHitElementText + " ";
	}

	std::string elementText = DataString::ElementString(statMod.GetElements(), true);
	if (elementText.length() > 0) {
		s += elementText + " ";
	}
	s += modTypeStrings[statMod.GetStatModType()];

	return s;
}

std::string DataString::StatModTypeString(StatModType statModType) {
	switch (statModType) {
	case StatModType::HP:						return "Maximum HP";
	case StatModType::HP_REGEN:					return "HP per Sec";
	case StatModType::HP_LEECH:					return "Life Leech";
	case StatModType::MP:						return "Maximum MP";
	case StatModType::MP_REGEN:					return "MP per Sec";
	case StatModType::MP_LEECH:					return "Mana Leech";
	case StatModType::SP:						return "Maximum SP";
	case StatModType::SP_REGEN:					return "SP per Sec";
	case StatModType::SP_LEECH:					return "Stamina Leech";
	case StatModType::STR:						return "Strength";
	case StatModType::DEX:						return "Dexterity";
	case StatModType::INT:						return "Intelligence";
	case StatModType::WIS:						return "Wisdom";
	case StatModType::ALL_ATTRIBUTES:			return "All Attributes";
	case StatModType::VIT:						return "Vitality";
	case StatModType::ARMOR:					return "Armor";
	case StatModType::DAMAGE:					return "Damage";
	case StatModType::HEALING:					return "Healing";
	case StatModType::ARMOR_PEN:				return "Armor Penetration";
	case StatModType::CRIT_CHANCE:				return "Critical Strike Chance";
	case StatModType::CRIT_DAMAGE:				return "Critical Strike Damage";
	case StatModType::CRIT_CHANCE_PROTECTION:	return "Reduced Chance to be Critically Struck";
	case StatModType::HASTE:					return "Haste";
	case StatModType::DOUBLE_STRIKE_CHANCE:		return "Double Strike Chance";
	case StatModType::COUNTER_CHANCE:			return "Counter Chance";
	case StatModType::ON_HIT_DAMAGE:			return "Damage on Hit";
	case StatModType::HIT_CHANCE:				return "Hit Chance";
	case StatModType::DODGE_CHANCE:				return "Dodge Chance";
	case StatModType::BLOCK_CHANCE:				return "Block Chance";
	case StatModType::MP_COST_REDUCTION:		return "MP Cost Reduction";
	case StatModType::SP_COST_REDUCTION:		return "SP Cost Reduction";
	case StatModType::COOLDOWN_REDUCTION:		return "Cooldown Reduction";
	case StatModType::STUN_RESISTANCE:			return "Stun Resistance";
	case StatModType::DISARM_RESISTANCE:		return "Disarm Resistance";
	case StatModType::SILENCE_RESISTANCE:		return "Silence Resistance";
	case StatModType::KNOCKBACK_RESISTANCE:		return "Knockback Resistance";
	case StatModType::SLOW_ROOT_RESISTANCE:		return "Snare Resistance";
	case StatModType::DEATH_RESISTANCE:			return "Death Resistance";
	case StatModType::MOVEMENT_SPEED:			return "Movement Speed";
	case StatModType::GOLD_FIND:				return "Gold Find";
	case StatModType::EXP_BOOST:				return "EXP Gained";
	default:									return "Unknown";
	}
}