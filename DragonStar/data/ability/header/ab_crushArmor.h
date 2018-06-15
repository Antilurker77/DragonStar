// ==================================
//
// ab_crushArmor.h
//
// Data for Crush Armor ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_CrushArmor : public Ability {
public:
	Ab_CrushArmor();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
