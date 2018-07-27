// ==================================
//
// ab_grandHeal.h
//
// Data for Grand Heal ability.
//
// ==================================

#pragma once

#include "../../ability.h"

class Ab_GrandHeal : public Ability {
public:
	Ab_GrandHeal();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);

	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
