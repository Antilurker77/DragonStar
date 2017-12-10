// ==================================
//
// inspectWindow.h
//
// Window that shows detailed
// information for a given actor.
//
// ==================================

#pragma once

class Actor;
class Aura;

#include <array>
#include <memory>

#include <SFML/Graphics.hpp>

#include "auraTooltip.h"
#include "richText.h"

typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Aura> AuraPtr;

class InspectWindow {
public:
	InspectWindow();

	// Sets the actor that appears in the window.
	void SetActor(ActorPtr& actor);

	// Update function. Mostly checks if aura tooltip should
	// be displayed.
	void Update(sf::Vector2i mousePos);

	// Renders the window.
	void Render(sf::RenderTarget& window);

private:
	const int width = 800;
	const int height = 600;
	const unsigned int fontSize = 14;
	const float outlineThickness = 1.f;

	sf::Font* font;

	sf::RectangleShape background;

	ActorPtr actor;

	std::vector<AuraPtr> buffs;
	std::vector<AuraPtr> debuffs;

	AuraTooltip auraTooltip;
	bool displayAuraTooltip;

	// Sprites
	std::array<sf::Sprite, 13> resistanceIcons;
	std::array<sf::Texture*, 13> resistanceIconTextures;

	// Texts
	sf::Text nameText;
	sfe::RichText levelText;
	sfe::RichText hpText;
	sfe::RichText mpText;
	sfe::RichText spText;

	sfe::RichText strText;
	sfe::RichText dexText;
	sfe::RichText intText;
	sfe::RichText wisText;

	sfe::RichText vitText;
	sfe::RichText msText;
	sfe::RichText actionText;
	sfe::RichText exhaustionText;

	sfe::RichText mainHandDamageText;
	sfe::RichText attackSpeedText;
	sfe::RichText hitChanceText;
	sfe::RichText criticalStrikeChanceText;

	sfe::RichText offHandDamageText;
	sfe::RichText attackRangeText;
	sfe::RichText doubleStrikeChanceText;
	sfe::RichText hasteText;

	sfe::RichText armorText;
	sfe::RichText evadeChanceText;
	sfe::RichText blockChanceText;

	sfe::RichText bonusText;

	sfe::RichText statusEffectText;

	sfe::RichText resistanceText;
	std::array<sf::Text, 13> resistanceTextValues;

	sf::Texture* hudTexture;
	sf::VertexArray auraIcons;

	std::vector<sf::Sprite> auraBuffIcons;
	std::vector<sf::Text> auraBuffDuration;

	std::vector<sf::Sprite> auraDebuffIcons;
	std::vector<sf::Text> auraDebuffDuration;
};
