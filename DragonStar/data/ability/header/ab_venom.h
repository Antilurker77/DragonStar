// ==================================
//
// ab_venom.h
//
// Data for Venom ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_Venom : public Ability {
public:
	Ab_Venom();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
