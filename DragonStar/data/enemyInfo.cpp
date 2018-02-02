// ==================================
//
// enemyInfo.cpp
//
// ==================================

#include "enemyInfo.h"

//#include "../scene/battleScene.h"
//#include "../entity/actor.h"

std::string EnemyInfo::GetFilepath() {
	return filepath;
}

std::string EnemyInfo::GetName() {
	return name;
}

std::string EnemyInfo::GetTitle() {
	return title;
}

CreatureType EnemyInfo::GetCreatureType() {
	return creatureType;
}

bool EnemyInfo::IsUnique() {
	return isUnique;
}

bool EnemyInfo::IsBoss() {
	return isBoss;
}

int EnemyInfo::GetBaseHP() {
	return baseHP;
}

int EnemyInfo::GetBaseMP() {
	return baseMP;
}

int EnemyInfo::GetBaseSP() {
	return baseSP;
}

int EnemyInfo::GetBaseSTR() {
	return baseSTR;
}

int EnemyInfo::GetBaseDEX() {
	return baseDEX;
}

int EnemyInfo::GetBaseINT() {
	return baseINT;
}

int EnemyInfo::GetBaseWIS() {
	return baseWIS;
}

int EnemyInfo::GetBaseVIT() {
	return baseVIT;
}

int EnemyInfo::GetBaseArmor() {
	return baseArmor;
}

int EnemyInfo::GetBaseMoveSpeed() {
	return baseMoveSpeed;
}

bool EnemyInfo::CanFly() {
	return canFly;
}

bool EnemyInfo::CanSwim() {
	return canSwim;
}

int EnemyInfo::GetAttackSpeed() {
	return attackSpeed;
}

int EnemyInfo::GetAttackRange() {
	return attackRange;
}

EquipType EnemyInfo::GetAttackType() {
	return attackType;
}

std::vector<Element> EnemyInfo::GetAttackElement() {
	return attackElement;
}

int EnemyInfo::GetAttackDamage() {
	return attackDamage;
}

double EnemyInfo::GetAttackMod() {
	return attackMod;
}

EquipType EnemyInfo::GetOffHandAttackType() {
	return offHandAttackType;
}

std::vector<Element> EnemyInfo::GetOffHandAttackElement() {
	return offHandAttackElement;
}

int EnemyInfo::GetOffHandAttackDamage() {
	return offHandAttackDamage;
}

double EnemyInfo::GetOffHandAttackMod() {
	return offHandAttackMod;
}

unsigned int EnemyInfo::GetBaseGold() {
	return baseGold;
}

unsigned int EnemyInfo::GetBaseEXP() {
	return baseEXP;
}

unsigned int EnemyInfo::GetLootPoints() {
	return lootPoints;
}

std::vector<StatMod> EnemyInfo::GetStatMods() {
	return statMods;
}

std::vector<AbilityID> EnemyInfo::GetAbilities() {
	return abilities;
}

void EnemyInfo::OnPreCalc(ActorPtr& user, ActorPtr& targetHit, EventOptions& eventOptions) {

}

void EnemyInfo::OnPostCalc(ActorPtr& user, ActorPtr& targetHit, EventOptions& eventOptions, EventResult& eventResult, double& damage) {

}

void EnemyInfo::OnPreCalcHeal(ActorPtr& user, ActorPtr& targetHealed, EventOptions& eventOptions) {

}

void EnemyInfo::OnPostCalcHeal(ActorPtr& user, ActorPtr& targetHealed, EventOptions& eventOptions, EventResult& eventResult, double& damage) {

}

void EnemyInfo::OnAttack(ActorPtr& user, ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult, bool isOffHand) {

}

void EnemyInfo::OnHit(ActorPtr& user, ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult, bool isOffHand) {

}

void EnemyInfo::OnHeal(ActorPtr& user, ActorPtr& targetHealed, EventOptions eventOptions, EventResult eventResult) {

}

void EnemyInfo::OnAttacked(ActorPtr& user, ActorPtr& attacker, EventOptions eventOptions, EventResult eventResult) {

}

void EnemyInfo::OnHealed(ActorPtr& user, ActorPtr& healer, EventOptions eventOptions, EventResult eventResult) {

}

void EnemyInfo::OnDeath(ActorPtr& user, ActorPtr& attacker, EventOptions eventOptions, EventResult eventResult) {

}

std::pair<sf::Vector3i, size_t> EnemyInfo::ExecuteAI(ActorPtr& user, BattleScene& battleScene) {
	return std::pair<sf::Vector3i, size_t>(sf::Vector3i(-1, -1, -1), 50);
}