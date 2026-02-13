#pragma once

#include "bitMask.h"


//bool debugPrimaryInternals = false;
//bool debugPermutations = false;


// ===================== 64-Bit Mask-Transform ENCRYPTION FUNCTIONS ====================================================================================================
// =====================================================================================================================================================================

// 64-BIT BLOCK TRANSFORM FUNCTION...
// ======================================================================================
void bool64bitMask_EN1(bool* pntrVar, int* rand9array) {
    if (debugBitMaskInternals) {
        std::cout << "\n --> STARTING FUNCTION : Line 725 : bool64bitMask_EN1 !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    bool* orgPntr = pntrVar;
    int seedVal = *(rand9array);

    // Read-In 64-Bit representation of passed array, while performing transformations into a new temporary/dynamic copy...
    if (debugPrimaryInternals) { std::cout << "\n --> INSIDE FUNCTION : Line 732 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Used in bool64bitMask_EN1 !!!\n"; }
    bool bool2d64translate[8][8] = { false };
    int ttlRows = 8;
    int ttlCols = 8;
    int pntrOffset = 0;

    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 64-Bit 8x8 Grid - Block Transforms
    //                                                                --1    DOUBLE INVERSE   -->   Double 90° or 180° Spin.
    //                                                                --2    Simple Diagonal Mirror -(\)-
    //                                                                --3    Simple Diagonal Mirror -(/)-
    //                                                                --4    90° Clockwise Transform.
    //                                                                --5    90° Counter-Clockwise Transform.
    //                                                                --6    Simple Inverse of Horizontal Line Read-In; preserving vertical order.
    //                                                                --7    Simple Inverse of Vertical Line-Order Read-In; preserving horizontal/sequential order.
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // *MATH --> POINTER = curRow * ttlCols + curCol          // EQ-VARIANT --> 1  curRow|curCol
    // *MATH -------------------------------------> MAPPING = bool2d64translate  [rowInv] [colInv]
    int overallLoopCntr = 0;
    for (int curCol = 0; curCol < ttlCols; curCol++) {
        int colInv = 7 - curCol;
        for (int curRow = 0; curRow < ttlRows; curRow++) {
            overallLoopCntr++;
            int rowInv = 7 - curRow;
            pntrOffset = curRow * ttlCols + curCol;  //*Pointer --:|:--> EQ.1-VARIANT == curRow|curCol
            pntrVar = orgPntr + pntrOffset;
            bool iterVal = *pntrVar;
            if (seedVal == 1) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 1--DOUBLE INVERSE ; Double 90° or 180° Spin..."; }
                bool2d64translate[rowInv][colInv] = *(pntrVar);
            }                   // 1--DOUBLE INVERSE --> Double 90° or 180° Spin
            else if (seedVal == 2) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 2--Simple Diagonal Mirror -(\)-..."; }
                bool2d64translate[curCol][curRow] = *(pntrVar);
            }                   // 2--Simple Diagonal Mirror -(\)-
            else if (seedVal == 3) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 3--Simple Diagonal Mirror -(/)-..."; }
                bool2d64translate[colInv][rowInv] = *(pntrVar);
            }                   // 3--Simple Diagonal Mirror -(/)-
            else if (seedVal == 4) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 4--90° Clockwise Transform..."; }
                bool2d64translate[curCol][rowInv] = *(pntrVar);
            }                   // 4--90° Clockwise Transform...
            else if (seedVal == 5) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 5--90° Counter-Clockwise Transform..."; }
                bool2d64translate[colInv][curRow] = *(pntrVar);
            }                   // 5--90° Counter-Clockwise Transform...
            else if (seedVal == 6) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 6--Simple Inverse of Horizontal Line Read-In; preserving vertical order..."; }
                bool2d64translate[curRow][colInv] = *(pntrVar);
            }                   // 6--Simple Inverse of Horizontal Line Read-In; preserving vertical order...
            else if (seedVal == 7) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 7--Simple Inverse of Horizontal Line Read-In; preserving vertical order..."; }
                bool2d64translate[rowInv][curCol] = *(pntrVar);
            }                   // 7--Simple Inverse of Vertical Line-Order Read-In; preserving horizontal/sequential order...
            //std::cout << "\tValue of *ptr: " << iterVal << "\t  | Value of ptr: " << pntrVar << "\t  | Transfer from [" << curRow << "][" << curCol << "]\t  | To [" << colInv << "][" << rowInv << "]" << endl;
        }
    }

    // Update the original 64-Bit-Map to the tranformed/permuted version & re-map...
    // CRITICAL STEP  ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    for (int curRow = 0; curRow < ttlRows; curRow++) {
        for (int curCol = 0; curCol < ttlCols; curCol++) {
            *(orgPntr + curRow * ttlCols + curCol) = bool2d64translate[curRow][curCol];
        }
    }

    //delete orgPntr;
    // ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // END OF 64-BIT BLOCK TRANSFORM FUNCTION ~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
}

