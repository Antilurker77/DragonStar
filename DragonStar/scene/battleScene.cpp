// ==================================
//
// battleScene.cpp
//
// ==================================

#include "battleScene.h"

#include "../command/abilityCommand.h"
#include "../command/moveCommand.h"
#include "../command/waitCommand.h"
#include "../core/camera.h"
#include "../core/random.h"
#include "../core/settings.h"
#include "../data/formation.h"
#include "../data/map.h"
#include "../data/tile.h"
#include "../data/weight.h"
#include "../ui/messageLog.h"

#include <unordered_map>

BattleScene::BattleScene() {
	Factory factory;

	activeActor = nullptr;

	playerGE = Entity(sf::Vector3i(0, 0, 0), "gfx/ui/tile/player_ge.png");
	enemyGE = Entity(sf::Vector3i(0, 0, 0), "gfx/ui/tile/enemy_ge.png");

	// UI Setup
	font = assetManager.LoadFont(settings.Font);
	messageLog.SetFont(settings.Font);
	debugText.setFont(*font);
	debugText.setOutlineThickness(2.f);
	debugText.setCharacterSize(30);
	debugText.setPosition(sf::Vector2f(settings.ScreenWidth / 2, 4));

	// Loads textures.
	selectTileTexture = assetManager.LoadTexture("gfx/ui/tile/select_tile.png");
	selectTileTexture->setSmooth(true);

	currentActorTileTexture = assetManager.LoadTexture("gfx/ui/tile/current_actor_tile.png");
	currentActorTileTexture->setSmooth(true);

	abilityTargetTexture = assetManager.LoadTexture("gfx/ui/tile/ability_target.png");
	abilityTargetTexture->setSmooth(true);

	// Sprites.
	selectTile.setTexture(*selectTileTexture);
	currentActorTile.setTexture(*currentActorTileTexture);
}

void BattleScene::SetCamera(Camera* c) {
	camera = c;
}

