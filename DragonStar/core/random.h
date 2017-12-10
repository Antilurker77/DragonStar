// ==================================
//
// random.h
//
// Calculates random values.
//
// ==================================

#include <random>

#pragma once

namespace Random {
	
	// Returns a random interger. Values are inclusive.
	int RandInt(int x, int y);

	// Returns a random interger. Values are inclusive.
	int RandInt(std::mt19937& mt, int x, int y);

	// Returns a random interger. Values are inclusive.
	int RandInt(std::mt19937_64& mt, int x, int y);

	// Returns a random unsigned interger. Values are inclusive.
	size_t RandSizeT(std::mt19937_64& mt, size_t x, size_t y);

	// Returns a random double. Values are inclusive.
	double RandDouble(double x, double y);

	// Returns a random double. Values are inclusive.
	double RandDouble(std::mt19937& mt, double x, double y);

	// Returns a random double. Values are inclusive.
	double RandDouble(std::mt19937_64& mt, double x, double y);

	// Returns a random seed. Used to generate the master
	// seed for initializing the mt19937_64.
	uint64_t RandSeed();

	// Returns a random seed.
	uint64_t RandSeed(std::mt19937_64& mt);
}