// 64-BIT-BLOCK {LINE x LINE} TRANSFORMS FUNCTION...
// ======================================================================================
void bool64bitMask_EN2(bool* pntrVar, int* seedArray /* values 1-7 */) {
    if (debugBitMaskInternals) {
        std::cout << "\n --> STARTING FUNCTION : Line 812 : bool64bitMask_EN2 !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 8-Bit LineByLine - Simple Transforms
    //                                                                --1    Flag swap rightONleft & leftONright        -- [0110 1000] --> [1000 0110]
    //                                                                --2    Flag swap !rightONleft & leftONright       -- [0110 1000] --> [0111 0110]
    //                                                                --3    Flag swap rightONleft & !leftONright       -- [0110 1000] --> [1000 1001]
    // 
    //                                                                -->    Xor operations should be different... Xor assigns 1 if the values are the same and 0 if the values are different.
    //                                                                --4    Flag keep left + XOR left w/right          -- [0110 1000] --> [0110 0001]
    //                                                                --5    Flag keep left + !XOR left w/right         -- [0110 1000] --> [0110 1110]
    //                                                                --6    Flag keep right + XOR right w/left         -- [0110 1000] --> [0001 1000]
    //                                                                --7    Flag keep right + !XOR right w/left        -- [0110 1000] --> [1110 1000]
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Xor Functions --> Construct Encryption Group
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Read-In 64-Bit representation of passed array, while performing transformations into a new temporary/dynamic copy...
    if (debugPrimaryInternals) { std::cout << "\n --> INSIDE FUNCTION : Line 831 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Used in bool64bitMask_EN2 !!!\n"; }
    bool bool2d64translate[8][8] = { false };
    int ttlRows = 8;
    int ttlCols = 8;

    bool* orgPntr = pntrVar;

    for (int i = 0; i < 8; i++) {   // Row loop
        // Grab toggle transform type from input array...
        int toggleVal = *(seedArray + 1 + i); // Planning for a passed array of 9 elements; Skip ahead +1...
        // Orient Row-Pointer for passing into transform function...
        pntrVar = orgPntr + (8 * i);
        int iterVal = *pntrVar;
        bool bLineLeft[4] = { *(pntrVar), *(pntrVar + 1), *(pntrVar + 2), *(pntrVar + 3) };
        bool bLineRight[4] = { *(pntrVar + 4), *(pntrVar + 5), *(pntrVar + 6), *(pntrVar + 7) };


        if (toggleVal == 1) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 1--Flag swap rightONleft& leftONright..."; }
                bool2d64translate[i][j] = bLineRight[j];
                bool2d64translate[i][j + 4] = bLineLeft[j];
            }
        }                                // 1--Flag swap rightONleft& leftONright
        else if (toggleVal == 2) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 2--Flag swap !rightONleft & leftONright..."; }
                bool2d64translate[i][j] = !bLineRight[j];
                bool2d64translate[i][j + 4] = bLineLeft[j];
            }
        }                                // 2--Flag swap !rightONleft & leftONright
        else if (toggleVal == 3) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 3--Flag swap rightONleft & !leftONright..."; }
                bool2d64translate[i][j] = bLineRight[j];
                bool2d64translate[i][j + 4] = !bLineLeft[j];
            }
        }                              // 3--Flag swap rightONleft & !leftONright
        else if (toggleVal == 4) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 4--Flag keep LEFT + XOR left w/right..."; }
                bool2d64translate[i][j] = bLineLeft[j];                                         // 4--Keep LEFT
                if (bLineLeft[j] == bLineRight[j]) { bool2d64translate[i][j + 4] = true; }
                else { bool2d64translate[i][j + 4] = false; }
            }
        }                              // 4--Flag keep left + XOR left w/right
        else if (toggleVal == 5) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 5--Flag keep LEFT + !XOR left w/right..."; }
                bool2d64translate[i][j] = bLineLeft[j];                                         // 5--Keep LEFT
                if (bLineLeft[j] == bLineRight[j]) { bool2d64translate[i][j + 4] = false; }
                else { bool2d64translate[i][j + 4] = true; }
            }
        }                               // 5--Flag keep left + !XOR left w/right
        else if (toggleVal == 6) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 6--Flag keep RIGHT + XOR right w/left..."; }
                bool2d64translate[i][j + 4] = bLineRight[j];                                    // 6--Keep RIGHT
                if (bLineLeft[j] == bLineRight[j]) { bool2d64translate[i][j] = true; }
                else { bool2d64translate[i][j] = false; }
            }
        }                                  // 6--Flag keep right + XOR right w/left
        else if (toggleVal == 7) {
            for (int j = 0; j < 4; j++) {
                if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 7--Flag keep RIGHT + !XOR left w/right..."; }
                bool2d64translate[i][j + 4] = bLineRight[j];                                    // 7--Keep RIGHT
                if (bLineLeft[j] == bLineRight[j]) { bool2d64translate[i][j] = false; }
                else { bool2d64translate[i][j] = true; }                                        // 7--Flag keep right + !XOR right w/left
            }
        }
    }

    // Update the original 64-Bit-Map to the tranformed/permuted version & re-map...
    // CRITICAL STEP  ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    for (int curRow = 0; curRow < ttlRows; curRow++) {
        for (int curCol = 0; curCol < ttlCols; curCol++) {
            *(orgPntr + curRow * ttlCols + curCol) = bool2d64translate[curRow][curCol];
        }
    }

    //delete orgPntr;
    // ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // This has been proven to translate all 7 variants correctly...
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // END OF 64-BIT {LINE x LINE} TRANSFORMS FUNCTION ~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
}

