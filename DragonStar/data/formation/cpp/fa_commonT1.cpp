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
		{ EnemyID::ARCANE_SENTRY, 0,{ 0, -5 } },
		{ EnemyID::ARCANE_SENTRY, 0,{ 5, 0 } },
		{ EnemyID::ARCANE_SENTRY, 0,{ -5, 5 } }
	};
}