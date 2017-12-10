// ==================================
//
// actorFilter.cpp
//
// ==================================

#pragma once

#include "actorFilter.h"
#include "actor.h"
#include "../core/random.h"
#include "../hex/hexMath.h"

#include <limits>

ActorPtr ActorFilter::RandomActor(std::vector<ActorPtr>& actors) {
	int random = Random::RandInt(0, actors.size() - 1);
	return actors[random];
}

std::vector<ActorPtr> ActorFilter::Reachable(std::vector<ActorPtr>& actors, ActorPtr& user, BattleScene& world, int maxDistance, bool ignoreLineOfSight, bool ignoreBodyBlock) {
	std::vector<ActorPtr> results;

	for (auto a : actors) {
		int checkDistance = maxDistance;
		while (checkDistance > 0) {
			std::vector<sf::Vector3i> ring = Hex::HexRing(a->GetHexPosition(), checkDistance);

			for (auto tile : ring) {
				if (tile == user->GetHexPosition() || (world.IsTileOccupied(tile) == false && world.IsTileWalkable(tile, user->CanFly(), user->CanSwim()))) {
					// check if enemy can hit target from tile
					if (ignoreLineOfSight == true || world.InLineOfSight(tile, a->GetHexPosition(), false, ignoreBodyBlock)) {
						results.push_back(a);
						checkDistance = 0;
						break;
					}
				}
			}

			checkDistance--;
		}
	}

	return results;
}

std::vector<ActorPtr> ActorFilter::WithinRange(std::vector<ActorPtr>& actors, ActorPtr& user, BattleScene& world, int range, bool ignoreLineOfSight, bool ignoreBodyBlock) {
	std::vector<ActorPtr> results;

	std::vector<sf::Vector3i> tilesToCheck = world.GetLineOfSight(user->GetHexPosition(), Hex::FilledHexagon(user->GetHexPosition(), range), user->IsPlayer(), ignoreBodyBlock, ignoreLineOfSight);
	for (auto a : actors) {
		if (std::find(tilesToCheck.begin(), tilesToCheck.end(), a->GetHexPosition()) != tilesToCheck.end()) {
			results.push_back(a);
		}
	}

	return results;
}

std::vector<ActorPtr> ActorFilter::Closest(std::vector<ActorPtr>& actors, sf::Vector3i point) {
	std::vector<ActorPtr> results;
	int closestDistance = std::numeric_limits<int>::max(); // I hope no actors are farther than ~2 billion tiles

	for (auto a : actors) {
		int distance = Hex::HexDistance(a->GetHexPosition(), point);
		if (distance < closestDistance) {
			results.clear();
			results.push_back(a);
			closestDistance = distance;
		}
		else if (closestDistance == distance) {
			results.push_back(a);
		}
	}

	return results;
}

std::vector<ActorPtr> ActorFilter::AttributeLessThan(std::vector<ActorPtr>& actors, Attribute attribute, double percent) {
	std::vector<ActorPtr> results;

	for (auto a : actors) {
		if (a->GetAttributePercent(attribute) <= percent) {
			results.push_back(a);
		}
	}

	return results;
}

std::vector<ActorPtr> ActorFilter::AttributeGreaterThan(std::vector<ActorPtr>& actors, Attribute attribute, double percent) {
	std::vector<ActorPtr> results;

	for (auto a : actors) {
		if (a->GetAttributePercent(attribute) <= percent) {
			results.push_back(a);
		}
	}

	return results;
}

std::vector<ActorPtr> ActorFilter::HasAura(std::vector<ActorPtr>& actors, AuraID auraID, int stackCount) {
	std::vector<ActorPtr> results;

	for (auto a : actors) {
		if (a->GetAuraStackCount(auraID) >= stackCount) {
			results.push_back(a);
		}
	}

	return results;
}

std::vector<ActorPtr> ActorFilter::DoesNotHaveAura(std::vector<ActorPtr>& actors, AuraID auraID) {
	std::vector<ActorPtr> results;

	for (auto a : actors) {
		if (a->GetAuraStackCount(auraID) == 0) {
			results.push_back(a);
		}
	}

	return results;
}