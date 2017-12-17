// ==================================
//
// abEn_bite.h
//
// Data for Bite enemy ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class AbEn_Bite : public Ability {
public:
	AbEn_Bite();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
