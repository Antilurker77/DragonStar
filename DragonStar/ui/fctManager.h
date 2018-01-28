// ==================================
//
// fctManager.h
//
// Class that manages floating combat
// text. Displays damage, healing,
// and auras.
//
// ==================================

#pragma once

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "richText.h"

enum class Attribute;
enum class Element;

struct FCTUnit {
	sf::RectangleShape Background;
	sfe::RichText Text;
	std::vector<sf::Sprite> Icons;
	float Lifespan = 0.f;
};

class FCTManager {
public:
	FCTManager();

	// Updates position of combat text. Removes text that
	// has expired.
	void Update(sf::Vector3i actorHexPos, float timePerUpdate);

	// Renders floating combat text.
	void Render(sf::RenderTarget& window);

	// Removes all floating combat text.
	void Clear();

	// Adds a damage or healing unit to the manager.
	void AddDamageHealUnit(int value, bool isCrit, std::vector<Element> elements, bool isHeal, Attribute attributeEffected);

	// Adds an aura unit to the manager.
	void AddAuraUnit(std::string name, bool isBuff, bool isExpired);

private:
	std::vector<FCTUnit> fcts;

	const float velocity = 10.f;
	const float lifespan = 3.f;
	const unsigned int fontSize = 14;
	const float boxHeight = 18.f;
};
