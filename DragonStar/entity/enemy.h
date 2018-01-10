// ==================================
//
// enemy.h
//
// Class for enemy (non-player)
// characters on the map.
//
// ==================================

#pragma once

class BattleScene;

enum class EnemyID;

#include "actor.h"
#include "../command/command.h"
#include "../data/enemyInfo.h"
#include "../data/factory.h"

class Enemy : public Actor {
public:
	Enemy(EnemyID id, int level, sf::Vector3i spawnPosition);

	CommandPtr CalcAICommand(BattleScene& battleScene);

	int GetMaxHP();
	int GetMaxMP();
	int GetMaxSP();

	double GetHPRegen();
	double GetMPRegen();
	double GetSPRegen();

	double GetHPLeech(EventOptions eventOptions, bool consumeBuffs);
	double GetMPLeech(EventOptions eventOptions, bool consumeBuffs);

	int GetSTR(bool consumeBuffs);
	int GetDEX(bool consumeBuffs);
	int GetINT(bool consumeBuffs);
	int GetWIS(bool consumeBuffs);
	int GetVIT(bool consumeBuffs);

	int GetArmor(bool consumeBuffs);

	bool IsDualWielding();
	int GetAttackSpeed();
	int GetAttackRange(bool consumeBuffs);
	double GetMainHandDamage(bool consumeBuffs);
	std::vector<Category> GetMainHandCategories();
	std::vector<Element> GetMainHandElements();
	double GetOffHandDamage(bool consumeBuffs);
	std::vector<Category> GetOffHandCategories();
	std::vector<Element> GetOffHandElements();

	double GetDamageDealt(EventOptions eventOptions, bool consumeBuffs);
	double GetDamageTaken(EventOptions eventOptions, bool consumeBuffs);
	double GetHealingDealt(EventOptions eventOptions, bool consumeBuffs);
	double GetHealingTaken(EventOptions eventOptions, bool consumeBuffs);
	double GetResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetArmorPen(EventOptions eventOptions, bool consumeBuffs);
	double GetResistancePen(EventOptions eventOptions, bool consumeBuffs);
	double GetCritChance(EventOptions eventOptions, bool consumeBuffs);
	double GetCritDamage(EventOptions eventOptions, bool consumeBuffs);
	double GetCritChanceProtection(EventOptions eventOptions, bool consumeBuffs);
	double GetCritDamageProtection(EventOptions eventOptions, bool consumeBuffs);
	double GetHaste(EventOptions eventOptions, bool consumeBuffs);
	double GetCastTimeReduction(EventOptions eventOptions, bool consumeBuffs);
	double GetInstantCast(EventOptions eventOptions, bool consumeBuffs);
	double GetRangeIncrease(EventOptions eventOptions, bool consumeBuffs);
	double GetDoubleStrikeChance(EventOptions eventOptions, bool consumeBuffs);
	double GetDoubleStrikeDamage(EventOptions eventOptions, bool consumeBuffs);
	double GetCounterChance(EventOptions eventOptions, bool consumeBuffs);
	std::vector<StatMod> GetOnHitDamage(EventOptions eventOptions, bool consumeBuffs, bool isOffHand);
	double GetHitChance(EventOptions eventOptions, bool consumeBuffs);
	double GetDodgeChance(EventOptions eventOptions, bool consumeBuffs);
	double GetBlockChance(EventOptions eventOptions, bool consumeBuffs);
	double GetHPCostReduction(EventOptions eventOptions, bool consumeBuffs);
	double GetMPCostReduction(EventOptions eventOptions, bool consumeBuffs);
	double GetSPCostReduction(EventOptions eventOptions, bool consumeBuffs);
	double GetCooldownReduction(EventOptions eventOptions, bool consumeBuffs);
	double GetAuraSnapshotPower(EventOptions eventOptions, bool consumeBuffs);
	double GetAuraSnapshotCritChance(EventOptions eventOptions, bool consumeBuffs);
	double GetAuraSnapshotCritPower(EventOptions eventOptions, bool consumeBuffs);
	double GetAuraSnapshotResistPen(EventOptions eventOptions, bool consumeBuffs);
	double GetStunResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetDisarmResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetSilenceResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetKnockbackResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetSnareResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetDeathResistance(EventOptions eventOptions, bool consumeBuffs);
	double GetGoldFind(bool consumeBuffs);
	double GetEXPBoost(bool consumeBuffs);

	unsigned int GetEXPDrop();
	unsigned int GetGoldDrop();
	unsigned int GetLootPoints();

	int GetMoveSpeed();
	bool CanFly();
	bool CanSwim();

	CreatureType GetCreatureType();

	bool IsPlayer();

	void SetAbilitySlotUser();
private:

	EnemyInfoPtr enemyInfo;

	// Gets a stat.
	double getStat(double initialValue, StatModType statModType, bool isMultiplicative, bool consumeBuffs);

	// Gets a stat.
	double getStat(double initialValue, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs);
};