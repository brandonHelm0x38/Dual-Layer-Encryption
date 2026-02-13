#pragma once

#include <iostream>
#include <string>

#include "basicFunctions.h"

#include "debugSettings.h"


// ===================== 64-Bit Mask-Transform ENCRYPTION FUNCTIONS ====================================================================================================
// =====================================================================================================================================================================

// 64-BIT BLOCK TRANSFORM FUNCTION...
// ======================================================================================
void bool64bitMask_EN1(bool* pntrVar, int* rand9array);

// 64-BIT-BLOCK {LINE x LINE} TRANSFORMS FUNCTION...
// ======================================================================================
void bool64bitMask_EN2(bool* pntrVar, int* seedArray /* values 1-7 */);

// Primary Bit-Masking Function; Calls 2 critical internal functions...
// ======================================================================================
std::string bitMaskTwistCharsEN(bool* inMatrix, int* rand9array);



// ===================== 64-Bit Mask-Transform DE-CRYPTION FUNCTIONS ===================================================================================================
// =====================================================================================================================================================================

// Convert the final permuted 64-bit block to a string of 8 chars...
// =====================================================================================
std::string buildDecrypted8chars(bool* inMatrixPntr, int* stdSeqArray, int* altrdSeqArray, int arraysLength);

// 64-BIT BLOCK TRANSFORM FUNCTION...
// ======================================================================================
void bool64bitMask_DE1(bool* pntrVar, int* rand9array);

// 64-BIT-BLOCK {LINE x LINE} TRANSFORMS FUNCTION...
// ======================================================================================
void bool64bitMask_DE2(bool* pntrVar, int* seedArray /* values 1-7 */);

// Primary/Parent/Main Bit-Masking Function...
// ======================================================================================
void bitMaskTwistCharsDE(bool* inMatrix, int* rand9array);