// Primary Bit-Masking Function; Calls 2 critical internal functions...
// ======================================================================================
std::string bitMaskTwistCharsEN(bool* inMatrix, int* rand9array) {
    if (debugMajorPermutations) {
        std::cout << "\n --> STARTING FUNCTION : Line 923 : bitMaskTwistCharsEN !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    bool* pntrVar3A = new bool[8 * 8];
    pntrVar3A = inMatrix;

    if (debugMajorPermutations) {
        std::cout << "\n --> INSIDE FUNCTION : Line 930 : bitMaskTwistCharsEN --> Read-Back Input data...";
        prnt64bitBool(pntrVar3A, 8, 8);
    }


    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Run bool64bitMask_EN1 --> Perform overall 64-bit block permutation
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 64-Bit 8x8 Grid - Block Transforms
    //                                                                --1    DOUBLE INVERSE   -->   Double 90° or 180° Spin.
    //                                                                --2    Simple Diagonal Mirror -(\)-
    //                                                                --3    Simple Diagonal Mirror -(/)-
    //                                                                --4    90° Clockwise Transform.
    //                                                                --5    90° Counter-Clockwise Transform.
    //                                                                --6    Simple Inverse of Horizontal Line Read-In; preserving vertical order.
    //                                                                --7    Simple Inverse of Vertical Line-Order Read-In; preserving horizontal/sequential order.
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-

    // This works with a passed pointer!  Ready for real encryption test!
    int* pntrVar4A = new int[9];
    pntrVar4A = &rand9array[0];

    bool64bitMask_EN1(pntrVar3A, pntrVar4A);
    if (debugMajorPermutations) {
        std::cout << "\n --> INSIDE FUNCTION : Line 955 : bitMaskTwistCharsEN --> Print Block Permutations block / bool64bitMask_EN1 --> blockTransform OUPUT...";
        prnt64bitBool(pntrVar3A, 8, 8);
    }


    //std::cout << "\n RUN -->  bitMaskTwistChars - Step 2.0  -::|::- Iterative LINE x LINE Tranformations...\n";
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 8-Bit LineByLine *allRows 90° Transform Style Glossary...
    //                                                                --1    Flag swap rightONleft & leftONright        -- [0110 1000] --> [1000 0110]
    //                                                                --2    Flag swap !rightONleft & leftONright       -- [0110 1000] --> [0111 0110]
    //                                                                --3    Flag swap rightONleft & !leftONright       -- [0110 1000] --> [1000 1001]
    // 
    //                                                                -->    Xor operations should be different... Xor assigns 1 if the values are the same and 0 if the values are different.
    //                                                                --4    Flag keep left + XOR left w/right          -- [0110 1000] --> [0110 0001]
    //                                                                --5    Flag keep left + !XOR left w/right         -- [0110 1000] --> [0110 1110]
    //                                                                --6    Flag keep right + XOR right w/left         -- [0110 1000] --> [0001 1000]
    //                                                                --7    Flag keep right + !XOR right w/left        -- [0110 1000] --> [1110 1000]
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Xor Functions --> Construct Encryption Group
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Calculate array  // Calculate 9 random numbers (1 - 7); These will be used to drive the iterative transforms...

    bool64bitMask_EN2(pntrVar3A, pntrVar4A); //--> Perform LINE x LINE permutations and Xor operations...
    if (debugMajorPermutations) {
        std::cout << "\n --> INSIDE FUNCTION : Line 981 : bitMaskTwistCharsEN --> Print Line x Line transformed block / bool64bitMask_EN2-->lineXlineTwist OUPUT...";
        prnt64bitBool(pntrVar3A, 8, 8);
    }


    // Calculate out new string to output; This is now 1 layer of working encryption!
    std::string funcDebug = "";
    std::string newStrng = "";
    std::string outputStrng = "";
    for (int row = 0; row < 8; row++) {
        int lineValue = 0;
        for (int col = 0; col < 8; col++) {
            //bool flagAdd = bool2d64bit2[row][col];
            bool flagAdd = *(pntrVar3A + (row * 8) + col);
            // HERE
            int colInv = 7 - col;
            if (flagAdd) {
                if (col == 7)
                    lineValue = lineValue + 1;
                else
                    lineValue = lineValue + expCalculator(2, colInv);
            }
        }
        // Must build out Final Bit-Mask & Cyphered string... after permutations, these values mess with processing...
        unsigned char testChar = static_cast<char>(lineValue);
        if (testChar == 0) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 1) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 2) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 3) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 4) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 5) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 6) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 7) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 8) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 9) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 10) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 11) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 12) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 13) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 14) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 15) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 16) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 17) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 18) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 19) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 20) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 21) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 22) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 23) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 24) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 25) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 26) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 27) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 28) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 29) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 30) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 31) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        //else if (testChar == 32) { // Always want to keep space characters...
        //    newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
        //    outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")"; }
        else if (testChar == 40) {  // Needed !!! This is the '(' character... which I need to be a cap value or it breaks my processing loops...
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        //else if (testChar == 91) { // Bracket variant '{'
        //    newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
        //    outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")"; }
        //else if (testChar == 123) { // Bracket variant '['
        //    newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
        //    outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")"; }
        else if (testChar == 127) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 129) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        //else if (testChar == 143) { // Latin A character with accent above...
        //    newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
        //    outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")"; }
        else if (testChar == 144) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 157) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 160) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else if (testChar == 255) {
            newStrng = newStrng + std::to_string(row + 1) + "/(" + std::to_string(lineValue) + ")  ";
            outputStrng = outputStrng + "(" + std::to_string(lineValue) + ")";
        }
        else {
            newStrng = newStrng + std::to_string(row + 1) + "/" + static_cast<char>(lineValue) + "  ";
            outputStrng = outputStrng + static_cast<char>(lineValue);
        }
    }

    //delete pntrVar3A;
    //delete pntrVar4A;

    if (debugMajorPermutations) { std::cout << "\n --> !!! END FUNCTION !!! : Line 1183 : bitMaskTwistCharsEN --> Confirm Output String --:|:--> " + newStrng + "\n"; }

    return outputStrng;
}


