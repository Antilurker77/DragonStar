// ==================================
//
// factory.h
//
// Class that returns data for all
// in-game objects.
//
// ==================================

#pragma once

class Ability;
class Aura;
class EnemyInfo;
class Formation;
class Item;
class Map;
class PlayerClass;
class Race;
class Tileset;

#include "id.h"

#include <memory>

typedef std::shared_ptr<Ability> AbilityPtr;
typedef std::shared_ptr<Aura> AuraPtr;
typedef std::shared_ptr<EnemyInfo> EnemyInfoPtr;
typedef std::shared_ptr<Formation> FormationPtr;
typedef std::shared_ptr<Item> ItemPtr;
typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<PlayerClass> PlayerClassPtr;
typedef std::shared_ptr<Race> RacePtr;
typedef std::unique_ptr<Tileset> TilesetPtr;

class Factory {
public:
	Factory();

	// Returns an Ability pointer based on ID.
	AbilityPtr CreateAbility(AbilityID id);

	// Returns an Ability Scroll based on ID.
	ItemPtr CreateAbilityScroll(AbilityID id);

	// Returns Aura data based on ID.
	AuraPtr CreateAura(AuraID id);

	// Returns Enemy Info data based on ID.
	EnemyInfoPtr CreateEnemyInfo(EnemyID id);

	// Returns formation data based on ID.
	FormationPtr CreateFormation(FormationID id);

	// Returns Equipment based on ID.
	ItemPtr CreateEquipment(EquipmentID id);

	// Returns Map data based on ID.
	MapPtr CreateMap(MapID id);

	// Returns Player Class data based on the ID.
	PlayerClassPtr CreatePlayerClass(PlayerClassID id);

	// Returns Race data based on ID.
	RacePtr CreateRace(RaceID id);

	// Returns Tileset data based on ID.
	TilesetPtr CreateTileset(TilesetID id);
	

private:

};