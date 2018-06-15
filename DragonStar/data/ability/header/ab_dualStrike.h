// ==================================
//
// ab_dualStrike.h
//
// Data for Dual Strike ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_DualStrike : public Ability {
public:
	Ab_DualStrike();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
	bool customUseCondition();
};
