// ==================================
//
// equipment.cpp
//
// ==================================

#include "equipment.h"
#include "../core/random.h"

#include <unordered_map>

unsigned int Equipment::GetPrice() {
	// todo: price calculation
	return 100u;
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

AuraID Equipment::GetOnHitAura() {
	return onHitAura;
}

bool Equipment::IsUnique() {
	return itemQuality == ItemQuality::UNIQUE;
}

bool Equipment::IsWeapon() {
	return attackSpeed > 0;
}

bool Equipment::IsTwoHanded() {
	std::vector<EquipType> check = {
		EquipType::SWORD_2H,
		EquipType::AXE_2H,
		EquipType::MACE_2H,
		EquipType::SPEAR,
		EquipType::BOW,
		EquipType::STAFF
	};
	if (std::find(check.begin(), check.end(), equipType) != check.end()) {
		return true;
	}
	return false;
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
		if (modsAdded == 0 && (equipType != EquipType::NECK && equipType!= EquipType::RING) && itemQuality >= ItemQuality::RARE) {
			// Wands, Staves, Off-Hand, and Light Armor can roll INT or WIS.
			if (equipType == EquipType::WAND || equipType == EquipType::STAFF || equipType == EquipType::OFF_HAND ||
				equipType == EquipType::LIGHT_HEAD || equipType == EquipType::LIGHT_BODY || equipType == EquipType::LIGHT_HANDS || equipType == EquipType::LIGHT_FEET) {
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
		Element element = Element::NONE;
		if (s == StatModType::DAMAGE) {
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

		if (s == StatModType::ON_HIT_DAMAGE) {
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

		if (s == StatModType::ON_HIT_DAMAGE) {
			statMods.push_back(StatMod(s, value, { element }, AbilityID::UNDEFINED));
		}
		else {
			statMods.push_back(StatMod(s, value, { Category::ANY }, { element }));
		}
	}

	if (!IsWeapon()) {
		rollResistanceStatMods(mt);
	}
}

int Equipment::howManyStatMods(std::mt19937_64& mt) {
	switch (itemQuality) {
	case ItemQuality::COMMON:
		if (equipType == EquipType::RING || equipType == EquipType::NECK || equipType == EquipType::OFF_HAND) {
			return 1;
		}
		else {
			return 0;
		}
		break;
	case ItemQuality::MAGICAL:
		return Random::RandInt(mt, 2, 3);
		break;
	case ItemQuality::RARE:
		return 4;
		break;
	case ItemQuality::MYTHIC:
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
	case EquipType::SWORD_1H:
	case EquipType::SWORD_2H:
	case EquipType::AXE_1H:
	case EquipType::AXE_2H:
	case EquipType::MACE_1H:
	case EquipType::MACE_2H:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::ALL_ATTRIBUTES, 1.0 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::SP_REGEN, 1.0 },
			{ StatModType::HP_LEECH, 0.5 },
			{ StatModType::MP_LEECH, 0.5 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::ON_HIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::DAGGER:
	case EquipType::CLAW:
	case EquipType::SPEAR:
	case EquipType::BOW:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::ALL_ATTRIBUTES, 1.0 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::SP_REGEN, 1.0 },
			{ StatModType::HP_LEECH, 0.5 },
			{ StatModType::MP_LEECH, 0.5 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::ON_HIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::WAND:
	case EquipType::STAFF:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::ALL_ATTRIBUTES, 1.0 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 1.0 },
			//{ StatModType::SP, 0.5 },
			//{ StatModType::SP_REGEN, 1.0 },
			{ StatModType::HP_LEECH, 0.5 },
			{ StatModType::MP_LEECH, 0.5 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::DAMAGE, 1.0 },
			//{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			//{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			//{ StatModType::ON_HIT_DAMAGE, 1.0 },
			//{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 1.0 },
			//{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::SHIELD:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 1.0 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::BLOCK_CHANCE, 1.0 },
			{ StatModType::SP_COST_REDUCTION, 1.0 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::BUCKLER:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 1.0 },
			//{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 1.0 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::BLOCK_CHANCE, 1.0 },
			//{ StatModType::SP_COST_REDUCTION, 1.0 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::OFF_HAND:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 1.0 },
			{ StatModType::MP_REGEN, 1.0 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::CRIT_DAMAGE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 1.0 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::LIGHT_HEAD:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 }
		};
		break;
	case EquipType::LIGHT_BODY:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::LIGHT_HANDS:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::HP_LEECH, 0.5 },
			{ StatModType::MP_LEECH, 0.5 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::ON_HIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
		};
		break;
	case EquipType::LIGHT_FEET:
		possibleAffixes = {
			{ StatModType::INT, 1.0 },
			{ StatModType::WIS, 1.0 },
			{ StatModType::DEX, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::MOVEMENT_SPEED, 1.0 },
		};
		break;
	case EquipType::MED_HEAD:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 }
		};
		break;
	case EquipType::MED_BODY:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::MED_HANDS:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::HP_LEECH, 0.5 },
			{ StatModType::MP_LEECH, 0.5 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::ON_HIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
		};
		break;
	case EquipType::MED_FEET:
		possibleAffixes = {
			{ StatModType::DEX, 1.0 },
			{ StatModType::STR, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::MOVEMENT_SPEED, 1.0 },
		};
		break;
	case EquipType::HEAVY_HEAD:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 }
		};
		break;
	case EquipType::HEAVY_BODY:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			//{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 }
		};
		break;
	case EquipType::HEAVY_HANDS:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::HP_LEECH, 0.5 },
			{ StatModType::MP_LEECH, 0.5 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::ON_HIT_DAMAGE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
		};
		break;
	case EquipType::HEAVY_FEET:
		possibleAffixes = {
			{ StatModType::STR, 1.0 },
			{ StatModType::INT, 0.5 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::VIT, 1.0 },
			{ StatModType::ARMOR, 1.0 },
			{ StatModType::HASTE, 1.0 },
			//{ StatModType::DODGE_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::MOVEMENT_SPEED, 1.0 },
		};
		break;
	case EquipType::NECK:
		possibleAffixes = {
			{ StatModType::STR, 0.25 },
			{ StatModType::DEX, 0.25 },
			{ StatModType::INT, 0.25 },
			{ StatModType::WIS, 0.25 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 },
			{ StatModType::GOLD_FIND, 0.25 }
		};
		break;
	case EquipType::RING:
		possibleAffixes = {
			{ StatModType::STR, 0.25 },
			{ StatModType::DEX, 0.25 },
			{ StatModType::INT, 0.25 },
			{ StatModType::WIS, 0.25 },
			{ StatModType::ALL_ATTRIBUTES, 0.5 },
			{ StatModType::HP, 1.0 },
			{ StatModType::MP, 0.5 },
			{ StatModType::SP, 0.5 },
			{ StatModType::HP_REGEN, 0.33 },
			{ StatModType::MP_REGEN, 0.34 },
			{ StatModType::SP_REGEN, 0.33 },
			{ StatModType::DAMAGE, 1.0 },
			{ StatModType::ARMOR_PEN, 1.0 },
			{ StatModType::CRIT_CHANCE, 1.0 },
			{ StatModType::HASTE, 1.0 },
			{ StatModType::DOUBLE_STRIKE_CHANCE, 1.0 },
			{ StatModType::HIT_CHANCE, 1.0 },
			{ StatModType::MP_COST_REDUCTION, 0.5 },
			{ StatModType::SP_COST_REDUCTION, 0.5 },
			{ StatModType::COOLDOWN_REDUCTION, 1.0 },
			{ StatModType::GOLD_FIND, 0.25 }
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
	case EquipType::SWORD_1H:
	case EquipType::SWORD_2H:
		possibleElements = {
			Element::ARCANE,
			Element::FIRE,
			Element::WATER,
			Element::WIND,
			Element::EARTH
		};
		break;
	case EquipType::AXE_1H:
	case EquipType::AXE_2H:
		possibleElements = {
			Element::PHYSICAL
		};
		break;
	case EquipType::MACE_1H:
	case EquipType::MACE_2H:
		possibleElements = {
			Element::PHYSICAL,
			Element::ICE,
			Element::LIGHTNING,
			Element::EARTH,
			Element::LIGHT
		};
		break;
	case EquipType::DAGGER:
		possibleElements = {
			Element::PHYSICAL,
			Element::POISON,
			Element::DARK
		};
		break;
	case EquipType::CLAW:
		possibleElements = {
			Element::PHYSICAL,
			Element::POISON
		};
		break;
	case EquipType::SPEAR:
		possibleElements = {
			Element::LIGHTNING,
			Element::WATER,
			Element::WIND
		};
		break;
	case EquipType::BOW:
		possibleElements = {
			Element::ARCANE,
			Element::FIRE,
			Element::ICE,
			Element::LIGHTNING,
			Element::POISON,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::LIGHT,
			Element::DARK
		};
		break;
	case EquipType::WAND:
	case EquipType::STAFF:
		possibleElements = {
			Element::ARCANE,
			Element::FIRE,
			Element::ICE,
			Element::LIGHTNING,
			Element::POISON,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::MIND,
			Element::LIGHT,
			Element::DARK
		};
		break;
	case EquipType::LIGHT_HANDS:
		possibleElements = {
			Element::ARCANE,
			Element::FIRE,
			Element::ICE,
			Element::LIGHTNING,
			Element::MIND,
			Element::POISON,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::LIGHT,
			Element::DARK
		};
		break;
	case EquipType::MED_HANDS:
		possibleElements = {
			Element::PHYSICAL,
			Element::LIGHTNING,
			Element::POISON,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::DARK
		};
		break;
	case EquipType::HEAVY_HANDS:
		possibleElements = {
			Element::PHYSICAL,
			Element::ARCANE,
			Element::FIRE,
			Element::ICE,
			Element::LIGHTNING,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::LIGHT
		};
		break;
	case EquipType::NECK:
		possibleElements = {
			Element::PHYSICAL,
			Element::ARCANE,
			Element::FIRE,
			Element::ICE,
			Element::LIGHTNING,
			Element::MIND,
			Element::POISON,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::LIGHT,
			Element::DARK
		};
		break;
	case EquipType::RING:
		possibleElements = {
			Element::PHYSICAL,
			Element::ARCANE,
			Element::FIRE,
			Element::ICE,
			Element::LIGHTNING,
			Element::MIND,
			Element::POISON,
			Element::WATER,
			Element::WIND,
			Element::EARTH,
			Element::LIGHT,
			Element::DARK
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
		Element::ARCANE,
		Element::FIRE,
		Element::ICE,
		Element::LIGHTNING,
		Element::MIND,
		Element::POISON,
		Element::WATER,
		Element::WIND,
		Element::EARTH,
		Element::LIGHT,
		Element::DARK
	};

	if (itemQuality == ItemQuality::MAGICAL) {
		resistCount = Random::RandInt(mt, 0, 1);
	}
	else if (itemQuality == ItemQuality::RARE) {
		resistCount = 1;
	}
	else if (itemQuality == ItemQuality::MYTHIC) {
		resistCount = 2;
	}

	for (int i = 0; i < resistCount; i++) {
		int randElement = Random::RandInt(mt, 0, possibleResists.size() - 1 - i);
		Element element = possibleResists[randElement];
		std::swap(possibleResists[randElement], possibleResists[possibleResists.size() - 1 - i]); // swap position in list so that same element isn't choosen twice

		int minResist = 5 + (((tier - 1) / 2) * 5);
		int maxResist = 10 + (((tier - 1) / 2) * 5);
		double resist = (double)Random::RandInt(mt, minResist, maxResist) / 100.0;

		statMods.push_back(StatMod(StatModType::RESISTANCE, resist, { Category::ANY }, { element }));
	}
}

