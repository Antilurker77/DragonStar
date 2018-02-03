// ==================================
//
// weight.cpp
//
// ==================================

#include "weight.h"

#include "id/abilityID.h"
#include "id/equipmentID.h"
#include "id/formationID.h"
#include "../core/random.h"

std::vector<FormationWeight> Weight::GetCommonFaWeights(int tier) {
	switch (tier) {
	case 1:
		return {
			{ FormationID::FLAMEBLADES_STALKERS_FIELD, 0.75 },
			{ FormationID::LESSER_FLAMEBLADES_FIELD, 1.0 },
			{ FormationID::SENTRY_AMBUSH, 1.0 },
			{ FormationID::SEWER_RATS, 0.5 },
			{ FormationID::SEWER_RATS_INTERSECTION, 1.0 },
			{ FormationID::SHADOW_STALKERS_FIELD, 1.0 }
		};
	default:
		return {
			{ FormationID::TEST_FORMATION_A, 1.0 },
			{ FormationID::TEST_FORMATION_B, 0.5 }
		};
	}
	
}

std::vector<FormationWeight> Weight::GetUniqueFaWeights(int tier) {
	switch (tier) {
	default:
		return {
			{ FormationID::TEST_UNIQUE, 1.0 },
			{ FormationID::FENROK, 1.0 }
		};
	}
}

std::vector<FormationWeight> Weight::GetBossFaWeights(int tier) {
	switch (tier) {
	default:
		return {
			{ FormationID::TEST_BOSS, 1.0 }
		};
	}
}

EquipmentID Weight::GetRandomEq(std::mt19937_64& mt, int tier) {
	EquipmentID id = EquipmentID::UNDEFINED;
	std::vector<EquipmentWeight> weights;

	// Tier 6
	if (tier >= 6) {
		
		// Jewelry
		weights.push_back({ EquipmentID::DRAGONITE_NECKLACE, 0.50 });
		weights.push_back({ EquipmentID::DRAGONITE_RING, 1.00 });
	}
	// Tier 5
	else if (tier == 5) {
		
		// Jewelry
		weights.push_back({ EquipmentID::DRAGONITE_NECKLACE, 0.50 });
		weights.push_back({ EquipmentID::DRAGONITE_RING, 1.00 });
	}
	// Tier 4
	else if (tier == 4) {
		
		// Jewelry
		weights.push_back({ EquipmentID::GOLD_NECKLACE, 0.50 });
		weights.push_back({ EquipmentID::GOLD_RING, 1.00 });
	}
	// Tier 3
	else if (tier == 3) {

		// Jewelry
		weights.push_back({ EquipmentID::GOLD_NECKLACE, 0.50 });
		weights.push_back({ EquipmentID::GOLD_RING, 1.00 });
	}
	// Tier 2
	else if (tier == 2) {

		// Jewelry
		weights.push_back({ EquipmentID::SILVER_NECKLACE, 0.50 });
		weights.push_back({ EquipmentID::SILVER_RING, 1.00 });
	}
	// Tier 1
	else {
		// Weapons
		weights.push_back({ EquipmentID::IRON_SWORD, 0.25 });
		weights.push_back({ EquipmentID::IRON_GREATSWORD, 0.25 });
		weights.push_back({ EquipmentID::IRON_AXE, 0.25 });
		weights.push_back({ EquipmentID::IRON_GREATAXE, 0.25 });
		weights.push_back({ EquipmentID::IRON_MACE, 0.25 });
		weights.push_back({ EquipmentID::IRON_GREATMACE, 0.25 });
		weights.push_back({ EquipmentID::IRON_DAGGER, 0.50 });
		weights.push_back({ EquipmentID::IRON_SPEAR, 0.50 });
		weights.push_back({ EquipmentID::LONGBOW, 0.25 });
		weights.push_back({ EquipmentID::LIGHT_CROSSBOW, 0.25 });
		weights.push_back({ EquipmentID::WOODEN_WAND, 0.50 });
		weights.push_back({ EquipmentID::WOODEN_STAFF, 0.50 });

		// Off-Hand
		weights.push_back({ EquipmentID::IRON_SHIELD, 0.25 });
		weights.push_back({ EquipmentID::IRON_BUCKLER, 0.25 });
		weights.push_back({ EquipmentID::POWER_ORB, 0.50 });

		// Armor
		weights.push_back({ EquipmentID::IRON_HELM, 0.50 });
		weights.push_back({ EquipmentID::LEATHER_HELMET, 0.50 });
		weights.push_back({ EquipmentID::SILK_HAT, 0.50 });
		weights.push_back({ EquipmentID::IRON_ARMOR, 0.50 });
		weights.push_back({ EquipmentID::LEATHER_ARMOR, 0.50 });
		weights.push_back({ EquipmentID::SILK_ROBES, 0.50 });
		weights.push_back({ EquipmentID::IRON_GAUNTLETS, 0.50 });
		weights.push_back({ EquipmentID::LEATHER_GLOVES, 0.50 });
		weights.push_back({ EquipmentID::SILK_GLOVES, 0.50 });
		weights.push_back({ EquipmentID::IRON_GREAVES, 0.50 });
		weights.push_back({ EquipmentID::LEATHER_BOOTS, 0.50 });
		weights.push_back({ EquipmentID::SILK_SHOES, 0.50 });

		// Jewelry
		weights.push_back({ EquipmentID::SILVER_NECKLACE, 0.50 });
		weights.push_back({ EquipmentID::SILVER_RING, 1.00 });
	}

	while (true) {
		size_t index = Random::RandSizeT(mt, 0u, weights.size() - 1);
		double weightRoll = Random::RandDouble(mt, 0.0, 1.0);
		if (weightRoll <= weights[index].second) {
			return weights[index].first;
		}
	}
}

