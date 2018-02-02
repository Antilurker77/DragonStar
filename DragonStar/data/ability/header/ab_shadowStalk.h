// ==================================
//
// ab_shadowStalk.h
//
// Data for Shadow Stalk ability.
//
// ==================================

#include "../../ability.h"

#pragma once

class Ab_ShadowStalk : public Ability {
public:
	Ab_ShadowStalk();

	std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile);
	std::vector<sf::Vector3i> GetExtraArea(sf::Vector3i selectedTile);
	std::string GetDescription();
protected:
	void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
	bool customExecuteCondition(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);
};
