// ==================================
//
// camera.h
//
// Camera class.
//
// ==================================

#pragma once

#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

class Camera{
public:
	Camera(sf::Vector2f size);
	Camera(sf::Vector2f pos, sf::Vector2f size);

	sf::View GetCamera();
	void SetPosition(sf::Vector2f pos);
	void SetSize(sf::Vector2f size);
	void SetZoom(float cameraZoom);
	void Interpolate(float intlop);

	void GetInput(sf::Event event);
	void Update(float secondsPerUpdate);

private:
	sf::View camera;
	float sensitivty;
	float zoom;
	sf::Vector2f velocity;

	sf::Vector2f currentPos;
	sf::Vector2f futurePos;


};