double Equipment::rollMod(StatModType smt, std::mt19937_64& mt) {
	std::unordered_map<EquipType, std::unordered_map<StatModType, std::vector<int>>> ranges;
	int min = 0;
	int max = 0;
	double value = 0;

	ranges[EquipType::SWORD_1H][StatModType::HP] = { 14, 20, 20, 40, 40, 60 };
	ranges[EquipType::SWORD_1H][StatModType::MP] = { 3, 5, 5, 10, 10, 15 };
	ranges[EquipType::SWORD_1H][StatModType::SP] = { 3, 6, 6, 9, 9, 12 };
	ranges[EquipType::SWORD_1H][StatModType::SP_REGEN] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::SWORD_1H][StatModType::HP_LEECH] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::SWORD_1H][StatModType::MP_LEECH] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::SWORD_1H][StatModType::STR] = { 3, 5, 5, 10, 10, 14 };
	ranges[EquipType::SWORD_1H][StatModType::DEX] = ranges[EquipType::SWORD_1H][StatModType::STR];
	ranges[EquipType::SWORD_1H][StatModType::INT] = ranges[EquipType::SWORD_1H][StatModType::STR];
	ranges[EquipType::SWORD_1H][StatModType::WIS] = ranges[EquipType::SWORD_1H][StatModType::STR];
	ranges[EquipType::SWORD_1H][StatModType::ALL_ATTRIBUTES] = { 1, 3, 3, 5, 5, 7 };
	ranges[EquipType::SWORD_1H][StatModType::DAMAGE] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::SWORD_1H][StatModType::HEALING] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::SWORD_1H][StatModType::ARMOR_PEN] = { 8, 10, 10, 12, 12, 15 };
	ranges[EquipType::SWORD_1H][StatModType::CRIT_CHANCE] = { 6, 7, 7, 8, 8, 10 };
	ranges[EquipType::SWORD_1H][StatModType::HASTE] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::SWORD_1H][StatModType::DOUBLE_STRIKE_CHANCE] = { 7, 9, 9, 12, 12, 15 };
	ranges[EquipType::SWORD_1H][StatModType::ON_HIT_DAMAGE] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::SWORD_1H][StatModType::HIT_CHANCE] = { 5, 7, 7, 8, 10, 10 };
	ranges[EquipType::SWORD_1H][StatModType::MP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5};
	ranges[EquipType::SWORD_1H][StatModType::SP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::SWORD_1H][StatModType::COOLDOWN_REDUCTION] = { 2, 3, 3, 4, 4, 6 };

	ranges[EquipType::AXE_1H] = ranges[EquipType::SWORD_1H];
	ranges[EquipType::MACE_1H] = ranges[EquipType::SWORD_1H];
	ranges[EquipType::DAGGER] = ranges[EquipType::SWORD_1H];
	ranges[EquipType::CLAW] = ranges[EquipType::SWORD_1H];
	ranges[EquipType::WAND] = ranges[EquipType::SWORD_1H];

	ranges[EquipType::SHIELD] = ranges[EquipType::SWORD_1H];
	ranges[EquipType::SHIELD][StatModType::HP_REGEN] = { 48, 68, 68, 100, 100, 136 };
	ranges[EquipType::SHIELD][StatModType::VIT] = { 3, 4, 4, 8, 8, 12 };
	ranges[EquipType::SHIELD][StatModType::ARMOR] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::SHIELD][StatModType::COUNTER_CHANCE] = { 11, 14, 14, 17, 17, 20 };
	ranges[EquipType::SHIELD][StatModType::BLOCK_CHANCE] = { 3, 4, 4, 5, 5, 6 };

	ranges[EquipType::OFF_HAND] = ranges[EquipType::SWORD_1H];
	ranges[EquipType::OFF_HAND][StatModType::MP_REGEN] = { 12, 17, 17, 25, 25, 34 };
	ranges[EquipType::OFF_HAND][StatModType::VIT] = ranges[EquipType::SHIELD][StatModType::VIT];
	ranges[EquipType::OFF_HAND][StatModType::CRIT_DAMAGE] = { 20, 25, 25, 30, 30, 40 };

	ranges[EquipType::SWORD_2H][StatModType::HP] = { 28, 40, 40, 80, 80, 120 };
	ranges[EquipType::SWORD_2H][StatModType::MP] = { 6, 10, 10, 20, 20, 30 };
	ranges[EquipType::SWORD_2H][StatModType::SP] = { 6, 12, 12, 18, 18, 24 };
	ranges[EquipType::SWORD_2H][StatModType::SP_REGEN] = { 12, 16, 16, 20, 20, 24 };
	ranges[EquipType::SWORD_2H][StatModType::HP_LEECH] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::SWORD_2H][StatModType::MP_LEECH] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::SWORD_2H][StatModType::STR] = { 6, 10, 10, 20, 20, 28 };
	ranges[EquipType::SWORD_2H][StatModType::DEX] = ranges[EquipType::SWORD_2H][StatModType::STR];
	ranges[EquipType::SWORD_2H][StatModType::INT] = ranges[EquipType::SWORD_2H][StatModType::STR];
	ranges[EquipType::SWORD_2H][StatModType::WIS] = ranges[EquipType::SWORD_2H][StatModType::STR];
	ranges[EquipType::SWORD_2H][StatModType::ALL_ATTRIBUTES] = { 2, 6, 6, 10, 10, 14 };
	ranges[EquipType::SWORD_2H][StatModType::DAMAGE] = { 8, 10, 10, 12, 12, 16 };
	ranges[EquipType::SWORD_2H][StatModType::HEALING] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::SWORD_2H][StatModType::ARMOR_PEN] = { 16, 20, 20, 24, 24, 30 };
	ranges[EquipType::SWORD_2H][StatModType::CRIT_CHANCE] = { 12, 14, 14, 16, 16, 20 };
	ranges[EquipType::SWORD_2H][StatModType::HASTE] = { 6, 8, 8, 10, 10, 14 };
	ranges[EquipType::SWORD_2H][StatModType::DOUBLE_STRIKE_CHANCE] = { 14, 18, 18, 24, 24, 30 };
	ranges[EquipType::SWORD_2H][StatModType::ON_HIT_DAMAGE] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::SWORD_2H][StatModType::HIT_CHANCE] = { 10, 14, 14, 16, 20, 20 };
	ranges[EquipType::SWORD_2H][StatModType::MP_COST_REDUCTION] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::SWORD_2H][StatModType::SP_COST_REDUCTION] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::SWORD_2H][StatModType::COOLDOWN_REDUCTION] = { 4, 6, 6, 8, 8, 12 };

	ranges[EquipType::AXE_2H] = ranges[EquipType::SWORD_2H];
	ranges[EquipType::MACE_2H] = ranges[EquipType::SWORD_2H];
	ranges[EquipType::SPEAR] = ranges[EquipType::SWORD_2H];
	ranges[EquipType::STAFF] = ranges[EquipType::SWORD_2H];
	ranges[EquipType::BOW] = ranges[EquipType::SWORD_2H];

	ranges[EquipType::HEAVY_HEAD][StatModType::HP] = { 40, 50, 50, 100, 100, 150 };
	ranges[EquipType::HEAVY_HEAD][StatModType::HP_REGEN] = { 32, 48, 48, 84, 84, 120 };
	ranges[EquipType::HEAVY_HEAD][StatModType::MP] = { 10, 12, 12, 25, 25, 38 };
	ranges[EquipType::HEAVY_HEAD][StatModType::MP_REGEN] = { 8, 12, 12, 21, 21, 30 };
	ranges[EquipType::HEAVY_HEAD][StatModType::SP] = { 2, 4, 4, 8, 8, 12 };
	ranges[EquipType::HEAVY_HEAD][StatModType::SP_REGEN] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::HEAVY_HEAD][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::HEAVY_HEAD][StatModType::DEX] = ranges[EquipType::HEAVY_HEAD][StatModType::STR];
	ranges[EquipType::HEAVY_HEAD][StatModType::INT] = ranges[EquipType::HEAVY_HEAD][StatModType::STR];
	ranges[EquipType::HEAVY_HEAD][StatModType::WIS] = ranges[EquipType::HEAVY_HEAD][StatModType::STR];
	ranges[EquipType::HEAVY_HEAD][StatModType::ALL_ATTRIBUTES] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::HEAVY_HEAD][StatModType::VIT] = { 2, 3, 3, 6, 6, 9 };
	ranges[EquipType::HEAVY_HEAD][StatModType::ARMOR] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_HEAD][StatModType::ARMOR_PEN] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::HEAVY_HEAD][StatModType::CRIT_DAMAGE] = { 20, 25, 25, 30, 30, 40 };
	ranges[EquipType::HEAVY_HEAD][StatModType::HIT_CHANCE] = { 5, 7, 7, 8, 10, 10 };
	ranges[EquipType::HEAVY_HEAD][StatModType::DODGE_CHANCE] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::HEAVY_HEAD][StatModType::MP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_HEAD][StatModType::SP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };

	ranges[EquipType::MED_HEAD] = ranges[EquipType::HEAVY_HEAD];
	ranges[EquipType::LIGHT_HEAD] = ranges[EquipType::HEAVY_HEAD];

	ranges[EquipType::HEAVY_BODY][StatModType::HP] = { 40, 60, 60, 120, 120, 180 };
	ranges[EquipType::HEAVY_BODY][StatModType::HP_REGEN] = { 60, 92, 92, 120, 120, 152 };
	ranges[EquipType::HEAVY_BODY][StatModType::MP] = { 10, 15, 15, 30, 30, 45 };
	ranges[EquipType::HEAVY_BODY][StatModType::MP_REGEN] = { 15, 23, 23, 30, 30, 38 };
	ranges[EquipType::HEAVY_BODY][StatModType::SP] = { 2, 4, 4, 8, 8, 12 };
	ranges[EquipType::HEAVY_BODY][StatModType::SP_REGEN] = { 6, 8, 8, 11, 11, 14 };
	ranges[EquipType::HEAVY_BODY][StatModType::STR] = { 3, 5, 5, 10, 10, 14 };
	ranges[EquipType::HEAVY_BODY][StatModType::DEX] = ranges[EquipType::HEAVY_BODY][StatModType::STR];
	ranges[EquipType::HEAVY_BODY][StatModType::INT] = ranges[EquipType::HEAVY_BODY][StatModType::STR];
	ranges[EquipType::HEAVY_BODY][StatModType::WIS] = ranges[EquipType::HEAVY_BODY][StatModType::STR];
	ranges[EquipType::HEAVY_BODY][StatModType::ALL_ATTRIBUTES] = { 1, 3, 3, 5, 5, 7 };
	ranges[EquipType::HEAVY_BODY][StatModType::VIT] = { 4, 6, 6, 12, 12, 18 };
	ranges[EquipType::HEAVY_BODY][StatModType::ARMOR] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::HEAVY_BODY][StatModType::COUNTER_CHANCE] = { 11, 14, 14, 17, 17, 20 };
	ranges[EquipType::HEAVY_BODY][StatModType::DODGE_CHANCE] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::HEAVY_BODY][StatModType::COOLDOWN_REDUCTION] = { 6, 8, 8, 12, 12, 16 };

	ranges[EquipType::MED_BODY] = ranges[EquipType::HEAVY_BODY];
	ranges[EquipType::LIGHT_BODY] = ranges[EquipType::HEAVY_BODY];

	ranges[EquipType::HEAVY_HANDS][StatModType::HP] = { 24, 30, 30, 60, 60, 90 };
	ranges[EquipType::HEAVY_HANDS][StatModType::MP] = { 6, 8, 8, 15, 15, 22 };
	ranges[EquipType::HEAVY_HANDS][StatModType::SP] = { 2, 4, 4, 7, 7, 10 };
	ranges[EquipType::HEAVY_HANDS][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::HEAVY_HANDS][StatModType::DEX] = ranges[EquipType::HEAVY_HANDS][StatModType::STR];
	ranges[EquipType::HEAVY_HANDS][StatModType::INT] = ranges[EquipType::HEAVY_HANDS][StatModType::STR];
	ranges[EquipType::HEAVY_HANDS][StatModType::WIS] = ranges[EquipType::HEAVY_HANDS][StatModType::STR];
	ranges[EquipType::HEAVY_HANDS][StatModType::ALL_ATTRIBUTES] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::HEAVY_HANDS][StatModType::VIT] = { 3, 4, 4, 8, 8, 12 };
	ranges[EquipType::HEAVY_HANDS][StatModType::HP_LEECH] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::HEAVY_HANDS][StatModType::MP_LEECH] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_HANDS][StatModType::ARMOR] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_HANDS][StatModType::DAMAGE] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::HEAVY_HANDS][StatModType::ARMOR_PEN] = { 4, 5, 5, 6, 6, 8 };
	ranges[EquipType::HEAVY_HANDS][StatModType::CRIT_CHANCE] = { 4, 5, 5, 7, 7, 9 };
	ranges[EquipType::HEAVY_HANDS][StatModType::HASTE] = { 3, 5, 5, 7, 7, 9 };
	ranges[EquipType::HEAVY_HANDS][StatModType::DOUBLE_STRIKE_CHANCE] = { 6, 8, 8, 10, 10, 12 };
	ranges[EquipType::HEAVY_HANDS][StatModType::ON_HIT_DAMAGE] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_HANDS][StatModType::HIT_CHANCE] = { 5, 7, 7, 8, 10, 10 };

	ranges[EquipType::MED_HANDS] = ranges[EquipType::HEAVY_HANDS];
	ranges[EquipType::LIGHT_HANDS] = ranges[EquipType::HEAVY_HANDS];

	ranges[EquipType::HEAVY_FEET][StatModType::HP] = { 32, 40, 40, 80, 80, 120 };
	ranges[EquipType::HEAVY_FEET][StatModType::HP_REGEN] = { 48, 64, 64, 100, 100, 136 };
	ranges[EquipType::HEAVY_FEET][StatModType::MP] = { 8, 10, 10, 20, 20, 30 };
	ranges[EquipType::HEAVY_FEET][StatModType::MP_REGEN] = { 12, 16, 16, 25, 25, 34 };
	ranges[EquipType::HEAVY_FEET][StatModType::SP] = { 2, 4, 4, 8, 8, 12 };
	ranges[EquipType::HEAVY_FEET][StatModType::SP_REGEN] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::HEAVY_FEET][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::HEAVY_FEET][StatModType::DEX] = ranges[EquipType::HEAVY_FEET][StatModType::STR];
	ranges[EquipType::HEAVY_FEET][StatModType::INT] = ranges[EquipType::HEAVY_FEET][StatModType::STR];
	ranges[EquipType::HEAVY_FEET][StatModType::WIS] = ranges[EquipType::HEAVY_FEET][StatModType::STR];
	ranges[EquipType::HEAVY_FEET][StatModType::ALL_ATTRIBUTES] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::HEAVY_FEET][StatModType::VIT] = { 2, 3, 3, 6, 6, 9 };
	ranges[EquipType::HEAVY_FEET][StatModType::ARMOR] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_FEET][StatModType::HASTE] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::HEAVY_FEET][StatModType::DODGE_CHANCE] = { 10, 12, 12, 15, 15, 20 };
	ranges[EquipType::HEAVY_FEET][StatModType::MP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_FEET][StatModType::SP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::HEAVY_FEET][StatModType::MOVEMENT_SPEED] = { 15, 20, 20, 25, 25, 30 };

	ranges[EquipType::MED_FEET] = ranges[EquipType::HEAVY_FEET];
	ranges[EquipType::LIGHT_FEET] = ranges[EquipType::HEAVY_FEET];

	ranges[EquipType::NECK][StatModType::HP] = { 32, 40, 40, 80, 80, 120 };
	ranges[EquipType::NECK][StatModType::HP_REGEN] = { 32, 48, 48, 84, 84, 120 };
	ranges[EquipType::NECK][StatModType::MP] = { 8, 10, 10, 20, 20, 30 };
	ranges[EquipType::NECK][StatModType::MP_REGEN] = { 8, 12, 12, 21, 21, 30 };
	ranges[EquipType::NECK][StatModType::SP] = { 2, 4, 4, 7, 7, 10 };
	ranges[EquipType::NECK][StatModType::SP_REGEN] = { 4, 6, 6, 8, 8, 10 };
	ranges[EquipType::NECK][StatModType::STR] = { 2, 4, 4, 7, 7, 11 };
	ranges[EquipType::NECK][StatModType::DEX] = ranges[EquipType::NECK][StatModType::STR];
	ranges[EquipType::NECK][StatModType::INT] = ranges[EquipType::NECK][StatModType::STR];
	ranges[EquipType::NECK][StatModType::WIS] = ranges[EquipType::NECK][StatModType::STR];
	ranges[EquipType::NECK][StatModType::ALL_ATTRIBUTES] = { 1, 3, 3, 4, 4, 6 };
	ranges[EquipType::NECK][StatModType::DAMAGE] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::NECK][StatModType::CRIT_CHANCE] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::NECK][StatModType::HASTE] = { 3, 4, 4, 5, 5, 7 };
	ranges[EquipType::NECK][StatModType::DOUBLE_STRIKE_CHANCE] = { 6, 8, 8, 10, 10, 12};
	ranges[EquipType::NECK][StatModType::HIT_CHANCE] = { 5, 7, 7, 8, 10, 10 };
	ranges[EquipType::NECK][StatModType::MP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::NECK][StatModType::SP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::NECK][StatModType::COOLDOWN_REDUCTION] = { 4, 6, 6, 8, 8, 12 };
	ranges[EquipType::NECK][StatModType::GOLD_FIND] = { 4, 7, 7, 10, 10, 12 };
	ranges[EquipType::NECK][StatModType::EXP_BOOST] = { 5, 8, 8, 11, 11, 14 };

	ranges[EquipType::RING][StatModType::HP] = { 14, 20, 20, 40, 40, 60 };
	ranges[EquipType::RING][StatModType::HP_REGEN] = { 20, 40, 40, 56, 56, 68 };
	ranges[EquipType::RING][StatModType::MP] = { 3, 5, 5, 10, 10, 15 };
	ranges[EquipType::RING][StatModType::MP_REGEN] = { 5, 10, 10, 14, 14, 17 };
	ranges[EquipType::RING][StatModType::SP] = { 2, 4, 4, 7, 7, 10 };
	ranges[EquipType::RING][StatModType::SP_REGEN] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::RING][StatModType::STR] = { 2, 3, 3, 5, 5, 7 };
	ranges[EquipType::RING][StatModType::DEX] = ranges[EquipType::RING][StatModType::STR];
	ranges[EquipType::RING][StatModType::INT] = ranges[EquipType::RING][StatModType::STR];
	ranges[EquipType::RING][StatModType::WIS] = ranges[EquipType::RING][StatModType::STR];
	ranges[EquipType::RING][StatModType::ALL_ATTRIBUTES] = { 1, 2, 2, 3, 3, 4 };
	ranges[EquipType::RING][StatModType::DAMAGE] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::RING][StatModType::ARMOR_PEN] = { 1, 2, 2, 3, 3, 5 };
	ranges[EquipType::RING][StatModType::CRIT_CHANCE] = { 2, 3, 3, 4, 4, 5};
	ranges[EquipType::RING][StatModType::HASTE] = { 2, 3, 3, 4, 4, 5};
	ranges[EquipType::RING][StatModType::DOUBLE_STRIKE_CHANCE] = { 4, 5, 5, 6, 6, 8};
	ranges[EquipType::RING][StatModType::HIT_CHANCE] = { 2, 3, 3, 4, 5, 5 };
	ranges[EquipType::RING][StatModType::MP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::RING][StatModType::SP_COST_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::RING][StatModType::COOLDOWN_REDUCTION] = { 2, 3, 3, 4, 4, 5 };
	ranges[EquipType::RING][StatModType::GOLD_FIND] = { 3, 4, 4, 5, 5, 6 };
	ranges[EquipType::RING][StatModType::EXP_BOOST] = { 5, 6, 6, 7, 7, 8 };

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