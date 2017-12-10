// ==================================
//
// entity.h
//
// Base class for any object that
// appears on the DungeonMap.
//
// ==================================

#pragma once

#include <SFML/Graphics.hpp>
#include "../core/assetManager.h"
#include "../hex/hexMath.h"

class Entity {
public:
	Entity();
	Entity(sf::Vector2f spawnPostion, std::string filePath);
	Entity(sf::Vector3i spawnPostion, std::string filePath);

	virtual void Update(float secondsPerUpdate);
	virtual void Draw(sf::RenderTarget& window, float timeRatio);

	// Draws the entity at the specified position instead of it's own position.
	virtual void Draw(sf::RenderTarget& window, sf::Vector2f pos);

	void Move(sf::Vector2f target);
	void Move(sf::Vector2f target, float unitsPerSecond);

	void MoveToHex(sf::Vector2i target);
	void MoveToHex(sf::Vector2i target, float unitsPerSecond);
	void MoveToHex(sf::Vector3i target);
	void MoveToHex(sf::Vector3i target, float unitsPerSecond);

	sf::Vector2f GetPosition();
	sf::Vector3i GetHexPosition();
	bool IsMoving();
	bool IsOnScreen(sf::RenderTarget& window);

protected:
	sf::Sprite sprite;
	sf::Texture* texture;

	sf::Vector2f velocity;
	sf::Vector2f velocityPerUpdate;
	sf::Vector2f destination;
	float speed;

};