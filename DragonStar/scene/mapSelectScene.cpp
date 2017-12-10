// ==================================
//
// mapSelectScene.cpp
//
// ==================================

#include "mapSelectScene.h"

#include "../core/assetManager.h"
#include "../core/camera.h"
#include "../core/settings.h"
#include "../core/random.h"

MapSelectScene::MapSelectScene() {
	// node select texture
	nodeTexture = assetManager.LoadTexture("gfx/ui/node/map_nodes.png");
	nodeTexture->setSmooth(false);

	sf::Vector2f buttonSize;

	equipButton.SetString("Equip", 18);
	buttonSize = equipButton.GetSize();
	equipButton.SetPosition(settings.ScreenWidth * 0.25, 8 + buttonSize.y / 2);

	abilityButton.SetString("Set Abilities", 18);
	buttonSize = abilityButton.GetSize();
	abilityButton.SetPosition(settings.ScreenWidth * 0.50, 8 + buttonSize.y / 2);

	shopButton.SetString("Shop", 18);
	buttonSize = shopButton.GetSize();
	shopButton.SetPosition(settings.ScreenWidth * 0.75, 8 + buttonSize.y / 2);

}

void MapSelectScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;
	sf::Mouse mouse;

	windowMousePos = mouse.getPosition(window);
	leftClick = false;
	rightClick = false;

	while (window.pollEvent(ev)) {
		switch (ev.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::MouseButtonReleased:
			if (ev.mouseButton.button == sf::Mouse::Left) {
				leftClick = true;
			}
			if (ev.mouseButton.button == sf::Mouse::Right) {
				rightClick = true;
			}
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			break;
		default:
			break;
		}
	}

}

GameState MapSelectScene::Update(float secondsPerUpdate) {
	GameState gameState = GameState::MAP_SELECT;
	displayFormationTooltip = false;

	if (displayWindow == false) {
		for (size_t i = 0; i < nodeRects.size(); i++) {
			if (leftClick == true && nodeRects[i].getGlobalBounds().contains(windowMousePos.x, windowMousePos.y)) {
				if (displayMaps && isReachableMap(currentDomain, i)) {
					selectedMapNode = maps[currentDomain][i];
					currentMap = i;
					gameState = GameState::BATTLE;
				}
				else if (!displayMaps && isReachableDomain(i)) {
					currentDomain = i;
					currentMapStep = 0;
					displayMaps = true;
					buildVertexArray(maps[currentDomain]);
				}
			}
			else if (nodeRects[i].getGlobalBounds().contains(windowMousePos.x, windowMousePos.y)) {
				if (displayMaps) {
					formationTooltip.SetMapNode(maps[currentDomain][i]);
					sf::Vector2f tooltipSize = formationTooltip.GetSize();
					formationTooltip.SetPosition(windowMousePos.x, windowMousePos.y - tooltipSize.y);
					displayFormationTooltip = true;
					break;
				}
				else {
					formationTooltip.SetMapNode(domains[i], true);
					sf::Vector2f tooltipSize = formationTooltip.GetSize();
					formationTooltip.SetPosition(windowMousePos.x, windowMousePos.y - tooltipSize.y);
					displayFormationTooltip = true;
					break;
				}
			}
		}
	}

	if (equipButton.Update(secondsPerUpdate, windowMousePos) && leftClick && displayWindow == false) {
		displayWindow = true;
		displayEquipWindow = true;
	}

	if (abilityButton.Update(secondsPerUpdate, windowMousePos) && leftClick && displayWindow == false) {
		displayWindow = true;
		displayAbilityWindow = true;
	}

	if (shopButton.Update(secondsPerUpdate, windowMousePos) && leftClick && displayWindow == false) {

	}

	if (displayEquipWindow) {
		displayEquipWindow = equipWindow.Update(secondsPerUpdate, windowMousePos, leftClick, rightClick);
		displayWindow = displayEquipWindow;
	}

	if (displayAbilityWindow) {
		displayAbilityWindow = abilityWindow.Update(secondsPerUpdate, windowMousePos, leftClick, rightClick);
		displayWindow = displayAbilityWindow;
	}

	return gameState;
}

