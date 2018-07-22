// ==================================
//
// factory.cpp
//
// ==================================

#include "factory.h"

#include "abilityScroll.h"
#include "ability/header/abiltyData.h"
#include "aura/header/auraData.h"
#include "enemy/header/enemyData.h"
#include "equipment/header/equipmentData.h"
#include "formation/header/formationData.h"
#include "map/header/mapData.h"
#include "playerClass/playerClassData.h"
#include "race/header/raceData.h"
#include "tileset/header/tilesetData.h"

#include "id/abilityID.h"
#include "id/auraID.h"
#include "id/enemyID.h"
#include "id/equipmentID.h"
#include "id/formationID.h"
#include "id/mapID.h"
#include "id/playerClassID.h"
#include "id/raceID.h"
#include "id/tilesetID.h"

AbilityPtr Factory::CreateAbility(AbilityID id) {
	switch (id) {
	case AbilityID::Attack:								return AbilityPtr(std::make_shared<Ab_Attack>());
	case AbilityID::ArcaneBlast:						return AbilityPtr(std::make_shared<Ab_ArcaneBlast>());
	case AbilityID::Bite:								return AbilityPtr(std::make_shared<Ab_Bite>());
	case AbilityID::Boulder:							return AbilityPtr(std::make_shared<Ab_Boulder>());
	case AbilityID::Chopper:							return AbilityPtr(std::make_shared<Ab_Chopper>());
	case AbilityID::Cleave:								return AbilityPtr(std::make_shared<Ab_Cleave>());
	case AbilityID::CrushArmor:							return AbilityPtr(std::make_shared<Ab_CrushArmor>());
	case AbilityID::DarkBolt:							return AbilityPtr(std::make_shared<Ab_DarkBolt>());
	case AbilityID::DragonfireBolt:						return AbilityPtr(std::make_shared<Ab_DragonfireBolt>());
	case AbilityID::DualStrike:							return AbilityPtr(std::make_shared<Ab_DualStrike>());
	case AbilityID::ElementalEnergy:					return AbilityPtr(std::make_shared<Ab_ElementalEnergy>());
	case AbilityID::Fireball:							return AbilityPtr(std::make_shared<Ab_Fireball>());
	case AbilityID::FireNova:							return AbilityPtr(std::make_shared<Ab_FireNova>());
	case AbilityID::FlameBolt:							return AbilityPtr(std::make_shared<Ab_FlameBolt>());
	case AbilityID::FlameSlash:							return AbilityPtr(std::make_shared<Ab_FlameSlash>());
	case AbilityID::Frost:								return AbilityPtr(std::make_shared<Ab_Frost>());
	case AbilityID::Gale:								return AbilityPtr(std::make_shared<Ab_Gale>());
	case AbilityID::Heal:								return AbilityPtr(std::make_shared<Ab_Heal>());
	case AbilityID::HealingRain:						return AbilityPtr(std::make_shared<Ab_HealingRain>());
	case AbilityID::HeartSeeker:						return AbilityPtr(std::make_shared<Ab_HeartSeeker>());
	case AbilityID::Icicle:								return AbilityPtr(std::make_shared<Ab_Icicle>());
	case AbilityID::LightBolt:							return AbilityPtr(std::make_shared<Ab_LightBolt>());
	case AbilityID::MagicMissile:						return AbilityPtr(std::make_shared<Ab_MagicMissile>());
	case AbilityID::MendWounds:							return AbilityPtr(std::make_shared<Ab_MendWounds>());
	case AbilityID::Obliterate:							return AbilityPtr(std::make_shared<Ab_Obliterate>());
	case AbilityID::PowerShot:							return AbilityPtr(std::make_shared<Ab_PowerShot>());
	case AbilityID::PowerStrike:						return AbilityPtr(std::make_shared<Ab_PowerStrike>());
	case AbilityID::PrismaticBolt:						return AbilityPtr(std::make_shared<Ab_PrismaticBolt>());
	case AbilityID::PsionicMissile:						return AbilityPtr(std::make_shared<Ab_PsionicMissile>());
	case AbilityID::RendingSlash:						return AbilityPtr(std::make_shared<Ab_RendingSlash>());
	case AbilityID::ShadowEnergy:						return AbilityPtr(std::make_shared<Ab_ShadowEnergy>());
	case AbilityID::ShadowStalk:						return AbilityPtr(std::make_shared<Ab_ShadowStalk>());
	case AbilityID::Shock:								return AbilityPtr(std::make_shared<Ab_Shock>());
	case AbilityID::Splash:								return AbilityPtr(std::make_shared<Ab_Splash>());
	case AbilityID::TerrifyingHowl:						return AbilityPtr(std::make_shared<Ab_TerrifyingHowl>());
	case AbilityID::Venom:								return AbilityPtr(std::make_shared<Ab_Venom>());
	case AbilityID::WarpSlice:							return AbilityPtr(std::make_shared<Ab_WarpSlice>());
	case AbilityID::WaterBolt:							return AbilityPtr(std::make_shared<Ab_WaterBolt>());
	case AbilityID::RacialCommandingShout:				return AbilityPtr(std::make_shared<Ab_CommandingShout>());
	case AbilityID::RacialDragonBreath:					return AbilityPtr(std::make_shared<Ab_DragonBreath>());

	// Returns Attack ability if ID is invalid.
	default:											return AbilityPtr(std::make_shared<Ab_Attack>());
	}
}

