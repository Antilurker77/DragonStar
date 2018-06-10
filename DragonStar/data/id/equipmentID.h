// ==================================
//
// equipmentID.h
//
// List of IDs for all equipment.
//
// ==================================

#pragma once

enum class EquipmentID {
	Undefined = 0,

	// Generic 1H Sword
	IronSword,
	SteelSword,
	PlatinumSword,
	MythrilSword,
	AdamantiteSword,
	DragoniteSword,

	// Unique 1H Sword
	Flametongue,

	// Generic 2H Sword
	IronGreatsword,
	SteelGreatsword,
	PlatinumGreatsword,
	MythrilGreatsword,
	AdamantiteGreatsword,
	DragoniteGreatsword,

	// Unique 2H Sword
	BladeOfTheFallenKingdom,

	// Generic 1H Axe
	IronAxe,
	SteelAxe,
	PlatinumAxe,
	MythrilAxe,
	AdamantiteAxe,
	DragoniteAxe,

	// Unique 1H Axe

	// Generic 2H Axe
	IronGreataxe,
	SteelGreataxe,
	PlatinumGreataxe,
	MythrilGreataxe,
	AdamantiteGreataxe,
	DragoniteGreataxe,

	// Unique 2H Axe

	// Generic 1H Mace
	IronMace,
	SteelMace,
	PlatinumMace,
	MythrilMace,
	AdamantiteMace,
	DragoniteMace,

	// Unique 1H Mace

	// Generic 2H Mace
	IronGreatmace,
	SteelGreatmace,
	PlatinumGreatmace,
	MythrilGreatmace,
	AdamantiteGreatmace,
	DragoniteGreatmace,

	// Unique 2H Mace

	// Generic Dagger
	IronDagger,
	SteelDagger,
	PlatinumDagger,
	MythrilDagger,
	AdamantiteDagger,
	DragoniteDagger,

	// Unique Dagger

	// Generic Claw

	// Unique Claw

	// Generic Spear
	IronSpear,
	SteelSpear,
	PlatinumSpear,
	MythrilSpear,
	AdamantiteSpear,
	DragoniteSpear,

	// Unique Spear
	CloudLance,

	// Generic Longbow
	Longbow,
	CompositeBow,
	RecerveBow,
	GrandBow,
	ElvenBow,
	DragoniteBow,

	// Unique Longbow

	// Generic Crossbow
	LightCrossbow,
	ReinforcedCrossbow,
	HeavyCrossbow,
	ElvenCrossbow,
	Arbalest,
	DragoniteCrossbow,

	// Unique Crossbow

	// Generic Wand
	WoodenWand,
	ApprenticeWand,
	MysticWand,
	RuneWand,
	SageWand,
	DraconicWand,

	// Unique Wand

	// Generic Staff
	WoodenStaff,
	ApprenticeStaff,
	MysticStaff,
	RuneStaff,
	SageStaff,
	DraconicStaff,

	// Unique Staff

	// Generic Shield
	IronShield,
	SteelShield,
	PlatinumShield,
	MythrilShield,
	AdamantiteShield,
	DragoniteShield,

	// Unique Shield

	// Generic Buckler
	IronBuckler,
	SteelBuckler,
	PlatinumBuckler,
	MythrilBuckler,
	AdamantiteBuckler,
	DragoniteBuckler,

	// Unique Buckler

	// Generic Off-Hand
	PowerOrb,
	ApprenticeOrb,
	MythicOrb,
	RuneOrb,
	SageOrb,
	DraconicOrb,

	// Unique Off-Hand

	// Generic Light Head
	SilkHat,
	ApprenticeHat,
	RuneHat,
	MysticHat,
	SageHat,
	DraconicHat,

	// Unique Light Head

	// Generic Light Body
	SilkRobes,
	ApprenticeRobes,
	RuneRobes,
	MysticRobes,
	SageRobes,
	DraconicRobes,

	// Unique Light Body
	SirensEmbrace,

	// Generic Light Hands
	SilkGloves,
	ApprenticeGloves,
	RuneGloves,
	MysticGloves,
	SageGloves,
	DraconicGloves,

	// Unique Light Hands

	// Generic Light Feet
	SilkShoes,
	ApprenticeShoes,
	RuneShoes,
	MysticShoes,
	SageShoes,
	DraconicShoes,

	// Unique Light Feet

	// Generic Medium Head
	LeatherHelmet,
	BeastHelmet,
	TrackerHelmet,
	PrimalHelmet,
	ZodiacHelmet,
	DragonscaleHelmet,

	// Unique Medium Head

	// Generic Medium Body
	LeatherArmor,
	BeastArmor,
	TrackerArmor,
	PrimalArmor,
	ZodiacArmor,
	DragonscaleArmor,

	// Unique Medium Body

	// Generic Medium Hands
	LeatherGloves,
	BeastGloves,
	TrackerGloves,
	PrimalGloves,
	ZodiacGloves,
	DragonscaleGloves,

	// Unique Medium Hands

	// Generic Medium Feet
	LeatherBoots,
	BeastBoots,
	TrackerBoots,
	PrimalBoots,
	ZodiacBoots,
	DragonscaleBoots,

	// Unique Medium Feet

	// Generic Heavy Head
	IronHelm,
	SteelHelm,
	PlatinumHelm,
	MythrilHelm,
	AdamantiteHelm,
	DragoniteHelm,

	// Unique Heavy Head

	// Generic Heavy Body
	IronArmor,
	SteelArmor,
	PlatinumArmor,
	MythrilArmor,
	AdamantiteArmor,
	DragoniteArmor,

	// Unique Heavy Body

	// Generic Heavy Hands
	IronGauntlets,
	SteelGauntlets,
	PlatinumGauntlets,
	MythrilGauntlets,
	AdamantiteGauntlets,
	DragoniteGauntlets,

	// Unique Heavy Hands
	StoneGauntlets,

	// Generic Heavy Feet
	IronGreaves,
	SteelGreaves,
	PlatinumGreaves,
	MythrilGreaves,
	AdamantiteGreaves,
	DragoniteGreaves,

	// Unique Heavy Feet

	// Generic Necklace
	SilverNecklace,
	GoldNecklace,
	DragoniteNecklace,

	// Unique Necklace
	AmuletOfDivineLight,

	// Generic Ring
	SilverRing,
	GoldRing,
	DragoniteRing,

	// Unique Ring
	BandOfTwinDisciplines,
	RingOfVitality,
	OmegaRing,

	// Trinket
	CharmOfStrength,
	CharmOfDexterity,
	CharmOfIntelligence,
	CharmOfWisdom,
	BrokenPocketwatch,
};

