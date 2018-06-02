// ==================================
//
// equipment.cpp
//
// ==================================

#include "equipment.h"

#include "id/abilityID.h"
#include "id/attribute.h"
#include "id/category.h"
#include "id/element.h"
#include "id/equipType.h"
#include "id/itemQuality.h"
#include "id/statModType.h"
#include "../core/random.h"

#include <unordered_map>

unsigned int Equipment::GetPrice() {
	double value = 10 + (tier - 1);

	if (IsWeapon()) {
		if (IsTwoHanded()) {
			value *= 3;
		}
		else {
			value *= 1.5;
		}
	}

	for (auto sm : statMods) {
		double mult = 1.0;
		switch (sm.GetStatModType()) {
		case StatModType::HP:
			mult = 0.1;
			break;
		case StatModType::HPLeech:
			mult = 280.0;
			break;
		case StatModType::MP:
			mult = 0.5;
			break;
		case StatModType::MPRegen:
			mult = 3.0;
			break;
		case StatModType::MPLeech:
			mult = 320.0;
			break;
		case StatModType::SPRegen:
			mult = 6.0;
			break;
		case StatModType::AllAttributes:
			mult = 2.0;
			break;
		case StatModType::VIT:
			mult = 1.4;
			break;
		case StatModType::Armor:
			mult = 1.9;
			break;
		case StatModType::Damage:
			mult = 120.0;
			break;
		case StatModType::Healing:
			mult = 240.0;
			break;
		case StatModType::ArmorPen:
			mult = 100.0;
			break;
		case StatModType::CritChance:
			mult = 100.0;
			break;
		case StatModType::CritPower:
			mult = 80.0;
			break;
		case StatModType::Haste:
			mult = 100.0;
			break;
		case StatModType::DoubleStrikeChance:
			mult = 100.0;
			break;
		case StatModType::CounterChance:
			mult = 66.7;
			break;
		case StatModType::OnHitDamage:
			mult = 1.0;
			break;
		case StatModType::HitChance:
			mult = 75.0;
			break;
		case StatModType::BlockChance:
			mult = 200.0;
			break;
		case StatModType::MPCostReduction:
			mult = 150.0;
			break;
		case StatModType::SPCostReduction:
			mult = 150.0;
			break;
		case StatModType::CooldownReduction:
			mult = 120.0;
			break;
		case StatModType::MovementSpeed:
			mult = 120.0;
			break;
		case StatModType::GoldFind:
			mult = 400.0;
			break;
		case StatModType::Resistance:
			mult = 0.0;
			break;
		default:
			mult = 1.0;
			break;
		}

		value += sm.GetValue() * mult;
	}

	if (itemQuality == ItemQuality::Rare) {
		value *= 1.1;
	}
	else if (itemQuality == ItemQuality::Mythic) {
		value *= 1.25;
	}

	return (unsigned int)std::round(value);
}

bool Equipment::IsEquipment() {
	return true;
}

std::string Equipment::GetTextureFilepath() {
	return textureFilepath;
}

EquipType Equipment::GetEquipType() {
	return equipType;
}

EquipmentID Equipment::GetEquipmentID() {
	return equipmentID;
}

int Equipment::GetEquipPower() {
	return equipPower;
}

int Equipment::GetAttackSpeed() {
	return attackSpeed;
}

int Equipment::GetAttackRange() {
	return attackRange;
}

double Equipment::GetAttackMod() {
	return attributeMultiplier;
}

std::vector<Element> Equipment::GetAttackElements() {
	return attackElements;
}

double Equipment::GetBlockChance() {
	return blockChance;
}

std::vector<StatMod> Equipment::GetStatMods() {
	return statMods;
}

std::vector<std::string> Equipment::GetExtraAffixStrings() {	
	return extraAffixes;
}

AuraID Equipment::GetOnHitAura() {
	return onHitAura;
}

bool Equipment::IsUnique() {
	return itemQuality == ItemQuality::Unique;
}

bool Equipment::IsWeapon() {
	return attackSpeed > 0;
}

bool Equipment::IsTwoHanded() {
	std::vector<EquipType> check = {
		EquipType::Sword2H,
		EquipType::Axe2H,
		EquipType::Mace2H,
		EquipType::Spear,
		EquipType::Bow,
		EquipType::Staff
	};
	if (std::find(check.begin(), check.end(), equipType) != check.end()) {
		return true;
	}
	return false;
}

bool Equipment::HasStatModType(StatModType smt) {
	for (auto s : statMods) {
		if (s.GetStatModType() == smt) {
			return true;
		}
	}

	return false;
}

