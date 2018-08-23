// ==================================
//
// ab_spellpower.h
//
// Data for Spellpower ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_Spellpower : public Ability {
public:
	Ab_Spellpower();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
