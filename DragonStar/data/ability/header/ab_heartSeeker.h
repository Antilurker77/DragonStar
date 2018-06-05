// ==================================
//
// ab_heartSeeker.h
//
// Data for Heart Seeker ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_HeartSeeker : public Ability {
public:
	Ab_HeartSeeker();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};