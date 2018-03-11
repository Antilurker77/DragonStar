// ==================================
//
// ab_lightBolt.h
//
// Data for Light Bolt ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_LightBolt : public Ability {
public:
	Ab_LightBolt();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};