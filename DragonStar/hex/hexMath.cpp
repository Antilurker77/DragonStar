// ==================================
//
// hexMath.cpp
//
// ==================================

#include "hexMath.h"

// Offsets a hex.
sf::Vector3i Hex::OffsetHex(sf::Vector3i coords, sf::Vector3i offset){
	return sf::Vector3i(coords.x + offset.x, coords.y + offset.y, coords.z + offset.z);
}

sf::Vector3i Hex::HexDifference(sf::Vector3i a, sf::Vector3i b) {
	return sf::Vector3i(a.x - b.x, a.y - b.y, a.z - b.z);
}

// Rounds a set of three floats to the nearest hex.
sf::Vector3i Hex::RoundHex(sf::Vector3f hex){
	int rx = roundf(hex.x);
	int ry = roundf(hex.y);
	int rz = roundf(hex.z);

	float xDiff = abs(rx - hex.x);
	float yDiff = abs(ry - hex.y);
	float zDiff = abs(rz - hex.z);

	if (xDiff > yDiff && xDiff > zDiff){
		rx = -ry - rz;
	}
	else if (yDiff > zDiff){
		ry = -rx - rz;
	}
	else {
		rz = -rx - ry;
	}

	return sf::Vector3i(rx, ry, rz);
}

// Returns the distance between two hexes.
int Hex::HexDistance(sf::Vector3i start, sf::Vector3i end){
	return std::max({ abs(start.x - end.x), abs(start.y - end.y), abs(start.z - end.z) });
}

// Hex linear interpolation, what ever that means.
sf::Vector3f Hex::HexLinearInterpolation(sf::Vector3i hexA, sf::Vector3i hexB, float t){
	return sf::Vector3f(hexA.x + (hexB.x - hexA.x) * t, hexA.y + (hexB.y - hexA.y) * t, hexA.z + (hexB.z - hexA.z) * t);
}

// Returns a vector containing the coordinates for a filled hexagon with the specified center and radius.
std::vector<sf::Vector3i> Hex::FilledHexagon(sf::Vector3i center, int radius){
	std::vector<sf::Vector3i> result;

	for (int dx = -radius; -radius <= dx && dx <= radius; dx++){
		for (int dy = std::max(-radius, -dx - radius); std::max(-radius, -dx - radius) <= dy && dy <= std::min(radius, -dx + radius); dy++){
			int dz = -dx - dy;
			result.push_back(Hex::OffsetHex(sf::Vector3i(dx, dy, dz), center));
		}
	}

	return result;
}

std::vector<sf::Vector3i> Hex::HexRing(sf::Vector3i center, int radius) {
	std::vector<sf::Vector3i> result;
	result.reserve(radius * 6);

	const std::vector<sf::Vector3i> directions = { sf::Vector3i(1, 0, -1), sf::Vector3i(1, -1, 0), sf::Vector3i(0, -1, 1), sf::Vector3i(-1, 0, 1), sf::Vector3i(-1, 1, 0), sf::Vector3i(0, 1, -1) };

	sf::Vector3i hex(center.x + (directions[4].x * radius), center.y + (directions[4].y * radius), center.z + (directions[4].z * radius));

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < radius; j++) {
			result.push_back(hex);
			hex = hex + directions[i];
		}
	}

	return result;
}

std::vector<sf::Vector3i> Hex::HexLine(sf::Vector3i start, sf::Vector3i end) {
	return Hex::HexLine(start, end, false);
}

// Returns a vector containing the coordinates for a line.
std::vector<sf::Vector3i> Hex::HexLine(sf::Vector3i start, sf::Vector3i end, bool positiveOffset){
	int distance = Hex::HexDistance(start, end);

	std::vector<sf::Vector3i> result;
	result.reserve(distance);

	//for (int i = 0; i <= distance; i++){
	//	result.push_back(Hex::RoundHex(Hex::HexLinearInterpolation(start, end, 1.0 / distance * i)));
	//}

	for (int i = 0; i <= distance; i++) {
		sf::Vector3f hex = Hex::HexLinearInterpolation(start, end, 1.0 / distance * i);
		if (positiveOffset) {
			hex.x += 0.00001f;
			hex.y += 0.00001f;
			hex.z -= 0.00002f;
		}
		else {
			hex.x -= 0.00001f;
			hex.y -= 0.00001f;
			hex.z += 0.00002f;
		}
		result.push_back(Hex::RoundHex(hex));
	}

	return result;
}

// Returns the pixel coordinates for a given tile.
sf::Vector2f Hex::HexToPixel(sf::Vector3i hex){
	int col = hex.x;
	int row = hex.z;

	int hexWidth = 64;
	int hexHeight = 56;
	int tileSize = 64;

	int posX = col * (hexWidth * 3 / 4) - (hexWidth / 2) - (tileSize - hexWidth) / 2;
	int posY = row * hexHeight + col * (hexHeight / 2) - (hexHeight / 2) - (tileSize - hexHeight) / 2;

	return sf::Vector2f(posX, posY);
}