std::vector<StatModType> Equipment::GetPossibleCraftMods() {
	std::vector<StatModType> craftableAffixes;
	auto possibleAffixes = getPossibleAffixes();

	for (auto smt : possibleAffixes) {
		if (smt.first != StatModType::STR && smt.first != StatModType::DEX &&
			smt.first != StatModType::INT && smt.first != StatModType::WIS) {
			craftableAffixes.push_back(smt.first);
		}
	}

	return craftableAffixes;
}

void Equipment::RollStatMods(ItemQuality quality, uint64_t seed) {
	itemQuality = quality;
	statMods.clear();
	std::mt19937_64 mt(seed);
	int statModCount = howManyStatMods(mt);
	std::vector<StatModType> selected;

	auto possibleAffixes = getPossibleAffixes();
	auto possibleElements = getPossibleElements();

	while (statModCount > 0) {
		size_t modsAdded = selected.size();
		size_t i = 0;

		// Rare or better non-jewelry items guarenteed main attribute.
		if (modsAdded == 0 && (equipType != EquipType::Neck && equipType!= EquipType::Ring) && itemQuality >= ItemQuality::Rare) {
			// Wands, Staves, Off-Hand, and Light Armor can roll INT or WIS.
			if (equipType == EquipType::Wand || equipType == EquipType::Staff || equipType == EquipType::OffHand ||
				equipType == EquipType::LightHead || equipType == EquipType::LightBody || equipType == EquipType::LightHands || equipType == EquipType::LightFeet) {
				i = Random::RandSizeT(mt, 0, 1);
			}
			else {
				i = 0;
			}
		}
		else {
			bool searching = true;
			while (searching) {
				i = Random::RandSizeT(mt, 0, possibleAffixes.size() - 1 - modsAdded);
				if (Random::RandDouble(mt, 0.0, 1.0) < possibleAffixes[i].second) {
					searching = false;
				}
			};
		}

		selected.push_back(possibleAffixes[i].first);

		std::swap(possibleAffixes[i], possibleAffixes[possibleAffixes.size() - 1 - modsAdded]);
		statModCount--;
	}

	std::sort(selected.begin(), selected.end());

	std::vector<Element> damageElements;
	std::vector<Element> onHitElements;

	for (auto s : selected) {
		double value = 0.0;
		Element element = Element::None;
		if (s == StatModType::Damage) {
			bool newElement = false;
			while (!newElement) {
				size_t choice = Random::RandSizeT(mt, 0, possibleElements.size() - 1);
				element = possibleElements[choice];
				if (std::find(damageElements.begin(), damageElements.end(), element) == damageElements.end()) {
					damageElements.push_back(element);
					newElement = true;
				}
			}
		}

		if (s == StatModType::OnHitDamage) {
			bool newElement = false;
			while (!newElement) {
				size_t choice = Random::RandSizeT(mt, 0, possibleElements.size() - 1);
				element = possibleElements[choice];
				if (std::find(onHitElements.begin(), onHitElements.end(), element) == onHitElements.end()) {
					onHitElements.push_back(element);
					newElement = true;
				}
			}
		}

		value = rollMod(s, mt);

		if (s == StatModType::OnHitDamage) {
			statMods.push_back(StatMod(s, value, { element }, AbilityID::Undefined));
		}
		else {
			statMods.push_back(StatMod(s, value, { Category::Any }, { element }));
		}
	}

	if (!IsWeapon()) {
		rollResistanceStatMods(mt);
	}
}

void Equipment::OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {

}

int Equipment::howManyStatMods(std::mt19937_64& mt) {
	switch (itemQuality) {
	case ItemQuality::Common:
		if (equipType == EquipType::Ring || equipType == EquipType::Neck || equipType == EquipType::OffHand) {
			return 1;
		}
		else {
			return 0;
		}
		break;
	case ItemQuality::Magical:
		return Random::RandInt(mt, 2, 3);
		break;
	case ItemQuality::Rare:
		return 4;
		break;
	case ItemQuality::Mythic:
		return 6;
		break;
	default:
		return 0;
		break;
	}
}

