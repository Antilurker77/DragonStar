// ==================================
//
// actor.ccp
//
// ==================================

#include "actor.h"

#include "statMath.h"
#include "../scene/battleScene.h"
#include "../data/factory.h"
#include "../ui/messageLog.h"

void Actor::SetWorld(BattleScene* w) {
	battleScene = w;
	for (size_t i = 0; i < abilities.size(); i++) {
		if (abilities[i] != nullptr) {
			abilities[i]->SetWorld(*w);
		}
	}
}

void Actor::ClearWorld() {
	battleScene = nullptr;
}

std::string Actor::GetName(){
	return name;
}

std::string Actor::GetActionName() {
	if (isCasting) {
		return abilities[castIndex]->GetName();
	}
	else if (exhaustion > 0) {
		return "Recovering";
	}
	else {
		return "";
	}
}

int Actor::GetExhaustion(){
	return exhaustion;
}

int Actor::GetLastActionExhaustion() {
	return lastActionExhaustion;
}

void Actor::DecrementExhaustion(){
	// HP Regen
	hpRegenOverflow += GetHPRegen() / 100.0;
	if (hpRegenOverflow >= 1.0) {
		int regen = std::floor(hpRegenOverflow);
		if (hpCurrent + regen > GetMaxHP()) {
			hpCurrent = GetMaxHP();
		}
		else {
			hpCurrent += regen;
		}
		hpRegenOverflow = std::fmod(hpRegenOverflow, 1.0);
	}
	else if (hpRegenOverflow <= -1.0) {
		int regen = std::ceil(hpRegenOverflow);
		if (hpCurrent + regen < 0) {
			hpCurrent = 0;
		}
		else {
			hpCurrent += regen;
		}
		hpRegenOverflow = std::fmod(hpRegenOverflow, 1.0);
	}

	// MP Regen
	mpRegenOverflow += GetMPRegen() / 100.0;
	if (mpRegenOverflow >= 1.0) {
		int regen = std::floor(mpRegenOverflow);
		if (mpCurrent + regen > GetMaxMP()) {
			mpCurrent = GetMaxMP();
		}
		else {
			mpCurrent += regen;
		}
		mpRegenOverflow = std::fmod(mpRegenOverflow, 1.0);
	}
	else if (mpRegenOverflow <= -1.0) {
		int regen = std::ceil(mpRegenOverflow);
		if (mpCurrent + regen < 0) {
			mpCurrent = 0;
		}
		else {
			mpCurrent += regen;
		}
		mpRegenOverflow = std::fmod(mpRegenOverflow, 1.0);
	}

	// SP Regen
	spRegenOverflow += GetSPRegen() / 100.0;
	if (spRegenOverflow >= 1.0) {
		int regen = std::floor(spRegenOverflow);
		if (spCurrent + regen > GetMaxSP()) {
			spCurrent = GetMaxSP();
		}
		else {
			spCurrent += regen;
		}
		spRegenOverflow = std::fmod(spRegenOverflow, 1.0);
	}
	else if (spRegenOverflow <= -1.0) {
		int regen = std::ceil(spRegenOverflow);
		if (spCurrent + regen < 0) {
			spCurrent = 0;
		}
		else {
			spCurrent += regen;
		}
		spRegenOverflow = std::fmod(spRegenOverflow, 1.0);
	}

	// Exhaustion
	if (exhaustion > 0){
		exhaustion--;
		if (exhaustion == 0) {
			lastActionExhaustion = 0;
		}
	}
	for (size_t i = 0; i < abilities.size(); i++) {
		if (abilities[i] != nullptr) {
			abilities[i]->DecrementCooldown();
		}
	}

	for (size_t i = 0; i < auras.size(); i++) {
		auras[i]->Tick();
	}

	// remove auras that have expired
	RemoveExpiredAuras();
}

void Actor::Wait(int timeToWait){
	exhaustion += timeToWait;
	lastActionExhaustion += timeToWait;
}

