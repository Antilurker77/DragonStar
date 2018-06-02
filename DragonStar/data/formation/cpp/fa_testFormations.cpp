// ==================================
//
// fa_testFormations.cpp
//
// ==================================

#include "../header/fa_testFormations.h"

#include "../../id/enemyID.h"
#include "../../id/mapID.h"

Fa_TestFormationA::Fa_TestFormationA() {
	name = "Test Formation A";
	isUnique = false;
	isBoss = false;
	mapID = MapID::TestArena;
	startingLocations = {
		sf::Vector2i(0, 4),
		sf::Vector2i(-1, 5),
		sf::Vector2i(1, 4),
		sf::Vector2i(0, 5),
		sf::Vector2i(-1, 6),
		sf::Vector2i(1, 5)
	};
	enemies = {
		{ EnemyID::TargetDummy, 0, {0, 0} }
	};
}

Fa_TestFormationB::Fa_TestFormationB() {
	name = "Test Formation B";
	isUnique = false;
	isBoss = false;
	mapID = MapID::TestArena;
	startingLocations = {
		sf::Vector2i(0, 4),
		sf::Vector2i(-1, 5),
		sf::Vector2i(1, 4),
		sf::Vector2i(0, 5),
		sf::Vector2i(-1, 6),
		sf::Vector2i(1, 5)
	};
	enemies = {
		{ EnemyID::TestMage, 0, { 0, 0 } },
		{ EnemyID::TestAssassin, 0, { -1, 0 } },
		{ EnemyID::TestAssassin, 0, { 1, -1 } }
	};
}

Fa_TestUnique::Fa_TestUnique() {
	name = "Test Unique";
	isUnique = true;
	isBoss = false;
	mapID = MapID::TestArenaB;
	startingLocations = {
		sf::Vector2i(0, 2),
		sf::Vector2i(-1, 3),
		sf::Vector2i(1, 2),
		sf::Vector2i(0, 3),
		sf::Vector2i(-1, 4),
		sf::Vector2i(1, 3)
	};
	enemies = {
		{ EnemyID::TestUnique, 0,{ 0, 0 } }
	};
}

Fa_TestBoss::Fa_TestBoss() {
	name = "Test Boss";
	isUnique = false;
	isBoss = true;
	mapID = MapID::TestArena;
	startingLocations = {
		sf::Vector2i(0, 4),
		sf::Vector2i(-1, 5),
		sf::Vector2i(1, 4),
		sf::Vector2i(0, 5),
		sf::Vector2i(-1, 6),
		sf::Vector2i(1, 5)
	};
	enemies = {
		{ EnemyID::TestEnemy, 0, { 0, 0 } }
	};
}