// ===================== 64-Bit Mask-Transform DE-CRYPTION FUNCTIONS ===================================================================================================
// =====================================================================================================================================================================

// Convert the final permuted 64-bit block to a string of 8 chars...
// =====================================================================================
std::string buildDecrypted8chars(bool* inMatrixPntr, int* stdSeqArray, int* altrdSeqArray, int arraysLength) {
    if (debugByteLineReadout) {
        std::cout << "\n --> STARTING FUNCTION : Line 578 --> buildDecrypted8chars !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    std::string decypheredStrng = "";

    // Loop through each row of the input matrix to build each search-character...
    for (int row = 0; row < 8; row++) {
        int intVal = 0;
        unsigned char currCharSrch;

        // Loop through each column of the input matrix to build the value for each search char.
        for (int col = 0; col < 8; col++) {
            int colInv = 7 - col;

            if (*(inMatrixPntr + (row * 8) + col) == true) {
                if (col == 7)
                    intVal = intVal + 1;
                else
                    intVal = intVal + expCalculator(2, colInv);
            }
        }
        currCharSrch = static_cast<char>(intVal);
        if (debugByteLineReadout) { std::cout << "\n --> INSIDE FUNCTION : Line 601 : buildDecrypted8chars -->\t |  Processing inMatrix Line# == " + std::to_string(row + 1) + "\t |  and Line-Total intVal == " + std::to_string(intVal); }

        // Build Final Cypher-Swapped string... I know this code works correctly...
        int posFlag = 0;
        //while ( *(altrdSeqArray + posFlag) != currCharSrch) {
        while (*(altrdSeqArray + posFlag) != intVal && posFlag < arraysLength) {
            if (debugCypherSwaps) { std::cout << "\n --> INSIDE FUNCTION : Line 607 : buildDecrypted8chars -->\t |  Checking purgedAltrdSeqArray[" + std::to_string(posFlag) + "] == " + std::to_string(*(altrdSeqArray + posFlag)); }
            posFlag++;
        }
        unsigned char decypheredChar = *(stdSeqArray + posFlag);
        decypheredStrng = decypheredStrng + static_cast<char>(decypheredChar);

    }
    return decypheredStrng;
}

// =============================== 64-Bit Mask-Transforms ===============================
// ======================================================================================

// 64-BIT BLOCK TRANSFORM FUNCTION...
// ======================================================================================
void bool64bitMask_DE1(bool* pntrVar, int* rand9array) {
    if (debugBitMaskInternals) {
        std::cout << "\n --> STARTING FUNCTION : Line 623 --> bool64bitMask_DE1 / blockTransformation !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    bool* orgPntr = pntrVar;
    int seedVal = *(rand9array);

    // Create a 64-bit block to perform permutations into and then overwrite input matrix; (Input Matrix should be all false or newly initialied)...
    if (debugBitMaskInternals) { std::cout << "\n --> INSIDE FUNCTION : Line 630 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Used in function bool64bitMask_DE1 !!!"; }
    bool bool2d64translate[8][8] = { false };
    int ttlRows = 8;
    int ttlCols = 8;
    int pntrOffset = 0;

    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 64-Bit 8x8 Grid - Block Transforms
    //                                                                --1    DOUBLE INVERSE   -->   Double 90° or 180° Spin.
    //                                                                --2    Simple Diagonal Mirror -(\)-
    //                                                                --3    Simple Diagonal Mirror -(/)-
    //                                                                --4    90° Clockwise Transform.
    //                                                                --5    90° Counter-Clockwise Transform.
    //                                                                --6    Simple Inverse of Horizontal Line Read-In; preserving vertical order.
    //                                                                --7    Simple Inverse of Vertical Line-Order Read-In; preserving horizontal/sequential order.
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // *MATH --> POINTER = curRow * ttlCols + curCol          // EQ-VARIANT --> 1  curRow|curCol
    // *MATH -------------------------------------> MAPPING = bool2d64translate  [rowInv] [colInv]
    int overallLoopCntr = 0;
    for (int curCol = 0; curCol < ttlCols; curCol++) {
        int colInv = 7 - curCol;
        for (int curRow = 0; curRow < ttlRows; curRow++) {
            overallLoopCntr++;
            int rowInv = 7 - curRow;
            pntrOffset = curRow * ttlCols + curCol;  //*Pointer --:|:--> EQ.1-VARIANT == curRow|curCol
            pntrVar = orgPntr + pntrOffset;
            bool iterVal = *pntrVar;
            if (seedVal == 1) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 1--DOUBLE INVERSE   -->   Double 90° or 180° Spin"; }
                bool2d64translate[rowInv][colInv] = *(pntrVar);
            }           // 1--DOUBLE INVERSE   -->   Double 90° or 180° Spin
            else if (seedVal == 2) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 2--Simple Diagonal Mirror -(\\)- "; }
                bool2d64translate[curCol][curRow] = *(pntrVar);
            }           // 2--Simple Diagonal Mirror -(\)-
            else if (seedVal == 3) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 3--Simple Diagonal Mirror -(/)-"; }
                bool2d64translate[colInv][rowInv] = *(pntrVar);
            }           // 3--Simple Diagonal Mirror -(/)-
            else if (seedVal == 4) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 4--90° Counter-Clockwise Transform (INVERSED)..."; }
                bool2d64translate[colInv][curRow] = *(pntrVar);
            }           // 5--90° Counter-Clockwise Transform...
            else if (seedVal == 5) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 5--90° Clockwise Transform (INVERSED)..."; }
                bool2d64translate[curCol][rowInv] = *(pntrVar);
            }           // 4--90° Clockwise Transform...
            else if (seedVal == 6) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 6--Simple Inverse of Horizontal Line Read-In; preserving vertical order..."; }
                bool2d64translate[curRow][colInv] = *(pntrVar);
            }           // 6--Simple Inverse of Horizontal Line Read-In; preserving vertical order...
            else if (seedVal == 7) {
                if (debugBitMaskInternals && overallLoopCntr == 63) { std::cout << "\n DEBUG PERMUTATIONS --> 7--Simple Inverse of Horizontal Line Read-In; preserving vertical order..."; }
                bool2d64translate[rowInv][curCol] = *(pntrVar);
            }           // 7--Simple Inverse of Vertical Line-Order Read-In; preserving horizontal/sequential order...
        //std::cout << "\tValue of *ptr: " << iterVal << "\t  | Value of ptr: " << pntrVar << "\t  | Transfer from [" << curRow << "][" << curCol << "]\t  | To [" << colInv << "][" << rowInv << "]" << endl;
        }
    }

    // Update the original 64-Bit-Map to the tranformed/permuted version & re-map...
    // CRITICAL STEP  ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    for (int curRow = 0; curRow < ttlRows; curRow++) {
        for (int curCol = 0; curCol < ttlCols; curCol++) {
            *(orgPntr + curRow * ttlCols + curCol) = bool2d64translate[curRow][curCol];
        }
    }
    // ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // END OF 64-BIT BLOCK TRANSFORM FUNCTION ~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
}

