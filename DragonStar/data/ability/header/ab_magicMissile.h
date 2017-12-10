// ==================================
//
// ab_magicMissile.h
//
// Data for Magic Missile ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_MagicMissile : public Ability {
public:
	Ab_MagicMissile();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};