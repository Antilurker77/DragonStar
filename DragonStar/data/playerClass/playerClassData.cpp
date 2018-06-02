// ==================================
//
// playerClassData.cpp
//
// ==================================

#include "playerClassData.h"

#include "../id/abilityType.h"
#include "../id/equipType.h"
#include "../id/playerClassID.h"

Pc_Adventurer::Pc_Adventurer() {
	name = "Adventurer";
	playerClassID = PlayerClassID::Adventurer;

	equippable = {
		EquipType::Sword1H,
		EquipType::Sword2H,
		EquipType::Axe1H,
		EquipType::Axe2H,
		EquipType::Mace1H,
		EquipType::Mace2H,
		EquipType::Dagger,
		EquipType::Claw,
		EquipType::Spear,
		EquipType::Bow,
		EquipType::Wand,
		EquipType::Staff,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::OffHand,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::SwordSkill, 3u },
		{ AbilityType::AxeSkill, 3u },
		{ AbilityType::MaceSkill, 3u },
		{ AbilityType::DaggerSkill, 3u },
		{ AbilityType::ClawSkill, 3u },
		{ AbilityType::SpearSkill, 3u },
		{ AbilityType::BowSkill, 3u },
		{ AbilityType::ShieldSkill, 3u },
		{ AbilityType::ArcaneSpell, 3u },
		{ AbilityType::FireSpell, 3u },
		{ AbilityType::IceSpell, 3u },
		{ AbilityType::LightningSpell, 3u },
		{ AbilityType::PoisonSpell, 3u },
		{ AbilityType::WaterSpell, 3u },
		{ AbilityType::WindSpell, 3u },
		{ AbilityType::EarthSpell, 3u },
		{ AbilityType::MindSpell, 3u },
		{ AbilityType::LightSpell, 3u },
		{ AbilityType::DarkSpell, 3u },
		{ AbilityType::SpiritSpell, 3u },
		{ AbilityType::AstralSpell, 3u },
		{ AbilityType::DivineHeal, 3u },
		{ AbilityType::NatureHeal, 3u },
		{ AbilityType::AstralHeal, 3u },
	};
}

Pc_Blademaster::Pc_Blademaster() {
	name = "Blademaster";
	playerClassID = PlayerClassID::Blademaster;

	equippable = {
		EquipType::Sword1H,
		EquipType::Sword2H,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::SwordSkill, 3u },
		{ AbilityType::ShieldSkill, 2u },
		{ AbilityType::ArcaneSpell, 1u },
		{ AbilityType::FireSpell, 1u },
		{ AbilityType::WaterSpell, 1u },
		{ AbilityType::WindSpell, 1u },
		{ AbilityType::EarthSpell, 1u },
	};
}

Pc_Berserker::Pc_Berserker() {
	name = "Berserker";
	playerClassID = PlayerClassID::Berserker;

	equippable = {
		EquipType::Axe1H,
		EquipType::Axe2H,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::AxeSkill, 3u },
		{ AbilityType::ShieldSkill, 2u }
	};
}

Pc_Guardian::Pc_Guardian() {
	name = "Guardian";
	playerClassID = PlayerClassID::Guardian;

	equippable = {
		EquipType::Mace1H,
		EquipType::Mace2H,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::MaceSkill, 3u },
		{ AbilityType::ShieldSkill, 3u },
		{ AbilityType::IceSpell, 1u },
		{ AbilityType::LightningSpell, 1u },
		{ AbilityType::EarthSpell, 1u },
		{ AbilityType::LightSpell, 1u },
		{ AbilityType::DivineHeal, 2u }
	};
}

Pc_Assassin::Pc_Assassin() {
	name = "Assassin";
	playerClassID = PlayerClassID::Assassin;

	equippable = {
		EquipType::Dagger,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::DaggerSkill, 3u },
		{ AbilityType::PoisonSpell, 1u },
		{ AbilityType::DarkSpell, 1u },
	};
}