std::vector<std::pair<StatModType, double>> Equipment::getPossibleAffixes() {
	std::vector<std::pair<StatModType, double>> possibleAffixes;

	switch (equipType) {
	case EquipType::Sword1H:
	case EquipType::Sword2H:
	case EquipType::Axe1H:
	case EquipType::Axe2H:
	case EquipType::Mace1H:
	case EquipType::Mace2H:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::AllAttributes, 1.0 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::SPRegen, 1.0 },
			{ StatModType::HPLeech, 0.5 },
			{ StatModType::MPLeech, 0.5 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::OnHitDamage, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::Dagger:
	case EquipType::Claw:
	case EquipType::Spear:
	case EquipType::Bow:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::AllAttributes, 1.0 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::SPRegen, 1.0 },
			{ StatModType::HPLeech, 0.5 },
			{ StatModType::MPLeech, 0.5 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::OnHitDamage, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::Wand:
	case EquipType::Staff:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::AllAttributes, 1.0 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 1.0 },
			//{ StatModType::SP, 0.5 },
			//{ StatModType::SP_REGEN, 1.0 },
			{ StatModType::HPLeech, 0.5 },
			{ StatModType::MPLeech, 0.5 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::Damage, 1.0 },
			//{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			//{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			//{ StatModType::ON_HIT_DAMAGE, 1.0 },
			//{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::MPCostReduction, 1.0 },
			//{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::Shield:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 1.0 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::BlockChance, 1.0 },
			{ StatModType::SPCostReduction, 1.0 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::Buckler:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 1.0 },
			//{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 1.0 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::BlockChance, 1.0 },
			//{ StatModType::SP_COST_REDUCTION, 1.0 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::OffHand:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 1.0 },
			{ StatModType::MPRegen, 1.0 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::CritPower, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::MPCostReduction, 1.0 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::LightHead:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritPower, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 }
		};
		break;
	case EquipType::LightBody:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::LightHands:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::HPLeech, 0.5 },
			{ StatModType::MPLeech, 0.5 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::OnHitDamage, 1.0 },
			{ StatModType::HitChance, 1.0 },
		};
		break;
	case EquipType::LightFeet:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::MovementSpeed, 1.0 },
		};
		break;
	case EquipType::MedHead:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritPower, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 }
		};
		break;
	case EquipType::MedBody:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::MedHands:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::HPLeech, 0.5 },
			{ StatModType::MPLeech, 0.5 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::OnHitDamage, 1.0 },
			{ StatModType::HitChance, 1.0 },
		};
		break;
	case EquipType::MedFeet:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::MovementSpeed, 1.0 },
		};
		break;
	case EquipType::HeavyHead:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritPower, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::DodgeChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 }
		};
		break;
	case EquipType::HeavyBody:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			//{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::CooldownReduction, 1.0 }
		};
		break;
	case EquipType::HeavyHands:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::HPLeech, 0.5 },
			{ StatModType::MPLeech, 0.5 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::OnHitDamage, 1.0 },
			{ StatModType::HitChance, 1.0 },
		};
		break;
	case EquipType::HeavyFeet:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::Armor, 1.0 },
			{ StatModType::Haste, 1.0 },
			//{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::MovementSpeed, 1.0 },
		};
		break;
	case EquipType::Neck:
		possibleAffixes = {
			{ StatModType::STR, 0.25 },
			{ StatModType::DEX, 0.25 },
			{ StatModType::INT, 0.25 },
			{ StatModType::WIS, 0.25 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::CooldownReduction, 1.0 },
			{ StatModType::GoldFind, 0.25 }
		};
		break;
	case EquipType::Ring:
		possibleAffixes = {
			{ StatModType::STR, 0.25 },
			{ StatModType::DEX, 0.25 },
			{ StatModType::INT, 0.25 },
			{ StatModType::WIS, 0.25 },
			{ StatModType::AllAttributes, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HPRegen, 0.33 },
			{ StatModType::MPRegen, 0.34 },
			{ StatModType::SPRegen, 0.33 },
			{ StatModType::Damage, 1.0 },
			{ StatModType::ArmorPen, 1.0 },
			{ StatModType::CritChance, 1.0 },
			{ StatModType::Haste, 1.0 },
			{ StatModType::DoubleStrikeChance, 1.0 },
			{ StatModType::HitChance, 1.0 },
			{ StatModType::MPCostReduction, 0.5 },
			{ StatModType::SPCostReduction, 0.5 },
			{ StatModType::CooldownReduction, 1.0 },
			{ StatModType::GoldFind, 0.25 }
		};
		break;
	default:
		break;
	}

	return possibleAffixes;
}