// Returns the pixel coordinates for a given tile.
sf::Vector2f Hex::HexToPixel(sf::Vector2i hex){
	int col = hex.x;
	int row = hex.y;

	int hexWidth = 64;
	int hexHeight = 56;
	int tileSize = 64;

	int posX = col * (hexWidth * 3 / 4) - (hexWidth / 2) - (tileSize - hexWidth) / 2;
	int posY = row * hexHeight + col * (hexHeight / 2) - (hexHeight / 2) - (tileSize - hexHeight) / 2;

	return sf::Vector2f(posX, posY);
}

sf::Vector3i Hex::PixelToHex(sf::Vector2f mousePos){
	sf::Vector2f hexCoord;
	sf::Vector3i roundHex;

	//mousePos.x = 540;
	//mousePos.y = 1164;

	hexCoord.x = mousePos.x * 2.f / 3.f / 32.f;
	hexCoord.y = (-mousePos.x / 3.f + sqrtf(3) / 3.f * mousePos.y) / 31.6f;

	roundHex = Hex::RoundHex(sf::Vector3f(hexCoord.x, -hexCoord.x - hexCoord.y, hexCoord.y));

	return roundHex;

}

// Gets the coordinates of the tiles surrounding a given tile.
std::vector<sf::Vector3i> Hex::GetHexNeighbors(sf::Vector3i center){
	std::vector<sf::Vector3i> result;
	result.push_back(sf::Vector3i(center.x + 1, center.y - 1, center.z));
	result.push_back(sf::Vector3i(center.x + 1, center.y, center.z - 1));
	result.push_back(sf::Vector3i(center.x, center.y + 1, center.z - 1));
	result.push_back(sf::Vector3i(center.x - 1, center.y + 1, center.z));
	result.push_back(sf::Vector3i(center.x - 1, center.y, center.z + 1));
	result.push_back(sf::Vector3i(center.x, center.y - 1, center.z + 1));

	return result;
}

// Gets the coordinates of the tiles surrounding a given tile.
std::vector<sf::Vector3i> Hex::GetHexNeighbors(sf::Vector2i center){
	return Hex::GetHexNeighbors(sf::Vector3i(center.x, -center.x - center.y, center.y));
}

int Hex::GetRoationAmount(sf::Vector3i center, sf::Vector3i cursor) {
	int result = 0;

	sf::Vector3i hex = Hex::HexDifference(cursor, center);
	if (hex.x == 0 && hex.z == -1) {
		result = 0;
	}
	if (hex.x == -1 && hex.z == 0) {
		result = 1;
	}
	if (hex.x == -1 && hex.z == 1) {
		result = 2;
	}
	if (hex.x == 0 && hex.z == 1) {
		result = 3;
	}
	if (hex.x == 1 && hex.z == 0) {
		result = 4;
	}
	if (hex.x == 1 && hex.z == -1) {
		result = 5;
	}

	return result;
}

std::vector<sf::Vector3i> Hex::RotateHex(sf::Vector3i center, sf::Vector3i cursor, std::vector<sf::Vector3i> area) {
	std::vector<sf::Vector3i> result;
	result.reserve(area.size());

	int timesToRotate = Hex::GetRoationAmount(center, cursor);
	for (size_t i = 0; i < area.size(); i++) {
		sf::Vector3i rotatedHex = Hex::HexDifference(area[i], center);

		// rotate left
		for (int j = 0; j < timesToRotate; j++) {
			sf::Vector3i hex(-rotatedHex.y, -rotatedHex.z, -rotatedHex.x);
			rotatedHex = hex;
		}
		rotatedHex = Hex::OffsetHex(rotatedHex, center);
		result.push_back(rotatedHex);
	}

	return result;
}

std::vector<sf::Vector3i> Hex::RotateHex(sf::Vector3i center, sf::Vector3i cursor, std::vector<sf::Vector3i> area, int timesToRotate) {
	std::vector<sf::Vector3i> result;
	result.reserve(area.size());

	for (size_t i = 0; i < area.size(); i++) {
		sf::Vector3i rotatedHex = Hex::HexDifference(area[i], center);

		// rotate left
		for (int j = 0; j < timesToRotate; j++) {
			sf::Vector3i hex(-rotatedHex.y, -rotatedHex.z, -rotatedHex.x);
			rotatedHex = hex;
		}
		rotatedHex = Hex::OffsetHex(rotatedHex, center);
		result.push_back(rotatedHex);
	}

	return result;
}

std::vector<sf::Vector3i> Hex::AllHexRotations(sf::Vector3i center, sf::Vector3i keyHex) {
	std::vector<sf::Vector3i> result = { keyHex };

	for (int i = 0; i < 5; i++) {
		sf::Vector3i rotatedHex = Hex::HexDifference(keyHex, center);
		for (int j = 0; j < i + 1; j++) {
			sf::Vector3i hex(-rotatedHex.y, -rotatedHex.z, -rotatedHex.x);
			rotatedHex = hex;
		}
		rotatedHex = Hex::OffsetHex(rotatedHex, center);
		result.push_back(rotatedHex);
	}

	return result;
}