Pc_Stormsinger::Pc_Stormsinger() {
	name = "Stormsinger";
	playerClassID = PlayerClassID::Stormsinger;

	equippable = {
		EquipType::Spear,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::SpearSkill, 3u },
		{ AbilityType::LightningSpell, 1u },
		{ AbilityType::WaterSpell, 1u },
		{ AbilityType::WindSpell, 1u },
	};
}

Pc_Ranger::Pc_Ranger() {
	name = "Ranger";
	playerClassID = PlayerClassID::Ranger;

	equippable = {
		EquipType::Bow,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::Tech, 3u },
		{ AbilityType::BowSkill, 3u },
		{ AbilityType::ArcaneSpell, 1u },
		{ AbilityType::FireSpell, 1u },
		{ AbilityType::IceSpell, 1u },
		{ AbilityType::LightningSpell, 1u },
		{ AbilityType::PoisonSpell, 1u },
		{ AbilityType::WaterSpell, 1u },
		{ AbilityType::WindSpell, 1u },
		{ AbilityType::EarthSpell, 1u },
		{ AbilityType::LightSpell, 1u },
		{ AbilityType::DarkSpell, 1u },
	};
}

Pc_Wizard::Pc_Wizard() {
	name = "Wizard";
	playerClassID = PlayerClassID::Wizard;

	equippable = {
		EquipType::Wand,
		EquipType::Staff,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::OffHand,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::ArcaneSpell, 3u },
		{ AbilityType::FireSpell, 3u },
		{ AbilityType::IceSpell, 3u },
		{ AbilityType::LightningSpell, 3u },
		{ AbilityType::AstralSpell, 3u }
	};
}

Pc_Shaman::Pc_Shaman() {
	name = "Shaman";
	playerClassID = PlayerClassID::Shaman;

	equippable = {
		EquipType::Wand,
		EquipType::Staff,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::OffHand,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::PoisonSpell, 3u },
		{ AbilityType::WaterSpell, 3u },
		{ AbilityType::WindSpell, 3u },
		{ AbilityType::EarthSpell, 3u },
		{ AbilityType::AstralSpell, 3u },
		{ AbilityType::NatureHeal, 1u }
	};
}

Pc_Acolyte::Pc_Acolyte() {
	name = "Acolyte";
	playerClassID = PlayerClassID::Acolyte;

	equippable = {
		EquipType::Wand,
		EquipType::Staff,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::OffHand,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::MindSpell, 3u },
		{ AbilityType::LightSpell, 3u },
		{ AbilityType::DarkSpell, 3u },
		{ AbilityType::AstralSpell, 3u },
		{ AbilityType::DivineHeal, 1u },
	};
}

Pc_Priest::Pc_Priest() {
	name = "Priest";
	playerClassID = PlayerClassID::Priest;

	equippable = {
		EquipType::Wand,
		EquipType::Staff,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::OffHand,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::LightSpell, 1u },
		{ AbilityType::DivineHeal, 3u },
		{ AbilityType::AstralHeal, 3u },
	};
}

Pc_Druid::Pc_Druid() {
	name = "Druid";
	playerClassID = PlayerClassID::Druid;

	equippable = {
		EquipType::Wand,
		EquipType::Staff,
		EquipType::Shield,
		EquipType::Buckler,
		EquipType::OffHand,
		EquipType::HeavyBody,
		EquipType::HeavyFeet,
		EquipType::HeavyHands,
		EquipType::HeavyHead,
		EquipType::LightBody,
		EquipType::LightFeet,
		EquipType::LightHands,
		EquipType::LightHead,
		EquipType::MedBody,
		EquipType::MedFeet,
		EquipType::MedHands,
		EquipType::MedHead,
		EquipType::Ring,
		EquipType::Neck,
		EquipType::Trinket
	};

	usable = {
		{ AbilityType::WaterSpell, 1u },
		{ AbilityType::WindSpell, 1u },
		{ AbilityType::EarthSpell, 1u },
		{ AbilityType::NatureHeal, 3u },
		{ AbilityType::AstralHeal, 3u },
	};
}