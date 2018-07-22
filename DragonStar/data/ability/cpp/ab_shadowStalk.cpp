// ==================================
//
// ab_shadowStalk.cpp
//
// ==================================

#include "../header/ab_shadowStalk.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../../core/random.h"
#include "../../../hex/hexMath.h"
#include "../../../scene/battleScene.h"

Ab_ShadowStalk::Ab_ShadowStalk() {
	setAttackDefault();

	name = "Shadow Stalk";
	abilityID = AbilityID::ShadowStalk;
	icon = "warp_slice.png";

	abilityTypes = {
		AbilityType::DaggerSkill
	};
	tier = 2;

	categories = {
		Category::Attack,
		Category::Skill,
		Category::Damaging,
		Category::SingleTarget,
		Category::Direct
	};

	elements = {
		Element::Dark
	};

	mpCost = 40;
	spCost = 60;
	cooldown = 1500;
	range = 5;
	aiSearchRange = range;
	useAttackRange = false;

	usage = UseType::Instant;

	requireTargetsInArea = true;
	ignoreBodyBlock = true;
}

std::vector<sf::Vector3i> Ab_ShadowStalk::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::vector<sf::Vector3i> Ab_ShadowStalk::GetExtraArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles;
	for (auto t : Hex::GetHexNeighbors(selectedTile)) {
		if (battleScene->IsTileWalkable(t, user->CanFly(), user->CanSwim()) && !battleScene->IsTileOccupied(t)) {
			tiles.push_back(t);
		}
	}
	return tiles;
}

std::string Ab_ShadowStalk::GetDescription() {
	std::string damage = "180%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.8, false, abilityOptions));
	}

	std::string desc = "Teleport to a random tile adjacent to the target, then deal #damage " + damage + " #default dark damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	return desc;
}

void Ab_ShadowStalk::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	std::vector<sf::Vector3i> tiles;
	for (auto t : Hex::GetHexNeighbors(cursor)) {
		if (battleScene->IsTileWalkable(t, user->CanFly(), user->CanSwim()) && !battleScene->IsTileOccupied(t)) {
			tiles.push_back(t);
		}
	}
	size_t index = Random::RandSizeT(0, tiles.size() - 1);
	user->MoveToHex(tiles[index]);

	Combat::WeaponAttack(user, targets[0], 1.8, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}

bool Ab_ShadowStalk::customExecuteCondition(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	std::vector<sf::Vector3i> tiles;
	for (auto t : Hex::GetHexNeighbors(cursor)) {
		if (battleScene->IsTileWalkable(t, user->CanFly(), user->CanSwim()) && !battleScene->IsTileOccupied(t)) {
			tiles.push_back(t);
		}
	}
	return tiles.size() > 0;
}