void Actor::FullHeal() {
	hpCurrent = GetMaxHP();
	mpCurrent = GetMaxMP();
	spCurrent = GetMaxSP();
	auras.clear();
	for (size_t i = 0; i < abilities.size(); i++) {
		if (abilities[i] != nullptr) {
			abilities[i]->ResetCooldown();
		}
	}
	isCasting = false;
	exhaustion = 0;

	hpRegenOverflow = 0.0;
	mpRegenOverflow = 0.0;
	spRegenOverflow = 0.0;
}

void Actor::ZeroHP() {
	hpCurrent = 0;
}

bool Actor::IsAlive() {
	if (hpCurrent <= 0) {
		return false;
	}
	return true;
}

// Returns the actor's current level.
int Actor::GetLevel(){
	return level;
}

int Actor::GetCurrentHP() {
	return hpCurrent;
}

int Actor::GetCurrentMP() {
	return mpCurrent;
}

int Actor::GetCurrentSP() {
	return spCurrent;
}

double Actor::GetAttributePercent(Attribute attribute) {
	switch (attribute) {
	case Attribute::HP:
		return (double)GetCurrentHP() / (double)GetMaxHP();
		break;
	case Attribute::MP:
		return (double)GetCurrentMP() / (double)GetMaxMP();
		break;
	case Attribute::SP:
		return (double)GetCurrentSP() / (double)GetMaxSP();
		break;
	default:
		return 0.0;
		break;
	}
}

AbilityPtr Actor::GetAbility(size_t index) {
	AbilityPtr a;
	try {
		a = abilities.at(index);
	}
	catch (std::out_of_range& e) {
		a = abilities[0];
	}
	return a;
}

std::vector<std::string> Actor::GetAbilityIcons() {
	std::vector<std::string> iconFilepaths;

	for (size_t i = 0; i < abilities.size(); i++) {
		if (abilities[i] != nullptr) {
			iconFilepaths.push_back(abilities[i]->GetIcon());
		}
		else {
			iconFilepaths.push_back("");
		}
	}

	return iconFilepaths;
}

std::vector<sf::Vector3i> Actor::GetAbilityRange(size_t index) {
	std::vector<sf::Vector3i> range = {};
	try {
		range = abilities.at(index)->GetTargetRange();
	}
	catch (std::out_of_range& e) {
		// do nothing if exception is thrown
	}
	return range;
}

std::vector<sf::Vector3i> Actor::GetAbilityAreaOfEffect(size_t index, sf::Vector3i cursor) {
	std::vector<sf::Vector3i> area = {};
	try {
		area = abilities.at(index)->GetTargetArea(cursor);
	}
	catch (std::out_of_range& e) {
		// do nothing if exception is thrown
	}
	return area;
}

bool Actor::IsAbilityAvailable(size_t index) {
	bool isAvailable = false;
	try {
		if (abilities.at(index) != nullptr) {
			isAvailable = abilities[index]->IsUsable();
		}
	}
	catch (std::out_of_range& e) {
		// do nothing if exception is thrown
	}
	return isAvailable;
}

bool Actor::IsFriendlyAbility(size_t index) {
	bool isFriendly = false;
	try {
		if (abilities.at(index) != nullptr) {
			isFriendly = abilities[index]->IsFriendly();
		}
	}
	catch (std::out_of_range& e) {
		// do nothing if exception is thrown
	}
	return isFriendly;
}


void Actor::UseAbility(size_t index, BattleScene& battleScene, sf::Vector3i cursor) {
	std::vector<sf::Vector3i> area = {};
	
	try {
		if (abilities.at(index) != nullptr) {
			abilities[index]->SetWorld(battleScene);
			if (IsCastReady() && IsAlive()) { // must be alive to finish cast
				if (castTarget != nullptr) {
					cursor = castTarget->GetHexPosition();
				}
				else {
					cursor = castLocation;
				}
			}
			area = abilities[index]->GetTargetArea(cursor);
			abilities[index]->UseAbility(cursor, area);
		}
		// clean up after casting is finished
		if (IsCastReady()) {
			isCasting = false;
			castTarget.reset();
		}
	}
	catch (std::out_of_range& e) {
		// do nothing if exception is thrown
	}

	if (IsCasting()) {
		castIndex = index;
	}
}