void MapSelectScene::Render(sf::RenderTarget& window, float timeRatio) {
	window.draw(nodeLines);
	window.draw(nodeVertex, nodeTexture);

	if (displayFormationTooltip) {
		formationTooltip.Render(window);
	}

	if (displayWindow == false) {
		equipButton.Render(window);
		abilityButton.Render(window);
		shopButton.Render(window);
	}
	else if (displayEquipWindow) {
		equipWindow.Render(window);
	}
	else if (displayAbilityWindow) {
		abilityWindow.Render(window);
	}
}

void MapSelectScene::SetSeed(uint64_t seed) {
	masterSeed = seed;
	// test
	masterSeed = 0x00000000deadbeef;

	buildDomains();

	if (displayMaps) {
		buildVertexArray(maps[currentDomain]);
	}
	else {
		buildVertexArray(domains);
	}
}

void MapSelectScene::SetParty(std::vector<ActorPtr>& actors) {
	party = actors;

	equipWindow.Initialize(party, inventory);
	abilityWindow.Initialize(party, inventory);
}

std::vector<ActorPtr> MapSelectScene::GetParty() {
	return party;
}

MapNode MapSelectScene::GetSelectedMapNode() {
	return selectedMapNode;
}

void MapSelectScene::CompleteMap(std::vector<ItemPtr> itemsAwarded, unsigned int goldAwarded) {
	gold += goldAwarded;
	for (auto i : itemsAwarded) {
		inventory.push_back(i);
	}

	// add current map to cleared list
	sf::Vector2i v = { currentDomain, currentMap };
	clearedMaps.push_back(v);
	maps[currentDomain][currentMap].IsCleared = true;

	// current domain progression
	if (selectedMapNode.IsBoss) {
		currentMapStep = 0;
		clearedDomains.push_back(currentDomain);
		domains[currentDomain].IsCleared = true;
		currentDomainStep++;
		displayMaps = false;
		buildVertexArray(domains);
	}
	else {
		currentMapStep++;
		buildVertexArray(maps[currentDomain]);
	}
}

void MapSelectScene::buildDomains() {
	domains.clear();
	maps.clear();
	std::mt19937_64 mt(masterSeed);

	// find out how many nodes per step there will be
	std::vector<size_t> nodesPerStep;
	nodesPerStep.resize(6);
	nodesPerStep[0] = 1; // first and last steps always have 1 one node
	nodesPerStep[5] = 1;

	for (size_t i = 1; i < 5; i++) {
		std::uniform_int_distribution<size_t> dist(2, 4);
		nodesPerStep[i] = dist(mt);
	}

	// generate the domain nodes
	// i = step, j = node within step
	for (size_t i = 0; i < nodesPerStep.size(); i++) {
		size_t n = nodesPerStep[i];
		for (size_t j = 0; j < n; j++) {
			MapNode d;
			d.FormationID = FormationID::TEST_BOSS;
			d.Seed = Random::RandSeed(mt);
			//d.Level = i * 4 + 1;
			d.Level = 1;
			d.Tier = std::min(i + 1u, 6u);
			d.Location = { (int)i, (int)j };
			d.IsBoss = true;
			d.NodesInStep = nodesPerStep[i];
			// node connections
			std::vector<size_t> connections;
			if (i < 7) {
				//connections.push_back(i + 1);
				size_t nodeNumber = domains.size();
				connections = calcConnections(nodeNumber, nodesPerStep, i, j);
				
			}

			d.connectedNodes = connections;

			domains.push_back(d);

			// build maps for this domain
			buildMaps(domains.size() - 1, d.Seed);
		}
	}
}

