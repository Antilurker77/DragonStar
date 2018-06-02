// ==================================
//
// aura.h
//
// Class that represents status
// effects on actors.
//
// ==================================

#pragma once

class Actor;
class Battlescene;

enum class AuraID;

#include "statMod.h"
#include "id/eventType.h"
#include "../core/combat.h"
#include "../core/wordWrap.h"

#include <SFML\System.hpp>

#include <memory>
#include <string>
#include <vector>

typedef std::shared_ptr<Actor> ActorPtr;

class Aura {
public:

	// Returns the aura's name.
	std::string GetName();

	// Returns the aura's ID.
	AuraID GetAuraID();

	// Returns the filename for the icon.
	std::string GetIcon();

	// Returns the description for this aura.
	virtual std::string GetDescription();

	// Returns the statMods for this aura.
	std::vector<StatMod> GetStatMods();

	// Returns whether the aura is hidden.
	bool IsHidden();

	// Returns whether aura is a buff.
	bool IsBuff();

	// Returns whether the aura can only be applied once per actor.
	bool IsUniquePerActor();

	// Returns whether the aura is unique and can only be applied once.
	bool IsUnique();

	// Returns whether the aura has a duration.
	bool IsUnlimitedDuration();

	// Returns the remaining duration of the aura.
	int GetRemainingDuration();

	// Returns the number of stacks of the aura.
	int GetStackCount();

	// Returns the actor that applied the aura.
	ActorPtr GetUser();

	// Returns the position of this ground effect.
	sf::Vector3i GetPosition();

	// Sets up the user. Use this if aura is a ground effect.
	void InitializeGroundEffect(ActorPtr& user, sf::Vector3i position);

	// Sets the target for ground effects.
	void SetTarget(ActorPtr& target);

	// Removes the target.
	void ClearTarget();

	// Sets up the user and target. Initializes run-time values.
	void InitializeAura(ActorPtr& user, ActorPtr& target);

	// Sets the special values for this aura.
	void SetValues(std::vector<int> values);

	// Sets a special value for this aura.
	void SetValue(size_t index, int v);

	// Clears special values for this aura.
	void ClearValues();

	// Tags the aura as used.
	void WasUsed(bool used);

	// Adds an additional stack to this aura and refreshes duration. Changes
	// the user to whoever applied the stack.
	void AddStack(ActorPtr& user);

	// Decriments the aura's duration (if applicable) and checks if the next
	// tick is ready.
	void Tick();

	// Returns true if the aura has expired.
	bool IsExpired();

	// Proc events.
	virtual void OnEvent(EventType eventType, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount);

	// Called when the aura is applied.
	virtual void OnApplication();

	// Called when the next tick is ready.
	virtual void OnTick();

	// Called when the aura expires.
	virtual void OnExpiry();

protected:

	// runtime values
	int durationRemaining;
	int nextTick;
	double nextTickPower;
	int maxDuration;
	int stackCount;
	bool wasUsed = false;

	double snapshotPower = 1.0;
	double snapshotCritChance = 0.0;
	double snapshotCritPower = 0.0;
	double snapshotResPen = 0.0;

	ActorPtr user; // which actor applied the aura
	ActorPtr target; // which actor has the aura
	sf::Vector3i position; // position of ground effect

	// values used for special aura effects.
	std::vector<int> values;

	// values set by sub-classes
	std::string name = "Unknown Aura";
	AuraID id{};
	std::string icon = "unknown.png";

	std::vector<Category> categories;
	std::vector<Element> elements;
	std::vector<StatMod> statMods;

	EventOptions auraOptions;

	bool canDodge = false;
	double bonusHit = 0.0;

	bool canBlock = false;

	bool canCrit = false;
	double bonusCrit = 0.0;
	double bonusCritDmg = 1.0; // multiplier on critical strikes

	bool canDoubleStrike = false;
	double bonusDoubleStrike = 0.0;

	bool canCounter = false;

	double bonusLifeLeech = 0.0;
	double bonusManaLeech = 0.0;
	double bonusStaminaLeech = 0.0;

	bool isHidden = false;
	bool isBuff = false;

	int baseDuration;
	int timePerTick = 100;
	int maxStacks = 1;
	bool hasTicks = false;
	bool fixedDuration = false; // if true, ignore VIT in calculations
	bool unlimitedDuration = false;
	bool consumedOnUse = false; // if true, aura will expire when called in combat calculations
	bool multiplyStatModsByStack = false;

	bool isStun = false;
	bool isDisarm = false;
	bool isSilence = false;
	bool isSlow = false;

	bool uniquePerActor = false; // determines if one actor can apply multiple copies of aura
	bool uniqueAura = false; // if true only one copy can be applied regardless of source

	bool removeAllStacksOnExpiration = false; // Determines whether all stacks or 1 stack are removed when aura expires

	// Calculates the duration based on VIT.
	void calcDuraiton();

	// Sets up the event options object.
	void setAuraOptions();

	// Called when the values for the aura is changed. Used for internal calculations.
	virtual void onValueChange();
};
