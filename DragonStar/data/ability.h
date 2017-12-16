// ==================================
//
// ability.h
//
// Class that stores ability data and
// executes ability actions.
//
// ==================================

#pragma once

class Actor;
class BattleScene;

#include "id.h"
#include "../core/combat.h"

#include <SFML\System.hpp>
#include <memory>

typedef std::shared_ptr<Actor> ActorPtr;

enum class UseType {
	INSTANT,
	CAST
};

class Ability {
public:

	// Sets the user of the ability.
	void SetUser(ActorPtr& user);

	// Sets the world reference.
	void SetWorld(BattleScene& battleScene);

	// Determines whether the ability is usable. Factors in
	// resource costs and status (stunned, silenced ect.).
	bool IsUsable();

	// Gets the targeting range of the ability.
	std::vector<sf::Vector3i> GetTargetRange();

	// Gets the targeting area of the ability.
	virtual std::vector<sf::Vector3i> GetTargetArea(sf::Vector3i selectedTile) = 0;

	// Executes the ability.
	void UseAbility(sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea);

	// Returns the ability's ID.
	AbilityID GetAbilityID();

	// Returns the ability's name.
	std::string GetName();

	// Returns the filepath for the ability's icon.
	std::string GetIcon();

	// Returns the ability types for this ability.
	std::vector<AbilityType> GetAbilityTypes();

	// Returns the tier of this ability.
	unsigned int GetTier();

	// Returns the range of this ability.
	int GetRange();

	// Returns whether the ability is a spell or not.
	bool IsSpell();

	// Returns the maximum search radius for the AI for this ability.
	int GetAISearchRange();

	// Returns targetOutsideCursor. Used for AI.
	bool CanTargetOutsideCursor();

	// Returns whether this ability ignores body block or not.
	bool IgnoreBodyBlock();

	// Returns whether this abilitiy ignores line of sight.
	bool IgnoreLineOfSight();

	// Returns whether ability targets friendly units.
	bool IsFriendly();

	// Returns whether the abiility is casted or not.
	bool IsCasted();

	// Returns the cast time of this ability. If the ability has no
	// user and is an attack, it returns attackSpeedMultiplier * -100.
	int GetCastTime(bool consumeBuffs = false);

	// Returns the MP cost for this ability.
	int GetMPCost();

	// Returns the SP cost for this ability.
	int GetSPCost();

	// Returns the cooldown for this ability.
	int GetCooldown();

	// Returns the current cooldown for this ability.
	int GetCurrentCooldown();

	// Ticks down the cooldown of this ability.
	void DecrementCooldown();

	// Resets the cooldown of this ability.
	void ResetCooldown();

	// Returns the tooltip description of this ability.
	virtual std::string GetDescription();

protected:
	AbilityID abilityID = AbilityID::UNDEFINED;
	std::vector<AbilityType> abilityTypes;
	unsigned int tier = 0;

	std::string name = "Unnamed Ability";
	std::string icon = "default.png";

	std::vector<Category> categories = {};
	std::vector<Element> elements = {};

	bool isAttack = false;
	int range = 0;
	int aiSearchRange = 0; // determines how many tiles around a target to check, used for enemyAI
	bool targetOutsideCursor = false; // tells AI if it's possible that the cursor and area of effect may not line up
	bool useAttackRange = false; // if true weapon determines attack range
	bool ignoreBodyBlock = false; // determines whether enemies can block spell
	bool ignoreLineOfSight = false;
	bool areaIgnoreBodyBlock = false;
	bool areaIgnoreLineOfSight = false;
	bool requireTarget = false; // determines whether ability uses cursor or not
	bool canIncreaseRange = false;
	bool requireTargetsInArea = false;
	bool isGroundTargeted = false; // determines whether ability targets actors or tiles
	bool hideRange = false; // used for self-targeting skills and skills with rotational areas
	bool keyTileRange = false; // single tile that is rotated around user, used for skills like cones
	sf::Vector3i keyTile;
	bool isFriendlyAbility = false;
	std::vector<EquipType> usableWeapons = {};
	const double offHandBasicMultiplier = 1.00; // Multiplier for basic off-hand attacks.

	UseType usage = UseType::INSTANT;
	int castTime = 0;
	double attackSpeedMultipler = 1.0;
	int channelTicks = 0;

	int hpCost = 0;
	int mpCost = 0;
	int spCost = 0;

	int cooldown = 0;

	EventOptions abilityOptions;

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

	ActorPtr user = nullptr;
	BattleScene* battleScene = nullptr;

	int calcCooldown = cooldown; // how much cooldown is actually applied when ability is used
	int currentCooldown = 0;

	// Displays the casting message in the message log.
	void outputCasting();

	// Sets default options for a weapon attack.
	void setAttackDefault();

	// Sets default options for a offensive spell.
	void setHarmfulSpellDefault();

	// Sets default options for a helpful spell.
	void setHelpfulSpellDefault();

	// Initializes the abilityOptions object.
	void setAbilityOptions();

	// Consumes the resource costs from the actor's resource pool.
	void consumeResources();

	// Causes the user to gain exhaustion.
	void exhaustUser();

	// Places the ability on cooldown.
	void putOnCooldown();

	// Rotates an area of effect.
	void rotateArea(sf::Vector3i cursor, std::vector<sf::Vector3i>& area);

	// Executes the ability.
	virtual void execute(std::vector<ActorPtr>& targets, sf::Vector3i cursor, std::vector<sf::Vector3i> targetArea) = 0;

	// Rolls a double strike.
	bool doubleStrike(ActorPtr& target);
};