std::vector<Element> Equipment::getPossibleElements() {
	std::vector<Element> possibleElements;

	switch (equipType) {
	case EquipType::Sword1H:
	case EquipType::Sword2H:
		possibleElements = {
			Element::Arcane,
			Element::Fire,
			Element::Water,
			Element::Wind,
			Element::Earth
		};
		break;
	case EquipType::Axe1H:
	case EquipType::Axe2H:
		possibleElements = {
			Element::Physical
		};
		break;
	case EquipType::Mace1H:
	case EquipType::Mace2H:
		possibleElements = {
			Element::Physical,
			Element::Ice,
			Element::Lightning,
			Element::Earth,
			Element::Light
		};
		break;
	case EquipType::Dagger:
		possibleElements = {
			Element::Physical,
			Element::Poison,
			Element::Dark
		};
		break;
	case EquipType::Claw:
		possibleElements = {
			Element::Physical,
			Element::Poison
		};
		break;
	case EquipType::Spear:
		possibleElements = {
			Element::Lightning,
			Element::Water,
			Element::Wind
		};
		break;
	case EquipType::Bow:
		possibleElements = {
			Element::Arcane,
			Element::Fire,
			Element::Ice,
			Element::Lightning,
			Element::Poison,
			Element::Water,
			Element::Wind,
			Element::Earth,
			Element::Light,
			Element::Dark
		};
		break;
	case EquipType::Wand:
	case EquipType::Staff:
	case EquipType::OffHand:
		possibleElements = {
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
			Element::Dark
		};
		break;
	case EquipType::LightHands:
		possibleElements = {
			Element::Arcane,
			Element::Fire,
			Element::Ice,
			Element::Lightning,
			Element::Mind,
			Element::Poison,
			Element::Water,
			Element::Wind,
			Element::Earth,
			Element::Light,
			Element::Dark
		};
		break;
	case EquipType::MedHands:
		possibleElements = {
			Element::Physical,
			Element::Lightning,
			Element::Poison,
			Element::Water,
			Element::Wind,
			Element::Earth,
			Element::Dark
		};
		break;
	case EquipType::HeavyHands:
		possibleElements = {
			Element::Physical,
			Element::Arcane,
			Element::Fire,
			Element::Ice,
			Element::Lightning,
			Element::Water,
			Element::Wind,
			Element::Earth,
			Element::Light
		};
		break;
	case EquipType::Neck:
		possibleElements = {
			Element::Physical,
			Element::Arcane,
			Element::Fire,
			Element::Ice,
			Element::Lightning,
			Element::Mind,
			Element::Poison,
			Element::Water,
			Element::Wind,
			Element::Earth,
			Element::Light,
			Element::Dark
		};
		break;
	case EquipType::Ring:
		possibleElements = {
			Element::Physical,
			Element::Arcane,
			Element::Fire,
			Element::Ice,
			Element::Lightning,
			Element::Mind,
			Element::Poison,
			Element::Water,
			Element::Wind,
			Element::Earth,
			Element::Light,
			Element::Dark
		};
		break;
	default:
		break;
	}

	return possibleElements;
}

void Equipment::rollResistanceStatMods(std::mt19937_64& mt) {
	int resistCount = 0;
	std::vector<Element> possibleResists = {
		Element::Arcane,
		Element::Fire,
		Element::Ice,
		Element::Lightning,
		Element::Mind,
		Element::Poison,
		Element::Water,
		Element::Wind,
		Element::Earth,
		Element::Light,
		Element::Dark
	};

	if (itemQuality == ItemQuality::Magical) {
		resistCount = Random::RandInt(mt, 0, 1);
	}
	else if (itemQuality == ItemQuality::Rare) {
		resistCount = 1;
	}
	else if (itemQuality == ItemQuality::Mythic) {
		resistCount = 2;
	}

	for (int i = 0; i < resistCount; i++) {
		int randElement = Random::RandInt(mt, 0, possibleResists.size() - 1 - i);
		Element element = possibleResists[randElement];
		std::swap(possibleResists[randElement], possibleResists[possibleResists.size() - 1 - i]); // swap position in list so that same element isn't choosen twice

		int minResist = 5 + (((tier - 1) / 2) * 5);
		int maxResist = 10 + (((tier - 1) / 2) * 5);
		double resist = (double)Random::RandInt(mt, minResist, maxResist) / 100.0;

		statMods.push_back(StatMod(StatModType::Resistance, resist, { Category::Any }, { element }));
	}
}

