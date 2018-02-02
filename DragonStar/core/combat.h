// ==================================
//
// combat.h
//
// Non-member functions that hanndle
// combat calculations and events.
//
// ==================================

#pragma once

class Actor;
class BattleScene;

enum class AbilityID;
enum class AuraID;
enum class Category;
enum class Element;
enum class Attribute;
enum class EquipType;

#include <memory>
#include <vector>

#include <SFML\System.hpp>

typedef std::shared_ptr<Actor> ActorPtr;

// Struct that stores 
struct EventOptions {
	AbilityID AbilityID{};
	AuraID AuraID{};
	std::vector<Category> Categories = {};
	std::vector<Element> Elements = {};
	std::vector<EquipType> AllowedWeaponTypes = {};

	bool CanDodge = false;
	bool CanBlock = false;
	bool CanCrit = true;
	bool CanDoubleStrike = false;
	bool CanCounter = false;

	double BonusHitChance = 0.0;
	double BonusArmorPen = 0.0;
	double BonusCritChance = 0.0;
	double BonusCritDamage = 1.0;
	double BonusDoubleStrikeChance = 0.0;
	double BonusLifeLeech = 0.0;
	double BonusManaLeech = 0.0;
	double BonusStaminaLeech = 0.0;

	std::string EventName = "Unknown Action";

	bool TriggerOnHit = true; // stops on-hit effects from triggering itself
};

// Struct containing the results of a combat event.
struct EventResult {
	int ResultValue = 0;
	int OnAttackValue = 0;
	int LifeLeeched = 0;
	int ManaLeeched = 0;
	int StaminaLeeched = 0;

	bool DidEvent = false;
	bool DidHit = false;
	bool DidBlock = false;
	bool DidCrit = false;
	bool DidDoubleStrike = false;
	bool DidCounter = false;
	bool DidKill = false;
};

namespace Combat {
	
	// Deals damage to the target using a weapon.
	EventResult WeaponAttack(ActorPtr& user, ActorPtr& target, double multiplier, bool isOffHand, EventOptions eventOptions);

	// Deals damage to the target. Scales base damage based on level and with attribute.
	EventResult ScalingAttack(ActorPtr& user, ActorPtr& target, double baseDamage, Attribute attribute, EventOptions eventOptions);

	// Deals damage to the target that does not scale with attributes or levels.
	EventResult FixedAttack(ActorPtr& user, ActorPtr& target, double damage, EventOptions eventOptions);

	// Deals damage to the target that ignores all attributes, levels, and modifiers.
	EventResult AbsoluteAttack(ActorPtr& user, ActorPtr& target, double damage, EventOptions eventOptions);

	// On hit effect that deals damage to the target.
	EventResult OnHit(ActorPtr& user, ActorPtr& target, double damage, EventOptions eventOptions);

	// On hit effect that heals damage to the target.
	EventResult OnHeal(ActorPtr& user, ActorPtr& target, double healAmount, EventOptions eventOptions);

	// Heals the target. Atrribute determines which kind of heal (HP, MP, SP). Scales with the user's wisdom and level.
	EventResult ScalingHeal(ActorPtr& user, ActorPtr& target, double healAmount, Attribute attribute, EventOptions eventOptions);

	// Heals the target. Attribute determines which kind of heal (HP, MP, SP). Does not scale with wisdom or levels.
	EventResult FixedHeal(ActorPtr& user, ActorPtr& target, double healAmount, Attribute attribute, EventOptions eventOptions);

	// Heals the target. Attribute determines which kind of heal (HP, MP, SP). Does not scale with attributes, levels, or modifiers.
	EventResult AbsoluteHeal(ActorPtr& user, ActorPtr& target, double healAmount, Attribute attribute, EventOptions eventOptions);

	// Adds a stack of the specified aura to the target.
	EventResult AddAuraStack(ActorPtr& user, ActorPtr& target, AuraID auraID);

	// Creates a ground effect at the targeted position.
	void CreateGroundEffect(ActorPtr& user, BattleScene* battleScene, AuraID auraID, sf::Vector3i position);

	// Estimates the amount of damage a weapon attack would do.
	int WeaponAttackEstimate(ActorPtr& user, double multiplier, bool isOffHand, EventOptions eventOptions);

	// Estimates the amount of damage a scaling attack would do.
	int ScalingAttackEstimate(ActorPtr& user, double baseDamage, Attribute attribute, EventOptions eventOptions);

	// Estimates the amount of healing a skill would do.
	int ScalingHealEstimate(ActorPtr& user, double healAmount, Attribute attribute, EventOptions eventOptions);
}
