// ==================================
//
// statMath.cpp
//
// ==================================

#include "statMath.h"

int CalcLinearStat(int stat, int level, int increment) {
	return stat + (level - 1) * increment;
}

int CalcPercentStat(int stat, int level, double percent) {
	return stat + (level - 1) * (stat * percent);
}

int CalcExpStat(int stat, int level) {
	double dstat = (double)stat;
	double levelMod = level - 1;

	double result = dstat;
	result += levelMod * (dstat / 10.0);
	result += pow(levelMod, 2.0) * (dstat / 100.0);

	return (int)floor(result);
}

unsigned int CalcExpStat(unsigned int stat, int level) {
	double dstat = (double)stat;
	double levelMod = level - 1;

	double result = dstat;
	result += levelMod * (dstat / 10.0);
	result += pow(levelMod, 2.0) * (dstat / 100.0);

	return (unsigned int)floor(result);
}

double CalcExpDoubleValue(double value, int level) {
	double levelMod = level - 1;

	double result = value;
	result += levelMod * (value / 10.0);
	result += pow(levelMod, 2.0) * (value / 100.0);

	return result;
}