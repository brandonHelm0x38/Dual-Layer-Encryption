#include "securityKey.h"


//bool debugKeySeeding = false;



// =========================== GENERATION, PARSING, & COMBINATION LOCK SECURITY KEY FUNCTIONS ==========================================================================
// =====================================================================================================================================================================

// Function takes in a seed value, and a blank [X]x[8] character matrix...
// Seed internal call to a random number generator, then builds [X]x[8] grid...
// =====================================================================================
// 128 bit (16-Character) ------> [2]x[8] Matrix Built...
// 256 bit (32-Character) ------> [4]x[8] Matrix Built...
// 512 bit (64-Character) ------> [8]x[8] Matrix Built...
// 
// 1024 bit (128-Character) ----> [16]x[8] Matrix Built... BUILD THIS VERSION !!! 4keys * 1024 = 4096 Bit Security
// 
// 2048 bit (256-Character) ----> [32]x[8] Matrix Built...

// Works for settings 128, 256, 512, 1024, 2048 !!!
// HAS TO BE BUILT WITH CORRESPONDING INITIALIZATION MATRIX, so can't nest IF statements to overload function...
// =====================================================================================
std::string genSecurityKey(unsigned long long int seedVal, char* charMatrixIn, int certBITsize) {
    if (debugKeySeeding) {
        std::cout << "\n --> STARTING FUNCTION : Line 714 : genSecurityKey64 -::|::--> Inititalizing arrays (Alphabetic && Numeric) for key generation...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
    }
    int bitsTOchars = certBITsize / 8;
    int calcRows = bitsTOchars / 8;


    // Initialize string output variable; Passed in matrix will also be available in main program as a second return...
    std::string secKeyStrng;

    // Seed the engine for generating the security key...
    std::mt19937_64 engine(seedVal);

    // Create a character array of capitalized american alphabet characters; ('A' == 65 && 'Z' == 90); Generate N chars based on charsORbits setting...
    std::uniform_int_distribution<int> asciiAlphaBounds(65, 90);
    int* secKeyAlphaArray = new int[bitsTOchars];
    // The above code sets up the function to be called in this next loop...
    for (int i = 0; i < bitsTOchars; ++i) {
        secKeyAlphaArray[i] = asciiAlphaBounds(engine);
    }
    // I know this works...
    if (debugKeySeeding) { print2D_intsWcharsMatrix(secKeyAlphaArray, 1, bitsTOchars); }

    // Create a character array of numeric characters; ('0' == 48 && '9' == 57); Generate N chars based on charsORbits setting...
    std::uniform_int_distribution<int> asciiNumBounds(48, 57);
    int* secKeyNumArray = new int[bitsTOchars];
    // The above code sets up the function to be called in this next loop...
    for (int i = 0; i < bitsTOchars; ++i) {
        secKeyNumArray[i] = asciiNumBounds(engine);
    }
    // I know this works...
    if (debugKeySeeding) { print2D_intsWcharsMatrix(secKeyNumArray, 1, bitsTOchars); }

    // Initialize a variable for stepping through and deciding which character to grab; Flip which array to grab from with even/odd; OR Flip with >/< MAX/2...
    unsigned long long int nextInt = engine();  // This will generate a new 64-bit number every time called...

    // Now loop through an overall algorithm aimed at generating X charsORbits...
    // Flip which array to grab from with even/odd; OR Flip with >/< MAX/2...
    // Build BOTH a matrix and corresponding string... HAS TO BE BUILT WITH CORRESPONDING INITIALIZATION MATRIX, so can't nest IF statements to overload function...
    int overallStepPos = 0;
    for (int currRow = 0; currRow < calcRows; currRow++) {
        for (int currCol = 0; currCol < 8; currCol++) {
            bool isEven = (nextInt % 2 == 0);
            //bool isTopHalf = nextInt > (18446744073709551615 / 2);
            bool isTopHalf = nextInt > (ULLONG_MAX / 2);

            if (isEven && isTopHalf) {
                *(charMatrixIn + currRow * 8 + currCol) = secKeyAlphaArray[overallStepPos];
                secKeyStrng = secKeyStrng + outputStrngFromASCIIval(secKeyAlphaArray[overallStepPos]);
            }
            else if (isEven && !isTopHalf) {
                *(charMatrixIn + currRow * 8 + currCol) = secKeyNumArray[overallStepPos];
                secKeyStrng = secKeyStrng + outputStrngFromASCIIval(secKeyNumArray[overallStepPos]);
            }
            else if (!isEven && isTopHalf) {
                *(charMatrixIn + currRow * 8 + currCol) = secKeyNumArray[overallStepPos];
                secKeyStrng = secKeyStrng + outputStrngFromASCIIval(secKeyNumArray[overallStepPos]);
            }
            else {
                *(charMatrixIn + currRow * 8 + currCol) = secKeyAlphaArray[overallStepPos];
                secKeyStrng = secKeyStrng + outputStrngFromASCIIval(secKeyAlphaArray[overallStepPos]);
            }

            nextInt = engine();  // This will generate a new 64-bit number every time called...
            overallStepPos++;
        }
    }

    return secKeyStrng;
}


