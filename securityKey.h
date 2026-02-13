#pragma once

#include <iostream>
#include <string>
#include <random>   // More advanced random number generators
#include <fstream>
#include <thread>
#include <chrono>

#include "basicFunctions.h"

#include "debugSettings.h"


// =========================== GENERATION, PARSING, & COMBINATION LOCK SECURITY KEY FUNCTIONS ==========================================================================
// =====================================================================================================================================================================

// Function takes in a seed value, and a blank [X]x[8] character matrix...
// Seed internal call to a random number generator, then builds [X]x[8] grid...
// =====================================================================================
// 1024 bit (128-Character) ----> [16]x[8] Matrix Built... BUILD THIS VERSION !!! 4-keys * 1024 = 4096 Bit Security
// =====================================================================================
std::string genSecurityKey(unsigned long long int seedVal, char* charMatrixIn, int certBITsize);

// ============================ PARSE SECURITY KEY FUNCTIONS ===========================================================================================================
// =====================================================================================================================================================================

// This is a function that inverts the 6-value scale used with the function immediately below; Used to determine how many steps ahead in the securityKey when running (parseHexValFromKey)...
// =====================================================================================
int stepAheadXref(char valTOinverse, int* scaleStepXrefsIn2);

// (customAZhexConverter) used in (parseHexValFromKey) immeadiately below this function...
// Translates each letter of the alphabet into a simple hex integer; xRefs all letters beyond standard range...
// This is used with a function that also inverts the 6-value scale (ABOVE)...
// =====================================================================================
std::string customAZhexConverter(char fullAZtoRandHex, int* alphaHexXrefsIn2, int* base10xRefs2);

// This is a function that will be internal to an app, but nest together with Cyber-Force in a way that increases security...
// MUST REMEMBER --> THIS SAME FUNCTION MUST WORK FOR BOTH ENCRYPTION & DECRYPTION AND BE PROVEN SECURE... CAN'T BE TIME-STAMP DEPENDENT !!!
// =====================================================================================
//static uint_fast64_t parseIntFromKey(string secKeyIn1024) {
std::string parseHexValFromKey(std::string secKeyIn1024, int* alphaHexXrefsIn1, int* base10xRefs1, int* scaleStepXrefsIn1);


// ===================== CYBER FORCE PRIMARY AUTHETICATION FUNCTION ====================================================================================================
// =====================================================================================================================================================================

// =====================================================================================
// Function variant which takes in 3-10 character hexaDecimal sequences translated from 1024-bit keys... I think this is the primary standard to collaborate on and compartmentalize... 
// Different encryption scripts may take in a string of additional seed characters/values for further compartmentalization.
// Create a callable, recreatable PRNG that takes in this seed data, and passes out a value to a re-creatable sequential number generator...

// I'VE THOUGHT ABOUT THIS MORE --> And this is a function that should make a call to a secure server and validate this is a trusted device... It must take in a device ID
// ======================================================================================
unsigned long long int cyberForceSecKeyComb(unsigned long long int internalServiceSeed /* Service-Layer */, uint_fast64_t activeDevID, std::string simulatedAPIfilepath);

