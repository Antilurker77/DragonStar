// ==================================
//
// eq_sword1H.cpp
//
// ==================================

#include "../header/eq_sword1H.h"

#include "../../id/abilityID.h"
#include "../../id/auraID.h"
#include "../../id/category.h"
#include "../../id/element.h"
#include "../../id/equipmentID.h"
#include "../../id/equipType.h"
#include "../../id/itemQuality.h"
#include "../../id/statModType.h"
#include "../../../core/random.h"

Eq_IronSword::Eq_IronSword() {
	name = "Iron Sword";
	iconFilepath = "sword.png";
	itemQuality = ItemQuality::Common;
	weight = 5;
	tier = 1;

	textureFilepath = "iron_sword.png";
	equipType = EquipType::Sword1H;
	equipmentID = EquipmentID::IronSword;

	equipPower = 50;
	attackSpeed = 200;
	attackRange = 1;
	attributeMultiplier = 1.00;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {};
}

// --------------------------------------------------------------------

Eq_Flametongue::Eq_Flametongue() {
	name = "Flametongue";
	iconFilepath = "sword.png";
	itemQuality = ItemQuality::Unique;
	weight = 5;
	tier = 1;

	textureFilepath = "iron_sword.png";
	equipType = EquipType::Sword1H;
	equipmentID = EquipmentID::Flametongue;

	equipPower = 50;
	attackSpeed = 200;
	attackRange = 1;
	attributeMultiplier = 1.00;
	attackElements = { Element::Physical };
	blockChance = 0.0;
	statMods = {
		StatMod(StatModType::SP, 5.0),
		StatMod(StatModType::STR, 5.0),
		StatMod(StatModType::Damage, 0.08, { Category::Any }, { Element::Fire }),
		StatMod(StatModType::OnHitDamage, 4.0, { Element::Fire }, { Category::Any }),
		StatMod(StatModType::CooldownReduction, 0.03),
		StatMod(StatModType::Resistance, 0.05, { Category::Any }, { Element::Fire })
	};
	extraAffixes = {
		"Attacks have a 10% chance to deal 100 fire damage to the target."
	};
}

void Eq_Flametongue::OnEvent(EventType eventType, ActorPtr& user, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {
	if (eventType == EventType::Attack) {
		auto cat = eventOptions.Categories;
		if (std::find(cat.begin(), cat.end(), Category::Direct) != cat.end()) {
			int roll = Random::RandInt(1, 100);
			if (roll <= 10) {
				EventOptions proc;
				proc.EventName = name;
				proc.Categories = { Category::Damaging, Category::SingleTarget };
				proc.Elements = { Element::Fire };
				proc.TriggerOnHit = false;

				Combat::FixedAttack(user, target, 100.0, proc);
			}
		}
	}

}

// --------------------------------------------------------------------
