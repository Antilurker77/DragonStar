// ==================================
//
// ab_warpSlice.h
//
// Data for Warp Slice ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_WarpSlice : public Ability {
public:
	Ab_WarpSlice();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::vector<sf::Vector3i> GetExtraArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
	bool customExecuteCondition(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
