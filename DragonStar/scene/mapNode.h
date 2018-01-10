// ==================================
//
// mapNode.h
//
// Struct holding data for a
// map node on the map select
// screen. Used for both domains and
// maps in a domain.
//
// ==================================

#pragma once

enum class FormationID;

#include <random>
#include <vector>

#include <SFML/System.hpp>

struct MapNode {
	FormationID FormationID; // nyi
	int Level = 0;
	int Tier = 0;
	uint64_t Seed = 0;
	sf::Vector2i Location = { 0, 0 };
	size_t NodesInStep = 0;
	bool IsUnique = false;
	bool IsBoss = false;
	std::vector<size_t> connectedNodes;
	bool IsCleared = false;
};