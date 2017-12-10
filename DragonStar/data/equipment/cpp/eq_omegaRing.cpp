// ==================================
//
// eq_omegaRing.cpp
//
// ==================================

#include "../header/eq_omegaRing.h"

Eq_OmegaRing::Eq_OmegaRing() {
	name = "Omega Ring";
	iconFilepath = "ring.png";
	itemQuality = ItemQuality::UNIQUE;
	weight = 1;
	tier = 4;

	textureFilepath = "omega_ring.png";
	equipType = EquipType::RING;
	equipmentID = EquipmentID::OMEGA_RING;

	equipPower = 0;
	blockChance = 0.0;
	attackSpeed = 0.0;
	statMods = {
		StatMod(StatModType::HP, 100.0),
		StatMod(StatModType::MP, 20.0),
		StatMod(StatModType::SP, 5.0),
		StatMod(StatModType::ALL_ATTRIBUTES, 5.0),
		StatMod(StatModType::ARMOR, 10.0),
		StatMod(StatModType::CRIT_CHANCE, 0.05),
		StatMod(StatModType::CRIT_DAMAGE, 0.25),
		StatMod(StatModType::HASTE, 0.04),
		StatMod(StatModType::DOUBLE_STRIKE_CHANCE, 0.08),
		StatMod(StatModType::RESISTANCE, 0.15,{ Category::ANY }, { Element::FIRE, Element::ICE, Element::LIGHTNING, Element::POISON, Element::WATER, Element::WIND, Element::EARTH, Element::LIGHT, Element::DARK })
	};
}