ItemPtr Factory::CreateAbilityScroll(AbilityID id) {
	return ItemPtr(std::make_shared<AbilityScroll>(id));
}

AuraPtr Factory::CreateAura(AuraID id) {
	switch (id) {
	case AuraID::BandOfTwinDisciplines:					return AuraPtr(std::make_shared<Au_BandOfTwinDisciplines>());
	case AuraID::CommandingShout:						return AuraPtr(std::make_shared<Au_CommandingShout>());
	case AuraID::CrushArmor:							return AuraPtr(std::make_shared<Au_CrushArmor>());
	case AuraID::ElementalEnergy:						return AuraPtr(std::make_shared<Au_ElementalEnergy>());
	case AuraID::FlameSlash:							return AuraPtr(std::make_shared<Au_FlameSlash>());
	case AuraID::Frost:									return AuraPtr(std::make_shared<Au_Frost>());
	case AuraID::Gale:									return AuraPtr(std::make_shared<Au_Gale>());
	case AuraID::HealingRain:							return AuraPtr(std::make_shared<Au_HealingRain>());
	case AuraID::HeartBroken:							return AuraPtr(std::make_shared<Au_HeartBroken>());
	case AuraID::Icicle:								return AuraPtr(std::make_shared<Au_Icicle>());
	case AuraID::MendWounds:							return AuraPtr(std::make_shared<Au_MendWounds>());
	case AuraID::PrismaticBolt:							return AuraPtr(std::make_shared<Au_PrismaticBolt>());
	case AuraID::RendingSlash:							return AuraPtr(std::make_shared<Au_RendingSlash>());
	case AuraID::ShadowEnergy:							return AuraPtr(std::make_shared<Au_ShadowEnergy>());
	case AuraID::SlimeTouch:							return AuraPtr(std::make_shared<Au_SlimeTouch>());
	case AuraID::TerrifyingHowl:						return AuraPtr(std::make_shared<Au_TerrifyingHowl>());
	case AuraID::Venom:									return AuraPtr(std::make_shared<Au_Venom>());

	// Returns Venom if ID is invalid.
	default:											return AuraPtr(std::make_shared<Au_Venom>());
	}
}