void MapSelectScene::buildMaps(size_t index, uint64_t seed) {
	std::vector<MapNode> mapNodes;
	std::mt19937_64 mt(seed);

	std::vector<FormationWeight> commonFormations = Weight::GetCommonFaWeights(0);
	std::vector<FormationWeight> uniqueFormations = Weight::GetUniqueFaWeights(0);

	// remove uniques that have already spawned
	Weight::RemoveUniqueFa(uniqueFormations, spawnedUniques);

	std::vector<size_t> nodesPerStep;
	std::uniform_int_distribution<size_t> dist(14, 16);
	nodesPerStep.resize(dist(mt));

	for (size_t i = 0; i < nodesPerStep.size(); i++) {
		std::uniform_int_distribution<size_t> dist(1, 3);
		nodesPerStep[i] = dist(mt);
	}

	nodesPerStep.push_back(1);

	for (size_t i = 0; i < nodesPerStep.size() - 1; i++) {
		size_t n = nodesPerStep[i];
		for (int j = 0; j < n; j++) {
			MapNode m;

			// determine formation ID

			// determine if unique
			if (uniqueFormations.size() > 0 && Random::RandDouble(mt, 0.0, 1.0) <= 0.30) {
				m.FormationID = Weight::GetRandomFa(mt, uniqueFormations);
				m.IsUnique = true;
				spawnedUniques.push_back(m.FormationID);
				Weight::RemoveUniqueFa(uniqueFormations, m.FormationID);
			}
			else {
				m.FormationID = Weight::GetRandomFa(mt, commonFormations);
			}

			m.Seed = Random::RandSeed(mt);
			//m.Level = domains[index].Level + std::floor(3.0 * ((double)(i + 1.0) / (double)nodesPerStep.size()));
			m.Level = 1;
			m.Tier = domains[index].Tier;
			m.Location = { (int)i, (int)j };
			m.NodesInStep = n;

			// node connections
			size_t nodeNumber = mapNodes.size();
			m.connectedNodes = calcConnections(nodeNumber, nodesPerStep, i, j);

			mapNodes.push_back(m);
		}
	}

	// add boss node
	MapNode m;
	m.FormationID = domains[index].FormationID;
	//m.Level = domains[index].Level + 3;
	m.Level = 1;
	m.Tier = domains[index].Tier;
	m.Seed = Random::RandSeed(mt);
	m.IsBoss = true;
	m.Location = { (int)nodesPerStep.size() - 1, 0 };
	m.NodesInStep = 1;
	mapNodes.push_back(m);

	maps.push_back(mapNodes);
}

