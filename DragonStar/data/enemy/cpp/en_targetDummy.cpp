// ==================================
//
// en_targetDummy.cpp
//
// ==================================

#include "../header/en_targetDummy.h"

En_TargetDummy::En_TargetDummy() {
	filepath = "common/target_dummy.png";

	name = "Target Dummy";
	title = "";

	creatureType = CreatureType::CONSTRUCT;

	baseHP = 5000;
	baseMP = 250;
	baseSP = 100;

	baseSTR = 10;
	baseDEX = 10;
	baseINT = 10;
	baseWIS = 10;
	baseVIT = 100;

	baseArmor = 50;

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

	baseGold = 70u;
	baseEXP = 100u;
	lootPoints = 450u;

	abilities = { };
	statMods = {
		StatMod(StatModType::RESISTANCE, 1.00, { Category::ANY }, { Element::MIND })
	};
}

Idea En_TargetDummy::ExecuteAI(ActorPtr& user, BattleScene& world) {
	// Target dummies stand around and do nothing.
	Idea idea;
	idea.first = sf::Vector3i(-1, -1, -1);
	idea.second = 0;
	return idea;
}