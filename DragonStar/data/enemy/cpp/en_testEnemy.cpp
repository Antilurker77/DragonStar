// ==================================
//
// en_testEnemy.cpp
//
// ==================================

#include "../header/en_testEnemy.h"

En_TestEnemy::En_TestEnemy() {
	filepath = "common/test_enemy.png";

	name = "Test Enemy";
	title = "";

	creatureType = CreatureType::HUMANOID;

	baseHP = 250;
	baseMP = 30;
	baseSP = 100;

	baseSTR = 24;
	baseDEX = 24;
	baseINT = 24;
	baseWIS = 24;
	baseVIT = 100;

	baseArmor = 30;

	canFly = false;
	canSwim = false;

	attackSpeed = 210;
	attackRange = 1;

	attackType = EquipType::UNARMED_STR;
	attackElement = { Element::PHYSICAL };
	attackDamage = 0;
	attackMod = 2.0;

	offHandAttackType = EquipType::NONE;
	offHandAttackElement = { Element::NONE };
	offHandAttackDamage = 0;
	offHandAttackMod = 0;

	baseGold = 15u;
	baseEXP = 30u;
	lootPoints = 100u;

	abilities = { AbilityID::RACIAL_DRAGON_BREATH };

}

Idea En_TestEnemy::ExecuteAI(ActorPtr& user, BattleScene& world) {
	Idea idea;
	std::vector<ActorPtr> players = world.GetPlayers(true);
	if (players.size() > 0) {
		ActorPtr target = ActorFilter::RandomActor(players);
		idea.first = target->GetHexPosition();

		if (user->IsAbilityAvailable(1)) {
			idea.second = 1;
		}
		else {
			idea.second = 0;
		}
	}
	else {
		idea.first = sf::Vector3i(-1, -1, -1);
	}
	return idea;
}