void MapSelectScene::buildVertexArray(std::vector<MapNode>& nodes) {
	nodeVertex.clear();
	nodeRects.clear();
	nodeLines.clear();

	nodeVertex.setPrimitiveType(sf::Quads);
	nodeVertex.resize(nodes.size() * 8);
	nodeRects.reserve(nodes.size());
	nodeLines.setPrimitiveType(sf::Lines);

	const int texSize = 64;

	const int marginX = 8;
	const int marginY = settings.ScreenHeight / 2;

	int i = 0;
	for (auto n : nodes) {
		sf::Vertex* quad = &nodeVertex[i * 4];
		
		int texX = 64; // default blue color nodes
		int texY = 0;

		// determine node color
		if (n.IsCleared) {
			texX = 0;
		}
		else if (n.IsUnique) {
			texX = 128;
		}
		else if (n.IsBoss) {
			texX = 192;
		}

		// position
		int posX = n.Location.x * nodeSize + marginX;
		int posY = n.Location.y * nodeSize + marginY;

		// adjust y based on how many nodes are in this step
		posY -= nodeSize * (n.NodesInStep - 1) / 2;

		// quad cords
		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(posX, posY);
		quad[1].position = sf::Vector2f(posX + texSize, posY);
		quad[2].position = sf::Vector2f(posX + texSize, posY + texSize);
		quad[3].position = sf::Vector2f(posX, posY + texSize);

		// quad texture cords
		// 0  1
		// 3  2
		quad[0].texCoords = sf::Vector2f(texX, texY);
		quad[1].texCoords = sf::Vector2f(texX + texSize, texY);
		quad[2].texCoords = sf::Vector2f(texX + texSize, texY + texSize);
		quad[3].texCoords = sf::Vector2f(texX, texY + texSize);

		// node rectangles
		sf::RectangleShape rect;
		sf::Vector2f size(32.f, 32.f);
		rect.setSize(size);
		rect.setPosition(posX + 16.f, posY + 16.f);
		nodeRects.push_back(rect);

		i++;
	}

	// node borders
	size_t c = 0;
	for (auto n : nodes) {
		sf::Vertex* quad = &nodeVertex[i * 4];

		int texX = 0;
		int texY = 64;

		// determine border color
		
		// if reachable
		if (displayMaps) {
			if (isReachableMap(currentDomain, c)) {
				texX = 64;
			}
		}
		else if (!displayMaps && isReachableDomain(c)) {
			texX = 64;
		}

		// position
		int posX = n.Location.x * nodeSize + marginX;
		int posY = n.Location.y * nodeSize + marginY;

		// adjust y based on how many nodes are in this step
		posY -= nodeSize * (n.NodesInStep - 1) / 2;

		// quad cords
		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(posX, posY);
		quad[1].position = sf::Vector2f(posX + texSize, posY);
		quad[2].position = sf::Vector2f(posX + texSize, posY + texSize);
		quad[3].position = sf::Vector2f(posX, posY + texSize);

		// quad texture cords
		// 0  1
		// 3  2
		quad[0].texCoords = sf::Vector2f(texX, texY);
		quad[1].texCoords = sf::Vector2f(texX + texSize, texY);
		quad[2].texCoords = sf::Vector2f(texX + texSize, texY + texSize);
		quad[3].texCoords = sf::Vector2f(texX, texY + texSize);

		i++;
		c++;
	}

	// lines
	mapConnections.clear();
	if (displayMaps) {
		for (size_t k = 0; k < maps[currentDomain].size(); k++) {
			for (size_t l = 0; l < maps[currentDomain][k].connectedNodes.size(); l++) {
				mapConnections.push_back({k, maps[currentDomain][k].connectedNodes[l] });
			}
		}
	}
	else {
		for (size_t k = 0; k < domains.size(); k++) {
			for (size_t l = 0; l < domains[k].connectedNodes.size(); l++) {
				mapConnections.push_back({ k, domains[k].connectedNodes[l] });
			}
		}
	}

	nodeLines.resize(mapConnections.size() * 2);

	int j = 0;
	for (auto c : mapConnections) {
		sf::Vertex* line = &nodeLines[j * 2];

		// position
		sf::Vector2i loc;
		if (displayMaps) {
			loc = getMapLocation(currentDomain, c.first);
		}
		else {
			loc = getDomainLocation(c.first);
		}

		line[0].position = sf::Vector2f(loc.x, loc.y);
		line[0].color = sf::Color(255, 255, 255, 255);

		if (displayMaps) {
			loc = getMapLocation(currentDomain, c.second);
		}
		else {
			loc = getDomainLocation(c.second);
		}

		line[1].position = sf::Vector2f(loc.x, loc.y);
		line[1].color = sf::Color(255, 255, 255, 255);

		j++;
	}
}

sf::Vector2i MapSelectScene::getDomainLocation(size_t index) {
	sf::Vector2i loc = { domains[index].Location.x, domains[index].Location.y };
	size_t nodesInStep = domains[index].NodesInStep;
	loc.x = loc.x * nodeSize + 8 + 32;
	loc.y = loc.y * nodeSize + settings.ScreenHeight / 2 + 32;

	// adjust y based on how many nodes are in this step
	loc.y -= nodeSize * (nodesInStep - 1) / 2;
	return loc;
}

sf::Vector2i MapSelectScene::getMapLocation(size_t domain, size_t index) {
	sf::Vector2i loc = { maps[domain][index].Location.x, maps[domain][index].Location.y };
	size_t nodesInStep = maps[domain][index].NodesInStep;
	loc.x = loc.x * nodeSize + 8 + 32;
	loc.y = loc.y * nodeSize + settings.ScreenHeight / 2 + 32;

	// adjust y based on how many nodes are in this step
	loc.y -= nodeSize * (nodesInStep - 1) / 2;

	return loc;
}

