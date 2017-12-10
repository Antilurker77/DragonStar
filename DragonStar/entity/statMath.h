// ==================================
//
// statMath.h
//
// Math functions for calculating
// stats.
//
// ==================================

#pragma once

#include <math.h>

// Calculates stat based on fixed gain per level.
int CalcLinearStat(int stat, int level, int increment);

// Calculates stat based on percent bonus per level.
int CalcPercentStat(int stat, int level, double percent);

// Calculates stat based on exponential bonus per level.
int CalcExpStat(int stat, int level);

// Calculates stat based on exponential bonus per level.
unsigned int CalcExpStat(unsigned int stat, int level);

// Calculates atat bases on exponential bonus per level.
double CalcExpDoubleValue(double value, int level);