// 64-BIT-BLOCK {LINE x LINE} TRANSFORMS FUNCTION...
// ======================================================================================
void bool64bitMask_DE2(bool* pntrVar, int* seedArray /* values 1-7 */) {
    if (debugBitMaskInternals) {
        std::cout << "\n --> STARTING FUNCTION : Line 707 --> bool64bitMask_DE2 / lineXlineBitMask !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 8-Bit LineByLine - Simple Transforms
    //                                                                --1    Flag swap rightONleft & leftONright        -- [0110 1000] --> [1000 0110]
    //                                                                --2    Flag swap !rightONleft & leftONright       -- [0110 1000] --> [0111 0110]
    //                                                                --3    Flag swap rightONleft & !leftONright       -- [0110 1000] --> [1000 1001]
    // 
    //                                                                -->    Xor operations should be different... Xor assigns 1 if the values are the same and 0 if the values are different.
    //                                                                --4    Flag keep left + XOR left w/right          -- [0110 1000] --> [0110 0001]
    //                                                                --5    Flag keep left + !XOR left w/right         -- [0110 1000] --> [0110 1110]
    //                                                                --6    Flag keep right + XOR right w/left         -- [0110 1000] --> [0001 1000]
    //                                                                --7    Flag keep right + !XOR right w/left        -- [0110 1000] --> [1110 1000]
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Xor Functions --> Construct Encryption Group
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Read-In 64-Bit representation of passed array, while performing transformations into a new temporary/dynamic copy...
    bool bool2d64translate[8][8] = { false };
    if (debugBitMaskInternals) { std::cout << "\n --> INSIDE FUNCTION : Line 727 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Used in function bool64bitMask_DE2 !!!"; }
    int ttlRows = 8;
    int ttlCols = 8;

    bool* orgPntr = pntrVar;

    for (int i = 0; i < 8; i++) {   // Row loop
        // Grab toggle transform type from input array...
        int toggleVal = *(seedArray + 1 + i); // Planning for a passed array of 9 elements; Skip ahead +1...
        // Orient Row-Pointer for passing into transform function...
        pntrVar = orgPntr + (8 * i);
        int iterVal = *pntrVar;
        // Build each half of the byte as separate variables; building 2 sets of 4...
        bool bLineLeft[4] = { *(pntrVar), *(pntrVar + 1), *(pntrVar + 2), *(pntrVar + 3) };
        bool bLineRight[4] = { *(pntrVar + 4), *(pntrVar + 5), *(pntrVar + 6), *(pntrVar + 7) };


        if (toggleVal == 1) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 1--Flag swap rightONleft& leftONright;  \t Simple Inverse"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j] = bLineRight[j];
                bool2d64translate[i][j + 4] = bLineLeft[j];
            }
        }        // 1--Flag swap rightONleft& leftONright; Simple Inverse
        else if (toggleVal == 2) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 2--Flag swap !rightONleft & leftONright;\t Inversed becomes --> !leftONright & rightONleft"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j] = bLineRight[j];
                bool2d64translate[i][j + 4] = !bLineLeft[j];
            }
        }       // 2--Flag swap !rightONleft & leftONright; Inversed becomes --> !leftONright & rightONleft
        else if (toggleVal == 3) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 3--Flag swap rightONleft & !leftONright;\t Inversed becomes --> !rightONleft & leftONright"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j] = !bLineRight[j];
                bool2d64translate[i][j + 4] = bLineLeft[j];
            }
        }        // 3--Flag swap rightONleft & !leftONright;  Inversed becomes --> !rightONleft & leftONright
        else if (toggleVal == 4) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 4--Flag keep LEFT + XOR right w/left;   \t Inversed becomes --> Flag keep LEFT + If bLineRight[j] == 1, RIGHT = bLineLeft[j], Else !bLineLeft[j]"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j] = bLineLeft[j];                         // 4--Keep LEFT
                if (bLineRight[j]) { bool2d64translate[i][j + 4] = bLineLeft[j]; }
                else { bool2d64translate[i][j + 4] = !bLineLeft[j]; }
            }
        }      // 4--Flag keep LEFT + XOR right w/left;  Inversed becomes --> Flag keep LEFT + If bLineRight[j] == 1, RIGHT = bLineLeft[j], Else !bLineLeft[j]
        else if (toggleVal == 5) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 5--Flag keep LEFT + !XOR right w/left;  \t Inversed becomes --> Flag keep LEFT + If bLineRight[j] == 0, RIGHT = bLineLeft[j], Else !bLineLeft[j]"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j] = bLineLeft[j];                         // 5--Keep LEFT
                if (!bLineRight[j]) { bool2d64translate[i][j + 4] = bLineLeft[j]; }
                else { bool2d64translate[i][j + 4] = !bLineLeft[j]; }
            }
        }      // 5--Flag keep LEFT + !XOR right w/left;  Inversed becomes --> Flag keep LEFT + If bLineRight[j] == 0, RIGHT = bLineLeft[j], Else !bLineLeft[j]
        else if (toggleVal == 6) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 6--Flag keep RIGHT + XOR left w/right;  \t Inversed becomes --> Flag keep RIGHT + If bLineLeft[j] == 1, LEFT = bLineRight[j], Else !bLineRight[j]"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j + 4] = bLineRight[j];                    // 6--Keep RIGHT
                if (bLineLeft[j]) { bool2d64translate[i][j] = bLineRight[j]; }
                else { bool2d64translate[i][j] = !bLineRight[j]; }
            }
        }         // 6--Flag keep RIGHT + XOR left w/right;  Inversed becomes --> Flag keep RIGHT + If bLineLeft[j] == 1, LEFT = bLineRight[j], Else !bLineRight[j]
        else if (toggleVal == 7) {
            if (debugBitMaskInternals) { std::cout << "\n DEBUG PERMUTATIONS --> 7--Flag keep RIGHT + !XOR left w/right; \t Inversed becomes --> Flag keep RIGHT + If bLineLeft[j] == 0, LEFT = bLineRight[j], Else !bLineRight[j]"; }
            for (int j = 0; j < 4; j++) {
                bool2d64translate[i][j + 4] = bLineRight[j];                    // 7--Keep RIGHT
                if (!bLineLeft[j]) { bool2d64translate[i][j] = bLineRight[j]; }
                else {
                    bool2d64translate[i][j] = !bLineRight[j];                // 7--Flag keep RIGHT + !XOR left w/right;  Inversed becomes --> Flag keep RIGHT + If bLineLeft[j] == 0, LEFT = bLineRight[j], Else !bLineRight[j]
                }
            }
        }
    }

    // Update the original 64-Bit-Map to the tranformed/permuted version & re-map...
    // CRITICAL STEP  ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    for (int curRow = 0; curRow < ttlRows; curRow++) {
        for (int curCol = 0; curCol < ttlCols; curCol++) {
            *(orgPntr + curRow * ttlCols + curCol) = bool2d64translate[curRow][curCol];
        }
    }
    // ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // END OF 64-BIT {LINE x LINE} TRANSFORMS FUNCTION ~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
}

