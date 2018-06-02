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

	if (elements[0] == Element::None) {
		return s;
	}

	// init text
	elementStrings[Element::Nonresistable] = "unresistable";
	elementStrings[Element::Physical] = "physical";
	elementStrings[Element::Arcane] = "arcane";
	elementStrings[Element::Fire] = "fire";
	elementStrings[Element::Ice] = "ice";
	elementStrings[Element::Lightning] = "lightning";
	elementStrings[Element::Poison] = "poison";
	elementStrings[Element::Water] = "water";
	elementStrings[Element::Wind] = "wind";
	elementStrings[Element::Earth] = "earth";
	elementStrings[Element::Mind] = "mind";
	elementStrings[Element::Light] = "light";
	elementStrings[Element::Dark] = "dark";
	elementStrings[Element::Astral] = "astral";
	elementStrings[Element::Spirit] = "spirit";
	elementStrings[Element::DivineHeal] = "divine";
	elementStrings[Element::NatureHeal] = "natural";

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
	modTypeStrings[StatModType::HPMult] = "Maximum HP";
	modTypeStrings[StatModType::HPRegen] = "HP per Sec";
	modTypeStrings[StatModType::HPLeech] = "Life Leech";
	modTypeStrings[StatModType::MP] = "Maximum MP";
	modTypeStrings[StatModType::MPMult] = "Maximum MP";
	modTypeStrings[StatModType::MPRegen] = "MP per Sec";
	modTypeStrings[StatModType::MPLeech] = "Mana Leech";
	modTypeStrings[StatModType::SP] = "Maximum SP";
	modTypeStrings[StatModType::SPMult] = "Maximum SP";
	modTypeStrings[StatModType::SPRegen] = "SP per Sec";
	modTypeStrings[StatModType::SPLeech] = "Stamina Leech";
	modTypeStrings[StatModType::STR] = "Strength";
	modTypeStrings[StatModType::STRMult] = "Strength";
	modTypeStrings[StatModType::DEX] = "Dexterity";
	modTypeStrings[StatModType::DEXMult] = "Dexterity";
	modTypeStrings[StatModType::INT] = "Intelligence";
	modTypeStrings[StatModType::INTMult] = "Intelligence";
	modTypeStrings[StatModType::WIS] = "Wisdom";
	modTypeStrings[StatModType::WISMult] = "Wisdom";
	modTypeStrings[StatModType::AllAttributes] = "All Attributes";
	modTypeStrings[StatModType::AllAttributesMult] = "All Attributes";
	modTypeStrings[StatModType::VIT] = "Vitality";
	modTypeStrings[StatModType::VITMult] = "Vitality";
	modTypeStrings[StatModType::Armor] = "Armor";
	modTypeStrings[StatModType::ArmorMult] = "Armor";
	modTypeStrings[StatModType::ArmorPerLevel] = "Armor Per Level";
	modTypeStrings[StatModType::Damage] = "Damage";
	modTypeStrings[StatModType::DamageTaken] = "Damage Taken";
	modTypeStrings[StatModType::Healing] = "Healing";
	modTypeStrings[StatModType::HealingTaken] = "Healing Received";
	modTypeStrings[StatModType::Resistance] = "Resistance";
	modTypeStrings[StatModType::ArmorPen] = "Armor Penetration";
	modTypeStrings[StatModType::ResistancePen] = "Resistance Penetration";
	modTypeStrings[StatModType::CritChance] = "Critical Strike Chance";
	modTypeStrings[StatModType::CritPower] = "Critical Strike Damage";
	modTypeStrings[StatModType::CritChanceProtection] = "Reduced Chance to be Critically Struck";
	modTypeStrings[StatModType::CritPowerProtection] = "Reduced Damage from Critical Strikes";
	modTypeStrings[StatModType::Haste] = "Haste";
	modTypeStrings[StatModType::CastTimeReduction] = "Cast Time Reduction";
	modTypeStrings[StatModType::Instant] = "Instant Cast";
	modTypeStrings[StatModType::Range] = "Range";
	modTypeStrings[StatModType::DoubleStrikeChance] = "Double Strike Chance";
	modTypeStrings[StatModType::DoubleStrikeDamage] = "Double Strike Damage";
	modTypeStrings[StatModType::CounterChance] = "Counter Chance";
	modTypeStrings[StatModType::OnHitDamage] = "Damage on Hit";
	modTypeStrings[StatModType::OnHitHealing] = "Life on Hit";
	modTypeStrings[StatModType::HitChance] = "Hit Chance";
	modTypeStrings[StatModType::DodgeChance] = "Dodge Chance";
	modTypeStrings[StatModType::BlockChance] = "Block Chance";
	modTypeStrings[StatModType::HPCostReduction] = "HP Cost Reduction";
	modTypeStrings[StatModType::MPCostReduction] = "MP Cost Reduction";
	modTypeStrings[StatModType::SPCostReduction] = "SP Cost Reduction";
	modTypeStrings[StatModType::CooldownReduction] = "Cooldown Reduction";
	modTypeStrings[StatModType::StunResistance] = "Stun Resistance";
	modTypeStrings[StatModType::DisarmResistance] = "Disarm Resistance";
	modTypeStrings[StatModType::SilenceResistance] = "Silence Resistance";
	modTypeStrings[StatModType::KnockbackResistance] = "Knockback Resistance";
	modTypeStrings[StatModType::SlowRootResistance] = "Snare Resistance";
	modTypeStrings[StatModType::DeathResistance] = "Death Resistance";
	modTypeStrings[StatModType::MovementSpeed] = "Movement Speed";
	modTypeStrings[StatModType::GoldFind] = "Gold Find";
	modTypeStrings[StatModType::EXPBoost] = "EXP Gained";

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
	case StatModType::HPRegen:					return "HP per Sec";
	case StatModType::HPLeech:					return "Life Leech";
	case StatModType::MP:						return "Maximum MP";
	case StatModType::MPRegen:					return "MP per Sec";
	case StatModType::MPLeech:					return "Mana Leech";
	case StatModType::SP:						return "Maximum SP";
	case StatModType::SPRegen:					return "SP per Sec";
	case StatModType::SPLeech:					return "Stamina Leech";
	case StatModType::STR:						return "Strength";
	case StatModType::DEX:						return "Dexterity";
	case StatModType::INT:						return "Intelligence";
	case StatModType::WIS:						return "Wisdom";
	case StatModType::AllAttributes:			return "All Attributes";
	case StatModType::VIT:						return "Vitality";
	case StatModType::Armor:					return "Armor";
	case StatModType::Damage:					return "Damage";
	case StatModType::Healing:					return "Healing";
	case StatModType::ArmorPen:				return "Armor Penetration";
	case StatModType::CritChance:				return "Critical Strike Chance";
	case StatModType::CritPower:				return "Critical Strike Damage";
	case StatModType::CritChanceProtection:	return "Reduced Chance to be Critically Struck";
	case StatModType::Haste:					return "Haste";
	case StatModType::DoubleStrikeChance:		return "Double Strike Chance";
	case StatModType::CounterChance:			return "Counter Chance";
	case StatModType::OnHitDamage:			return "Damage on Hit";
	case StatModType::HitChance:				return "Hit Chance";
	case StatModType::DodgeChance:				return "Dodge Chance";
	case StatModType::BlockChance:				return "Block Chance";
	case StatModType::MPCostReduction:		return "MP Cost Reduction";
	case StatModType::SPCostReduction:		return "SP Cost Reduction";
	case StatModType::CooldownReduction:		return "Cooldown Reduction";
	case StatModType::StunResistance:			return "Stun Resistance";
	case StatModType::DisarmResistance:		return "Disarm Resistance";
	case StatModType::SilenceResistance:		return "Silence Resistance";
	case StatModType::KnockbackResistance:		return "Knockback Resistance";
	case StatModType::SlowRootResistance:		return "Snare Resistance";
	case StatModType::DeathResistance:			return "Death Resistance";
	case StatModType::MovementSpeed:			return "Movement Speed";
	case StatModType::GoldFind:				return "Gold Find";
	case StatModType::EXPBoost:				return "EXP Gained";
	default:									return "Unknown";
	}
}