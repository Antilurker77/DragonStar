// ==================================
//
// aura.cpp
//
// ==================================

#include "aura.h"

#include "id/abilityID.h"
#include "../entity/actor.h"

std::string Aura::GetName() {
	return name;
}

AuraID Aura::GetAuraID() {
	return id;
}

std::string Aura::GetIcon() {
	return icon;
}

std::string Aura::GetDescription() {
	return "No description available.";
}

std::vector<StatMod> Aura::GetStatMods() {
	if (!multiplyStatModsByStack) {
		return statMods;
	}
	else {
		std::vector<StatMod> sm;
		for (size_t i = 0; i < statMods.size(); i++) {
			sm.push_back(StatMod(statMods[i], stackCount));
		}
		return sm;
	}
}

bool Aura::IsHidden() {
	return isHidden;
}

bool Aura::IsBuff() {
	return isBuff;
}

bool Aura::IsUniquePerActor() {
	return uniquePerActor;
}

bool Aura::IsUnique() {
	return uniqueAura;
}

bool Aura::IsUnlimitedDuration() {
	return unlimitedDuration;
}

int Aura::GetRemainingDuration() {
	return durationRemaining;
}

int Aura::GetStackCount() {
	return stackCount;
}

ActorPtr Aura::GetUser() {
	return user;
}

sf::Vector3i Aura::GetPosition() {
	return position;
}

void Aura::InitializeGroundEffect(ActorPtr& user, sf::Vector3i position) {
	this->user = user;
	this->position = position;

	durationRemaining = baseDuration;
	nextTick = timePerTick;
	nextTickPower = 1.0;
	stackCount = 1;
}

void Aura::SetTarget(ActorPtr& target) {
	this->target = target;
}

void Aura::ClearTarget() {
	target = nullptr;
}

void Aura::InitializeAura(ActorPtr& user, ActorPtr& target) {
	this->user = user;
	this->target = target;

	calcDuraiton();
	durationRemaining = maxDuration;
	nextTick = timePerTick;
	nextTickPower = 1.0;
	stackCount = 1;
	setAuraOptions();
}

void Aura::SetValues(std::vector<int> values) {
	this->values = values;
	onValueChange();
}

void Aura::SetValue(size_t index, int v) {
	values[index] = v;
	onValueChange();
}

void Aura::ClearValues() {
	values.clear();
	onValueChange();
}

void Aura::WasUsed(bool used) {
	wasUsed = used;
}

void Aura::AddStack(ActorPtr& user) {
	if (stackCount < maxStacks) {
		stackCount++;
	}
	this->user = user;
	calcDuraiton();

	if (nextTick < timePerTick) {
		durationRemaining = maxDuration + nextTick; // stops ticks from clipping
		nextTick = timePerTick;
		nextTickPower = 1.0;
	}
	else {
		durationRemaining = maxDuration;
	}
}

void Aura::Tick() {
	if (!unlimitedDuration) {
		if (hasTicks) {
			nextTick--;
			durationRemaining--;
			if (nextTick == 0) {
				setAuraOptions();

				if (target != nullptr) {
					OnTick();
				}

				// if timePerTick is greater than the remaning duration, set
				// up a partial tick
				if (durationRemaining > 0 && timePerTick > durationRemaining) {
					nextTick = durationRemaining;
					nextTickPower = (double)nextTick / (double)timePerTick;
				}
				else {
					nextTick = timePerTick;
					nextTickPower = 1.0;
				}
			}
		}
		else {
			durationRemaining--;
		}

		// fire OnExpiry if remaining duration is 0
		if (durationRemaining == 0) {
			setAuraOptions();

			if (target != nullptr) {
				OnExpiry();
			}

			stackCount--;
			if (stackCount > 0 && !removeAllStacksOnExpiration) {
				durationRemaining = maxDuration;
				nextTick = timePerTick;
				nextTickPower = 1.0;
			}
			else {
				stackCount = 0;
			}
		}
	}

	if (wasUsed && consumedOnUse) {
		setAuraOptions();

		if (target != nullptr) {
			OnExpiry();
		}
		
		if (removeAllStacksOnExpiration) {
			stackCount = 0;
			durationRemaining = 0;
			nextTick = 0;
		}
		else {
			stackCount--;
			durationRemaining = maxDuration;
			nextTick = timePerTick;
			nextTickPower = 1.0;
		}
	}
	wasUsed = false;

	if (target != nullptr && target->IsAlive() == false) {
		target->ClearAuras();
	}
}

bool Aura::IsExpired() {
	// kinda hacky, stops auras that should expire
	// from sticking around
	if (wasUsed && consumedOnUse) {
		setAuraOptions();

		if (target != nullptr) {
			OnExpiry();
		}

		if (removeAllStacksOnExpiration) {
			stackCount = 0;
			durationRemaining = 0;
			nextTick = 0;
		}
		else {
			stackCount--;
			durationRemaining = maxDuration;
			nextTick = timePerTick;
			nextTickPower = 1.0;
		}
	}
	wasUsed = false;
	
	return stackCount == 0;
}

void Aura::OnEvent(EventType eventType, ActorPtr& target, BattleScene* battleScene, EventOptions& eventOptions, EventResult& eventResult, bool isOffHand, double& amount) {

}

void Aura::OnApplication() {

}

void Aura::OnTick() {

}

void Aura::OnExpiry() {

}

void Aura::calcDuraiton() {
	if (fixedDuration) {
		maxDuration = baseDuration;
	}
	else {
		int vit = 100;
		if (target != nullptr) {
			vit = target->GetVIT(true);
		}
		
		if (isBuff) {
			maxDuration = baseDuration * ((double)vit / 100.0);
		}
		else {
			maxDuration = baseDuration * (100.0 / (double)vit);
		}
	}

	//todo: include stun resistance, disarm resistance ect
	if (target != nullptr) {
		if (isStun) {

		}

		if (isDisarm) {

		}

		if (isSilence) {

		}

		if (isSlow) {

		}
	}
}

void Aura::setAuraOptions() {
	auraOptions.AbilityID = AbilityID::UNDEFINED;
	auraOptions.AuraID = id;
	auraOptions.BonusCritChance = bonusCrit + snapshotCritChance;
	auraOptions.BonusCritDamage = bonusCritDmg + snapshotCritPower;
	auraOptions.BonusLifeLeech = bonusLifeLeech;
	auraOptions.BonusManaLeech = bonusManaLeech;
	auraOptions.BonusStaminaLeech = bonusStaminaLeech;
	auraOptions.CanBlock = canBlock;
	auraOptions.CanCounter = canCounter;
	auraOptions.CanCrit = canCrit;
	auraOptions.CanDodge = canDodge;
	auraOptions.CanDoubleStrike = canDoubleStrike;
	auraOptions.Categories = categories;
	auraOptions.Elements = elements;
	auraOptions.EventName = name;
	if (isBuff) {
		auraOptions.EventName += " (Buff)";
	}
	else {
		auraOptions.EventName += " (Debuff)";
	}

}

void Aura::onValueChange() {

}