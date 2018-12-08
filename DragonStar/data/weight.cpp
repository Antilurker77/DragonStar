// ==================================
//
// weight.cpp
//
// ==================================

#include "weight.h"

#include <array>

#include "id/abilityID.h"
#include "id/equipmentID.h"
#include "id/formationID.h"
#include "../core/random.h"

std::vector<FormationWeight> Weight::GetCommonFaWeights(int tier) {
	switch (tier) {
	case 1:
		return {
			{ FormationID::FlamebladesStalkersField, 0.75 },
			{ FormationID::LesserFlamebladesField, 1.0 },
			{ FormationID::SentryAmbush, 1.0 },
			{ FormationID::SewerRats, 0.5 },
			{ FormationID::SewerRatsSlimes, 1.0 },
			{ FormationID::SewerSlimes, 0.5 },
			{ FormationID::SewerRatsIntersection, 1.0 },
			{ FormationID::ShadowStalkersField, 1.0 }
		};
	default:
		return {
			{ FormationID::TestFormationA, 1.0 },
			{ FormationID::TestFormationB, 0.5 }
		};
	}
	
}

std::vector<FormationWeight> Weight::GetUniqueFaWeights(int tier) {
	switch (tier) {
	default:
		return {
			{ FormationID::TestUnique, 1.0 },
			{ FormationID::Fenrok, 1.0 }
		};
	}
}

std::vector<FormationWeight> Weight::GetBossFaWeights(int tier) {
	switch (tier) {
	default:
		return {
			{ FormationID::TestBoss, 1.0 }
		};
	}
}

EquipmentID Weight::GetRandomEq(std::mt19937_64& mt, int tier) {
	EquipmentID id = EquipmentID::Undefined;
	std::vector<EquipmentWeight> weights;

	// Tier 6
	if (tier >= 6) {
		
		// Jewelry
		weights.push_back({ EquipmentID::DragoniteNecklace, 0.50 });
		weights.push_back({ EquipmentID::DragoniteRing, 1.00 });
	}
	// Tier 5
	else if (tier == 5) {
		
		// Jewelry
		weights.push_back({ EquipmentID::DragoniteNecklace, 0.50 });
		weights.push_back({ EquipmentID::DragoniteRing, 1.00 });
	}
	// Tier 4
	else if (tier == 4) {
		
		// Jewelry
		weights.push_back({ EquipmentID::GoldNecklace, 0.50 });
		weights.push_back({ EquipmentID::GoldRing, 1.00 });
	}
	// Tier 3
	else if (tier == 3) {

		// Jewelry
		weights.push_back({ EquipmentID::GoldNecklace, 0.50 });
		weights.push_back({ EquipmentID::GoldRing, 1.00 });
	}
	// Tier 2
	else if (tier == 2) {

		// Jewelry
		weights.push_back({ EquipmentID::SilverNecklace, 0.50 });
		weights.push_back({ EquipmentID::SilverRing, 1.00 });
	}
	// Tier 1
	else {
		// Weapons
		weights.push_back({ EquipmentID::IronSword, 0.25 });
		weights.push_back({ EquipmentID::IronGreatsword, 0.25 });
		weights.push_back({ EquipmentID::IronAxe, 0.25 });
		weights.push_back({ EquipmentID::IronGreataxe, 0.25 });
		weights.push_back({ EquipmentID::IronMace, 0.25 });
		weights.push_back({ EquipmentID::IronGreatmace, 0.25 });
		weights.push_back({ EquipmentID::IronDagger, 0.50 });
		weights.push_back({ EquipmentID::IronSpear, 0.50 });
		weights.push_back({ EquipmentID::Longbow, 0.25 });
		weights.push_back({ EquipmentID::LightCrossbow, 0.25 });
		weights.push_back({ EquipmentID::WoodenWand, 0.50 });
		weights.push_back({ EquipmentID::WoodenStaff, 0.50 });

		// Off-Hand
		weights.push_back({ EquipmentID::IronShield, 0.25 });
		weights.push_back({ EquipmentID::IronBuckler, 0.25 });
		weights.push_back({ EquipmentID::PowerOrb, 0.50 });

		// Armor
		weights.push_back({ EquipmentID::IronHelm, 0.50 });
		weights.push_back({ EquipmentID::LeatherHelmet, 0.50 });
		weights.push_back({ EquipmentID::SilkHat, 0.50 });
		weights.push_back({ EquipmentID::IronArmor, 0.50 });
		weights.push_back({ EquipmentID::LeatherArmor, 0.50 });
		weights.push_back({ EquipmentID::SilkRobes, 0.50 });
		weights.push_back({ EquipmentID::IronGauntlets, 0.50 });
		weights.push_back({ EquipmentID::LeatherGloves, 0.50 });
		weights.push_back({ EquipmentID::SilkGloves, 0.50 });
		weights.push_back({ EquipmentID::IronGreaves, 0.50 });
		weights.push_back({ EquipmentID::LeatherBoots, 0.50 });
		weights.push_back({ EquipmentID::SilkShoes, 0.50 });

		// Jewelry
		weights.push_back({ EquipmentID::SilverNecklace, 0.50 });
		weights.push_back({ EquipmentID::SilverRing, 1.00 });
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
		weights.push_back({ EquipmentID::Flametongue, 0.50 });
		
		weights.push_back({ EquipmentID::HowlingSands, 0.50 });

		weights.push_back({ EquipmentID::CloudLance, 0.50 });
		
		weights.push_back({ EquipmentID::StaffOfTheNovice, 0.50 });

		weights.push_back({ EquipmentID::StoneGauntlets, 0.50 });

		weights.push_back({ EquipmentID::AmuletOfDivineLight, 0.50 });
		
		weights.push_back({ EquipmentID::BandOfTwinDisciplines, 0.50 });
		weights.push_back({ EquipmentID::RingOfVitality, 0.50 });
		
		weights.push_back({ EquipmentID::CharmOfStrength, 1.00 });
		weights.push_back({ EquipmentID::CharmOfDexterity, 1.00 });
		weights.push_back({ EquipmentID::CharmOfIntelligence, 1.00 });
		weights.push_back({ EquipmentID::CharmOfWisdom, 1.00 });
		weights.push_back({ EquipmentID::CharmOfConstitution, 1.00 });
		weights.push_back({ EquipmentID::SpringWaterStone, 1.00 });
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
		return EquipmentID::Undefined;
	}
}

