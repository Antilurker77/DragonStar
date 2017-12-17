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

Factory::Factory(){

}

AbilityPtr Factory::CreateAbility(AbilityID id) {
	switch (id) {
	case AbilityID::ATTACK:								return AbilityPtr(std::make_shared<Ab_Attack>());
	case AbilityID::ARCANE_BLAST:						return AbilityPtr(std::make_shared<Ab_ArcaneBlast>());
	case AbilityID::DARK_BOLT:							return AbilityPtr(std::make_shared<Ab_DarkBolt>());
	case AbilityID::ELEMENTAL_ENERGY:					return AbilityPtr(std::make_shared<Ab_ElementalEnergy>());
	case AbilityID::FLAME_BOLT:							return AbilityPtr(std::make_shared<Ab_FlameBolt>());
	case AbilityID::FLAME_SLASH:						return AbilityPtr(std::make_shared<Ab_FlameSlash>());
	case AbilityID::GALE:								return AbilityPtr(std::make_shared<Ab_Gale>());
	case AbilityID::HEAL:								return AbilityPtr(std::make_shared<Ab_Heal>());
	case AbilityID::HEALING_RAIN:						return AbilityPtr(std::make_shared<Ab_HealingRain>());
	case AbilityID::ICICLE:								return AbilityPtr(std::make_shared<Ab_Icicle>());
	case AbilityID::MAGIC_MISSILE:						return AbilityPtr(std::make_shared<Ab_MagicMissile>());
	case AbilityID::MEND_WOUNDS:						return AbilityPtr(std::make_shared<Ab_MendWounds>());
	case AbilityID::POWER_STRIKE:						return AbilityPtr(std::make_shared<Ab_PowerStrike>());
	case AbilityID::PRISMATIC_BOLT:						return AbilityPtr(std::make_shared<Ab_PrismaticBolt>());
	case AbilityID::RENDING_SLASH:						return AbilityPtr(std::make_shared<Ab_RendingSlash>());
	case AbilityID::SHOCK:								return AbilityPtr(std::make_shared<Ab_Shock>());
	case AbilityID::SPLASH:								return AbilityPtr(std::make_shared<Ab_Splash>());
	case AbilityID::VENOM:								return AbilityPtr(std::make_shared<Ab_Venom>());
	case AbilityID::WATER_BOLT:							return AbilityPtr(std::make_shared<Ab_WaterBolt>());
	case AbilityID::RACIAL_COMMANDING_SHOUT:			return AbilityPtr(std::make_shared<Ab_CommandingShout>());
	case AbilityID::RACIAL_DRAGON_BREATH:				return AbilityPtr(std::make_shared<Ab_DragonBreath>());

	// Returns Attack ability if ID is invalid.
	default:											return AbilityPtr(std::make_shared<Ab_Attack>());
	}
}

ItemPtr Factory::CreateAbilityScroll(AbilityID id) {
	return ItemPtr(std::make_shared<AbilityScroll>(id));
}

AuraPtr Factory::CreateAura(AuraID id) {
	switch (id) {
	case AuraID::COMMANDING_SHOUT:						return AuraPtr(std::make_shared<Au_CommandingShout>());
	case AuraID::ELEMENTAL_ENERGY:						return AuraPtr(std::make_shared<Au_ElementalEnergy>());
	case AuraID::FLAME_SLASH:							return AuraPtr(std::make_shared<Au_FlameSlash>());
	case AuraID::GALE:									return AuraPtr(std::make_shared<Au_Gale>());
	case AuraID::HEALING_RAIN:							return AuraPtr(std::make_shared<Au_HealingRain>());
	case AuraID::ICICLE:								return AuraPtr(std::make_shared<Au_Icicle>());
	case AuraID::MEND_WOUNDS:							return AuraPtr(std::make_shared<Au_MendWounds>());
	case AuraID::PRISMATIC_BOLT:						return AuraPtr(std::make_shared<Au_PrismaticBolt>());
	case AuraID::RENDING_SLASH:							return AuraPtr(std::make_shared<Au_RendingSlash>());
	case AuraID::VENOM:									return AuraPtr(std::make_shared<Au_Venom>());

	// Returns Venom if ID is invalid.
	default:											return AuraPtr(std::make_shared<Au_Venom>());
	}
}

EnemyInfoPtr Factory::CreateEnemyInfo(EnemyID id) {
	switch (id) {
	// Common
	case EnemyID::TEST_ASSASSIN:						return EnemyInfoPtr(std::make_shared<En_TestAssassin>());
	case EnemyID::TEST_ENEMY:							return EnemyInfoPtr(std::make_shared<En_TestEnemy>());
	case EnemyID::TEST_MAGE:							return EnemyInfoPtr(std::make_shared<En_TestMage>());
	case EnemyID::TARGET_DUMMY:							return EnemyInfoPtr(std::make_shared<En_TargetDummy>());

	// Unique
	case EnemyID::TEST_UNIQUE:							return EnemyInfoPtr(std::make_shared<En_TestUnique>());

	// Returns Test Enemy if ID is invalid.
	default:											return EnemyInfoPtr(std::make_shared<En_TestEnemy>());
	}
}