double Equipment::rollMod(StatModType smt, std::mt19937_64& mt) {
	std::unordered_map<EquipType, std::unordered_map<StatModType, std::vector<int>>> ranges;
	int min = 0;
	int max = 0;
	double value = 0;

	ranges[EquipType::Sword1H][StatModType::HP] = { 14, 20, 20, 40, 40, 60 };
	ranges[EquipType::Sword1H][StatModType::MP] = { 3, 5, 5, 10, 10, 15 };
	ranges[EquipType::Sword1H][StatModType::SP] = { 3, 6, 6, 9, 9, 12 };
	ranges[EquipType::Sword1H][StatModType::SPRegen] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::Sword1H][StatModType::HPLeech] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Sword1H][StatModType::MPLeech] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Sword1H][StatModType::STR] = { 3, 5, 5, 10, 10, 14 };
	ranges[EquipType::Sword1H][StatModType::DEX] = ranges[EquipType::Sword1H][StatModType::STR];
	ranges[EquipType::Sword1H][StatModType::INT] = ranges[EquipType::Sword1H][StatModType::STR];
	ranges[EquipType::Sword1H][StatModType::WIS] = ranges[EquipType::Sword1H][StatModType::STR];
	ranges[EquipType::Sword1H][StatModType::AllAttributes] = { 1, 3, 3, 5, 5, 7 };
	ranges[EquipType::Sword1H][StatModType::Damage] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::Sword1H][StatModType::Healing] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Sword1H][StatModType::ArmorPen] = { 8, 10, 10, 12, 12, 15 };
	ranges[EquipType::Sword1H][StatModType::CritChance] = { 6, 7, 7, 8, 8, 10 };
	ranges[EquipType::Sword1H][StatModType::Haste] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::Sword1H][StatModType::DoubleStrikeChance] = { 7, 9, 9, 12, 12, 15 };
	ranges[EquipType::Sword1H][StatModType::OnHitDamage] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Sword1H][StatModType::HitChance] = { 5, 7, 7, 8, 10, 10 };
	ranges[EquipType::Sword1H][StatModType::MPCostReduction] = { 2, 3, 3, 4, 4, 5};
	ranges[EquipType::Sword1H][StatModType::SPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Sword1H][StatModType::CooldownReduction] = { 2, 3, 3, 4, 4, 6 };

	ranges[EquipType::Axe1H] = ranges[EquipType::Sword1H];
	ranges[EquipType::Mace1H] = ranges[EquipType::Sword1H];
	ranges[EquipType::Dagger] = ranges[EquipType::Sword1H];
	ranges[EquipType::Claw] = ranges[EquipType::Sword1H];
	ranges[EquipType::Wand] = ranges[EquipType::Sword1H];

	ranges[EquipType::Shield] = ranges[EquipType::Sword1H];
	ranges[EquipType::Shield][StatModType::HPRegen] = { 48, 68, 68, 100, 100, 136 };
	ranges[EquipType::Shield][StatModType::VIT] = { 3, 4, 4, 8, 8, 12 };
	ranges[EquipType::Shield][StatModType::Armor] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::Shield][StatModType::CounterChance] = { 11, 14, 14, 17, 17, 20 };
	ranges[EquipType::Shield][StatModType::BlockChance] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Buckler] = ranges[EquipType::Shield];

	ranges[EquipType::OffHand] = ranges[EquipType::Sword1H];
	ranges[EquipType::OffHand][StatModType::MPRegen] = { 12, 17, 17, 25, 25, 34 };
	ranges[EquipType::OffHand][StatModType::VIT] = ranges[EquipType::Shield][StatModType::VIT];
	ranges[EquipType::OffHand][StatModType::CritPower] = { 20, 25, 25, 30, 30, 40 };

	ranges[EquipType::Sword2H][StatModType::HP] = { 28, 40, 40, 80, 80, 120 };
	ranges[EquipType::Sword2H][StatModType::MP] = { 6, 10, 10, 20, 20, 30 };
	ranges[EquipType::Sword2H][StatModType::SP] = { 6, 12, 12, 18, 18, 24 };
	ranges[EquipType::Sword2H][StatModType::SPRegen] = { 12, 16, 16, 20, 20, 24 };
	ranges[EquipType::Sword2H][StatModType::HPLeech] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::Sword2H][StatModType::MPLeech] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::Sword2H][StatModType::STR] = { 6, 10, 10, 20, 20, 28 };
	ranges[EquipType::Sword2H][StatModType::DEX] = ranges[EquipType::Sword2H][StatModType::STR];
	ranges[EquipType::Sword2H][StatModType::INT] = ranges[EquipType::Sword2H][StatModType::STR];
	ranges[EquipType::Sword2H][StatModType::WIS] = ranges[EquipType::Sword2H][StatModType::STR];
	ranges[EquipType::Sword2H][StatModType::AllAttributes] = { 2, 6, 6, 10, 10, 14 };
	ranges[EquipType::Sword2H][StatModType::Damage] = { 8, 10, 10, 12, 12, 16 };
	ranges[EquipType::Sword2H][StatModType::Healing] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::Sword2H][StatModType::ArmorPen] = { 16, 20, 20, 24, 24, 30 };
	ranges[EquipType::Sword2H][StatModType::CritChance] = { 12, 14, 14, 16, 16, 20 };
	ranges[EquipType::Sword2H][StatModType::Haste] = { 6, 8, 8, 10, 10, 14 };
	ranges[EquipType::Sword2H][StatModType::DoubleStrikeChance] = { 14, 18, 18, 24, 24, 30 };
	ranges[EquipType::Sword2H][StatModType::OnHitDamage] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::Sword2H][StatModType::HitChance] = { 10, 14, 14, 16, 20, 20 };
	ranges[EquipType::Sword2H][StatModType::MPCostReduction] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::Sword2H][StatModType::SPCostReduction] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::Sword2H][StatModType::CooldownReduction] = { 4, 6, 6, 8, 8, 12 };

	ranges[EquipType::Axe2H] = ranges[EquipType::Sword2H];
	ranges[EquipType::Mace2H] = ranges[EquipType::Sword2H];
	ranges[EquipType::Spear] = ranges[EquipType::Sword2H];
	ranges[EquipType::Staff] = ranges[EquipType::Sword2H];
	ranges[EquipType::Bow] = ranges[EquipType::Sword2H];

	ranges[EquipType::HeavyHead][StatModType::HP] = { 40, 50, 50, 100, 100, 150 };
	ranges[EquipType::HeavyHead][StatModType::HPRegen] = { 32, 48, 48, 84, 84, 120 };
	ranges[EquipType::HeavyHead][StatModType::MP] = { 10, 12, 12, 25, 25, 38 };
	ranges[EquipType::HeavyHead][StatModType::MPRegen] = { 8, 12, 12, 21, 21, 30 };
	ranges[EquipType::HeavyHead][StatModType::SP] = { 2, 4, 4, 8, 8, 12 };
	ranges[EquipType::HeavyHead][StatModType::SPRegen] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::HeavyHead][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::HeavyHead][StatModType::DEX] = ranges[EquipType::HeavyHead][StatModType::STR];
	ranges[EquipType::HeavyHead][StatModType::INT] = ranges[EquipType::HeavyHead][StatModType::STR];
	ranges[EquipType::HeavyHead][StatModType::WIS] = ranges[EquipType::HeavyHead][StatModType::STR];
	ranges[EquipType::HeavyHead][StatModType::AllAttributes] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::HeavyHead][StatModType::VIT] = { 2, 3, 3, 6, 6, 9 };
	ranges[EquipType::HeavyHead][StatModType::Armor] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyHead][StatModType::ArmorPen] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::HeavyHead][StatModType::CritPower] = { 20, 25, 25, 30, 30, 40 };
	ranges[EquipType::HeavyHead][StatModType::HitChance] = { 5, 7, 7, 8, 10, 10 };
	ranges[EquipType::HeavyHead][StatModType::DodgeChance] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::HeavyHead][StatModType::MPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyHead][StatModType::SPCostReduction] = { 2, 3, 3, 4, 4, 5 };

	ranges[EquipType::MedHead] = ranges[EquipType::HeavyHead];
	ranges[EquipType::LightHead] = ranges[EquipType::HeavyHead];

	ranges[EquipType::HeavyBody][StatModType::HP] = { 40, 60, 60, 120, 120, 180 };
	ranges[EquipType::HeavyBody][StatModType::HPRegen] = { 60, 92, 92, 120, 120, 152 };
	ranges[EquipType::HeavyBody][StatModType::MP] = { 10, 15, 15, 30, 30, 45 };
	ranges[EquipType::HeavyBody][StatModType::MPRegen] = { 15, 23, 23, 30, 30, 38 };
	ranges[EquipType::HeavyBody][StatModType::SP] = { 2, 4, 4, 8, 8, 12 };
	ranges[EquipType::HeavyBody][StatModType::SPRegen] = { 6, 8, 8, 11, 11, 14 };
	ranges[EquipType::HeavyBody][StatModType::STR] = { 3, 5, 5, 10, 10, 14 };
	ranges[EquipType::HeavyBody][StatModType::DEX] = ranges[EquipType::HeavyBody][StatModType::STR];
	ranges[EquipType::HeavyBody][StatModType::INT] = ranges[EquipType::HeavyBody][StatModType::STR];
	ranges[EquipType::HeavyBody][StatModType::WIS] = ranges[EquipType::HeavyBody][StatModType::STR];
	ranges[EquipType::HeavyBody][StatModType::AllAttributes] = { 1, 3, 3, 5, 5, 7 };
	ranges[EquipType::HeavyBody][StatModType::VIT] = { 4, 6, 6, 12, 12, 18 };
	ranges[EquipType::HeavyBody][StatModType::Armor] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::HeavyBody][StatModType::CounterChance] = { 11, 14, 14, 17, 17, 20 };
	ranges[EquipType::HeavyBody][StatModType::DodgeChance] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::HeavyBody][StatModType::CooldownReduction] = { 6, 8, 8, 12, 12, 16 };

	ranges[EquipType::MedBody] = ranges[EquipType::HeavyBody];
	ranges[EquipType::LightBody] = ranges[EquipType::HeavyBody];

	ranges[EquipType::HeavyHands][StatModType::HP] = { 24, 30, 30, 60, 60, 90 };
	ranges[EquipType::HeavyHands][StatModType::MP] = { 6, 8, 8, 15, 15, 22 };
	ranges[EquipType::HeavyHands][StatModType::SP] = { 2, 4, 4, 7, 7, 10 };
	ranges[EquipType::HeavyHands][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::HeavyHands][StatModType::DEX] = ranges[EquipType::HeavyHands][StatModType::STR];
	ranges[EquipType::HeavyHands][StatModType::INT] = ranges[EquipType::HeavyHands][StatModType::STR];
	ranges[EquipType::HeavyHands][StatModType::WIS] = ranges[EquipType::HeavyHands][StatModType::STR];
	ranges[EquipType::HeavyHands][StatModType::AllAttributes] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::HeavyHands][StatModType::VIT] = { 3, 4, 4, 8, 8, 12 };
	ranges[EquipType::HeavyHands][StatModType::HPLeech] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::HeavyHands][StatModType::MPLeech] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyHands][StatModType::Armor] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyHands][StatModType::Damage] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::HeavyHands][StatModType::ArmorPen] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::HeavyHands][StatModType::CritChance] = { 4, 5, 5, 7, 7, 9 };
	ranges[EquipType::HeavyHands][StatModType::Haste] = { 3, 5, 5, 7, 7, 9 };
	ranges[EquipType::HeavyHands][StatModType::DoubleStrikeChance] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::HeavyHands][StatModType::OnHitDamage] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyHands][StatModType::HitChance] = { 5, 7, 7, 8, 10, 10 };

	ranges[EquipType::MedHands] = ranges[EquipType::HeavyHands];
	ranges[EquipType::LightHands] = ranges[EquipType::HeavyHands];

	ranges[EquipType::HeavyFeet][StatModType::HP] = { 32, 40, 40, 80, 80, 120 };
	ranges[EquipType::HeavyFeet][StatModType::HPRegen] = { 48, 64, 64, 100, 100, 136 };
	ranges[EquipType::HeavyFeet][StatModType::MP] = { 8, 10, 10, 20, 20, 30 };
	ranges[EquipType::HeavyFeet][StatModType::MPRegen] = { 12, 16, 16, 25, 25, 34 };
	ranges[EquipType::HeavyFeet][StatModType::SP] = { 2, 4, 4, 8, 8, 12 };
	ranges[EquipType::HeavyFeet][StatModType::SPRegen] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::HeavyFeet][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::HeavyFeet][StatModType::DEX] = ranges[EquipType::HeavyFeet][StatModType::STR];
	ranges[EquipType::HeavyFeet][StatModType::INT] = ranges[EquipType::HeavyFeet][StatModType::STR];
	ranges[EquipType::HeavyFeet][StatModType::WIS] = ranges[EquipType::HeavyFeet][StatModType::STR];
	ranges[EquipType::HeavyFeet][StatModType::AllAttributes] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::HeavyFeet][StatModType::VIT] = { 2, 3, 3, 6, 6, 9 };
	ranges[EquipType::HeavyFeet][StatModType::Armor] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyFeet][StatModType::Haste] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::HeavyFeet][StatModType::DodgeChance] = { 10, 12, 12, 15, 15, 20 };
	ranges[EquipType::HeavyFeet][StatModType::MPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyFeet][StatModType::SPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HeavyFeet][StatModType::MovementSpeed] = { 15, 20, 20, 25, 25, 30 };

	ranges[EquipType::MedFeet] = ranges[EquipType::HeavyFeet];
	ranges[EquipType::LightFeet] = ranges[EquipType::HeavyFeet];

	ranges[EquipType::Neck][StatModType::HP] = { 32, 40, 40, 80, 80, 120 };
	ranges[EquipType::Neck][StatModType::HPRegen] = { 32, 48, 48, 84, 84, 120 };
	ranges[EquipType::Neck][StatModType::MP] = { 8, 10, 10, 20, 20, 30 };
	ranges[EquipType::Neck][StatModType::MPRegen] = { 8, 12, 12, 21, 21, 30 };
	ranges[EquipType::Neck][StatModType::SP] = { 2, 4, 4, 7, 7, 10 };
	ranges[EquipType::Neck][StatModType::SPRegen] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::Neck][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::Neck][StatModType::DEX] = ranges[EquipType::Neck][StatModType::STR];
	ranges[EquipType::Neck][StatModType::INT] = ranges[EquipType::Neck][StatModType::STR];
	ranges[EquipType::Neck][StatModType::WIS] = ranges[EquipType::Neck][StatModType::STR];
	ranges[EquipType::Neck][StatModType::AllAttributes] = { 1, 3, 3, 4, 4, 6 };
	ranges[EquipType::Neck][StatModType::Damage] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Neck][StatModType::CritChance] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Neck][StatModType::Haste] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::Neck][StatModType::DoubleStrikeChance] = { 6, 8, 8, 10, 10, 12};
	ranges[EquipType::Neck][StatModType::HitChance] = { 5, 7, 7, 8, 10, 10 };
	ranges[EquipType::Neck][StatModType::MPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Neck][StatModType::SPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Neck][StatModType::CooldownReduction] = { 4, 6, 6, 8, 8, 12 };
	ranges[EquipType::Neck][StatModType::GoldFind] = { 4, 7, 7, 10, 10, 12 };
	ranges[EquipType::Neck][StatModType::EXPBoost] = { 5, 8, 8, 11, 11, 14 };

	ranges[EquipType::Ring][StatModType::HP] = { 14, 20, 20, 40, 40, 60 };
	ranges[EquipType::Ring][StatModType::HPRegen] = { 20, 40, 40, 56, 56, 68 };
	ranges[EquipType::Ring][StatModType::MP] = { 3, 5, 5, 10, 10, 15 };
	ranges[EquipType::Ring][StatModType::MPRegen] = { 5, 10, 10, 14, 14, 17 };
	ranges[EquipType::Ring][StatModType::SP] = { 2, 4, 4, 7, 7, 10 };
	ranges[EquipType::Ring][StatModType::SPRegen] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Ring][StatModType::STR] = { 2, 3, 3, 5, 5, 7 };
	ranges[EquipType::Ring][StatModType::DEX] = ranges[EquipType::Ring][StatModType::STR];
	ranges[EquipType::Ring][StatModType::INT] = ranges[EquipType::Ring][StatModType::STR];
	ranges[EquipType::Ring][StatModType::WIS] = ranges[EquipType::Ring][StatModType::STR];
	ranges[EquipType::Ring][StatModType::AllAttributes] = { 1, 2, 2, 3, 3, 4 };
	ranges[EquipType::Ring][StatModType::Damage] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Ring][StatModType::ArmorPen] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::Ring][StatModType::CritChance] = { 2, 3, 3, 4, 4, 5};
	ranges[EquipType::Ring][StatModType::Haste] = { 2, 3, 3, 4, 4, 5};
	ranges[EquipType::Ring][StatModType::DoubleStrikeChance] = { 4, 5, 5, 6, 6, 8};
	ranges[EquipType::Ring][StatModType::HitChance] = { 2, 3, 3, 4, 5, 5 };
	ranges[EquipType::Ring][StatModType::MPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Ring][StatModType::SPCostReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Ring][StatModType::CooldownReduction] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::Ring][StatModType::GoldFind] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::Ring][StatModType::EXPBoost] = { 5, 6, 6, 7, 7, 8 };

	try {
		auto v = ranges.at(equipType).at(smt);

		if (tier == 1 || tier == 2) {
			min = v.at(0);
			max = v.at(1);
		}
		else if (tier == 3 || tier == 4) {
			min = v.at(2);
			max = v.at(3);
		}
		else {
			min = v.at(4);
			max = v.at(5);
		}
	}
	catch (std::out_of_range& e) {

	}

	value = Random::RandInt(mt, min, max);

	if (StatModCalc::IsPercent(smt) && value != 0.0) {
		value = value / 100.0;
	}

	if (StatModCalc::IsDecimal(smt) && value != 0.0) {
		value = value / 10.0;
	}

	return value;
}