AbilityID Weight::GetRandomAb(std::mt19937_64& mt, int tier) {
	std::vector<AbilityWeight> weights;

	// Determine ability tier.
	//double tierRoll = Random::RandDouble(mt, 0.0, 1.0);
	int tierRoll = Random::RandInt(mt, 1, 100);
	int tierPicked = 1;

	// Determine which ability tier to take from.
	if (tier <= 6 && tier >= 1) {
		std::array<std::array<int, 2>, 6> tierWeights = { {
			{90, 100},
			{80, 100},
			{60, 90},
			{45, 85},
			{10, 40},
			{10, 30}
		} };

		if (tierRoll > tierWeights[tier - 1][1]) {
			tierPicked = 3;
		}
		else if (tierRoll > tierWeights[tier - 1][0]) {
			tierPicked = 2;
		}
		else {
			tierPicked = 1;
		}
	}

	// Roll ID
	int classRoll = Random::RandInt(mt, 1, 11);

	switch (classRoll) {
	// Blademaster
	case 1:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::Cleave, 1.00 });
			weights.push_back({ AbilityID::PowerStrike, 1.00 });
			weights.push_back({ AbilityID::RendingSlash, 1.00 });
			weights.push_back({ AbilityID::FlameSlash, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::WarpSlice, 1.00 });
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
			weights.push_back({ AbilityID::Cleave, 1.00 });
			weights.push_back({ AbilityID::PowerStrike, 1.00 });
			weights.push_back({ AbilityID::RendingSlash, 1.00 });
			weights.push_back({ AbilityID::Chopper, 1.00 });
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
			weights.push_back({ AbilityID::Cleave, 1.00 });
			weights.push_back({ AbilityID::PowerStrike, 1.00 });
			weights.push_back({ AbilityID::CrushArmor, 1.00 });
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
			weights.push_back({ AbilityID::PowerStrike, 1.00 });
			weights.push_back({ AbilityID::RendingSlash, 1.00 });
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
			weights.push_back({ AbilityID::PowerStrike, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::Tempest, 1.00 });
			break;
		case 3:
			weights.push_back({ AbilityID::Trident, 1.00 });
			break;
		default:
			break;
		}
		break;
	// Ranger
	case 6:
		switch (tierPicked) {
		case 1:
			weights.push_back({ AbilityID::PowerShot, 1.00 });
			weights.push_back({ AbilityID::HeartSeeker, 1.00 });
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
			weights.push_back({ AbilityID::Spellpower, 0.50 });
			weights.push_back({ AbilityID::PrismaticBolt, 1.00 });
			weights.push_back({ AbilityID::ElementalEnergy, 1.00 });
			weights.push_back({ AbilityID::MagicMissile, 1.00 });
			weights.push_back({ AbilityID::ArcaneBlast, 1.00 });
			weights.push_back({ AbilityID::FlameBolt, 1.00 });
			weights.push_back({ AbilityID::DragonfireBolt, 1.00 });
			weights.push_back({ AbilityID::FireNova, 1.00 });
			weights.push_back({ AbilityID::Icicle, 1.00 });
			weights.push_back({ AbilityID::Frost, 1.00 });
			weights.push_back({ AbilityID::Shock, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::Fireball, 1.00 });
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
			weights.push_back({ AbilityID::Spellpower, 0.50 });
			weights.push_back({ AbilityID::PrismaticBolt, 1.00 });
			weights.push_back({ AbilityID::ElementalEnergy, 1.00 });
			weights.push_back({ AbilityID::Venom, 1.00 });
			weights.push_back({ AbilityID::Splash, 1.00 });
			weights.push_back({ AbilityID::WaterBolt, 1.00 });
			weights.push_back({ AbilityID::Gale, 1.00 });
			weights.push_back({ AbilityID::Boulder, 1.00 });
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
			weights.push_back({ AbilityID::Spellpower, 0.50 });
			weights.push_back({ AbilityID::PrismaticBolt, 1.00 });
			weights.push_back({ AbilityID::ElementalEnergy, 1.00 });
			weights.push_back({ AbilityID::PsionicMissile, 1.00 });
			weights.push_back({ AbilityID::LightBolt, 1.00 });
			weights.push_back({ AbilityID::DarkBolt, 1.00 });
			break;
		case 2:
			weights.push_back({ AbilityID::Obliterate, 1.00 });
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
			weights.push_back({ AbilityID::Spellpower, 0.50 });
			weights.push_back({ AbilityID::Heal, 1.00 });
			weights.push_back({ AbilityID::GrandHeal, 1.00 });
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
			weights.push_back({ AbilityID::Spellpower, 0.50 });
			weights.push_back({ AbilityID::MendWounds, 1.00 });
			weights.push_back({ AbilityID::MendingWaters, 1.00 });
			break;
		case 2:
			break;
		case 3:
			weights.push_back({ AbilityID::HealingRain, 1.00 });
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
		return AbilityID::PowerStrike;
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