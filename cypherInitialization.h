#pragma once

#include <iostream>
#include <vector>
#include <numeric>
#include <string>
#include <random>

#include "basicFunctions.h"

#include "debugSettings.h"


// There are currently 38 characters that are being purged... so initialize 2 arrays to modify of length 256 - 38 = 218...
// =====================================================================================
// Switch to utilize char* arrays instead of int*...
void initializeCypher(int* stdSeqArray, int* cypherArray, unsigned long long seedVal);