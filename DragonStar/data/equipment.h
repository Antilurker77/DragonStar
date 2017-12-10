// ==================================
//
// equipment.h
//
// Base class for all equippable
// items in the game.
//
// ==================================

#pragma once

#include "item.h"
#include "statMod.h"

#include <random>
#include <vector>

class Equipment : public Item {
public:
	// Returns the value of the item based on the item type and the stat mods.
	unsigned int GetPrice();

	// Returns whether the item is an equipment or not.
	bool IsEquipment();

	// Returns the filepath for the sprite texture.
	std::string GetTextureFilepath();

	// Returns the equip type of the equipment.
	EquipType GetEquipType();

	// Returns the id of the equipment.
	EquipmentID GetEquipmentID();

	// Returns the damage for weapons or armor value for armor.
	int GetEquipPower();

	// Returns the attack speed for the weapon. Armor always returns 0.
	int GetAttackSpeed();

	// Returns the attack range for the weapon. Armor always returns 0.
	int GetAttackRange();

	// Returns the attribute multiplier for the weapon. Armor always returns 0.
	double GetAttackMod();

	// Returns the elements for the weapon. Armor is blank.
	std::vector<Element> GetAttackElements();

	// Returns the block chance from the item. Only works for shields.
	double GetBlockChance();

	// Returns the stat mods of the item.
	std::vector<StatMod> GetStatMods();

	// Returns the aura used for on-hit events.
	AuraID GetOnHitAura();

	// Returns true if the item is unique.
	bool IsUnique();

	// Returns true if the item is a weapon.
	bool IsWeapon();

	// Returns true if the item is two-handed.
	bool IsTwoHanded();

	// Generates statMods for the item based on the given quality.
	void RollStatMods(ItemQuality quality, uint64_t seed);

protected:
	std::string textureFilepath;
	
	int baseValue;
	EquipType equipType;
	EquipmentID equipmentID;
	int equipPower = 0; // damage for weapons, armor amount for armor
	int attackSpeed = 0;
	int attackRange = 0;
	double attributeMultiplier = 0.0; // multiplier for weapons, always 0 for armor
	std::vector<Element> attackElements; // elements for weapon attacks
	double blockChance = 0.0; // shield block chance
	std::vector<StatMod> statMods;
	AuraID onHitAura = AuraID::UNDEFINED; // special aura created to trigger on-hit events

	// Determines how many affixes to roll given an item quality.
	int howManyStatMods(std::mt19937_64& mt);

	// Adds resistances to the item. Uncommon has a 50% of one
	// resistance, rare has one, epic has two.
	void rollResistanceStatMods(std::mt19937_64& mt);

	// Generates stat mods for a 1H sword.
	void rollOneHandSwordStatMods(std::mt19937_64& mt);

	// Generates stat mods for a spear.
	void rollSpearStatMods(std::mt19937_64& mt);

	// Generates stat mods for light body armor.
	void rollLightBodyArmorStatMods(std::mt19937_64& mt);

	// Generates stat mods for a neck.
	void rollNeckMods(std::mt19937_64& mt);

	// Generates stat mods for a ring.
	void rollRingMods(std::mt19937_64& mt);

	// -----------------------

	// Returns a random value for the given stat mod type.
	double rollMod(StatModType smt, std::mt19937_64& mt);

	// Rolls values for maximum HP.
	int rollModMaxHP(std::mt19937_64& mt);

	// Rolls values for an attribute.
	int rollModAttribute(std::mt19937_64& mt);
};