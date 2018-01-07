// ==================================
//
// mapSelectScene.h
//
// Scene where the user selects the
// domain to start, which formation
// in that domain to fight, manage
// the party, and shop.
//
// ...most of this is NYI.
//
// ==================================

#pragma once

class Camera;

#include <memory>
#include <vector>

#include "mapNode.h"
#include "../core/gameState.h"
#include "../data/item.h"
#include "../data/weight.h"
#include "../entity/player.h"
#include "../ui/abilityWindow.h"
#include "../ui/button.h"
#include "../ui/equipWindow.h"
#include "../ui/formationTooltip.h"
#include "../ui/shopWindow.h"

typedef std::pair<size_t, size_t> Connection;

class MapSelectScene {
public:
	MapSelectScene();

	// Reads input from the user and processes events.
	void ReadInput(sf::RenderWindow& window);

	// Update function.
	GameState Update(float secondsPerUpdate);

	// Renders the UI to the screen.
	void Render(sf::RenderTarget& window, float timeRatio);

	// Causes the scene to ignore click inputs for a given number of seconds.
	void SetClickBuffer(float seconds);

	// Sets the seed and rebuilds the domains.
	void SetSeed(uint64_t seed);

	// Sets the party reference.
	void SetParty(std::vector<ActorPtr>& actors);

	// Returns the party reference.
	std::vector<ActorPtr> GetParty();

	// Returns the selected map node.
	MapNode GetSelectedMapNode();

	// Tells the scene that the player has completed the map.
	void CompleteMap(std::vector<ItemPtr> itemsAwarded, unsigned int goldAwarded);

private:

	// Data
	std::vector<ActorPtr> party;
	std::vector<ItemPtr> inventory;
	unsigned int gold = 0u;
	std::vector<sf::Vector2i> clearedMaps; // first is domain number, second is map number
	std::vector<size_t> clearedDomains;
	std::vector<FormationID> spawnedUniques;

	uint64_t masterSeed = 0ull;

	std::vector<MapNode> domains;
	std::vector<std::vector<MapNode>> maps;
	std::vector<Connection> domainConnections;
	std::vector<Connection> mapConnections;

	int currentDomain = 0;
	int currentMap = 0;
	int currentDomainStep = 0;
	int currentMapStep = 0;

	// Node Display
	sf::VertexArray nodeVertex;
	sf::Texture* nodeTexture;
	std::vector<sf::RectangleShape> nodeRects;
	sf::VertexArray nodeLines;

	// UI
	const int nodeSize = 75;
	sf::Vector2i windowMousePos;
	sf::Vector2f worldMousePos;
	bool leftClick;
	bool rightClick;
	bool scrollUp;
	bool scrollDown;
	float clickBuffer = 0.f; // Buffer for click input. Stops clicks from immediately firing off on scene change.

	Button equipButton;
	Button abilityButton;
	Button shopButton;
	sf::Text seedText;

	sf::RectangleShape goldBackground;
	sf::Sprite goldIcon;
	sf::Text goldText;

	EquipWindow equipWindow;
	AbilityWindow abilityWindow;
	ShopWindow shopWindow;

	bool displayWindow = false;
	bool displayEquipWindow = false;
	bool displayAbilityWindow = false;
	bool displayShopWindow = false;

	bool displayMaps = false; // true when displaying domains

	FormationTooltip formationTooltip;
	bool displayFormationTooltip = false;

	MapNode selectedMapNode;

	// -----------------------------------

	// Resets and builds the domains and maps.
	void buildDomains();

	// Builds the maps for the domains. Helper function, do
	// not call outside buildDomains().
	void buildMaps(size_t index, uint64_t seed);

	// Creates a vertex array with the given nodes.
	void buildVertexArray(std::vector<MapNode>& nodes);

	// Returns the pixel location of a domain node.
	sf::Vector2i getDomainLocation(size_t index);

	// Returns the pixel location of a map node.
	sf::Vector2i getMapLocation(size_t domain, size_t index);

	// Returns a list of connections for a given node.
	std::vector<size_t> calcConnections(size_t nodeNumber, std::vector<size_t> nodesPerStep, size_t i, size_t j);

	// Returns true if the domain is a valid choice.
	bool isReachableDomain(size_t index);

	// Returns true if the map is a valid choice.
	bool isReachableMap(size_t domain, size_t index);

	// Updates the gold display.
	void updateGoldDisplay();
};