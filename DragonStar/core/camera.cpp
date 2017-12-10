// ==================================
//
// camera.cpp
//
// ==================================

#include "camera.h"

// Default location is left corner at 0, 0.
Camera::Camera(sf::Vector2f size){
	camera.setSize(size);
	camera.setCenter(sf::Vector2f(size.x / 2, size.y / 2));
	futurePos.x = size.x / 2;
	futurePos.y = size.y / 2;
	sensitivty = 600.f;
	zoom = 1.f;
}

// Sets size and center.
Camera::Camera(sf::Vector2f pos, sf::Vector2f size){
	camera.setSize(size);
	camera.setCenter(pos);
	futurePos = pos;
	sensitivty = 600.f;
	zoom = 1.f;
}

// Returns the view.
sf::View Camera::GetCamera(){
	return camera;
}

// Moves the camera to the designated positon.
void Camera::SetPosition(sf::Vector2f pos){
	camera.setCenter(pos);
	futurePos = pos;
}

// Resizes the camera.
void Camera::SetSize(sf::Vector2f size){
	camera.setSize(size);
}

// Sets the camera's zoom.
void Camera::SetZoom(float cameraZoom){
	camera.zoom(cameraZoom);
}

// Checks for input from player.
void Camera::GetInput(sf::Event event){
	camera.setCenter(futurePos);
	currentPos = camera.getCenter();
	velocity = { 0.f, 0.f };

	// Repeats while key is held down.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		velocity.y -= sensitivty * zoom;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		velocity.x += sensitivty * zoom;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		velocity.y += sensitivty * zoom;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		velocity.x -= sensitivty * zoom;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)){
		camera.zoom(1.f / zoom);
		zoom = 1.f;
	}
	if (event.mouseWheelScroll.delta == 1){
		camera.zoom(0.90f);
		zoom *= 0.90f;
	}
	if (event.mouseWheelScroll.delta == -1){
		camera.zoom(1.10f);
		zoom *= 1.10f;
	}
}

// Adjusts camera speed based on how long it takes inbetween frames.
void Camera::Update(float secondsPerUpdate){
	velocity.x = velocity.x * secondsPerUpdate;
	velocity.y = velocity.y * secondsPerUpdate;

	futurePos.x += velocity.x;
	futurePos.y += velocity.y;

}

// Makes camera movement smooth.
void Camera::Interpolate(float intlop){
	camera.setCenter(sf::Vector2f(currentPos.x + velocity.x * intlop, currentPos.y + velocity.y * intlop));
}