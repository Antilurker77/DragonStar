// ==================================
//
// actorFilter.h
//
// Collection of functions that
// filter a list of actors based on
// a specific condition. Mainly used
// for Enemy AI.
//
// ==================================

#pragma once

class Actor;

enum class AuraID;

#include "../scene/battleScene.h"

#include <SFML\System.hpp>

#include <memory>
#include <vector>

typedef std::shared_ptr<Actor> ActorPtr;


namespace ActorFilter {
	// Returns a random actor from the list.
	ActorPtr RandomActor(std::vector<ActorPtr>& actors);

	// Returns a list of reachable actors.
	std::vector<ActorPtr> Reachable(std::vector<ActorPtr>& actors, ActorPtr& user, BattleScene& battleScene, int maxDistance, bool ignoreLineOfSight, bool ignoreBodyBlock);

	// Returns actors within X tiles of the user.
	std::vector<ActorPtr> WithinRange(std::vector<ActorPtr>& actors, ActorPtr& user, BattleScene& battleScene, int range, bool ignoreLineOfSight, bool ignoreBodyBlock);

	// Returns the actors closest to a given point. Ignores line of sight and viable paths.
	std::vector<ActorPtr> Closest(std::vector<ActorPtr>& actors, sf::Vector3i point);

	// Filters actors who's attribute percent is less than or equal to a given value.
	std::vector<ActorPtr> AttributeLessThan(std::vector<ActorPtr>& actors, Attribute attribute, double percent);

	// Filters actors who's attribute percent is greater than or equal to a given value.
	std::vector<ActorPtr> AttributeGreaterThan(std::vector<ActorPtr>& actors, Attribute attribute, double percent);

	// Sorts actors by armor (greatest in front). Can return all actors or the X lowest.
	std::vector<ActorPtr> SortByArmor(std::vector<ActorPtr>& actors, size_t maxNumOfActors = 1);

	// Returns actors that have the specified aura.
	std::vector<ActorPtr> HasAura(std::vector<ActorPtr>& actors, AuraID auraID, int stackCount = 1);

	// Returns actors that do not have the specified aura.
	std::vector<ActorPtr> DoesNotHaveAura(std::vector<ActorPtr>& actors, AuraID auraID);

}
