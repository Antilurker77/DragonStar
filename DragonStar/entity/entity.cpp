// ==================================
//
// entity.cpp
//
// ==================================

#include "entity.h"

Entity::Entity(){
	sprite.setPosition(0, 0);
	destination = { 0, 0 };
}

Entity::Entity(sf::Vector2f spawnPosition, std::string filePath){
	texture = assetManager.LoadTexture(filePath);
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setPosition(spawnPosition);
	destination = spawnPosition;
}

Entity::Entity(sf::Vector3i spawnPosition, std::string filePath){
	texture = assetManager.LoadTexture(filePath);
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setPosition(Hex::HexToPixel(spawnPosition));
	destination = Hex::HexToPixel(spawnPosition);
}

void Entity::Update(float secondsPerUpdate){
	if (sprite.getPosition() != destination){
		sf::Vector2f updatePos = sprite.getPosition();
		velocityPerUpdate.x = velocity.x * secondsPerUpdate;
		velocityPerUpdate.y = velocity.y * secondsPerUpdate;

		// Make sure the entity doesn't overshoot it's destination.
		if (abs(destination.x - sprite.getPosition().x) < abs(velocityPerUpdate.x)){
			updatePos.x = destination.x;
		}
		else {
			updatePos.x += velocityPerUpdate.x;
		}

		// Make sure the entity doesn't overshoot it's destination.
		if (abs(destination.y - sprite.getPosition().y) < abs(velocityPerUpdate.y)){
			updatePos.y = destination.y;
		}
		else {
			updatePos.y += velocityPerUpdate.y;
		}

		sprite.setPosition(updatePos);
	}
	else {
		velocity = { 0, 0 };
		velocityPerUpdate = { 0, 0 };
	}
}

void Entity::Draw(sf::RenderTarget& window, float timeRatio){
	if (IsMoving() == true){
		sf::Vector2f oldPos = sprite.getPosition();
		sf::Vector2f interlopPos = { oldPos.x + velocityPerUpdate.x * timeRatio, oldPos.y + velocityPerUpdate.y * timeRatio };

		// Don't overshoot target destination.
		if (abs(destination.x - oldPos.x) < abs(velocityPerUpdate.x * timeRatio)){
			interlopPos.x = destination.x;
		}
		if (abs(destination.y - oldPos.y) < abs(velocityPerUpdate.y * timeRatio)){
			interlopPos.y = destination.y;
		}
		sprite.setPosition(interlopPos);
		if (IsOnScreen(window)){
			window.draw(sprite);
		}
		sprite.setPosition(oldPos);
	}
	else {
		if (IsOnScreen(window)){
			window.draw(sprite);
		}
	}
}

void Entity::Draw(sf::RenderTarget& window, sf::Vector2f pos, float scale) {
	sf::Vector2f oldPos = sprite.getPosition();
	auto oldScale = sprite.getScale();
	sprite.setPosition(pos);
	sprite.setScale(scale, scale);
	if (IsOnScreen(window)) {
		window.draw(sprite);
	}
	sprite.setPosition(oldPos);
	sprite.setScale(oldScale);
}

sf::Vector2f Entity::GetSize() {
	return sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
}

// Returns the sprite's pixel coordinates.
sf::Vector2f Entity::GetPosition(){
	return sprite.getPosition();
}

// Returns the sprite's hex coordinates based on
// the center of the sprite.
sf::Vector3i Entity::GetHexPosition(){
	sf::Vector2f center = sprite.getPosition();
	center.x += sprite.getTextureRect().width / 2;
	center.y += sprite.getTextureRect().height / 2;
	return Hex::PixelToHex(center);
}

// Check to see if this entity is currently moving.
bool Entity::IsMoving(){
	return (sprite.getPosition() != destination);
}

// Check to see if the sprite is currently on the screen.
bool Entity::IsOnScreen(sf::RenderTarget& window){
	sf::View camera = window.getView();
	sf::FloatRect screen(camera.getCenter().x - camera.getSize().x / 2, camera.getCenter().y - camera.getSize().y / 2, camera.getSize().x, camera.getSize().y);
	sf::FloatRect rect = sprite.getGlobalBounds();
	if (screen.intersects(rect)){
		return true;
	}
	else {
		return false;
	}

}

// Instantly moves the entity to the designated locaiton.
void Entity::Move(sf::Vector2f target){
	destination = target;
	sprite.setPosition(target);
}

// Moves the entity to the designated location. Speed is in units per second.
void Entity::Move(sf::Vector2f target, float unitsPerSecond){
	destination = target;
	speed = unitsPerSecond;

	float distance = sqrt(powf(target.x - sprite.getPosition().x, 2) + powf(target.y - sprite.getPosition().y, 2));
	velocity.x = (unitsPerSecond / distance) * (target.x - sprite.getPosition().x);
	velocity.y = (unitsPerSecond / distance) * (target.y - sprite.getPosition().y);
}

// Instantly moves the entity to the designated hex.
void Entity::MoveToHex(sf::Vector2i target){
	sf::Vector2f movePos = Hex::HexToPixel(sf::Vector2i(target.x, target.y));

	// Offset sprite.
	movePos.x += 64 / 2;
	movePos.x -= sprite.getTextureRect().width / 2;

	movePos.y += 64 / 2;
	movePos.y -= sprite.getTextureRect().height / 2;

	Move(movePos);
}

// Instantly moves the entity to the designated hex.
void Entity::MoveToHex(sf::Vector3i target){
	MoveToHex(sf::Vector2i(target.x, target.z));
}

// Moves the entity to the designated hex. Speed is in units per second.
void Entity::MoveToHex(sf::Vector2i target, float unitsPerSecond){
	sf::Vector2f movePos = Hex::HexToPixel(sf::Vector2i(target.x, target.y));

	// Offset sprite.
	movePos.x += 64 / 2;
	movePos.x -= sprite.getTextureRect().width / 2;

	movePos.y += 64 / 2;
	movePos.y -= sprite.getTextureRect().height / 2;

	Move(movePos, unitsPerSecond);
}

// Moves the entity to the designated hex. Speed is in units per second.
void Entity::MoveToHex(sf::Vector3i target, float unitsPerSecond){
	MoveToHex(sf::Vector2i(target.x, target.z), unitsPerSecond);
}