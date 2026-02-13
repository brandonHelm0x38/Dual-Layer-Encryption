#pragma once

#include <iostream>
#include <string>
#include <regex>

#include "debugSettings.h"


// ============== BASIC DEBUG & STRING OUTPUT FORMATTING ===============================================================================================================
// =====================================================================================================================================================================

// Basic function for interupting processing; Break-Check outputs and whether to continue the program...
// =====================================================================================
char checkBreak(std::string msg);

// Function which handles menu options interface for command line...
// =====================================================================================
char validToggleChar(char* validArray, std::string functionMsg, int validArrayLen);

// Function for printing debug output... take in string, and pad a set number of characters; (string, length, L/R) --> L == Left Justify (string|padSpaces) ; R == Right Justify (padSpaces|string)...
// =====================================================================================
std::string padOutput(std::string data, int outFieldLen, char justifySide);

// Easier to use this function.
// =====================================================================================
std::string outputStrngFromASCIIval(int asciiVal);

// Logic check to ensure user is inputting valid Windows filepaths; MODIFY for Mac/Linux...etc...
// =====================================================================================
bool isValidPathFormat(const std::string& path);

// Isn't actually used for the command line in this program... it's to filter padded spaces when grabbing blocks of 8 chars in decryption...
// =====================================================================================
std::string eatTrailingSpaces(std::string inStrng);


// ============== ROOT THEORY --> DYNAMIC ARRAYS AND RELATIONAL FUNCTIONS ==============================================================================================
// =====================================================================================================================================================================

// Print 64-Bit Numeric Representation...
// =====================================================================================
void prnt64bitBool(bool* pntrVar, int rows, int cols);

// Print any 2D Integer Matrix...
// =====================================================================================
void print2D_intTblLyr(int* pntrVar, int rows, int cols);

// Print a single line of a CSV file; Translating the input array into a Comma-Separated line of text...
// =====================================================================================
std::string printIntArrayToCSV(int* pntrVar, int arrayLen);

// Print 2D Integer Matrix with ASCII chars; Need 2 versions; 1 - Which takes in an integer array for debug...
// =====================================================================================
void print2D_intsWcharsMatrix(int* pntrVar, int ttlRows, int ttlCols);

// Print 2D Character Matrix; Need 2 versions; 1 - Which takes in a character array for debug...
// =====================================================================================
void print2D_charMatrix(char* pntrVar, int ttlRows, int ttlCols);

// Pass in a CSV line from a file, an array to map the data to, and the array length...
// =====================================================================================
void buildIntArrayFromCSV(std::string csvLineIn, int* buildArray, int arrayLen);



// ==================================== BASIC MATH =====================================================================================================================
// =====================================================================================================================================================================

// Basic exponential value calculator...
// =====================================================================================
unsigned long long expCalculator(int base, int exp);

// Print out miniature 64-Bit-Block with additional byte/line readout and line X line updated total summaries as you calculate a 64-bit int from a boolean 64-bit block/matrix...
// =====================================================================================
unsigned long long convert64bitBooltoInt(bool* pntrVar);



// ================================== BASIC FUNCTIONS ==================================================================================================================
// =====================================================================================================================================================================

// 8-Bit / Single-Byte Binary String Generator...
// =====================================================================================
std::string binary8bit(int valueIn);

// Take in a variable length string which recognies bracketed values, and build a boolean grid representation...
// =====================================================================================
void buildBoolGridFrom8chars(std::string inStrng, bool* pntrVar);

// Take in a variable length string which recognies bracketed values, and build a boolean grid representation...
// =====================================================================================
void buildBoolGridFromString1(std::string inStrng, bool* pntrVar);

// ==================================== Fast64 MATH ====================================================================================================================
// =====================================================================================================================================================================

// Hexadecimal Converter --> Simple function for calcualting a 64-bit integer from a standardized notation (0x) + 16 chars Hexadecimal...
// =====================================================================================
unsigned long long calcHexVal(std::string inputSeq);

// Hexadecimal Converter --> Also returns a 64-bit Boolean grid representation of the value; Used in initial seeding...
// =====================================================================================
unsigned long long fast64buildBoolInt(std::string fast64seedOut, bool* blankMatrixIn);
