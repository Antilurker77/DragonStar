// ==================================
//
// ab_attack.h
//
// Data for Attack ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_Attack : public Ability {
public:
	Ab_Attack();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor,std::vector<sf::Vector3i> targetArea);
};