// ============================ PARSE SECURITY KEY FUNCTIONS ===========================================================================================================
// =====================================================================================================================================================================

// This is a function that inverts the 6-value scale used with the function immediately below; Used to determine how many steps ahead in the securityKey when running (parseHexValFromKey)...
// =====================================================================================
int stepAheadXref(char valTOinverse, int* scaleStepXrefsIn2) {
    if (debugKeySeeding) {
        std::cout << "\n --> STARTING FUNCTION : Line 808 : stepAheadXref -::|::--> RUNNING...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    int outputStepInt = 0;

    if (debugKeySeeding) {
        std::cout << "\n --> INSIDE FUNCTION : stepAheadXref : Line 812 -::|::--> Check input value == " + std::to_string(valTOinverse) + "\t | And translated char == " + outputStrngFromASCIIval(valTOinverse);
    }

    //   10 - 1   |   11 - 2   |   12 - 3   |   13 - 4   |   14 - 5   |   15 - 6
    //   10 - 6   |   11 - 5   |   12 - 4   |   13 - 3   |   15 - 2   |   15 - 1
    // Map xRef's; Consider how to segment these in the code body and draw from generated tables/database files...
    if (valTOinverse == 'A')       // 65  // ~~~~~~~~~ 1st BRACKET --> For Standard Hex-Alpha xRef Range ~~~~~~~~~
        outputStepInt = *(scaleStepXrefsIn2 + 0);
    else if (valTOinverse == 'B')  // 66
        outputStepInt = *(scaleStepXrefsIn2 + 1);
    else if (valTOinverse == 'C')  // 67
        outputStepInt = *(scaleStepXrefsIn2 + 2);
    else if (valTOinverse == 'D')  // 68
        outputStepInt = *(scaleStepXrefsIn2 + 3);
    else if (valTOinverse == 'E')  // 69
        outputStepInt = *(scaleStepXrefsIn2 + 4);
    else if (valTOinverse == 'F')  // 70
        outputStepInt = *(scaleStepXrefsIn2 + 5);
    else if (valTOinverse == '0')  // 0  // ~~~~~~~~~ 2nd BRACKET --> For Standard Numeric xRef Range ~~~~~~~~~
        outputStepInt = *(scaleStepXrefsIn2 + 6);
    else if (valTOinverse == '1')  // 1
        outputStepInt = *(scaleStepXrefsIn2 + 7);
    else if (valTOinverse == '2')  // 2
        outputStepInt = *(scaleStepXrefsIn2 + 8);
    else if (valTOinverse == '3')  // 3
        outputStepInt = *(scaleStepXrefsIn2 + 9);
    else if (valTOinverse == '4')  // 4
        outputStepInt = *(scaleStepXrefsIn2 + 10);
    else if (valTOinverse == '5')  // 5
        outputStepInt = *(scaleStepXrefsIn2 + 11);
    else if (valTOinverse == '6')  // 6
        outputStepInt = *(scaleStepXrefsIn2 + 12);
    else if (valTOinverse == '7')  // 7
        outputStepInt = *(scaleStepXrefsIn2 + 13);
    else if (valTOinverse == '8')  // 8
        outputStepInt = *(scaleStepXrefsIn2 + 14);
    else if (valTOinverse == '9')  // 9
        outputStepInt = *(scaleStepXrefsIn2 + 15);
    else
        std::cout << "\n --> ERROR : stepAheadXref : Line 855 :: INVALID HEX-VALUE INPUT; CONVERSION FAILED...";

    if (debugKeySeeding) { std::cout << "\n --> !!! END FUNCTION !!! : stepAheadXref : Line 843 -::|::--> Output translated integer step-value == " + std::to_string(outputStepInt); }

    return outputStepInt;
}

// (customAZhexConverter) used in (parseHexValFromKey) immeadiately below this function...
// Translates each letter of the alphabet into a simple hex integer; xRefs all letters beyond standard range...
// This is used with a function that also inverts the 6-value scale (ABOVE)...
// =====================================================================================
std::string customAZhexConverter(char fullAZtoRandHex, int* alphaHexXrefsIn2, int* base10xRefs2) {
    if (debugKeySeeding) {
        std::cout << "\n --> STARTING FUNCTION : Line 855 : customAZhexConverter -::|::--> RUNNING...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    std::string outputCharStrng;  // RETURN VARIABLE !!! --> Consider char version that converts the asciiVal in MAIN...
    //unsigned char asciiValNotation = fullAZtoRandHex[0];

    if (debugKeySeeding) {
        std::cout << "\n --> INSIDE FUNCTION : customAZhexConverter : Line 860 -::|::--> Check input value == " + std::to_string(fullAZtoRandHex) + "\t | Which is ASCII character == " + static_cast<char>(fullAZtoRandHex);
    }


    //   A - 1   |   B - 2   |   C - 3   |   D - 4   |   E - 5   |   F - 6
    // Map xRef's; Consider how to segment these in the code body and draw from generated tables/database files...
    if (fullAZtoRandHex == '0')       // 48  // ~~~~~~~~~ 1st BRACKET ~~~~~~~~~
        outputCharStrng = std::to_string(*(base10xRefs2 + 0));
    else if (fullAZtoRandHex == '1')  // 49
        outputCharStrng = std::to_string(*(base10xRefs2 + 1));
    else if (fullAZtoRandHex == '2')  // 50
        outputCharStrng = std::to_string(*(base10xRefs2 + 2));
    else if (fullAZtoRandHex == '3')  // 51
        outputCharStrng = std::to_string(*(base10xRefs2 + 3));
    else if (fullAZtoRandHex == '4')  // 52
        outputCharStrng = std::to_string(*(base10xRefs2 + 4));
    else if (fullAZtoRandHex == '5')  // 53
        outputCharStrng = std::to_string(*(base10xRefs2 + 5));
    else if (fullAZtoRandHex == '6')  // 54
        outputCharStrng = std::to_string(*(base10xRefs2 + 6));
    else if (fullAZtoRandHex == '7')  // 55
        outputCharStrng = std::to_string(*(base10xRefs2 + 7));
    else if (fullAZtoRandHex == '8')  // 56
        outputCharStrng = std::to_string(*(base10xRefs2 + 8));
    else if (fullAZtoRandHex == '9')  // 57
        outputCharStrng = std::to_string(*(base10xRefs2 + 9));
    else if (fullAZtoRandHex == 'A')  // 65  // ~~~~~~~~~ 1st 6-char BRACKET ~~~~~~~~~
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 0));
    else if (fullAZtoRandHex == 'B')  // 66
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 1));
    else if (fullAZtoRandHex == 'C')  // 67
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 2));
    else if (fullAZtoRandHex == 'D')  // 68
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 3));
    else if (fullAZtoRandHex == 'E')  // 69
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 4));
    else if (fullAZtoRandHex == 'F')  // 70
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 5));
    else if (fullAZtoRandHex == 'G')  // 71  // ~~~~~~~~~ 2nd 6-char BRACKET ~~~~~~~~~
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 6));
    else if (fullAZtoRandHex == 'H')  // 72
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 7));
    else if (fullAZtoRandHex == 'I')  // 73
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 8));
    else if (fullAZtoRandHex == 'J')  // 74
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 9));
    else if (fullAZtoRandHex == 'K')  // 75
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 10));
    else if (fullAZtoRandHex == 'L')  // 76
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 11));
    else if (fullAZtoRandHex == 'M')  // 77  // ~~~~~~~~~ 3rd 6-char BRACKET ~~~~~~~~~
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 12));
    else if (fullAZtoRandHex == 'N')  // 78
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 13));
    else if (fullAZtoRandHex == 'O')  // 79
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 14));
    else if (fullAZtoRandHex == 'P')  // 80
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 15));
    else if (fullAZtoRandHex == 'Q')  // 81
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 16));
    else if (fullAZtoRandHex == 'R')  // 82
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 17));
    else if (fullAZtoRandHex == 'S')  // 83  // ~~~~~~~~~ 4th 6-char BRACKET ~~~~~~~~~
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 18));
    else if (fullAZtoRandHex == 'T')  // 84
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 18));
    else if (fullAZtoRandHex == 'U')  // 85
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 20));
    else if (fullAZtoRandHex == 'V')  // 86
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 21));
    else if (fullAZtoRandHex == 'W')  // 87
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 22));
    else if (fullAZtoRandHex == 'X')  // 88
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 23));
    else if (fullAZtoRandHex == 'Y')  // 89  // ~~~~~~~~~ 5th 2-char BRACKET ~~~~~~~~~
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 24));
    else if (fullAZtoRandHex == 'Z')  // 90
        outputCharStrng = outputStrngFromASCIIval(*(alphaHexXrefsIn2 + 25));
    else
        std::cout << "\n --> ERROR : customAZhexConverter : Line 953 :: INVALID INPUT; CONVERSION FAILED...";

    if (debugKeySeeding) { std::cout << "\n --> !!! END FUNCTION !!! : customAZhexConverter : Line 909 -::|::--> Output translated char == " + outputStrngFromASCIIval(fullAZtoRandHex); }

    return outputCharStrng;
}

