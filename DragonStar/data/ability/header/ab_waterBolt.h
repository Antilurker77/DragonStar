// ==================================
//
// ab_waterBolt.h
//
// Data for Water Bolt ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_WaterBolt : public Ability {
public:
	Ab_WaterBolt();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};