EnemyInfoPtr Factory::CreateEnemyInfo(EnemyID id) {
	switch (id) {
	// Common
	case EnemyID::TestAssassin:							return EnemyInfoPtr(std::make_shared<En_TestAssassin>());
	case EnemyID::TestEnemy:							return EnemyInfoPtr(std::make_shared<En_TestEnemy>());
	case EnemyID::TestMage:								return EnemyInfoPtr(std::make_shared<En_TestMage>());
	case EnemyID::ArcaneSentry:							return EnemyInfoPtr(std::make_shared<En_ArcaneSentry>());
	case EnemyID::GiantRat:								return EnemyInfoPtr(std::make_shared<En_GiantRat>());
	case EnemyID::LesserFlameblade:						return EnemyInfoPtr(std::make_shared<En_LesserFlameblade>());
	case EnemyID::ShadowStalker:						return EnemyInfoPtr(std::make_shared<En_ShadowStalker>());
	case EnemyID::Slime:								return EnemyInfoPtr(std::make_shared<En_Slime>());
	case EnemyID::TargetDummy:							return EnemyInfoPtr(std::make_shared<En_TargetDummy>());

	// Unique
	case EnemyID::TestUnique:							return EnemyInfoPtr(std::make_shared<En_TestUnique>());
	case EnemyID::Fenrok:								return EnemyInfoPtr(std::make_shared<En_Fenrok>());

	// Returns Test Enemy if ID is invalid.
	default:											return EnemyInfoPtr(std::make_shared<En_TestEnemy>());
	}
}

FormationPtr Factory::CreateFormation(FormationID id) {
	switch (id) {
	// Common
	case FormationID::TestFormationA:					return FormationPtr(std::make_shared<Fa_TestFormationA>());
	case FormationID::TestFormationB:					return FormationPtr(std::make_shared<Fa_TestFormationB>());
	case FormationID::FlamebladesStalkersField:			return FormationPtr(std::make_shared<Fa_FlamebladesStalkersField>());
	case FormationID::LesserFlamebladesField:			return FormationPtr(std::make_shared<Fa_LesserFlamebladesField>());
	case FormationID::SentryAmbush:						return FormationPtr(std::make_shared<Fa_SentryAmbush>());
	case FormationID::SewerRats:						return FormationPtr(std::make_shared<Fa_SewerRats>());
	case FormationID::SewerRatsSlimes:					return FormationPtr(std::make_shared<Fa_SewerRatsSlimes>());
	case FormationID::SewerSlimes:						return FormationPtr(std::make_shared<Fa_SewerSlimes>());
	case FormationID::SewerRatsIntersection:			return FormationPtr(std::make_shared<Fa_SewerRatsIntersection>());
	case FormationID::ShadowStalkersField:				return FormationPtr(std::make_shared<Fa_ShadowStalkersField>());

	// Unique
	case FormationID::TestUnique:						return FormationPtr(std::make_shared<Fa_TestUnique>());
	case FormationID::Fenrok:							return FormationPtr(std::make_shared<Fa_Fenrok>());

	// Boss
	case FormationID::TestBoss:							return FormationPtr(std::make_shared<Fa_TestBoss>());

	// Returns Test Boss formation if ID is invalid.
	default:											return FormationPtr(std::make_shared<Fa_TestBoss>());
	}
}

