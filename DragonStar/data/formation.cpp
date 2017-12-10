// ==================================
//
// formation.cpp
//
// ==================================

#include "formation.h"

std::string Formation::GetName() {
	return name;
}

bool Formation::IsUnique() {
	return isUnique;
}

bool Formation::IsBoss() {
	return isBoss;
}

MapID Formation::GetMapID() {
	return mapID;
}

std::vector<sf::Vector2i> Formation::GetStartingLocations() {
	return startingLocations;
}

std::vector<EnemySpawn> Formation::GetEnemySpawns() {
	return enemies;
}

void Formation::LevelFactor(int level) {

}