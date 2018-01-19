// ==================================
//
// fa_uniqueT1.cpp
//
// ==================================

#include "../header/fa_uniqueT1.h"

#include "../../id/enemyID.h"
#include "../../id/mapID.h"

Fa_Fenrok::Fa_Fenrok() {
	name = "Fenrok";
	isUnique = true;
	isBoss = false;
	mapID = MapID::FIELD_FIELD;
	startingLocations = {
		sf::Vector2i(1, 2),
		sf::Vector2i(0, 3),
		sf::Vector2i(2, 2),
		sf::Vector2i(1, 3),
		sf::Vector2i(0, 4),
		sf::Vector2i(2, 3)
	};
	enemies = {
		{ EnemyID::FENROK, 0,{ 1, -2 } }
	};
}