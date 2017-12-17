// ==================================
//
// fa_commonT1.cpp
//
// ==================================

#include "../header/fa_commonT1.h"

Fa_SentryAmbush::Fa_SentryAmbush() {
	name = "Sentry Ambush";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FIELD_SMALL_ISLAND;
	startingLocations = {
		sf::Vector2i(0, -1),
		sf::Vector2i(-1, 0),
		sf::Vector2i(1, -1),
		sf::Vector2i(0, 0),
		sf::Vector2i(-1, 1),
		sf::Vector2i(1, 0)
	};
	enemies = {
		{ EnemyID::ARCANE_SENTRY, 0,{ 0, -4 } },
		{ EnemyID::ARCANE_SENTRY, 0,{ 4, 0 } },
		{ EnemyID::ARCANE_SENTRY, 0,{ -4, 4 } }
	};
}

Fa_SewerRats::Fa_SewerRats() {
	name = "Sewer Rats";
	isUnique = false;
	isBoss = false;
	mapID = MapID::FIELD_SEWER;
	startingLocations = {
		sf::Vector2i(2, 3),
		sf::Vector2i(3, 2),
		sf::Vector2i(2, 4),
		sf::Vector2i(4, 2),
		sf::Vector2i(3, 4),
		sf::Vector2i(4, 3)
	};
	enemies = {
		{ EnemyID::GIANT_RAT, 0,{ -4, 4 } },
		{ EnemyID::GIANT_RAT, 0,{ -5, 5 } },
		{ EnemyID::GIANT_RAT, 0,{ 5, -5 } },
		{ EnemyID::GIANT_RAT, 0,{ 4, -5 } },
		{ EnemyID::GIANT_RAT, 0,{ -3, -3 } },
		{ EnemyID::GIANT_RAT, 0,{ -4, -3 } },
		{ EnemyID::GIANT_RAT, 0,{ -3, -4 } }
	};
}