// ==================================
//
// ab_warpSlice.cpp
//
// ==================================

#include "../header/ab_warpSlice.h"

#include "../../id/abilityID.h"
#include "../../id/abilityType.h"
#include "../../id/attribute.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipType.h"
#include "../../../core/random.h"
#include "../../../hex/hexMath.h"
#include "../../../scene/battleScene.h"

Ab_WarpSlice::Ab_WarpSlice() {
	setAttackDefault();

	name = "Warp Slice";
	abilityID = AbilityID::WarpSlice;
	icon = "warp_slice.png";

	abilityTypes = {
		AbilityType::SwordSkill
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
		Element::Arcane
	};

	usableWeapons = {
		EquipType::Sword1H,
		EquipType::Sword2H
	};

	mpCost = 40;
	spCost = 20;
	cooldown = 2000;
	range = 3;
	useAttackRange = false;

	usage = UseType::Instant;

	requireTargetsInArea = true;
	ignoreBodyBlock = true;
}

std::vector<sf::Vector3i> Ab_WarpSlice::GetTargetArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles = { selectedTile };
	return tiles;
}

std::vector<sf::Vector3i> Ab_WarpSlice::GetExtraArea(sf::Vector3i selectedTile) {
	std::vector<sf::Vector3i> tiles;
	for (auto t : Hex::GetHexNeighbors(selectedTile)) {
		if (battleScene->IsTileWalkable(t, user->CanFly(), user->CanSwim()) && !battleScene->IsTileOccupied(t)) {
			tiles.push_back(t);
		}
	}
	return tiles;
}

std::string Ab_WarpSlice::GetDescription() {
	std::string damage = "150%";

	if (user != nullptr) {
		damage = std::to_string(Combat::WeaponAttackEstimate(user, 1.5, false, abilityOptions));
	}

	std::string desc = "Teleport to a random tile adjacent to the target, then deal #damage " + damage + " #default arcane damage.";
	desc = WordWrap::WrapString(desc, charPerLine);

	desc += "\n\nRequires sword.";

	return desc;
}

void Ab_WarpSlice::execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	std::vector<sf::Vector3i> tiles;
	for (auto t : Hex::GetHexNeighbors(cursor)) {
		if (battleScene->IsTileWalkable(t, user->CanFly(), user->CanSwim()) && !battleScene->IsTileOccupied(t)) {
			tiles.push_back(t);
		}
	}
	size_t index = Random::RandSizeT(0, tiles.size() - 1);
	user->MoveToHex(tiles[index]);

	Combat::WeaponAttack(user, targets[0], 1.5, false, abilityOptions);
	Combat::WeaponAttack(user, targets[0], offHandBasicMultiplier, true, abilityOptions);
}

bool Ab_WarpSlice::customExecuteCondition(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) {
	std::vector<sf::Vector3i> tiles;
	for (auto t : Hex::GetHexNeighbors(cursor)) {
		if (battleScene->IsTileWalkable(t, user->CanFly(), user->CanSwim()) && !battleScene->IsTileOccupied(t)) {
			tiles.push_back(t);
		}
	}
	return tiles.size() > 0;
}