// Primary/Parent/Main Bit-Masking Function...
// ======================================================================================
void bitMaskTwistCharsDE(bool* inMatrix, int* rand9array) {
    if (debugMajorPermutations) {
        std::cout << "\n --> STARTING FUNCTION : Line 818 : bitMaskTwistCharsDE !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    int* pntrVar3A = new int[9];
    pntrVar3A = &rand9array[0];
    // Create/Initialize and print out an all False Boolean[8][8] Matrix...
    bool* pntrVar2A = new bool[8 * 8];
    pntrVar2A = inMatrix;

    if (debugMajorPermutations) {
        std::cout << "\n --> INSIDE FUNCTION : Line 829 : bitMaskTwistCharsDE --> Read-Back Input data...";
        prnt64bitBool(pntrVar2A, 8, 8);
    }

    // INVERSE STEPS FOR DECRYPTION --> RUN BIT-MASK PERMUTATIONS FIRST !!!
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 8-Bit LineByLine *allRows 90° Transform Style Glossary...
    //                                                                --1    Flag swap rightONleft & leftONright        -- [0110 1000] --> [1000 0110]
    //                                                                --2    Flag swap !rightONleft & leftONright       -- [0110 1000] --> [0111 0110]
    //                                                                --3    Flag swap rightONleft & !leftONright       -- [0110 1000] --> [1000 1001]
    // 
    //                                                                -->    Xor operations should be different... Xor assigns 1 if the values are the same and 0 if the values are different.
    //                                                                --4    Flag keep left + XOR left w/right          -- [0110 1000] --> [0110 0001]
    //                                                                --5    Flag keep left + !XOR left w/right         -- [0110 1000] --> [0110 1110]
    //                                                                --6    Flag keep right + XOR right w/left         -- [0110 1000] --> [0001 1000]
    //                                                                --7    Flag keep right + !XOR right w/left        -- [0110 1000] --> [1110 1000]
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Xor Functions --> Construct Encryption Group
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Calculate array  // Calculate 9 random numbers (1 - 7); These will be used to drive the iterative transforms...

    bool64bitMask_DE2(pntrVar2A, pntrVar3A); //--> Perform LINE x LINE permutations and Xor operations...
    if (debugMajorPermutations) {
        std::cout << "\n\n --> INSIDE FUNCTION : Line 855 : bitMaskTwistCharsDE --> Print Line x Line transformed block / bool64bitMask_DE2-->lineXlineTwist OUPUT...";
        prnt64bitBool(pntrVar2A, 8, 8);
    }

    // INVERSE STEPS FOR DECRYPTION --> RUN BLOCK TWIST PERMUTATIONS SECOND !!!
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // Run bool64bitMask_DE1 --> Perform overall 64-bit block permutation
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    //                                                                I can imagine using an array of values [ 1 - 7 ] ; To drive each layer of Read-In Transform...
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-
    // CRITICAL STEP - 64-Bit 8x8 Grid - Block Transforms
    //                                                                --1    DOUBLE INVERSE   -->   Double 90° or 180° Spin.
    //                                                                --2    Simple Diagonal Mirror -(\)-
    //                                                                --3    Simple Diagonal Mirror -(/)-
    //                                                                --4    90° Clockwise Transform.
    //                                                                --5    90° Counter-Clockwise Transform.
    //                                                                --6    Simple Inverse of Horizontal Line Read-In; preserving vertical order.
    //                                                                --7    Simple Inverse of Vertical Line-Order Read-In; preserving horizontal/sequential order.
    // CRITICAL STEP - ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~- ~-

    bool64bitMask_DE1(pntrVar2A, pntrVar3A);
    if (debugMajorPermutations) {
        std::cout << "\n\n --> INSIDE FUNCTION : Line 878 : bitMaskTwistCharsDE --> Print Block Permutations block / bool64bitMask_DE1 --> blockTransform OUPUT...";
        prnt64bitBool(pntrVar2A, 8, 8);
    }
    // End of function...
}