void Actor::SpendResource(Attribute attribute, int amount) {
	switch (attribute) {
	case Attribute::HP:
		if (amount > hpCurrent) {
			hpCurrent = 0;
		}
		else {
			hpCurrent -= amount;
		}
		break;
	case Attribute::MP:
		if (amount > mpCurrent) {
			mpCurrent = 0;
		}
		else {
			mpCurrent -= amount;
		}
		break;
	case Attribute::SP:
		if (amount > spCurrent) {
			spCurrent = 0;
		}
		else {
			spCurrent -= amount;
		}
		break;
	default:
		break;
	}
}

void Actor::StartCast(sf::Vector3i cursor, int castTime) {
	this->castLocation = cursor;
	this->castTime = castTime;
	isCasting = true;
	this->Wait(castTime);
}

void Actor::StartCast(ActorPtr& target, int castTime) {
	this->castTarget = target;
	this->castTime = castTime;
	isCasting = true;
	this->Wait(castTime);
}

bool Actor::IsCasting() {
	return isCasting;
}

bool Actor::IsCastReady() {
	if (isCasting && exhaustion == 0) {
		return true;
	}
	else {
		return false;
	}
}

size_t Actor::GetCastIndex() {
	return castIndex;
}

sf::Vector3i Actor::GetTargetCursor() {
	if (castTarget != nullptr) {
		return castTarget->GetHexPosition();
	}
	else {
		return castLocation;
	}
}

int Actor::GetAuraStackCount(AuraID auraID) {
	for (auto aura : auras) {
		if (aura->GetAuraID() == auraID) {
			return aura->GetStackCount();
		}
	}

	return 0; // if actor doesn't have aura
}

std::vector<AuraPtr> Actor::GetBuffAuras() {
	std::vector<AuraPtr> buffs;

	for (size_t i = 0; i < auras.size(); i++) {
		if (auras[i]->IsBuff() && auras[i]->IsHidden() == false) {
			buffs.push_back(auras[i]);
		}
	}

	return buffs;
}

std::vector<AuraPtr> Actor::GetDebuffAuras() {
	std::vector<AuraPtr> debuffs;

	for (size_t i = 0; i < auras.size(); i++) {
		if (auras[i]->IsBuff() == false && auras[i]->IsHidden() == false) {
			debuffs.push_back(auras[i]);
		}
	}

	return debuffs;
}

void Actor::OnPreCalc(ActorPtr& targetHit, EventOptions& eventOptions) {
	for (auto au : auras) {
		au->OnPreCalc(targetHit, eventOptions);
	}
}

void Actor::OnPostCalc(ActorPtr& targetHit, EventOptions& eventOptions, EventResult& eventResult, double& damage) {
	for (auto au : auras) {
		au->OnPostCalc(targetHit, eventOptions, eventResult, damage);
	}
}

void Actor::OnPreCalcHeal(ActorPtr& targetHit, EventOptions& eventOptions) {
	for (auto au : auras) {
		au->OnPreCalcHeal(targetHit, eventOptions);
	}
}

void Actor::OnPostCalcHeal(ActorPtr& targetHit, EventOptions& eventOptions, EventResult& eventResult, double& heal) {
	for (auto au : auras) {
		au->OnPostCalcHeal(targetHit, eventOptions, eventResult, heal);
	}
}

