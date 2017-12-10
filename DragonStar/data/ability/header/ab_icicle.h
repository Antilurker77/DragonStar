// ==================================
//
// ab_icicle.h
//
// Data for Icicle ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Icicle : public Ability {
public:
	Ab_Icicle();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};