ItemPtr Factory::CreateEquipment(EquipmentID id) {
	switch (id) {
	case EquipmentID::AmuletOfDivineLight:				return ItemPtr(std::make_shared<Eq_AmuletOfDivineLight>());
	case EquipmentID::BandOfTwinDisciplines:			return ItemPtr(std::make_shared<Eq_BandOfTwinDisciplines>());
	case EquipmentID::CharmOfConstitution:				return ItemPtr(std::make_shared<Eq_CharmOfConstitution>());
	case EquipmentID::CharmOfDexterity:					return ItemPtr(std::make_shared<Eq_CharmOfDexterity>());
	case EquipmentID::CharmOfIntelligence:				return ItemPtr(std::make_shared<Eq_CharmOfIntelligence>());
	case EquipmentID::CharmOfStrength:					return ItemPtr(std::make_shared<Eq_CharmOfStrength>());
	case EquipmentID::CharmOfWisdom:					return ItemPtr(std::make_shared<Eq_CharmOfWisdom>());
	case EquipmentID::CloudLance:						return ItemPtr(std::make_shared<Eq_CloudLance>());
	case EquipmentID::DragoniteNecklace:				return ItemPtr(std::make_shared<Eq_DragoniteNecklace>());
	case EquipmentID::DragoniteRing:					return ItemPtr(std::make_shared<Eq_DragoniteRing>());
	case EquipmentID::Flametongue:						return ItemPtr(std::make_shared<Eq_Flametongue>());
	case EquipmentID::GoldNecklace:						return ItemPtr(std::make_shared<Eq_GoldNecklace>());
	case EquipmentID::GoldRing:							return ItemPtr(std::make_shared<Eq_GoldRing>());
	case EquipmentID::IronArmor:						return ItemPtr(std::make_shared<Eq_IronArmor>());
	case EquipmentID::IronAxe:							return ItemPtr(std::make_shared<Eq_IronAxe>());
	case EquipmentID::IronBuckler:						return ItemPtr(std::make_shared<Eq_IronBuckler>());
	case EquipmentID::IronDagger:						return ItemPtr(std::make_shared<Eq_IronDagger>());
	case EquipmentID::IronGauntlets:					return ItemPtr(std::make_shared<Eq_IronGauntlets>());
	case EquipmentID::IronGreataxe:						return ItemPtr(std::make_shared<Eq_IronGreataxe>());
	case EquipmentID::IronGreatmace:					return ItemPtr(std::make_shared<Eq_IronGreatmace>());
	case EquipmentID::IronGreatsword:					return ItemPtr(std::make_shared<Eq_IronGreatsword>());
	case EquipmentID::IronGreaves:						return ItemPtr(std::make_shared<Eq_IronGreaves>());
	case EquipmentID::IronHelm:							return ItemPtr(std::make_shared<Eq_IronHelm>());
	case EquipmentID::IronMace:							return ItemPtr(std::make_shared<Eq_IronMace>());
	case EquipmentID::IronShield:						return ItemPtr(std::make_shared<Eq_IronShield>());
	case EquipmentID::IronSpear:						return ItemPtr(std::make_shared<Eq_IronSpear>());
	case EquipmentID::IronSword:						return ItemPtr(std::make_shared<Eq_IronSword>());
	case EquipmentID::LeatherArmor:						return ItemPtr(std::make_shared<Eq_LeatherArmor>());
	case EquipmentID::LeatherBoots:						return ItemPtr(std::make_shared<Eq_LeatherBoots>());
	case EquipmentID::LeatherGloves:					return ItemPtr(std::make_shared<Eq_LeatherGloves>());
	case EquipmentID::LeatherHelmet:					return ItemPtr(std::make_shared<Eq_LeatherHelmet>());
	case EquipmentID::Longbow:							return ItemPtr(std::make_shared<Eq_Longbow>());
	case EquipmentID::OmegaRing:						return ItemPtr(std::make_shared<Eq_OmegaRing>());
	case EquipmentID::PowerOrb:							return ItemPtr(std::make_shared<Eq_PowerOrb>());
	case EquipmentID::RingOfVitality:					return ItemPtr(std::make_shared<Eq_RingOfVitality>());
	case EquipmentID::SilkGloves:						return ItemPtr(std::make_shared<Eq_SilkGloves>());
	case EquipmentID::SilkHat:							return ItemPtr(std::make_shared<Eq_SilkHat>());
	case EquipmentID::SilkRobes:						return ItemPtr(std::make_shared<Eq_SilkRobes>());
	case EquipmentID::SilkShoes:						return ItemPtr(std::make_shared<Eq_SilkShoes>());
	case EquipmentID::SilverNecklace:					return ItemPtr(std::make_shared<Eq_SilverNecklace>());
	case EquipmentID::SilverRing:						return ItemPtr(std::make_shared<Eq_SilverRing>());
	case EquipmentID::SpringWaterStone:					return ItemPtr(std::make_shared<Eq_SpringWaterStone>());
	case EquipmentID::StoneGauntlets:					return ItemPtr(std::make_shared<Eq_StoneGauntlets>());
	case EquipmentID::WoodenStaff:						return ItemPtr(std::make_shared<Eq_WoodenStaff>());
	case EquipmentID::WoodenWand:						return ItemPtr(std::make_shared<Eq_WoodenWand>());

	// Returns Silver Ring if ID is invalid.
	default:											return ItemPtr(std::make_shared<Eq_SilverRing>());
	}
}