void Actor::OnHit(ActorPtr& targetHit, EventOptions eventOptions, EventResult eventResult, bool isOffHand) {
	if (eventResult.DidHit) {
		std::vector<StatMod> statMods;
		int totalDamage = 0;
		EventOptions eventOptionsLocal;
		eventOptionsLocal.AbilityID = AbilityID::UNDEFINED;
		eventOptionsLocal.AuraID = AuraID::UNDEFINED;
		eventOptionsLocal.Categories = { Category::DAMAGING };
		eventOptionsLocal.TriggerOnHit = false;

		statMods = GetOnHitDamage(eventOptions, true, isOffHand);

		for (auto sm : statMods) {
			eventOptionsLocal.Elements = sm.GetOnHitElements();
			EventResult eventResult = Combat::OnHit(getPtr(), targetHit, sm.GetValue(), eventOptionsLocal);
			totalDamage += eventResult.ResultValue;
		}

		if (totalDamage > 0) {
			std::string output = name + "'s on-hit effects hit " + targetHit->GetName() + " for ";
			output += std::to_string(totalDamage);
			output += " damage.";
			messageLog.AddMessage(output);
		}

		// Weapon effects.
		Factory factory;
		AuraID auraID = getWeaponOnHitAura(isOffHand);
		if (auraID != AuraID::UNDEFINED) {
			AuraPtr weaponAura = factory.CreateAura(auraID);
			weaponAura->InitializeAura(getPtr(), getPtr());
			weaponAura->OnHit(targetHit, eventOptions, eventResult);
		}
	}

	for (auto au : auras) {
		au->OnHit(targetHit, eventOptions, eventResult);
	}
}

void Actor::OnHeal(ActorPtr& targetHealed, EventOptions eventOptions, EventResult eventResult) {
	for (auto au : auras) {
		au->OnHeal(targetHealed, eventOptions, eventResult);
	}

	// todo: on-heal effects
}

void Actor::OnAttacked(ActorPtr& attacker, EventOptions eventOptions, EventResult eventResult) {
	for (auto au : auras) {
		au->OnAttacked(attacker, eventOptions, eventResult);
	}
}

void Actor::OnHealed(ActorPtr& healer, EventOptions eventOptions, EventResult eventResult) {
	for (auto au : auras) {
		au->OnHealed(healer, eventOptions, eventResult);
	}
}

void Actor::RemoveExpiredAuras() {
	if (auras.size() > 0) {
		const auto pred = [](const AuraPtr& a) { return a->IsExpired(); };
		auras.erase(std::remove_if(auras.begin(), auras.end(), pred), auras.end());
	}
}

void Actor::ClearAuras() {
	auras.clear();
}

bool Actor::GrantEXP(unsigned int xp) {
	return false;
}

unsigned int Actor::GetEXP() {
	return 0u;
}

unsigned int Actor::GetEXPToNextLevel() {
	return 0u;
}

unsigned int Actor::GetEXPDrop() {
	return 0u;
}

unsigned int Actor::GetGoldDrop() {
	return 0u;
}

unsigned int Actor::GetLootPoints() {
	return 0u;
}

int Actor::DamageActor(double damage, std::vector<Element> elements, bool isCrit) {
	int damageDealt = (int)std::round(damage);

	// don't deal less than 0 damage
	if (damageDealt < 0) {
		damageDealt = 0;
	}
	
	// cap damage dealt at target's current hp
	if (damageDealt > hpCurrent) {
		damageDealt = hpCurrent;
		hpCurrent = 0;
	}
	else {
		hpCurrent -= damageDealt;
	}

	return damageDealt;
}

int Actor::HealActor(double healAmount, std::vector<Element> elements, Attribute whatToHeal, bool isCrit) {
	int amountHealed = (int)std::round(healAmount);

	// don't damage actors with healing
	if (amountHealed < 0) {
		amountHealed = 0;
	}

	// cap healing at target's missing ammount
	switch (whatToHeal) {
	case Attribute::HP:
		if (amountHealed > GetMaxHP() - hpCurrent) {
			amountHealed = GetMaxHP() - hpCurrent;
		}
		hpCurrent += amountHealed;
		break;
	case Attribute::MP:
		if (amountHealed > GetMaxMP() - mpCurrent) {
			amountHealed = GetMaxMP() - mpCurrent;
		}
		mpCurrent += amountHealed;
		break;
	case Attribute::SP:
		if (amountHealed > GetMaxSP() - spCurrent) {
			amountHealed = GetMaxSP() - spCurrent;
		}
		spCurrent += amountHealed;
		break;
	default:
		if (amountHealed > GetMaxHP() - hpCurrent) {
			amountHealed = GetMaxHP() - hpCurrent;
		}
		hpCurrent += amountHealed;
		break;
	}

	return amountHealed;
}

