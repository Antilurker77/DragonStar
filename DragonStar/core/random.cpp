// ==================================
//
// random.cpp
//
// ==================================

#include "random.h"

int Random::RandInt(int x, int y) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(x, y);
	return dist(mt);
}

int Random::RandInt(std::mt19937& mt, int x, int y) {
	std::uniform_int_distribution<int> dist(x, y);
	return dist(mt);
}

int Random::RandInt(std::mt19937_64& mt, int x, int y) {
	std::uniform_int_distribution<int> dist(x, y);
	return dist(mt);
}

size_t Random::RandSizeT(size_t x, size_t y) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<size_t> dist(x, y);
	return dist(mt);
}

size_t Random::RandSizeT(std::mt19937_64& mt, size_t x, size_t y) {
	std::uniform_int_distribution<size_t> dist(x, y);
	return dist(mt);
}

double Random::RandDouble(double x, double y) {
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> dist(x, y);
	return dist(mt);
}

double Random::RandDouble(std::mt19937& mt, double x, double y) {
	std::uniform_real_distribution<double> dist(x, y);
	return dist(mt);
}

double Random::RandDouble(std::mt19937_64& mt, double x, double y) {
	std::uniform_real_distribution<double> dist(x, y);
	return dist(mt);
}

uint64_t Random::RandSeed() {
	std::random_device rd;
	uint64_t seed = (uint64_t)rd() << 32 | rd();
	return seed;
}

uint64_t Random::RandSeed(std::mt19937_64& mt) {
	std::uniform_int_distribution<uint64_t> dist(0);
	return dist(mt);
}