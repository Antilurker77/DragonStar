// ==================================
//
// enemyInfo.h
//
// Base class that stores data for
// enemies.
//
// ==================================

#pragma once

class Actor;
class BattleScene;

enum class AbilityID;
enum class CreatureType;
enum class EquipType;
enum class Element;

#include <memory>

#include "../data/statMod.h"
#include "../entity/actorFilter.h"

#include <SFML/System.hpp>

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::pair<sf::Vector3i, size_t> Idea;
typedef std::vector<ActorPtr> ActorVector;

class EnemyInfo {
public:
	// Returns the filepath of the enemy texture.
	std::string GetFilepath();

	std::string GetName();
	std::string GetTitle();

	CreatureType GetCreatureType();
	bool IsUnique();
	bool IsBoss();

	int GetBaseHP();
	int GetBaseMP();
	int GetBaseSP();

	int GetBaseSTR();
	int GetBaseDEX();
	int GetBaseINT();
	int GetBaseWIS();
	int GetBaseVIT();

	int GetBaseArmor();

	int GetBaseMoveSpeed();
	bool CanFly();
	bool CanSwim();

	int GetAttackSpeed();
	int GetAttackRange();
	
	EquipType GetAttackType();
	std::vector<Element> GetAttackElement();
	int GetAttackDamage();
	double GetAttackMod();

	EquipType GetOffHandAttackType();
	std::vector<Element> GetOffHandAttackElement();
	int GetOffHandAttackDamage();
	double GetOffHandAttackMod();

	unsigned int GetBaseGold();
	unsigned int GetBaseEXP();
	unsigned int GetLootPoints();

	std::vector<StatMod> GetStatMods();
	std::vector<AbilityID> GetAbilities();

	virtual void OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount);

	virtual Idea ExecuteAI(ActorPtr& user, BattleScene& battleScene);

protected:
	std::string filepath = "gfx/actor/enemy/common/test_enemy.png";
	
	std::string name = "Unknown Enemy";
	std::string title = "";

	CreatureType creatureType{};
	bool isUnique = false;
	bool isBoss = false;

	int baseHP = 101;
	int baseMP = 10;
	int baseSP = 100;

	int baseSTR = 10;
	int baseDEX = 10;
	int baseINT = 10;
	int baseWIS = 10;
	int baseVIT = 50;

	int baseArmor = 20;

	int baseMoveSpeed = 35;
	bool canFly = false;
	bool canSwim = false;

	int attackSpeed = 195;
	int attackRange = 1;
	
	EquipType attackType{};
	std::vector<Element> attackElement = {};
	int attackDamage = 0;
	double attackMod = 2.0;

	EquipType offHandAttackType{};
	std::vector<Element> offHandAttackElement = {};
	int offHandAttackDamage = 0;
	double offHandAttackMod = 1.0;

	unsigned int baseGold = 0;
	unsigned int baseEXP = 0;
	unsigned int lootPoints = 0;

	std::vector<StatMod> statMods = {};

	std::vector<AbilityID> abilities = {};

};