// ==================================
//
// ab_rendingSlash.h
//
// Data for Rending Slash ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_RendingSlash : public Ability {
public:
	Ab_RendingSlash();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