FormationPtr Factory::CreateFormation(FormationID id) {
	switch (id) {
	// Common
	case FormationID::TEST_FORMATION_A:					return FormationPtr(std::make_shared<Fa_TestFormationA>());
	case FormationID::TEST_FORMATION_B:					return FormationPtr(std::make_shared<Fa_TestFormationB>());

	// Unique
	case FormationID::TEST_UNIQUE:						return FormationPtr(std::make_shared<Fa_TestUnique>());

	// Boss
	case FormationID::TEST_BOSS:						return FormationPtr(std::make_shared<Fa_TestBoss>());

	// Returns Test Boss formation if ID is invalid.
	default:											return FormationPtr(std::make_shared<Fa_TestBoss>());
	}
}

ItemPtr Factory::CreateEquipment(EquipmentID id) {
	switch (id) {
	case EquipmentID::DRAGONITE_NECKLACE:				return ItemPtr(std::make_shared<Eq_DragoniteNecklace>());
	case EquipmentID::DRAGONITE_RING:					return ItemPtr(std::make_shared<Eq_DragoniteRing>());
	case EquipmentID::GOLD_NECKLACE:					return ItemPtr(std::make_shared<Eq_GoldNecklace>());
	case EquipmentID::GOLD_RING:						return ItemPtr(std::make_shared<Eq_GoldRing>());
	case EquipmentID::IRON_SPEAR:						return ItemPtr(std::make_shared<Eq_IronSpear>());
	case EquipmentID::OMEGA_RING:						return ItemPtr(std::make_shared<Eq_OmegaRing>());
	case EquipmentID::SILK_ROBES:						return ItemPtr(std::make_shared<Eq_SilkRobes>());
	case EquipmentID::SILVER_NECKLACE:					return ItemPtr(std::make_shared<Eq_SilverNecklace>());
	case EquipmentID::SILVER_RING:						return ItemPtr(std::make_shared<Eq_SilverRing>());

	// Returns Iron Ring if ID is invalid.
	default:											return ItemPtr(std::make_shared<Eq_SilverRing>());
	}
}

// Returns map data, including tiles and tileset properties.
MapPtr Factory::CreateMap(MapID id){
	switch (id){
	case MapID::BASIC_DUNGEON:							return MapPtr(std::make_shared<Mp_BasicDungeon>());
	case MapID::TEST_MAP:								return MapPtr(std::make_shared<Mp_TestMap>());
	case MapID::TEST_MAP_XL:							return MapPtr(std::make_shared<Mp_TestMapXL>());
	case MapID::TEST_MAP_XS:							return MapPtr(std::make_shared<Mp_TestMapXS>());
	case MapID::TEST_ARENA:								return MapPtr(std::make_shared<Mp_TestArena>());
	case MapID::TEST_ARENA_B:							return MapPtr(std::make_shared<Mp_TestArenaB>());

	// Returns TEST map if ID is invalid.
	default:											return MapPtr(std::make_shared<Mp_TestMap>());
	}
}

PlayerClassPtr Factory::CreatePlayerClass(PlayerClassID id) {
	switch (id) {
	case PlayerClassID::BLADEMASTER:					return PlayerClassPtr(std::make_shared<Pc_Blademaster>());
	case PlayerClassID::STORMSINGER:					return PlayerClassPtr(std::make_shared<Pc_Stormsinger>());

	// Return Adventurer player class if ID is invalid.
	default:											return PlayerClassPtr(std::make_shared<Pc_Adventurer>());
	}
}

// Returns race data.
RacePtr Factory::CreateRace(RaceID id){
	switch (id){
	case RaceID::HUMAN:									return RacePtr(std::make_shared<Human>());
	case RaceID::VULPINE:								return RacePtr(std::make_shared<Vulpine>());
	case RaceID::RUNETOUCHED:							return RacePtr(std::make_shared<Runetouched>());

	// Returns HUMAN race data if ID is invalid.
	default:											return RacePtr(std::make_shared<Human>());
	}
}

// Returns tileset data. Used by maps.
TilesetPtr Factory::CreateTileset(TilesetID id){
	switch (id){
	case TilesetID::TEST_TILESET:						return TilesetPtr(std::make_unique<Ts_TestTileset>());

	// Returns TEST tileset if ID is invalid.
	default:											return TilesetPtr(std::make_unique<Ts_TestTileset>());
	}

}