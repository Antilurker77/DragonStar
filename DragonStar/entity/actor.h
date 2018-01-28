// ==================================
//
// actor.h
//
// Base class for any actor that
// appears on the DungeonMap.
//
// ==================================

#pragma once

class Ability;
class BattleScene;

enum class AbilityID;
enum class CreatureType;

#include "entity.h"
#include "../data/ability.h"
#include "../data/aura.h"
#include "../data/factory.h"
#include "../ui/fctManager.h"

#include <memory>

class Actor : public Entity, public std::enable_shared_from_this<Actor> {
public:
	// Sets the world reference.
	void SetWorld(BattleScene* w);

	// Clears the world reference.
	void ClearWorld();
	
	// Updates the FCT Manager.
	void UpdateFCT(float secondsPerUpdate);

	// Renders floating combat text.
	void RenderFCT(sf::RenderTarget& window);

	// Removes all floating combat text.
	void ClearFCT();

	// Returns the actor's name.
	std::string GetName();
	
	// Returns the action string of the current actor. No action is blank,
	// casting returns ability name, others return Recovering.
	std::string GetActionName();

	// Get's the actor's current exhaustion level.
	int GetExhaustion();

	// Returns the actor's cost of their last action.
	int GetLastActionExhaustion();

	// Reduces exhaustion by one. Also ticks auras and removes auras that have expired,
	// as well as trigger regen effects.
	void DecrementExhaustion();

	// Increases the actors exhaustion by the specified amount.
	void Wait(int timeToWait);

	// Fully heals the actor, resets all cooldowns, and removes all auras.
	void FullHeal();

	// Sets the actor's HP to zero.
	void ZeroHP();

	// Returns true if actor is alive.
	bool IsAlive();

	// stats
	int GetLevel();

	// Returns the actor's current HP.
	int GetCurrentHP();

	// Returns the actors's current MP.
	int GetCurrentMP();

	// Returns the actor's current SP.
	int GetCurrentSP();

	// Returns the percent of max for a given attribute.
	double GetAttributePercent(Attribute attribute);

	// Returns the actor's maxinum HP.
	virtual int GetMaxHP() = 0;

	// Returns the actor's maxinum MP.
	virtual int GetMaxMP() = 0;

	// Returns the actor's maxinum SP.
	virtual int GetMaxSP() = 0;

	// Returns the actor's HP regeneration per second.
	virtual double GetHPRegen() = 0;

	// Returns the actor's MP regeneration per second.
	virtual double GetMPRegen() = 0;

	// Returns the actor's SP regeneration per second.
	virtual double GetSPRegen() = 0;

