// ==================================
//
// hexMath.h
//
// Functions used for various hex
// algorithms.
//
// ==================================

#pragma once

#include <vector>
#include <SFML\System.hpp>

namespace std {

	template <>
	struct hash<sf::Vector3i>
	{
		std::size_t operator()(const sf::Vector3i& v) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()(v.x)
				^ (hash<int>()(v.y) << 1)) >> 1)
				^ (hash<int>()(v.z) << 1);
		}
	};

}

namespace Hex {

	sf::Vector3i OffsetHex(sf::Vector3i coords, sf::Vector3i offset);

	// Returns the difference between two hexes.
	sf::Vector3i HexDifference(sf::Vector3i a, sf::Vector3i b);

	sf::Vector3i RoundHex(sf::Vector3f hex);
	int HexDistance(sf::Vector3i start, sf::Vector3i end);
	sf::Vector3f HexLinearInterpolation(sf::Vector3i hexA, sf::Vector3i hexB, float t);

	std::vector<sf::Vector3i> FilledHexagon(sf::Vector3i center, int radius);

	// Returns a ring of hexagons with the specified radius.
	std::vector<sf::Vector3i> HexRing(sf::Vector3i center, int radius);

	std::vector<sf::Vector3i> HexLine(sf::Vector3i start, sf::Vector3i end);
	std::vector<sf::Vector3i> HexLine(sf::Vector3i start, sf::Vector3i end, bool positiveOffset);

	sf::Vector2f HexToPixel(sf::Vector3i hex);
	sf::Vector2f HexToPixel(sf::Vector2i hex);
	sf::Vector3i PixelToHex(sf::Vector2f mousePos);

	std::vector<sf::Vector3i> GetHexNeighbors(sf::Vector3i center, int radius = 1);
	std::vector<sf::Vector3i> GetHexNeighbors(sf::Vector2i center, int radius = 1);

	// Used for ability targeting. Determines how many times it needs to be rotated left.
	// Cursor must be adjacent to center.
	int GetRoationAmount(sf::Vector3i center, sf::Vector3i cursor);

	// Rotates a vector of hexes around a center point. Cursor must be adjacent to center.
	std::vector<sf::Vector3i> RotateHex(sf::Vector3i center, sf::Vector3i cursor, std::vector<sf::Vector3i> area);

	// Rotates a vector of hexes around a center point.
	std::vector<sf::Vector3i> RotateHex(sf::Vector3i center, sf::Vector3i cursor, std::vector<sf::Vector3i> area, int timesToRotate);

	// Returns all possible locations for a hex when rotated around a given center.
	std::vector<sf::Vector3i> AllHexRotations(sf::Vector3i center, sf::Vector3i keyHex);
}