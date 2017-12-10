// ==================================
//
// battleScene.h
//
// Scene that manages input, ui, and
// entities for battles.
//
// ==================================

#pragma once

#pragma once

class Camera;
class Enemy;

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "mapNode.h"
#include "../command/command.h"
#include "../core/gameState.h"
#include "../entity/entity.h"
#include "../entity/player.h"
#include "../entity/enemy.h"
#include "../ui/abilityBar.h"
#include "../ui/auraTooltip.h"
#include "../ui/cursorActorHUD.h"
#include "../ui/inspectWindow.h"
#include "../ui/victoryWindow.h"

class BattleScene {
public:
	BattleScene();

	// Sets the camera reference.
	void SetCamera(Camera* c);

	void ReadInput(sf::RenderWindow& window);
	GameState Update(float secondsPerUpdate);
	void RenderWorld(sf::RenderWindow& window, float timeRatio);
	void RenderUI(sf::RenderWindow& window, float timeRatio);

	// Initializes the battle.
	void Initialize(std::vector<ActorPtr>& players, MapNode mapNode);

	// Returns the current map.
	MapPtr GetMap();

	// Creates a ground effect at the selected location.
	void CreateGroundEffect(ActorPtr& user, AuraID auraID, sf::Vector3i location);

	// Pathfinding
	std::vector<sf::Vector3i> Pathfind(ActorPtr& actor, sf::Vector3i destination);
	double GetPathCost(std::vector<sf::Vector3i>& path);
	bool IsTileOccupied(sf::Vector3i tile);
	bool IsTileOccupied(sf::Vector2i tile);
	bool IsTileOpeque(sf::Vector3i tile);
	bool IsTileWalkable(sf::Vector3i tile, bool canFly, bool canSwim);

	// Line of Sight

	// Removes all tiles not within line of sight.
	std::vector<sf::Vector3i> GetLineOfSight(sf::Vector3i origin, std::vector<sf::Vector3i> tiles, bool isPlayer, bool ignoreBodyBlock, bool ignoreLineOfSight);

	// Checks if two tiles are within line of sight.
	bool InLineOfSight(sf::Vector3i start, sf::Vector3i end, bool isPlayer, bool ignoreBodyBlock);

	// Data polling.

	// Returns all player actors.
	std::vector<ActorPtr> GetPlayers(bool aliveOnly);

	// Returns all enemy actors.
	std::vector<ActorPtr> GetEnemies(bool aliveOnly);

	// Returns the actor at the speficied location. Does not return dead actors.
	ActorPtr GetActorAtHex(sf::Vector3i hex);

	// Returns valid ability targets for a given area.
	std::vector<ActorPtr> GetAbilityTargets(std::vector<sf::Vector3i> targetArea, bool isFriendlySpell, bool isPlayer);

	// Returns all ground effect auras at the designated position that affect a given actor type.
	std::vector<AuraPtr> GetGroundEffectsAtHex(sf::Vector3i hex, bool isPlayer);

	// Returns the amount of gold earned during this battle.
	unsigned int GetGoldAwared();

	// Returns the items earned during this battle.
	std::vector<ItemPtr> GetItemsAwarded();

private:
	std::vector<Entity> entities;
	std::vector<ActorPtr> actors;
	std::vector<AuraPtr> groundEffects;

	Entity playerGE;
	Entity enemyGE;

	CommandPtr command;

	ActorPtr activeActor;

	MapPtr currentMap;
	uint64_t seed;
	unsigned int level = 0u;
	int tier = 0;
	bool isBoss = false;
	bool isUnique = false;

	bool victory = false;
	bool defeat = false;

	unsigned int expAwarded = 0u;
	unsigned int goldAwarded = 0u;
	std::vector<ItemPtr> itemsAwarded = {};

	// Input
	sf::Vector2i windowMousePosition;
	sf::Vector2f worldMousePosition;
	sf::Vector3i mouseTile;
	ActorPtr cursorActor;

	bool leftClick = false;

	// === UI Stuff ===
	Camera* camera;

	std::vector<AuraTooltip> auraTooltips;

	AbilityBar abilityBar;
	CursorActorHUD cursorActorHUD;
	InspectWindow inspectWindow;
	VictoryWindow victoryWindow;

	bool isWindowOpen = false;
	bool isInspectWindowOpen = false;
	bool isVictoryWindowOpen = false;

	sf::Font* font;

	sf::Texture* selectTileTexture;
	sf::Texture* abilityTargetTexture;
	sf::Sprite selectTile;
	sf::Texture* currentActorTileTexture;
	sf::Sprite currentActorTile;

	sf::Text debugText;

	// Ability Targeting
	sf::VertexArray abilityTargetVertexArray;
	bool isTargeting = false;
	bool needToRecalcVertexArray = false;
	size_t abilityIndex = 0;
	sf::Vector3i lastCursor = { 0, 0, 0 };
	sf::Vector3i targetCursor = { 0, 0, 0 };

	// ----------------------------------

	// Updates the world.
	void updateWorld(float secondsPerUpdate);

	// Updates UI elements.
	GameState updateUI(float secondsPerUpdate);

	// Builds the ability vertex array.
	void buildAbilityVertexArray(std::vector<sf::Vector3i> range, std::vector<sf::Vector3i> area, bool isHelpfulAbility);

	// Resets the ability vertex array.
	void resetAbilityVertexArray();

	// Checks to see if the player has won.
	bool checkVictory();

	// Checks to see it the player has lost.
	bool checkDefeat();

	// Calculates the rewards for victory.
	void calcVictory();
};