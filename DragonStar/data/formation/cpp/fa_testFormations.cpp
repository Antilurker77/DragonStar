// ==================================
//
// fa_testFormations.cpp
//
// ==================================

#include "../header/fa_testFormations.h"

Fa_TestFormationA::Fa_TestFormationA() {
	name = "Test Formation A";
	isUnique = false;
	isBoss = false;
	mapID = MapID::TEST_ARENA;
	startingLocations = {
		sf::Vector2i(0, 4),
		sf::Vector2i(-1, 5),
		sf::Vector2i(1, 4),
		sf::Vector2i(0, 5),
		sf::Vector2i(-1, 6),
		sf::Vector2i(1, 5)
	};
	enemies = {
		{ EnemyID::TARGET_DUMMY, 0, {0, 0} }
	};
}

Fa_TestFormationB::Fa_TestFormationB() {
	name = "Test Formation B";
	isUnique = false;
	isBoss = false;
	mapID = MapID::TEST_ARENA;
	startingLocations = {
		sf::Vector2i(0, 4),
		sf::Vector2i(-1, 5),
		sf::Vector2i(1, 4),
		sf::Vector2i(0, 5),
		sf::Vector2i(-1, 6),
		sf::Vector2i(1, 5)
	};
	enemies = {
		{ EnemyID::TEST_MAGE, 0, { 0, 0 } },
		{ EnemyID::TEST_ASSASSIN, 0, { -1, 0 } },
		{ EnemyID::TEST_ASSASSIN, 0, { 1, -1 } }
	};
}

Fa_TestUnique::Fa_TestUnique() {
	name = "Test Unique";
	isUnique = true;
	isBoss = false;
	mapID = MapID::TEST_ARENA_B;
	startingLocations = {
		sf::Vector2i(0, 2),
		sf::Vector2i(-1, 3),
		sf::Vector2i(1, 2),
		sf::Vector2i(0, 3),
		sf::Vector2i(-1, 4),
		sf::Vector2i(1, 3)
	};
	enemies = {
		{ EnemyID::TEST_UNIQUE, 0,{ 0, 0 } }
	};
}

Fa_TestBoss::Fa_TestBoss() {
	name = "Test Boss";
	isUnique = false;
	isBoss = true;
	mapID = MapID::TEST_ARENA;
	startingLocations = {
		sf::Vector2i(0, 4),
		sf::Vector2i(-1, 5),
		sf::Vector2i(1, 4),
		sf::Vector2i(0, 5),
		sf::Vector2i(-1, 6),
		sf::Vector2i(1, 5)
	};
	enemies = {
		{ EnemyID::TEST_ENEMY, 0, { 0, 0 } }
	};
}