// =====================================================================================
// 1024 bit (128-Character) ----> [16]x[8] Matrix Built... BUILD THIS VERSION !!!

// This is a function that will be internal to an app, but nest together with Cyber-Force in a way that increases security...
// MUST REMEMBER --> THIS SAME FUNCTION MUST WORK FOR BOTH ENCRYPTION & DECRYPTION AND BE PROVEN SECURE... CAN'T BE TIME-STAMP DEPENDENT !!!
// =====================================================================================
//static uint_fast64_t parseIntFromKey(string secKeyIn1024) {
std::string parseHexValFromKey(std::string secKeyIn1024, int* alphaHexXrefsIn1, int* base10xRefs1, int* scaleStepXrefsIn1) {
    if (debugKeySeeding) {
        std::cout << "\n --> STARTING FUNCTION : Line 828 : parseHexValFromKey !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    std::string convertedHexVal = "";  // RETURN VARIABLE !!!
    int dayDecidesStartPos = 3; // TUESDAY == 3; Could xRef to make each week of the year slightly unique... Generate each week and include in main security updates to apps/operating-systems?

    // For error trapping, this function should always only be used in 1024-bit/128-character key generation...
    int valInLen = secKeyIn1024.length();
    if (valInLen != 128)
        std::cout << "\n --> parseHexValFromKey :: ERROR :: INVALID INPUT...";

    // Must Hard-Code first character to begin algorithm with... True first is too predictable; COULD THIS SOMEHOW BE DAY OF THE WEEK DEPENDENT ???
    unsigned char processChar = secKeyIn1024[dayDecidesStartPos];  // Really this is 1024/8 = 128 characters...

    // Might need a function which converts asciiValues 'A'-'Z' to a HexaDecimal Conversion --> customAZhexConverter...
    // A - 10   |   B - 11   |   C - 12   |   D - 13   |   E - 14   |   F - 15
    // INVERSE for another step... If you add the customAZhexConverter output xRef for each set of 6-chars in all 26 in total, with the last 2 a random chance unique to the algorithm..
    // --------------------------> It then must decide how many characters to step ahead in the secKeyIn1024, Find a way to inverse the scale of 6 to determine the step ahead...

    // Begin primary parsing algorithm to build a 16-character Hexadecimal value...
    // Make sure your loop does not step ahead more than 120 characters (-16 ?) total...

    // Loop until you know 16 characters have been found and converted to an overall Hexadecimal string...
    int charsFound = 0;
    int trackPos = 0 + dayDecidesStartPos;
    while (charsFound < 16) {  // Only need to parse 16 total characters and convert to Hexadecimal values...
        if (debugKeySeeding) {
            std::cout << "\n --> INSIDE FUNCTION : parseHexValFromKey : Line 954 --> Starting loop through SecurityKey from overall position == " + std::to_string(trackPos) + "\t |  Building Hex string position == " + std::to_string(charsFound + 1);
        }

        std::string conversionCharStrng = customAZhexConverter(secKeyIn1024[trackPos], alphaHexXrefsIn1, base10xRefs1);
        convertedHexVal = convertedHexVal + conversionCharStrng;
        char conversionChar = static_cast<char>(conversionCharStrng[0]);
        int invStepAhead = stepAheadXref(conversionChar, scaleStepXrefsIn1);
        trackPos = trackPos + invStepAhead;
        charsFound++;

        if (debugKeySeeding) {
            std::cout << "\n --> INSIDE FUNCTION : parseHexValFromKey : Line 963 --> End parseHexValFromKey loop;\t |  Next loop stepping ahead x == " + std::to_string(invStepAhead) + " positions. \t |  To begin next loop at overall SecurityKey position == " + std::to_string(trackPos) + "\n\n";
        }
    }

    // Return the generated string in the Fast64 notation...
    return "0x" + convertedHexVal;
}


// ===================== CYBER FORCE PRIMARY AUTHETICATION FUNCTION ====================================================================================================
// =====================================================================================================================================================================

// =====================================================================================
// Function variant which takes in 3-10 character hexaDecimal sequences translated from 1024-bit keys... I think this is the primary standard to collaborate on and compartmentalize... 
// Different encryption scripts may take in a string of additional seed characters/values for further compartmentalization.
// Create a callable, recreatable PRNG that takes in this seed data, and passes out a value to a re-creatable sequential number generator...
// 
// I'VE THOUGHT ABOUT THIS MORE --> And this is a function that should make a call to a secure server and validate this is a trusted device... It must take in a device ID
// ======================================================================================
//static unsigned long long int cyberForceSecKeyComb(unsigned long long int internalSeed /* Service-Layer */, uint_fast64_t rgstrdDevID, string rgstrdDevSecKey, string osSecSecKey, string appSecKey) {  // PROD VERSION
unsigned long long int cyberForceSecKeyComb(unsigned long long int internalServiceSeed /* Service-Layer */, uint_fast64_t activeDevID, std::string simulatedAPIfilepath) {
    std::string debugMsg;
    int continueTgl;

    // In PROD, Will scan critical system resources match for a specific Active-Device-ID...
    // This function would make a call to return the valid combination, parsing each using ACTIVE-DEVOSAPP-SECURITY-TABLES to ensure all registered security keys match expected collections of products...
    if (activeDevID == 0x5555555555555555) {
        std::cout << "\n --> Simulated API : Call Cyber-Force : (-Step 0.2-) --:|:--> Cyber-Force has validated Brandon Helm's Active-Device-ID == " + std::to_string(activeDevID);
        std::cout << "\n --> Simulated API : Call Cyber-Force : (-Step 0.2-) --:|:--> Loading Active-Security-Tables to validate DEVICE; OS; APP product stack match registrations to autheticate this call...";
        std::cout << std::endl;
        std::cout << std::endl;

        debugMsg = "BREAK CHECK --> Cyber-Force Call has been made with with Active-Device-ID == " + std::to_string(activeDevID) + " --:|:--> Load DEV-OS-APP Active-Security-Tables ??? ...";
        continueTgl = checkBreak(debugMsg);
        if (continueTgl == 'N') {
            exit(1);
        }
    }
    //else
    //    return 1;

    // Open the OS & APP Active-Security-Tales using ifstream...
    std::ifstream osNappSecTablesFileIn(simulatedAPIfilepath);
    // Confirm file opening...
    std::cout << "\n --> Simulated API : Call Cyber-Force : (-Step 0.2-) --:|:--> Opening DEV-OS-APP Active-Security-Tables @: " + simulatedAPIfilepath;
    if (!osNappSecTablesFileIn.is_open()) {
        // print error message and return
        std::cerr << "\n\tFailed to open file @: " << simulatedAPIfilepath;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        exit(1);
    }
    else
        std::cout << "\n\tDEV-OS-APP Active-Security-Tables file opened successfully @: " << simulatedAPIfilepath;

    // CALIBRATE-ENCRYPTION-SEED --:|:--> Simulate an API to authenticate other system resources from the requesting device...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // These will be re-used for each parseHexValFromKey call; Overwritten with buildIntArrayFromCSV...
    int* alphaHexXrefs = new int[26];
    int* base10xRefs = new int[10];
    int* scaleStepXrefs = new int[16];

    // Device Security Layer...
    std::string alphaHexXrefsDEVkey_Strng = "";
    getline(osNappSecTablesFileIn, alphaHexXrefsDEVkey_Strng);           // Line 1 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...

    std::string alphaHexXrefsDEV_Strng = "";
    getline(osNappSecTablesFileIn, alphaHexXrefsDEV_Strng);              // Line 2 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(alphaHexXrefsDEV_Strng, alphaHexXrefs, 26);

    std::string base10xRefsDEV_Strng = "";
    getline(osNappSecTablesFileIn, base10xRefsDEV_Strng);                // Line 3 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(base10xRefsDEV_Strng, base10xRefs, 10);

    std::string scaleStepXrefsDEV_Strng = "";
    getline(osNappSecTablesFileIn, scaleStepXrefsDEV_Strng);             // Line 4 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(scaleStepXrefsDEV_Strng, scaleStepXrefs, 16);

    std::string deviceSeedHex = parseHexValFromKey(alphaHexXrefsDEVkey_Strng, alphaHexXrefs, base10xRefs, scaleStepXrefs);
    unsigned long long int deviceSeed = calcHexVal(deviceSeedHex);

    // OS Security Layer...
    std::string alphaHexXrefsOSkey_Strng = "";
    getline(osNappSecTablesFileIn, alphaHexXrefsOSkey_Strng);           // Line 5 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...

    std::string alphaHexXrefsOS_Strng = "";
    getline(osNappSecTablesFileIn, alphaHexXrefsOS_Strng);              // Line 6 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(alphaHexXrefsOS_Strng, alphaHexXrefs, 26);

    std::string base10xRefsOS_Strng = "";
    getline(osNappSecTablesFileIn, base10xRefsOS_Strng);                // Line 7 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(base10xRefsOS_Strng, base10xRefs, 10);

    std::string scaleStepXrefsOS_Strng = "";
    getline(osNappSecTablesFileIn, scaleStepXrefsOS_Strng);             // Line 8 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(scaleStepXrefsOS_Strng, scaleStepXrefs, 16);

    std::string osSeedHex = parseHexValFromKey(alphaHexXrefsDEVkey_Strng, alphaHexXrefs, base10xRefs, scaleStepXrefs);
    unsigned long long int osSeed = calcHexVal(osSeedHex);

    // APP Security Layer...
    std::string alphaHexXrefsAPPkey_Strng = "";
    getline(osNappSecTablesFileIn, alphaHexXrefsAPPkey_Strng);           // Line 5 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...

    std::string alphaHexXrefsAPP_Strng = "";
    getline(osNappSecTablesFileIn, alphaHexXrefsAPP_Strng);              // Line 6 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(alphaHexXrefsAPP_Strng, alphaHexXrefs, 26);

    std::string base10xRefsAPP_Strng = "";
    getline(osNappSecTablesFileIn, base10xRefsAPP_Strng);                // Line 7 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(base10xRefsAPP_Strng, base10xRefs, 10);

    std::string scaleStepXrefsAPP_Strng = "";
    getline(osNappSecTablesFileIn, scaleStepXrefsAPP_Strng);             // Line 8 from OS & APP Active Security Tables file; Replace with Cyber-Force DataBase API...
    buildIntArrayFromCSV(scaleStepXrefsAPP_Strng, scaleStepXrefs, 16);

    std::string appSeedHex = parseHexValFromKey(alphaHexXrefsAPPkey_Strng, alphaHexXrefs, base10xRefs, scaleStepXrefs);
    unsigned long long int appSeed = calcHexVal(appSeedHex);

    // Combine parsed values to simulate key combination functionality...
    return deviceSeed + osSeed + appSeed + internalServiceSeed;

    //uint_fast64_t key1 = 0xb5026f5aa96619e9;    // Will come from hidden system resources tables;  Needs to be repeatable for testing...
    //uint_fast64_t key2 = 0x5555555555555555;    // Will come from hidden system resources tables;  Needs to be repeatable for testing...
    //uint_fast64_t key3 = 0x71d67fffeda60000;    // Will come from hidden system resources tables;  Needs to be repeatable for testing...
    //uint_fast64_t generatedKey;                 // 
    //uint_fast64_t timeSeed = unixEp;            // Will require logging last unixEpoch of most recent IAM call into hidden system resources tables;  Needs to be repeatable for testing...

    ////typedef mersenne_twister_engine<uint_fast64_t, 64, 312, 156, 31, 0xb5026f5aa96619e9, 29, 0x5555555555555555, 17, 0x71d67fffeda60000, 37, 0xfff7eee000000000, 43, 6364136223846793005> mt19937_64;      //
    //typedef mersenne_twister_engine<uint_fast64_t, 64, 312, 156, 31, 0xb5026f5aa96619e9, 29, 0x5555555555555555, 17, 0x71d67fffeda60000, 37, 0xfff7eee000000000, 43, timeSeed> mt19937_64;      //
    //
}