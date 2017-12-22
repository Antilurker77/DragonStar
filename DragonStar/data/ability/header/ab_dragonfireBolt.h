// ==================================
//
// ab_dragonfireBolt.h
//
// Data for Dragonfire Bolt ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_DragonfireBolt : public Ability {
public:
	Ab_DragonfireBolt();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