bool Actor::AddAuraStack(ActorPtr& user, AuraID auraID) {
	Factory factory;
	AuraPtr newAura = factory.CreateAura(auraID);
	newAura->InitializeAura(user, getPtr());

	// dont add auras who's duration was reduced to 0
	if (newAura->IsUnlimitedDuration() == false && newAura->GetRemainingDuration() == 0) {
		return false;
	}

	for (size_t i = 0; i < auras.size(); i++) {
		if (newAura->GetAuraID() == auras[i]->GetAuraID()) {
			if (newAura->IsUnique()) {
				auras[i]->AddStack(user);
				return true;
			}
			else if (newAura->IsUniquePerActor() && auras[i]->GetUser() == user) {
				auras[i]->AddStack(user);
				return true;
			}
		}
	}

	auras.push_back(newAura);
	return true;
}

void Actor::Walk(sf::Vector3i destination, double moveMod){
	int moveCost = GetMoveSpeed() * moveMod ;
	MoveToHex(destination, 300);
	exhaustion += moveCost;
}

ActorPtr Actor::getPtr() {
	return shared_from_this();
}

void Actor::SetAbilitySlotWorld(size_t index, BattleScene* w) {
	try {
		if (abilities[index] != nullptr) {
			abilities[index]->SetWorld(*w);
		}
	}
	catch (std::out_of_range& e) {
		// do nothing if exception is thrown
	}
}

AuraID Actor::getWeaponOnHitAura(bool isOffHand) {
	return AuraID::UNDEFINED;
}

std::vector<StatMod> Actor::getAuraStatMods() {
	std::vector<StatMod> statMods;
	for (size_t i = 0; i < auras.size(); i++) {
		std::vector<StatMod> auraStatMods = auras[i]->GetStatMods();
		for (size_t j = 0; j < auraStatMods.size(); j++) {
			statMods.push_back(auraStatMods[j]);
		}
	}
	return statMods;
}

void Actor::getStatModValueFromAuras(double& value, StatModType statModType, bool isMultiplicative, bool consumeBuffs) {
	EventOptions eo;
	eo.Categories = { Category::NONE };
	eo.Elements = { Element::NONE };
	eo.AbilityID = AbilityID::UNDEFINED;
	eo.AuraID = AuraID::UNDEFINED;
	
	getStatModValueFromAuras(value, statModType, eo, isMultiplicative, consumeBuffs);
}

void Actor::getStatModValueFromAuras(double& value, StatModType statModType, EventOptions eventOptions, bool isMultiplicative, bool consumeBuffs) {
	for (size_t i = 0; i < auras.size(); i++) {
		double oldValue = value;
		std::vector<StatMod> statMods = auras[i]->GetStatMods();
		StatModCalc::GetStatModValue(value, statMods, statModType, eventOptions, isMultiplicative);
		
		// if the value has changed, then the aura's stat mod was used
		if (consumeBuffs && value != oldValue) {
			auras[i]->WasUsed(true);
		}
	}
}

Attribute Actor::getWeaponAttribute(EquipType weaponType) {
	switch (weaponType) {
	case EquipType::UNARMED_STR:
	case EquipType::SWORD_1H:
	case EquipType::SWORD_2H:
	case EquipType::AXE_1H:
	case EquipType::AXE_2H:
	case EquipType::MACE_1H:
	case EquipType::MACE_2H:
		return Attribute::STR;
		break;
	case EquipType::UNARMED_DEX:
	case EquipType::DAGGER:
	case EquipType::CLAW:
	case EquipType::SPEAR:
	case EquipType::BOW:
		return Attribute::DEX;
		break;
	case EquipType::UNARMED_INT:
	case EquipType::WAND:
		return Attribute::INT;
		break;
	default:
		return Attribute::STR;
		break;
	}
}