EquipmentID Weight::GetRandomUniqueEq(std::mt19937_64& mt, int tier, std::vector<EquipmentID>& existingUniques) {
	std::vector<EquipmentWeight> weights;

	switch (tier) {
	case 1:
		weights.push_back({ EquipmentID::CHARM_OF_STRENGTH, 1.00 });
		weights.push_back({ EquipmentID::CHARM_OF_DEXTERITY, 1.00 });
		weights.push_back({ EquipmentID::CHARM_OF_INTELLIGENCE, 1.00 });
		weights.push_back({ EquipmentID::CHARM_OF_WISDOM, 1.00 });
		break;
	default:
		break;
	}

	for (auto eu : existingUniques) {
		for (size_t i = 0; i < weights.size(); i++) {
			if (eu == weights[i].first) {
				weights.erase(weights.begin() + i);
				break;
			}
		}
	}

	if (!weights.empty()) {
		while (true) {
			size_t index = Random::RandSizeT(mt, 0u, weights.size() - 1u);
			double roll = Random::RandDouble(mt, 0.0, 1.0);
			if (roll <= weights[index].second) {
				return weights[index].first;
			}
		}
	}
	else {
		return EquipmentID::UNDEFINED;
	}
}

AbilityID Weight::GetRandomAb(std::mt19937_64& mt, int tier) {
	std::vector<AbilityWeight> weights;

	// Determine ability tier.
	double tierRoll = Random::RandDouble(mt, 0.0, 1.0);
	int tierPicked = 1;

	// Determine which ability tier to take from.
	switch (tier) {
	case 1:
		if (tierRoll >= 0.9) {
			tierPicked = 2;
		}
		else {
			tierPicked = 1;
		}
		break;
	case 2:
		if (tierRoll >= 0.8) {
			tierPicked = 2;
		}
		else {
			tierPicked = 1;
		}
		break;
	case 3:
		if (tierRoll >= 0.9) {
			tierPicked = 3;
		}
		else if (tierRoll >= 0.6) {
			tierPicked = 1;
		}
		else {
			tierPicked = 2;
		}
		break;
	case 4:
		if (tierRoll >= 0.85) {
			tierPicked = 3;
		}
		else if (tierRoll >= 0.65) {
			tierPicked = 1;
		}
		else {
			tierPicked = 2;
		}
		break;
	case 5:
		if (tierRoll >= 0.9) {
			tierPicked = 1;
		}
		else if (tierRoll >= 0.6) {
			tierPicked = 2;
		}
		else {
			tierPicked = 3;
		}
		break;
	case 6:
		if (tierRoll >= 0.9) {
			tierPicked = 1;
		}
		else if (tierRoll >= 0.7) {
			tierPicked = 2;
		}
		else {
			tierPicked = 3;
		}
		break;
	default:
		tierPicked = 1;
		break;
	}

	// Roll ID
	int classRoll = Random::RandInt(mt, 1, 11);

	switch (classRoll) {
	// Blademaster
	case 1:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::POWER_STRIKE, 1.00 });
			weights.push_back({ AbilityID::RENDING_SLASH, 1.00 });
			weights.push_back({ AbilityID::FLAME_SLASH, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::WARP_SLICE, 1.00 });
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Berserker
	case 2:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::POWER_STRIKE, 1.00 });
			weights.push_back({ AbilityID::RENDING_SLASH, 1.00 });
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Guardian
	case 3:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::POWER_STRIKE, 1.00 });
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Assassin
	case 4:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::POWER_STRIKE, 1.00 });
			weights.push_back({ AbilityID::RENDING_SLASH, 1.00 });
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Stormsinger
	case 5:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::POWER_STRIKE, 1.00 });
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Ranger
	case 6:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::POWER_STRIKE, 1.00 }); //todo: power shot
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Wizard
	case 7:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::PRISMATIC_BOLT, 1.00 });
			weights.push_back({ AbilityID::ELEMENTAL_ENERGY, 1.00 });
			weights.push_back({ AbilityID::MAGIC_MISSILE, 1.00 });
			weights.push_back({ AbilityID::ARCANE_BLAST, 1.00 });
			weights.push_back({ AbilityID::FLAME_BOLT, 1.00 });
			weights.push_back({ AbilityID::DRAGONFIRE_BOLT, 1.00 });
			weights.push_back({ AbilityID::FIRE_NOVA, 1.00 });
			weights.push_back({ AbilityID::ICICLE, 1.00 });
			weights.push_back({ AbilityID::SHOCK, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::FIREBALL, 1.00 });
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Shaman
	case 8:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::PRISMATIC_BOLT, 1.00 });
			weights.push_back({ AbilityID::ELEMENTAL_ENERGY, 1.00 });
			weights.push_back({ AbilityID::VENOM, 1.00 });
			weights.push_back({ AbilityID::SPLASH, 1.00 });
			weights.push_back({ AbilityID::WATER_BOLT, 1.00 });
			weights.push_back({ AbilityID::GALE, 1.00 });
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Acolyte
	case 9:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::PRISMATIC_BOLT, 1.00 });
			weights.push_back({ AbilityID::ELEMENTAL_ENERGY, 1.00 });
			weights.push_back({ AbilityID::DARK_BOLT, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::OBLITERATE, 1.00 });
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Priest
	case 10:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::HEAL, 1.00 });
			break;
		case 2:
			break;
		case 3:
			break;
		default:
			break;
		}
		break;
	// Druid
	case 11:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::MEND_WOUNDS, 1.00 });
			break;
		case 2:
			break;
		case 3:
			weights.push_back({ AbilityID::HEALING_RAIN, 1.00 });
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (weights.size() > 0){
		while (true) {
			size_t index = Random::RandSizeT(mt, 0u, weights.size() - 1);
			double weightRoll = Random::RandDouble(mt, 0.0, 1.0);
			if (weightRoll <= weights[index].second) {
				return weights[index].first;
			}
		}
	}
	else {
		return AbilityID::POWER_STRIKE;
	}
}

FormationID Weight::GetRandomFa(std::mt19937_64& mt, std::vector<FormationWeight>& formations) {
	std::uniform_int_distribution<size_t> dist(0u, formations.size() - 1);
	std::uniform_real_distribution<double> roll(0.0, 1.0);
	while (true) {
		size_t index = dist(mt);
		double weightRoll = roll(mt);
		if (weightRoll <= formations[index].second) {
			return formations[index].first;
		}
	}
}

void Weight::RemoveUniqueFa(std::vector<FormationWeight>& formations, FormationID id) {
	for (size_t i = 0; i < formations.size(); i++) {
		if (formations[i].first == id) {
			formations.erase(formations.begin() + i);
			break;
		}
	}
}

void Weight::RemoveUniqueFa(std::vector<FormationWeight>& formations, std::vector<FormationID> id) {
	for (auto f : id) {
		Weight::RemoveUniqueFa(formations, f);
	}
}