std::vector<size_t> MapSelectScene::calcConnections(size_t nodeNumber, std::vector<size_t> nodesPerStep, size_t i, size_t j) {
	std::vector<size_t> connections;
	
	switch (nodesPerStep[i + 1]) {
		// next step has one node
	case 1:
		connections.push_back(nodeNumber + nodesPerStep[i] - j);
		break;
		// next step has two nodes
	case 2:
		switch (nodesPerStep[i]) {
		case 1:
			connections.push_back(nodeNumber + 1);
			connections.push_back(nodeNumber + 2);
			break;
		case 2:
			connections.push_back(nodeNumber + 2);
			break;
		case 3:
			switch (j) {
			case 0:
				connections.push_back(nodeNumber + 3);
				break;
			case 1:
				connections.push_back(nodeNumber + 2);
				connections.push_back(nodeNumber + 3);
				break;
			case 2:
				connections.push_back(nodeNumber + 2);
				break;
			default:
				break;
			}
			break;
		case 4:
			switch (j) {
			case 0:
				connections.push_back(nodeNumber + 4);
				break;
			case 1:
				connections.push_back(nodeNumber + 3);
				break;
			case 2:
				connections.push_back(nodeNumber + 3);
				break;
			case 3:
				connections.push_back(nodeNumber + 2);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
		// next step has 3 nodes
	case 3:
		switch (nodesPerStep[i]) {
		case 1:
			connections.push_back(nodeNumber + 1);
			connections.push_back(nodeNumber + 2);
			connections.push_back(nodeNumber + 3);
			break;
		case 2:
			connections.push_back(nodeNumber + 2);
			connections.push_back(nodeNumber + 3);
			break;
		case 3:
			connections.push_back(nodeNumber + 3);
			break;
		case 4:
			switch (j) {
			case 0:
				connections.push_back(nodeNumber + 4);
				break;
			case 1:
				connections.push_back(nodeNumber + 3);
				connections.push_back(nodeNumber + 4);
				break;
			case 2:
				connections.push_back(nodeNumber + 3);
				connections.push_back(nodeNumber + 4);
				break;
			case 3:
				connections.push_back(nodeNumber + 3);
				break;
			}
			break;
		default:
			break;
		}
		break;
		// next step has 4 nodes
	case 4:
		switch (nodesPerStep[i]) {
		case 1:
			connections.push_back(nodeNumber + 1);
			connections.push_back(nodeNumber + 2);
			connections.push_back(nodeNumber + 3);
			connections.push_back(nodeNumber + 4);
			break;
		case 2:
			connections.push_back(nodeNumber + 2 + j);
			connections.push_back(nodeNumber + 3 + j);
			break;
		case 3:
			connections.push_back(nodeNumber + 3);
			connections.push_back(nodeNumber + 4);
			break;
		case 4:
			connections.push_back(nodeNumber + 4);
			break;
		default:
			break;
		}

		break;

	default:
		break;
	}

	return connections;
}

bool MapSelectScene::isReachableDomain(size_t index) {
	// first domain is always accessable at start
	if (currentDomainStep == 0 && domains[index].Location.x == 0 && domains[index].IsCleared == false) {
		return true;
	}

	MapNode testNode = domains[index];

	// check if on right step
	if (testNode.Location.x == currentDomainStep && testNode.IsCleared == false) {
		// check if a cleared domain connects to this node
		for (auto i : clearedDomains) {
			auto connections = domains[i].connectedNodes;
			if (std::find(connections.begin(), connections.end(), index) != connections.end()) {
				return true;
			}
		}
	}

	return false;
}

bool MapSelectScene::isReachableMap(size_t domain, size_t index) {
	// hacky fix for multiple starting nodes
	if (currentMapStep == 0 && maps[domain][index].Location.x == 0 && maps[domain][index].IsCleared == false) {
		return true;
	}

	MapNode testNode = maps[domain][index];

	// check if on right step
	if (testNode.Location.x == currentMapStep && testNode.IsCleared == false) {
		// check if a cleared domain connects to this node
		for (auto i : clearedMaps) {
			if (i.x == currentDomain) {
				auto connections = maps[i.x][i.y].connectedNodes;
				if (std::find(connections.begin(), connections.end(), index) != connections.end()) {
					return true;
				}
			}
		}
	}

	return false;
}