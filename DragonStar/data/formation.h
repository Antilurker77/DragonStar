// ==================================
//
// formation.h
//
// Base class that holds formation
// data. Formations state which map
// is used, where and what enemies
// are spawned, and where the party's
// starting location is.
//
// ==================================

#pragma once

enum class EnemyID;
enum class MapID;

#include <array>
#include <string>
#include <tuple>
#include <vector>

#include <SFML/System.hpp>

// Enemy ID, Bonus Levels Granted, Starting Location
typedef std::tuple<EnemyID, int, sf::Vector2i> EnemySpawn;

class Formation {
public:
	// Returns the name of the formation.
	std::string GetName();

	// Returns whether the formation is unique or not.
	bool IsUnique();

	// Returns whether the formation is a boss stage.
	bool IsBoss();

	// Returns the map ID.
	MapID GetMapID();

	// Returns the starting locations for the player's party.
	std::vector<sf::Vector2i> GetStartingLocations();

	// Returns enemy list, level bonus, and spawn location.
	std::vector<EnemySpawn> GetEnemySpawns();

	// Adds additional modifactions based on level.
	virtual void LevelFactor(int level);

protected:
	std::string name = "Unknown Formation";
	bool isUnique = false;
	bool isBoss = false;
	MapID mapID{};
	std::vector<sf::Vector2i> startingLocations;
	std::vector<EnemySpawn> enemies;
};