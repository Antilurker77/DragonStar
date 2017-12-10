// ==================================
//
// ab_arcaneBlast.h
//
// Data for Arcane Blast ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_ArcaneBlast : public Ability {
public:
	Ab_ArcaneBlast();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