	// Returns the actor's life leech.
	virtual double GetHPLeech(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's life leech.
	virtual double GetMPLeech(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's strength.
	virtual int GetSTR(bool consumeBuffs) = 0;

	// Returns the actor's dexterity.
	virtual int GetDEX(bool consumeBuffs) = 0;

	// Returns the actor's intellegence.
	virtual int GetINT(bool consumeBuffs) = 0;

	// Returns the actor's wisdom.
	virtual int GetWIS(bool consumeBuffs) = 0;

	// Returns the actor's vitality.
	virtual int GetVIT(bool consumeBuffs) = 0;

	// Returns the actor's armor value.
	virtual int GetArmor(bool consumeBuffs) = 0;

	// Returns the ability at the specified index. Returns 0 if out of range.
	AbilityPtr GetAbility(size_t index);

	// Returns a vector containing the filepaths for all abilities' icons.
	std::vector<std::string> GetAbilityIcons();

	// Returns the targeting range of the ability with the specified index.
	std::vector<sf::Vector3i> GetAbilityRange(size_t index);

	// Returns the area of effect of the ability with the specified index.
	std::vector<sf::Vector3i> GetAbilityAreaOfEffect(size_t index, sf::Vector3i cursor);

	// Returns the extra area of the ability with the specified index.
	std::vector<sf::Vector3i> GetAbilityExtraArea(size_t index, sf::Vector3i cursor);

	// Returns whether the ability at the selected index is currently available or not.
	bool IsAbilityAvailable(size_t index);

	// Returns if the ability at the specified index is friendly or not.
	bool IsFriendlyAbility(size_t index);

	// Uses the selected ability.
	void UseAbility(size_t abilityIndex, BattleScene& battleScene, sf::Vector3i cursor);

	// Spends a resource to pay a cost.
	void SpendResource(Attribute attribute, int amount);

	// Makes the actor start casting, targeting a speficic location.
	void StartCast(sf::Vector3i location, int castTime);

	// Makes the actor start casting, targeting a speficic actor.
	void StartCast(ActorPtr& target, int castTime);

	// Returns whether actor is casting or not.
	bool IsCasting();

	// Checks if the caster's spell is ready. Returns false if cast isn't
	// ready or if player isn't casting.
	bool IsCastReady();

	// Returns which slot the actor is casting.
	size_t GetCastIndex();

	// Returns where the actor is targeting.
	sf::Vector3i GetTargetCursor();

	// Interrupts the actor's cast, if the cast can be interrupted.
	void InterruptCast();

	// Returns true if the user has at least one copy of the aura.
	bool HasAura(AuraID auraID);

	// Returns the number of stacks of the specified aura the actor has.
	int GetAuraStackCount(AuraID auraID);

	// Returns all the buffs the given actor has. Does not return hidden auras.
	std::vector<AuraPtr> GetBuffAuras();

	// Returns all the debuffs the given actor has. Does not return hidden auras.
	std::vector<AuraPtr> GetDebuffAuras();

	// Triggers events that are used before combat calculations.
	void OnPreCalc(ActorPtr& targetHit, EventOptions& eventOptions);

	// Triggers events that are used after combat calculations but before damage is dealt.
	void OnPostCalc(ActorPtr& targetHit, EventOptions& eventOptions, EventResult& eventResult, double& damage);

	// Triggers events that are used before healing combat calculations.
	void OnPreCalcHeal(ActorPtr& targetHit, EventOptions& eventOptions);

	// Triggers events that are used after healing combat calculations but before healing is dealt.
	void OnPostCalcHeal(ActorPtr& targetHit, EventOptions& eventOptions, EventResult& eventResult, double& heal);

	// Triggers events that happen when the actor hits something. Also triggers on-hit stat mods.
	void OnHit(ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult, bool isOffHand);

	// Triggers events that happen when the actor heals something. Also triggers on-heal stat mods.
	void OnHeal(ActorPtr& targetHealed, EventOptions eventOptions, EventResult eventResult);

	// Triggers events that happen when the actor takes damage.
	void OnAttacked(ActorPtr& attacker, EventOptions eventOptions, EventResult eventResult);

	// Triggers events that happen when the actor is healed.
	void OnHealed(ActorPtr& healer, EventOptions eventOptions, EventResult eventResult);

	// Removes expired auras from the actor.
	void RemoveExpiredAuras();

	// Removes all auras from the actor.
	void ClearAuras();

	// Checks if the actor is dual wielding.
	virtual bool IsDualWielding() = 0;

	// Returns the actor's weapon attack speed.
	virtual int GetAttackSpeed() = 0;

	// Returns the actor's weapon attack range.
	virtual int GetAttackRange(bool consumeBuffs) = 0;

	// Returns the actor's main hand weapon damage.
	virtual double GetMainHandDamage(bool consumeBuffs) = 0;

	// Returns the categories of the actor's main hand weapon.
	virtual std::vector<Category> GetMainHandCategories() = 0;

	// Returns the elements of the actor's main hand weapon.
	virtual std::vector<Element> GetMainHandElements() = 0;

	// Returns the actor's off-hand weapon damage.
	virtual double GetOffHandDamage(bool consumeBuffs) = 0;

	// Returns the categories of the actor's off-hand weapon.
	virtual std::vector<Category> GetOffHandCategories() = 0;

	// Returns the elements of the actor's off-hand weapon.
	virtual std::vector<Element> GetOffHandElements() = 0;

	// Returns the actor's damage dealt multiplier.
	virtual double GetDamageDealt(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's damage taken multiplier.
	virtual double GetDamageTaken(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's healing done multiplier.
	virtual double GetHealingDealt(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's healing taken multiplier.
	virtual double GetHealingTaken(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's resistance for a given damage type.
	virtual double GetResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the target's armor penetration.
	virtual double GetArmorPen(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the target's resistance penetration.
	virtual double GetResistancePen(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's critical strike chance.
	virtual double GetCritChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's critical strike damage.
	virtual double GetCritDamage(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's critical strike protection.
	virtual double GetCritChanceProtection(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's critical strike damage protection.
	virtual double GetCritDamageProtection(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's haste.
	virtual double GetHaste(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's cast time reduction.
	virtual double GetCastTimeReduction(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns whether the actor's spells are instant. A value of 1 or greater means spells are instant.
	virtual double GetInstantCast(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's range increase.
	virtual double GetRangeIncrease(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's double strike change.
	virtual double GetDoubleStrikeChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's double strike damage multiplier.
	virtual double GetDoubleStrikeDamage(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's counter attack chance.
	virtual double GetCounterChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's on hit damage stat mods.
	virtual std::vector<StatMod> GetOnHitDamage(EventOptions eventOptions, bool consumeBuffs, bool isOffHand) = 0;

	// Return the actor's hit chance.
	virtual double GetHitChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's dodge chance.
	virtual double GetDodgeChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's block chance.
	virtual double GetBlockChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's HP cost reduction.
	virtual double GetHPCostReduction(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's MP cost reduction.
	virtual double GetMPCostReduction(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's SP cost reduction.
	virtual double GetSPCostReduction(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's cooldown reduction.
	virtual double GetCooldownReduction(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's aura power snapshot value.
	virtual double GetAuraSnapshotPower(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's aura crit chance snapshot value.
	virtual double GetAuraSnapshotCritChance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's aura crit damage snapshot value.
	virtual double GetAuraSnapshotCritPower(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's aura resistance penetration snapshot value.
	virtual double GetAuraSnapshotResistPen(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's stun resistance.
	virtual double GetStunResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Returns the actor's disarm resistance.
	virtual double GetDisarmResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's silence resistance.
	virtual double GetSilenceResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's knockback resistance.
	virtual double GetKnockbackResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's slow / snare resistance.
	virtual double GetSnareResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's instant death resistance.
	virtual double GetDeathResistance(EventOptions eventOptions, bool consumeBuffs) = 0;

	// Return the actor's gold find.
	virtual double GetGoldFind(bool consumeBuffs) = 0;

	// Returns the actor's EXP multiplier.
	virtual double GetEXPBoost(bool consumeBuffs) = 0;

	virtual bool GrantEXP(unsigned int xp);
	virtual unsigned int GetEXP();
	virtual unsigned int GetEXPToNextLevel();

	virtual unsigned int GetEXPDrop();
	virtual unsigned int GetGoldDrop();
	virtual unsigned int GetLootPoints();

	// Combat

	// Deals damage to the selected actor. Returns the total ammount of damage dealt.
	int DamageActor(double damage, std::vector<Element> elements, bool isCrit);

	// Heals the selected actor. Returns the total amount healed.
	int HealActor(double healAmount, std::vector<Element> elements, Attribute whatToHeal, bool isCrit);

	// Attempts to add a stack of the aura to the actor. Returns true if stack was added.
	bool AddAuraStack(ActorPtr& user, AuraID auraID);

	// Movement

	// Moves the actor to the designated tile. Use only for
	// valid adjacent tiles. Increases exhaustion.
	void Walk(sf::Vector3i destination, double moveMod);

	// Returns the amount of time the actor takes to move one tile.
	virtual int GetMoveSpeed() = 0;

	virtual bool CanSwim() = 0;

	virtual bool CanFly() = 0;

	virtual CreatureType GetCreatureType() = 0;

	// Returns true if the actor is a player.
	virtual bool IsPlayer() = 0;

	// Shared Pointer

	// Returns an ActorPtr for this object.
	ActorPtr getPtr();

	// Test: Sets the ability slot user.
	virtual void SetAbilitySlotUser() = 0;

	// Sets the world reference for a given ability.
	void SetAbilitySlotWorld(size_t index, BattleScene* w);

protected:
	BattleScene* battleScene = nullptr;
	
	FCTManager fctManager;

	std::string name;

	// stats
	int level;

	int hpCurrent;
	int mpCurrent;
	int spCurrent;

	double hpRegenOverflow = 0.0;
	double mpRegenOverflow = 0.0;
	double spRegenOverflow = 0.0;

	int exhaustion;
	int lastActionExhaustion = 0;

	bool isCasting = false;
	size_t castIndex = 0;
	int castTime = 0;
	sf::Vector3i castLocation;
	ActorPtr castTarget;

	// ability slots
	std::vector<AbilityPtr> abilities;

	// auras
	std::vector<AuraPtr> auras;

	// aura statMods
	std::vector<StatMod> getAuraStatMods();

	// Gets a stat.
	virtual double getStat(double initialValue, StatModType statModType, bool isMultiplicative, bool consumeBuffs) = 0;

	// Gets a stat.
	virtual double getStat(double initialValue, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs) = 0;

	// Return the actor's on hit aura ID. Only used for players.
	virtual AuraID getWeaponOnHitAura(bool isOffHand);

	// Gets stat mod value from auras.
	void getStatModValueFromAuras(double& value, StatModType statModType, bool isMultiplicative, bool consumeBuffs);

	// Gets stat mod value from auras.
	void getStatModValueFromAuras(double& value, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs);

	// Returns the attribute for a weapon type.
	Attribute getWeaponAttribute(EquipType weaponType);

};

typedef std::shared_ptr<Actor> ActorPtr;