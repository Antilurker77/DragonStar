// ==================================
//
// player.h
//
// Class for player-controlled
// characters.
//
// ==================================

#pragma once

class Race;

#include "actor.h"

#include "../data/equipment.h"

#include <array>
#include <memory>

typedef std::shared_ptr<Item> ItemPtr;

class Player : public Actor {
public:
	Player(std::string n, RaceID raceID, PlayerClassID classID, bool female = false);

	void Update(float secondsPerUpdate);
	void Draw(sf::RenderTarget& window, float timeRatio);
	void Draw(sf::RenderTarget& window, sf::Vector2f pos);

	int GetMaxHP();
	int GetMaxMP();
	int GetMaxSP();

	double GetHPRegen();
	double GetMPRegen();
	double GetSPRegen();

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

	// Awards the player with experience points. Also
	// checks if the user has enough EXP to reach the
	// next level.
	bool GrantEXP(unsigned int xp);

	// Returns the player's current amount of EXP.
	unsigned int GetEXP();

	// Attempts to equip an item. Returns true if equipped.
	bool Equip(std::vector<ItemPtr>& inventory, size_t index, size_t slot);

	// Unequips an item.
	void Unequip(std::vector<ItemPtr>& inventory, size_t slot);

	// Returns the equipment in a given slot.
	// Slot 0: Main-Hand
	// Slot 1: Off-Hand
	// Slot 2: Head
	// Slot 3: Neck
	// Slot 4: Body
	// Slot 5: Hands
	// Slot 6: Ring 1
	// Slot 7: Ring 2
	// Slot 8: Feet
	// Slot 9: Trinket
	ItemPtr GetEquipment(size_t slot);
	
	// Returns all equipment the player is wearing.
	std::array<ItemPtr, 10u> GetAllEquipment();

	// Returns the IDs of the abilities the player has learned. Does not
	// return equipped ability IDs.
	std::vector<AbilityID> GetLearnedAbilities();

	// Returns the ability types this player can learn.
	std::vector<AbilityType> GetLearnableAbilityTypes();

	// Returns true if the given ability scroll is learnable.
	bool IsLearnable(ItemPtr& scroll);

	// Teaches a character an ability using a scroll.
	void LearnAbility(std::vector<ItemPtr>& inventory, size_t index);

	// Equips the ability of a given index into the specified slot.
	void EquipAbility(size_t index, size_t slot);

	// Unequips an ability.
	void UnequipAbility(size_t slot);

	// Returns true if the player is female.
	bool IsFemale();

	// Returns the current amount of EXP required to
	// get to the next level.
	unsigned int GetEXPToNextLevel();

	int GetMoveSpeed();
	bool CanFly();
	bool CanSwim();

	CreatureType GetCreatureType();

	bool IsPlayer();

	void SetAbilitySlotUser();
private:
	std::shared_ptr<Race> race;
	PlayerClassPtr playerClass;

	// Equipment
	// Slot 0: Main-Hand
	// Slot 1: Off-Hand
	// Slot 2: Head
	// Slot 3: Neck
	// Slot 4: Body
	// Slot 5: Hands
	// Slot 6: Ring 1
	// Slot 7: Ring 2
	// Slot 8: Feet
	// Slot 9: Trinket
	std::array<ItemPtr, 10> equipment;

	// Equipment Sprites
	// Slot 0: Body
	// Slot 1: Necklace
	// Slot 2: Hair
	// Slot 3: Head
	// Slot 4: Hands
	// Slot 5: Feet
	// Slot 6: Main Hand
	// Slot 7: Off-Hand
	std::array<sf::Sprite, 8> equipmentSprites;

	// Slot 0: Body
	// Slot 1: Necklace
	// Slot 2: Hair
	// Slot 3: Head
	// Slot 4: Hands
	// Slot 5: Feet
	// Slot 6: Main Hand
	// Slot 7: Off-Hand
	std::array<sf::Texture*, 8> equipmentTextures;

	std::vector<AbilityID> learnedAbilities;

	// player-only stats
	unsigned int exp = 0u;
	bool isFemale = false;

	// Gets a stat.
	double getStat(double initialValue, StatModType statModType, bool isMultiplicative, bool consumeBuffs);

	// Gets a stat.
	double getStat(double initialValue, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs);

	AuraID getWeaponOnHitAura(bool isOffHand);

	// Sets up the equipment texture for a given slot.
	void setEquipmentTexture(size_t slot);

	// Returns true if the equipment sprite should be drawn.
	bool drawEquip(size_t index);
};