void BattleScene::ReadInput(sf::RenderWindow& window) {
	sf::Event ev;

	sf::Mouse mouse;
	windowMousePosition = mouse.getPosition(window);
	worldMousePosition = window.mapPixelToCoords(windowMousePosition, camera->GetCamera());
	leftClick = false;

	command = nullptr;

	// Does not repeat if key is held down.
	while (window.pollEvent(ev)) {
		sf::Vector3i hex = Hex::PixelToHex(worldMousePosition);
		debugText.setString("(" + std::to_string(hex.x) + ", " + std::to_string(hex.y) + ", " + std::to_string(hex.z) + ")");

		switch (ev.type) {

			// Close Button
			case sf::Event::Closed:
				window.close();
				break;

			// Mouse Button
			case sf::Event::MouseButtonPressed:
				// Left Click
				if (ev.mouseButton.button == sf::Mouse::Left) {
					leftClick = true;

					// Opens inspect window if targeting an actor and not using an ability.
					if (!isWindowOpen && !isTargeting) {
						if (IsTileOccupied(hex)) {
							inspectWindow.SetActor(GetActorAtHex(hex));
							isInspectWindowOpen = true;
							isWindowOpen = true;
							break; // stop event polling
						}
					}
					
					// Closes inspect window on left click.
					if (isInspectWindowOpen) {
						isInspectWindowOpen = false;
						isWindowOpen = false;
						break;
					}
					
					// Fire of ability if currently targeting.
					if (isTargeting) {
						command = CommandPtr(std::make_shared<AbilityCommand>(abilityIndex, *this, targetCursor));
						abilityIndex = 0;
						isTargeting = false;
						resetAbilityVertexArray();
					}
				}

			// Right Click
			if (ev.mouseButton.button == sf::Mouse::Right) {
				// Cancel ability if user is targeting.
				if (isTargeting) {
					abilityIndex = 0;
					isTargeting = false;
					resetAbilityVertexArray();
				}
				else if (activeActor != nullptr){
					// If the tile is unoccupied, move the actor towards the location.
					if (IsTileOccupied(hex) == false) {
						command = CommandPtr(new MoveCommand(*this, hex));
					}
					// If the tile has an enemy, initiate Attack.
					else {
						abilityIndex = 0;
						isTargeting = true;
						needToRecalcVertexArray = true;
					}
				}
			}
			break;

			// Keyboard Key Released
			// In the future, keys will be made rebindable.
		case sf::Event::KeyReleased:
			if (!isWindowOpen && activeActor != nullptr) {
				// Wait Command
				if (ev.key.code == settings.BattleKeybinds.Wait) {
					command = CommandPtr(std::make_shared<WaitCommand>(100));
					abilityIndex = 0;
					isTargeting = false;
					resetAbilityVertexArray();
				}

				// Ability Slot 0 -- Attack
				if (ev.key.code == settings.BattleKeybinds.Attack && activeActor->IsAbilityAvailable(0)) {
					abilityIndex = 0;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}


				// Ability Slot 1
				if (ev.key.code == settings.BattleKeybinds.Ability1 && activeActor->IsAbilityAvailable(1)) {
					abilityIndex = 1;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 2
				if (ev.key.code == settings.BattleKeybinds.Ability2 && activeActor->IsAbilityAvailable(2)) {
					abilityIndex = 2;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 3
				if (ev.key.code == settings.BattleKeybinds.Ability3 && activeActor->IsAbilityAvailable(3)) {
					abilityIndex = 3;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 4
				if (ev.key.code == settings.BattleKeybinds.Ability4 && activeActor->IsAbilityAvailable(4)) {
					abilityIndex = 4;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 5
				if (ev.key.code == settings.BattleKeybinds.Ability5 && activeActor->IsAbilityAvailable(5)) {
					abilityIndex = 5;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 6
				if (ev.key.code == settings.BattleKeybinds.Ability6 && activeActor->IsAbilityAvailable(6)) {
					abilityIndex = 6;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 7
				if (ev.key.code == settings.BattleKeybinds.Ability7 && activeActor->IsAbilityAvailable(7)) {
					abilityIndex = 7;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 8
				if (ev.key.code == settings.BattleKeybinds.Ability8 && activeActor->IsAbilityAvailable(8)) {
					abilityIndex = 8;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 9
				if (ev.key.code == settings.BattleKeybinds.Ability9 && activeActor->IsAbilityAvailable(9)) {
					abilityIndex = 9;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 10
				if (ev.key.code == settings.BattleKeybinds.Ability10 && activeActor->IsAbilityAvailable(10)) {
					abilityIndex = 10;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Ability Slot 11 -- Racial
				if (ev.key.code == settings.BattleKeybinds.AbilityRacial && activeActor->IsAbilityAvailable(11)) {
					abilityIndex = 11;
					isTargeting = true;
					needToRecalcVertexArray = true;
				}

				// Debug -- Instantly Kills All Foes
				if (ev.key.code == settings.BattleKeybinds.DebugVictory) {
					for (size_t i = 0; i < actors.size(); i++) {
						if (actors[i]->IsPlayer() == false) {
							actors[i]->ZeroHP();
						}
					}
				}
			}
			if (ev.key.code == sf::Keyboard::Escape) {
				window.close();
			}
			break;
		default:
			break;
		}

		if (!needToRecalcVertexArray) {
			if (lastCursor != hex) {
				needToRecalcVertexArray = true;
			}
		}

		if (isTargeting && needToRecalcVertexArray) {
			if (activeActor != nullptr && activeActor->IsPlayer()) {
				activeActor->SetAbilitySlotWorld(abilityIndex, this);
				sf::Vector3i cursor = hex;
				if (activeActor->IsAbilityAvailable(abilityIndex)) {
					std::vector<sf::Vector3i> targetRange = activeActor->GetAbilityRange(abilityIndex);

					// If the target range is empty, the ability is self-targeted or has no targets.
					// It can be immediately fired off.
					if (targetRange.size() == 0) {
						command = CommandPtr(std::make_shared<AbilityCommand>(abilityIndex, *this, targetCursor));
						abilityIndex = 0;
						isTargeting = false;
						resetAbilityVertexArray();
					}
					// If the cursor isn't in targeting range, find the closest tile in range to the cursor.
					else if (std::find(targetRange.begin(), targetRange.end(), cursor) == targetRange.end()) {
						double bestDistance = 0.0;
						for (size_t i = 0; i < targetRange.size(); i++) {
							sf::Vector2f t = Hex::HexToPixel(targetRange[i]);
							t.x += 32;
							t.y += 14;
							double checkDistance = std::sqrt(std::pow(worldMousePosition.x - t.x, 2) + std::pow(worldMousePosition.y - t.y, 2));
							if (checkDistance < bestDistance || i == 0) {
								bestDistance = checkDistance;
								cursor = targetRange[i];
							}
						}
					}

					if (targetRange.size() > 0) {
						std::vector<sf::Vector3i> targetArea = activeActor->GetAbilityAreaOfEffect(abilityIndex, cursor);

						buildAbilityVertexArray(targetRange, targetArea, activeActor->IsFriendlyAbility(abilityIndex));
					}
				}
				lastCursor = hex;
				targetCursor = cursor;
				needToRecalcVertexArray = false; // disabled to see if performance is an issue (it is)
			}
		}
	}

	camera->GetInput(ev);
}

GameState BattleScene::Update(float secondsPerUpdate) {
	GameState gameState;
	updateWorld(secondsPerUpdate);
	gameState = updateUI(secondsPerUpdate);
	return gameState;
}

void BattleScene::RenderWorld(sf::RenderWindow& window, float timeRatio) {
	currentMap->Draw(window);

	// Draw entites.
	for (unsigned int i = 0; i < entities.size(); i++) {
		entities[i].Draw(window, timeRatio);
	}

	// Draw actors
	for (unsigned int i = 0; i < actors.size(); i++) {
		if (actors[i]->IsAlive()) {
			actors[i]->Draw(window, timeRatio);
		}
	}

	// Draw ground effects.
	// todo: stop drawing the sprite multiple times
	// if multiple auras on same tile
	for (auto ge : groundEffects) {
		if (ge->GetUser()->IsPlayer()) {
			playerGE.MoveToHex(ge->GetPosition());
			playerGE.Draw(window, timeRatio);
		}
		else {
			enemyGE.MoveToHex(ge->GetPosition());
			enemyGE.Draw(window, timeRatio);
		}
	}

	// World UI Elements
	if (!isWindowOpen) {
		window.draw(selectTile);
		if (activeActor != nullptr) {
			window.draw(currentActorTile);
		}
	}
	window.draw(abilityTargetVertexArray, abilityTargetTexture);
}

void BattleScene::RenderUI(sf::RenderWindow& window, float timeRatio) {
	if (!isWindowOpen) {
		if (cursorActor != nullptr) {
			cursorActorHUD.Render(window);
		}

		if (activeActor != nullptr && activeActor->IsPlayer()) {
			abilityBar.Render(window);
		}

		for (auto at : auraTooltips) {
			at.Render(window);
		}

		messageLog.Render(window);
		window.draw(debugText);
	}
	else if (isInspectWindowOpen) {
		inspectWindow.Render(window);
	}
	else if (isVictoryWindowOpen) {
		victoryWindow.Render(window, timeRatio);
	}

}

void BattleScene::Initialize(std::vector<ActorPtr>& players, MapNode mapNode) {
	Factory factory;
	groundEffects.clear();
	actors.clear();
	victory = false;
	defeat = false;
	isVictoryWindowOpen = false;
	isWindowOpen = false;

	seed = mapNode.Seed;
	level = mapNode.Level;
	tier = mapNode.Tier;
	isBoss = mapNode.IsBoss;
	isUnique = mapNode.IsUnique;

	FormationPtr formation = factory.CreateFormation(mapNode.FormationID);
	formation->LevelFactor(mapNode.Level);

	currentMap = factory.CreateMap(formation->GetMapID());

	auto playerStartingLocations = formation->GetStartingLocations();
	for (size_t i = 0; i < players.size(); i++) {
		players[i]->MoveToHex(playerStartingLocations[i]);
		actors.push_back(players[i]);
	}

	auto enemies = formation->GetEnemySpawns();
	for (auto e : enemies) {
		EnemyID id = std::get<0>(e);
		int level = std::get<1>(e) + mapNode.Level;
		sf::Vector2i v = std::get<2>(e);
		sf::Vector3i spawnLocation = { v.x, -v.x - v.y, v.y };
		actors.push_back(ActorPtr(std::make_shared<Enemy>(id, level, spawnLocation)));
	}

	for (size_t i = 0; i < actors.size(); i++) {
		actors[i]->SetAbilitySlotUser();
		actors[i]->SetWorld(this);
	}
}

MapPtr BattleScene::GetMap() {
	return currentMap;
}

void BattleScene::CreateGroundEffect(ActorPtr& user, AuraID auraID, sf::Vector3i location) {
	Factory factory;
	AuraPtr groundEffect = factory.CreateAura(auraID);
	groundEffect->InitializeGroundEffect(user, location);
	groundEffects.push_back(groundEffect);
}

std::vector<sf::Vector3i> BattleScene::Pathfind(ActorPtr& actor, sf::Vector3i destination) {
	std::vector<sf::Vector3i> path;
	std::vector<std::pair<sf::Vector3i, double>> frontier;
	std::unordered_map<sf::Vector3i, sf::Vector3i> cameFrom;
	std::unordered_map<sf::Vector3i, double> costSoFar;
	sf::Vector3i start = actor->GetHexPosition();
	bool flying = actor->CanFly();
	bool swimming = actor->CanSwim();
	bool isPlayer = actor->IsPlayer();
	int moves = 2;

	frontier.push_back(std::pair<sf::Vector3i, double>(start, 0));
	cameFrom[start] = start;
	costSoFar[start] = 0;

	enum class LineType {
		NegativeOnly,
		PositiveOnly,
		Both
	};

	while (!frontier.empty()) {
		// sorts the frontier
		std::sort(frontier.begin(), frontier.end(),
			[](const std::pair<sf::Vector3i, double>& lhs, const std::pair<sf::Vector3i, double>& rhs) {
			return lhs.second < rhs.second;
		}
		);

		auto current = frontier.front().first;

		if (current == destination) {
			break;
		}


		// Get neighbors of the current tile the actor can actually travel to.
		// Don't include tiles that are occupied by another actor.
		std::vector<sf::Vector3i> neighbors = Hex::GetHexNeighbors(current, moves);
		std::vector<sf::Vector3i> goodNeighbors;
		std::vector<LineType> neighborLineType;

		for (size_t i = 0; i < neighbors.size(); i++) {
			Tile tile = currentMap->GetTile(neighbors[i]);
			if (IsTileWalkable(neighbors[i], flying, swimming)) {
				if (IsTileOccupied(neighbors[i]) == false) {
					// Need to test offsets for both lines.
					auto line = Hex::HexLine(current, neighbors[i], false);
					bool passableN = true;
					for (auto t : line) {
						if (t != current && t != neighbors[i]) {
							if (IsTileWalkable(t, flying, swimming)) {
								auto actorOnTile = GetActorAtHex(t);
								if (actorOnTile != nullptr) {
									bool actorOnTileFlying = actorOnTile->CanFly();
									bool actorOnTilePlayer = actorOnTile->IsPlayer();

									// Flying actors can fly over non-flying actors.
									if (flying && !actorOnTileFlying) {
										passableN = true;
									}
									// Can pass by allies.
									else if (isPlayer == actorOnTilePlayer) {
										passableN = true;
									}
									else {
										passableN = false;
										break;
									}
								}
							}
							else {
								passableN = false;
								break;
							}
						}
					}

					// Check other line.
					bool passableP = true;
					line = Hex::HexLine(current, neighbors[i], true);
					for (auto t : line) {
						if (t != current && t != neighbors[i]) {
							if (IsTileWalkable(t, flying, swimming)) {
								auto actorOnTile = GetActorAtHex(t);
								if (actorOnTile != nullptr) {
									bool actorOnTileFlying = actorOnTile->CanFly();
									bool actorOnTilePlayer = actorOnTile->IsPlayer();

									// Flying actors can fly over non-flying actors.
									if (flying && !actorOnTileFlying) {
										passableP = true;
									}
									// Can pass by allies.
									else if (isPlayer == actorOnTilePlayer) {
										passableP = true;
									}
									else {
										passableP = false;
										break;
									}
								}
							}
							else {
								passableP = false;
								break;
							}
						}
					}
					
					// Pass on valid offsets.
					if (passableN || passableP) {
						goodNeighbors.push_back(neighbors[i]);
						if (passableN && passableP) {
							neighborLineType.push_back(LineType::Both);
						}
						else if (passableN) {
							neighborLineType.push_back(LineType::NegativeOnly);
						}
						else {
							neighborLineType.push_back(LineType::PositiveOnly);
						}
					}
				}
			}
		}

		// Not even gonna pretend I understand this.
		for (size_t i = 0; i < goodNeighbors.size(); i++) {
			auto next = goodNeighbors[i];
			auto offsets = neighborLineType[i];
			double newCost = 0.0;
			bool offset = false;

			// Figure out which offset leads to the cheapest path.
			if (offsets == LineType::NegativeOnly) {
				newCost = costSoFar[current] + currentMap->DistanceHeuristic(current, next, false);
				offset = false;
			}
			else if (offsets == LineType::PositiveOnly) {
				newCost = costSoFar[current] + currentMap->DistanceHeuristic(current, next, true);
				offset = true;
			}
			else {
				double costN = costSoFar[current] + currentMap->DistanceHeuristic(current, next, false);
				double costP = costSoFar[current] + currentMap->DistanceHeuristic(current, next, true);
				newCost = std::min(costN, costP);
				offset = costN > costP;
			}

			if (!costSoFar.count(next) || newCost < costSoFar[next]) {
				costSoFar[next] = newCost;
				double priority = newCost + currentMap->DistanceHeuristic(next, destination, offset);
				cameFrom[next] = current;
				frontier.push_back(std::pair<sf::Vector3i, double>(next, priority));
			}
		}

		frontier.erase(frontier.begin());
	}

	// Create the vector and return the path.
	sf::Vector3i current = destination;
	path.push_back(current);

	while (current != sf::Vector3i(start)) {
		auto i = cameFrom.find(current);
		if (i != cameFrom.end()) { // Prevents path from adding destination if no path exists.
			current = i->second; // cameFrom[current]
		}
		else {
			return std::vector<sf::Vector3i>();
		}
		path.push_back(current);
	}

	std::reverse(path.begin(), path.end());
	path.erase(path.begin());

	return path;
}

double BattleScene::GetPathCost(ActorPtr& actor, std::vector<sf::Vector3i>& path) {
	double cost = currentMap->GetTile(path[0]).MoveMod;
	auto position = actor->GetHexPosition();
	for (size_t i = 1; i < path.size(); i++) {
		actor->MoveToHex(path[i - 1]); // so hacky
		cost += GetMoveCost(actor, path[i]);
	}
	actor->MoveToHex(position);
	return cost;
}

double BattleScene::GetMoveCost(ActorPtr& actor, sf::Vector3i destination) {
	double costN = 0.0;
	double costP = 0.0;

	auto current = actor->GetHexPosition();
	bool flying = actor->CanFly();
	bool swimming = actor->CanSwim();
	bool isPlayer = actor->IsPlayer();

	auto line = Hex::HexLine(current, destination, false);
	bool passableN = true;
	for (auto t : line) {
		if (t != current && t != destination) {
			if (IsTileWalkable(t, flying, swimming)) {
				auto actorOnTile = GetActorAtHex(t);
				if (actorOnTile != nullptr) {
					bool actorOnTileFlying = actorOnTile->CanFly();
					bool actorOnTilePlayer = actorOnTile->IsPlayer();

					// Flying actors can fly over non-flying actors.
					if (flying && !actorOnTileFlying) {
						passableN = true;
					}
					// Can pass by allies.
					else if (isPlayer == actorOnTilePlayer) {
						passableN = true;
					}
					else {
						passableN = false;
						break;
					}
				}
			}
			else {
				passableN = false;
				break;
			}
		}
	}

	for (auto t : line) {
		if (t != current) {
			costN += currentMap->GetTile(t).MoveMod;
		}
	}

	// Check other line.
	bool passableP = true;
	line = Hex::HexLine(current, destination, true);
	for (auto t : line) {
		if (t != current && t != destination) {
			if (IsTileWalkable(t, flying, swimming)) {
				auto actorOnTile = GetActorAtHex(t);
				if (actorOnTile != nullptr) {
					bool actorOnTileFlying = actorOnTile->CanFly();
					bool actorOnTilePlayer = actorOnTile->IsPlayer();

					// Flying actors can fly over non-flying actors.
					if (flying && !actorOnTileFlying) {
						passableP = true;
					}
					// Can pass by allies.
					else if (isPlayer == actorOnTilePlayer) {
						passableP = true;
					}
					else {
						passableP = false;
						break;
					}
				}
			}
			else {
				passableP = false;
				break;
			}
		}
	}

	for (auto t : line) {
		if (t != current) {
			costP += currentMap->GetTile(t).MoveMod;
		}
	}

	if (passableN && !passableP) {
		return costN;
	}
	else if (passableP && !passableN) {
		return costP;
	}
	else {
		return std::min(costN, costP);
	}
}

bool BattleScene::IsTileOccupied(sf::Vector3i tile) {
	for (size_t i = 0; i < actors.size(); i++) {
		if (tile == actors[i]->GetHexPosition() && actors[i]->IsAlive()) {
			return true;
		}
	}
	return false;
}

bool BattleScene::IsTileOccupied(sf::Vector2i tile) {
	return IsTileOccupied(sf::Vector3i(tile.x, -tile.x - tile.y, tile.y));
}

bool BattleScene::IsTileOpeque(sf::Vector3i tile) {
	return currentMap->GetTile(tile).IsOpaque;
}

bool BattleScene::IsTileWalkable(sf::Vector3i tile, bool canFly, bool canSwim) {
	Tile t = currentMap->GetTile(tile);
	return t.IsPassible == true || (t.IsWater == true && canSwim == true) || (t.IsFlyable == true && canFly == true);
}

std::vector<sf::Vector3i> BattleScene::GetLineOfSight(sf::Vector3i origin, std::vector<sf::Vector3i> tiles, bool isPlayer, bool ignoreBodyBlock, bool ignoreLineOfSight) {
	// if it ignores line of sight, just return the original area
	if (ignoreLineOfSight) {
		return tiles;
	}

	std::vector<sf::Vector3i> result = {};

	for (size_t i = 0; i < tiles.size(); i++) {
		bool goodTile = true;

		std::vector<sf::Vector3i> line = Hex::HexLine(origin, tiles[i], false);
		for (size_t j = 0; j < line.size(); j++) {
			// tile is blocked if any tile in line is opeque
			Tile tile = currentMap->GetTile(line[j]);
			if (tile.IsOpaque) {
				goodTile = false;
				break; // don't need to check the rest of the line
			}
			// check if enemies can block line of sight
			// does not care if enemy is at end of tile
			if (goodTile && !ignoreBodyBlock && (line[j] != tiles[i])) {
				for (size_t k = 0; k < actors.size(); k++) {
					if (actors[k]->GetHexPosition() == line[j] && isPlayer != actors[k]->IsPlayer() && actors[k]->IsAlive()) {
						goodTile = false;
						break;
					}
				}
			}
		}
		// need to check lines with both offsets for symmetry
		line = Hex::HexLine(origin, tiles[i], true);
		for (size_t j = 0; j < line.size(); j++) {
			// tile is blocked if any tile in line is opeque
			Tile tile = currentMap->GetTile(line[j]);
			if (tile.IsOpaque) {
				goodTile = false;
				break; // don't need to check the rest of the line
			}
			// check if enemies can block line of sight
			// does not care if enemy is at end of tile
			if (goodTile && !ignoreBodyBlock && (line[j] != tiles[i])) {
				for (size_t k = 0; k < actors.size(); k++) {
					if (actors[k]->GetHexPosition() == line[j] && isPlayer != actors[k]->IsPlayer() && actors[k]->IsAlive()) {
						goodTile = false;
						break;
					}
				}
			}
		}
		if (goodTile) {
			result.push_back(tiles[i]);
		}
	}

	return result;
}

bool BattleScene::InLineOfSight(sf::Vector3i start, sf::Vector3i end, bool isPlayer, bool ignoreBodyBlock) {
	bool inLineOfSight = true;

	std::vector<sf::Vector3i> line = Hex::HexLine(start, end, false);
	for (size_t j = 0; j < line.size(); j++) {
		// tile is blocked if any tile in line is opeque
		Tile tile = currentMap->GetTile(line[j]);
		if (tile.IsOpaque) {
			inLineOfSight = false;
			break; // don't need to check the rest of the line
		}
		// check if enemies can block line of sight
		// does not care if enemy is at end of tile
		if (inLineOfSight && !ignoreBodyBlock && (line[j] != end)) {
			for (size_t k = 0; k < actors.size(); k++) {
				if (actors[k]->GetHexPosition() == line[j] && isPlayer != actors[k]->IsPlayer() && actors[k]->IsAlive()) {
					inLineOfSight = false;
					break;
				}
			}
		}
	}
	// need to check lines with both offsets for symmetry
	line = Hex::HexLine(start, end, true);
	for (size_t j = 0; j < line.size(); j++) {
		// tile is blocked if any tile in line is opeque
		Tile tile = currentMap->GetTile(line[j]);
		if (tile.IsOpaque) {
			inLineOfSight = false;
			break; // don't need to check the rest of the line
		}
		// check if enemies can block line of sight
		// does not care if enemy is at end of tile
		if (inLineOfSight && !ignoreBodyBlock && (line[j] != end)) {
			for (size_t k = 0; k < actors.size(); k++) {
				if (actors[k]->GetHexPosition() == line[j] && isPlayer != actors[k]->IsPlayer() && actors[k]->IsAlive()) {
					inLineOfSight = false;
					break;
				}
			}
		}
	}

	return inLineOfSight;
}

std::vector<ActorPtr> BattleScene::GetPlayers(bool aliveOnly) {
	std::vector<ActorPtr> results;
	for (auto a : actors) {
		if (a->IsPlayer()) {
			if (!aliveOnly || a->IsAlive() == aliveOnly) {
				results.push_back(a);
			}
		}
	}
	return results;
}

std::vector<ActorPtr> BattleScene::GetEnemies(bool aliveOnly) {
	std::vector<ActorPtr> results;
	for (auto a : actors) {
		if (!a->IsPlayer()) {
			if (!aliveOnly || a->IsAlive() == aliveOnly) {
				results.push_back(a);
			}
		}
	}
	return results;
}

ActorPtr BattleScene::GetActorAtHex(sf::Vector3i hex) {
	for (size_t i = 0; i < actors.size(); i++) {
		if (actors[i]->IsAlive() && actors[i]->GetHexPosition() == hex) {
			return actors[i];
		}
	}

	return nullptr;
}

std::vector<ActorPtr> BattleScene::GetAbilityTargets(std::vector<sf::Vector3i> targetArea, bool isFriendlySpell, bool isPlayer) {
	std::vector<ActorPtr> targets = {};

	if (isPlayer) {
		if (isFriendlySpell) {
			for (size_t i = 0; i < actors.size(); i++) {
				if (std::find(targetArea.begin(), targetArea.end(), actors[i]->GetHexPosition()) != targetArea.end()) {
					if (isPlayer == actors[i]->IsPlayer() && actors[i]->IsAlive()) {
						targets.push_back(actors[i]);
					}
				}
			}
		}
		else {
			for (size_t i = 0; i < actors.size(); i++) {
				if (std::find(targetArea.begin(), targetArea.end(), actors[i]->GetHexPosition()) != targetArea.end()) {
					if (isPlayer != actors[i]->IsPlayer() && actors[i]->IsAlive()) {
						targets.push_back(actors[i]);
					}
				}
			}
		}
	}
	else {
		if (isFriendlySpell) {
			for (size_t i = 0; i < actors.size(); i++) {
				if (std::find(targetArea.begin(), targetArea.end(), actors[i]->GetHexPosition()) != targetArea.end()) {
					if (isPlayer == actors[i]->IsPlayer() && actors[i]->IsAlive()) {
						targets.push_back(actors[i]);
					}
				}
			}
		}
		else {
			for (size_t i = 0; i < actors.size(); i++) {
				if (std::find(targetArea.begin(), targetArea.end(), actors[i]->GetHexPosition()) != targetArea.end()) {
					if (isPlayer != actors[i]->IsPlayer() && actors[i]->IsAlive()) {
						targets.push_back(actors[i]);
					}
				}
			}
		}
	}

	return targets;
}

std::vector<AuraPtr> BattleScene::GetGroundEffectsAtHex(sf::Vector3i position, bool isPlayer) {
	std::vector<AuraPtr> results;

	for (auto ge : groundEffects) {
		if (ge->GetPosition() == position) {
			// make sure actor respects buff / debuff targeting
			ActorPtr a = ge->GetUser();
			if ((ge->IsBuff() && isPlayer == a->IsPlayer()) || (!ge->IsBuff() && isPlayer != a->IsPlayer())) {
				results.push_back(ge);
			}
		}
	}

	return results;
}

unsigned int BattleScene::GetGoldAwared() {
	return goldAwarded;
}

std::vector<ItemPtr> BattleScene::GetItemsAwarded() {
	return itemsAwarded;
}

void BattleScene::updateWorld(float secondsPerUpdate) {
	bool movingActor = false;
	bool casted = false;

	for (size_t i = 0; i < entities.size(); i++) {
		entities[i].Update(secondsPerUpdate);
	}

	for (size_t i = 0; i < actors.size(); i++) {
		actors[i]->Update(secondsPerUpdate);
		if (actors[i]->IsMoving()) {
			movingActor = true;
		}
	}

	if (!defeat) {
		defeat = checkDefeat();
	}

	// losing takes priority over winning
	if (!defeat && !victory) {
		victory = checkVictory();

		// award items and exp
		if (victory) {
			calcVictory();
		}
	}

	// don't update actors if victory or defeat has been achieved
	if (!victory && !defeat) {

		// Check to see if any actors are standing in ground effects.
		// Check to see if any actors have finished casting.
		if (movingActor == false) {
			for (auto ge : groundEffects) {
				ge->ClearTarget();
				for (auto a : actors) {
					if (ge->GetPosition() == a->GetHexPosition()) {
						bool player = ge->GetUser()->IsPlayer();

						// make sure actor respects buff / debuff targeting
						if ((ge->IsBuff() && player == a->IsPlayer()) || (!ge->IsBuff() && player != a->IsPlayer())) {
							ge->SetTarget(a);
						}
						break;
					}
				}
			}

			for (size_t j = 0; j < actors.size(); j++) {
				if (actors[j]->IsCastReady()) {
					activeActor = actors[j];
					command = CommandPtr(std::make_shared<AbilityCommand>(activeActor->GetCastIndex(), *this, activeActor->GetTargetCursor()));
					casted = true;
					break; // Stop looking for an actor if one is found.
				}
			}
		}

		// Checks if an enemy is an active actor.
		// If an enemy is ready, get their action.
		// AI command overwrites user input.
		if (movingActor == false && activeActor != nullptr && activeActor->IsPlayer() == false && casted == false) {
			Enemy* activeEnemy = (Enemy*)activeActor.get();
			command = activeEnemy->CalcAICommand(*this);
		}

		// Code block determining who's turn it is.
		// Waits until all actors have finished moving.
		if (movingActor == false && activeActor == nullptr) {
			int exhaustPerUpdate = 200 * secondsPerUpdate;

			command = nullptr; // stops player input commands from being immediately applied to a recently found active actor

			for (int i = 0; i < exhaustPerUpdate; i++) {

				// remove groundEffects that have expired
				if (groundEffects.size() > 0) {
					const auto pred = [](const AuraPtr& a) { return a->IsExpired(); };
					groundEffects.erase(std::remove_if(groundEffects.begin(), groundEffects.end(), pred), groundEffects.end());
				}

				for (size_t j = 0; j < actors.size(); j++) {
					if (actors[j]->GetExhaustion() == 0 && actors[j]->IsAlive()) {
						activeActor = actors[j];
						break; // Stop looking for an active actor if one is found.
					}
				}

				// If no actor is ready, decrement exhaustion.
				if (activeActor == nullptr) {
					for (size_t j = 0; j < actors.size(); j++) {
						if (actors[j]->IsAlive()) {
							actors[j]->DecrementExhaustion();
						}
					}

					for (auto ge : groundEffects) {
						ge->Tick();
					}
				}

				// Remove expired auras. Done after auras tick so that
				// the last tick doesn't get cut off.
				for (auto a : actors) {
					a->RemoveExpiredAuras();
				}

				// Stops dead actors from taking a turn, since OnExpiry()
				// can kill them.
				if (activeActor != nullptr && activeActor->IsAlive() == false) {
					activeActor = nullptr;
				}
			}
		}
		if (movingActor == false && command != nullptr && activeActor != nullptr) {
			command->Execute(activeActor);
			if (activeActor->GetExhaustion() > 0 || casted) {
				activeActor = nullptr;
			}
			command = nullptr;
		}
	}
}

GameState BattleScene::updateUI(float secondsPerUpdate) {
	GameState gameState = GameState::BATTLE;
	
	messageLog.Update();

	mouseTile = Hex::PixelToHex(worldMousePosition);
	sf::Vector2f selectPos = Hex::HexToPixel(mouseTile);
	//selectPos.x -= (256 - 204) / 2;
	//selectPos.y -= (256 - 176) / 2;
	selectTile.setPosition(selectPos);

	// current actor tile
	if (activeActor != nullptr) {
		sf::Vector2f actorHexPos = Hex::HexToPixel(activeActor->GetHexPosition());
		currentActorTile.setPosition(actorHexPos);
	}

	// abilityBar
	abilityBar.SetPosition(settings.ScreenWidth, settings.ScreenHeight);

	// cursorActorHUD
	cursorActor = GetActorAtHex(sf::Vector3i(mouseTile.x, -mouseTile.z - mouseTile.x, mouseTile.z));

	// inspect window
	if (isInspectWindowOpen) {
		inspectWindow.Update(windowMousePosition);
	}

	// victory window

	if (isVictoryWindowOpen && leftClick) {
		isVictoryWindowOpen = false;
		isWindowOpen = false;
		gameState = GameState::MAP_SELECT;
	}

	if (victory && !isVictoryWindowOpen) {
		std::vector<ActorPtr> players = GetPlayers(false);
		victoryWindow.Initialize(expAwarded, goldAwarded, itemsAwarded, players);
		isVictoryWindowOpen = true;
		isWindowOpen = true;
	}

	if (isVictoryWindowOpen) {
		victoryWindow.Update(secondsPerUpdate, windowMousePosition);
	}

	// ground effect tooltips
	auraTooltips.clear();

	int y = settings.ScreenHeight;
	for (auto ge : groundEffects){
		if (ge->GetPosition() == mouseTile) {
			AuraTooltip at;
			at.SetAura(ge);
			sf::Vector2f tooltipSize = at.GetSize();
			at.SetPosition(settings.ScreenWidth - tooltipSize.x - 4, y - tooltipSize.y - 4);
			y -= tooltipSize.y + 4; // so tooltips stack properly
			auraTooltips.push_back(at);
		}
	}

	if (cursorActor != nullptr) {
		cursorActorHUD.Update(cursorActor, settings.ScreenWidth, settings.ScreenHeight);
	}

	std::string activeName;
	if (activeActor != nullptr && activeActor->IsPlayer()) {
		abilityBar.SetIcons(activeActor);
		abilityBar.Update(activeActor, windowMousePosition);
	}

	return gameState;
}

void BattleScene::buildAbilityVertexArray(std::vector<sf::Vector3i> range, std::vector<sf::Vector3i> area, bool isHelpfulAbility) {
	// Remove tiles from range so that area and range
	// aren't drawn on top of each other.
	std::vector<sf::Vector3i> rangeToDraw = range;
	for (size_t i = 0; i < area.size(); i++) {
		sf::Vector3i test = area[i];
		rangeToDraw.erase(std::remove(rangeToDraw.begin(), rangeToDraw.end(), area[i]), rangeToDraw.end());
	}

	// Create the vertex array
	abilityTargetVertexArray.setPrimitiveType(sf::Quads);
	abilityTargetVertexArray.resize(rangeToDraw.size() * 4 + area.size() * 4);

	int hexWidth = 64;
	int hexHeight = 56;

	int tileSize = 64;

	// Range
	int i = 0;

	for (const auto &tile : rangeToDraw) {
		int texX = 0;
		int texY = 0;

		sf::Vertex* quad = &abilityTargetVertexArray[i * 4];

		int col = tile.x;
		int row = tile.z;

		int posX = col * (hexWidth * 3 / 4) - (hexWidth / 2) - (tileSize - hexWidth) / 2;
		int posY = row * hexHeight + col * (hexHeight / 2) - (hexHeight / 2) - (tileSize - hexHeight) / 2;

		// quad cords
		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(posX, posY);
		quad[1].position = sf::Vector2f(posX + tileSize, posY);
		quad[2].position = sf::Vector2f(posX + tileSize, posY + tileSize);
		quad[3].position = sf::Vector2f(posX, posY + tileSize);

		// quad texture cords
		// 0  1
		// 3  2
		quad[0].texCoords = sf::Vector2f(texX, texY);
		quad[1].texCoords = sf::Vector2f(texX + tileSize, texY);
		quad[2].texCoords = sf::Vector2f(texX + tileSize, texY + tileSize);
		quad[3].texCoords = sf::Vector2f(texX, texY + tileSize);

		i++;
	}

	// Area

	for (const auto &tile : area) {
		int texX = 0;
		int texY = 0;

		if (!isHelpfulAbility) {
			texX = tileSize;
			texY = 0;
		}
		else {
			texX = 0;
			texY = tileSize;
		}

		sf::Vertex* quad = &abilityTargetVertexArray[i * 4];

		int col = tile.x;
		int row = tile.z;

		int posX = col * (hexWidth * 3 / 4) - (hexWidth / 2) - (tileSize - hexWidth) / 2;
		int posY = row * hexHeight + col * (hexHeight / 2) - (hexHeight / 2) - (tileSize - hexHeight) / 2;

		// quad cords
		// 0  1
		// 3  2
		quad[0].position = sf::Vector2f(posX, posY);
		quad[1].position = sf::Vector2f(posX + tileSize, posY);
		quad[2].position = sf::Vector2f(posX + tileSize, posY + tileSize);
		quad[3].position = sf::Vector2f(posX, posY + tileSize);

		// quad texture cords
		// 0  1
		// 3  2
		quad[0].texCoords = sf::Vector2f(texX, texY);
		quad[1].texCoords = sf::Vector2f(texX + tileSize, texY);
		quad[2].texCoords = sf::Vector2f(texX + tileSize, texY + tileSize);
		quad[3].texCoords = sf::Vector2f(texX, texY + tileSize);

		i++;
	}
}

void BattleScene::resetAbilityVertexArray() {
	abilityTargetVertexArray.clear();
}

bool BattleScene::checkVictory() {
	return GetEnemies(true).empty();
}

bool BattleScene::checkDefeat() {
	return GetPlayers(true).empty();
}

void BattleScene::calcVictory() {
	std::mt19937_64 mt(seed);
	Factory factory;

	unsigned int exp = 0u;
	unsigned int gold = 0u;
	unsigned int lootPoints = 0u;
	itemsAwarded.clear();
	double goldMult = 0.0;

	// Get Gold and EXP
	std::vector<ActorPtr> enemies = GetEnemies(false);
	for (auto e : enemies) {
		exp += e->GetEXPDrop();
		gold += e->GetGoldDrop();
		lootPoints += e->GetLootPoints();
	}

	// Awarp EXP and calc Gold Find
	std::vector<ActorPtr> players = GetPlayers(false);
	for (size_t i = 0; i < players.size(); i++) {
		//players[i]->GrantEXP(exp);
		goldMult += players[i]->GetGoldFind(true);
		players[i]->FullHeal();
	}

	expAwarded = exp;
	goldAwarded = gold * (1.0 + goldMult);

	// Items
	while (lootPoints > 0u) {
		std::uniform_int_distribution<unsigned int> dist(0u, 99u);
		if (dist(mt) < lootPoints) {
			if (lootPoints < 100u) {
				lootPoints = 0u;
			}
			else {
				lootPoints -= 100u;
			}

			// Generate the item.
			if (dist(mt) >= 70u){
				AbilityID id = Weight::GetRandomAb(mt, tier);
				ItemPtr item = factory.CreateAbilityScroll(id);
				itemsAwarded.push_back(item);
			}
			else {
				ItemQuality quality;
				unsigned int qualRoll = dist(mt);
				if (qualRoll >= 90u) {
					quality = ItemQuality::MYTHIC;
				}
				else if (qualRoll >= 60u) {
					quality = ItemQuality::RARE;
				}
				else if (qualRoll >= 20u) {
					quality = ItemQuality::MAGICAL;
				}
				else {
					quality = ItemQuality::COMMON;
				}

				EquipmentID id = Weight::GetRandomEq(mt, tier);
				ItemPtr item = factory.CreateEquipment(id);
				Equipment* eq = (Equipment*)item.get();
				eq->RollStatMods(quality, Random::RandSeed(mt));
				itemsAwarded.push_back(item);
			}
		}
	}

	//EquipmentID id = EquipmentID::OMEGA_RING;
	//ItemPtr item = factory.CreateEquipment(id);
	//itemsAwarded.push_back(item);
}