// Returns map data, including tiles and tileset properties.
MapPtr Factory::CreateMap(MapID id){
	switch (id){
	case MapID::BasicDungeon:							return MapPtr(std::make_shared<Mp_BasicDungeon>());
	case MapID::TestMap:								return MapPtr(std::make_shared<Mp_TestMap>());
	case MapID::TestMapXL:								return MapPtr(std::make_shared<Mp_TestMapXL>());
	case MapID::TestMapXS:								return MapPtr(std::make_shared<Mp_TestMapXS>());
	case MapID::TestArena:								return MapPtr(std::make_shared<Mp_TestArena>());
	case MapID::TestArenaB:								return MapPtr(std::make_shared<Mp_TestArenaB>());
	case MapID::FieldField:								return MapPtr(std::make_shared<Mp_FieldField>());
	case MapID::FieldSmallIsland:						return MapPtr(std::make_shared<Mp_FieldSmallIsland>());
	case MapID::FieldSewer:								return MapPtr(std::make_shared<Mp_FieldSewer>());
	case MapID::FieldSewerIntersection:					return MapPtr(std::make_shared<Mp_FieldSewerIntersection>());

	// Returns TEST map if ID is invalid.
	default:											return MapPtr(std::make_shared<Mp_TestMap>());
	}
}

PlayerClassPtr Factory::CreatePlayerClass(PlayerClassID id) {
	switch (id) {
	case PlayerClassID::Adventurer:						return PlayerClassPtr(std::make_shared<Pc_Adventurer>());
	case PlayerClassID::Blademaster:					return PlayerClassPtr(std::make_shared<Pc_Blademaster>());
	case PlayerClassID::Berserker:						return PlayerClassPtr(std::make_shared<Pc_Berserker>());
	case PlayerClassID::Guardian:						return PlayerClassPtr(std::make_shared<Pc_Guardian>());
	case PlayerClassID::Assassin:						return PlayerClassPtr(std::make_shared<Pc_Assassin>());
	case PlayerClassID::Stormsinger:					return PlayerClassPtr(std::make_shared<Pc_Stormsinger>());
	case PlayerClassID::Ranger:							return PlayerClassPtr(std::make_shared<Pc_Ranger>());
	case PlayerClassID::Wizard:							return PlayerClassPtr(std::make_shared<Pc_Wizard>());
	case PlayerClassID::Shaman:							return PlayerClassPtr(std::make_shared<Pc_Shaman>());
	case PlayerClassID::Acolyte:						return PlayerClassPtr(std::make_shared<Pc_Acolyte>());
	case PlayerClassID::Priest:							return PlayerClassPtr(std::make_shared<Pc_Priest>());
	case PlayerClassID::Druid:							return PlayerClassPtr(std::make_shared<Pc_Druid>());

	// Return Adventurer player class if ID is invalid.
	default:											return PlayerClassPtr(std::make_shared<Pc_Adventurer>());
	}
}

// Returns race data.
RacePtr Factory::CreateRace(RaceID id){
	switch (id){
	case RaceID::Human:									return RacePtr(std::make_shared<Human>());
	case RaceID::Vulpine:								return RacePtr(std::make_shared<Vulpine>());
	case RaceID::Runetouched:							return RacePtr(std::make_shared<Runetouched>());

	// Returns HUMAN race data if ID is invalid.
	default:											return RacePtr(std::make_shared<Human>());
	}
}

// Returns tileset data. Used by maps.
TilesetPtr Factory::CreateTileset(TilesetID id){
	switch (id){
	case TilesetID::TestTileset:						return TilesetPtr(std::make_unique<Ts_TestTileset>());
	case TilesetID::Field:								return TilesetPtr(std::make_unique<Ts_Field>());

	// Returns TEST tileset if ID is invalid.
	default:											return TilesetPtr(std::make_unique<Ts_TestTileset>());
	}

}