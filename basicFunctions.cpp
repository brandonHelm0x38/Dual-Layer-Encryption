#include "basicFunctions.h"


//bool debugKeySeeding = false;
//bool debugPrimaryInternals = false;
//bool debugByteLineReadout = false;
//
//bool oldPASSEDdebug = false;


// ==================================== BASIC DEBUG ====================================================================================================================
// =====================================================================================================================================================================

// Basic function for interupting processing; Break-Check outputs and whether to continue the program...
// =====================================================================================
char checkBreak(std::string msg) {
    char cTgl;
    char original;
    char upperCase;
    std::cout << "\n\n" + msg;
    std::cout << "\nContinue the program? Enter y/Y for Yes or n/N for No...";
    std::cin >> cTgl;
    upperCase = std::toupper(cTgl);
    while (upperCase != 'N' && upperCase != 'Y') {
        std::cout << "\nYou did not enter y/Y for Yes or n/N for No...";
        std::cout << "\nContinue the program? Enter y/Y for Yes or n/N for No...";
        std::cin >> cTgl;
        upperCase = std::toupper(cTgl);
    }
    return upperCase;
}

// Function which handles menu options interface for command line...
// =====================================================================================
char validToggleChar(char* validArray, std::string functionMsg, int validArrayLen) {
    char* orgPntr = validArray;
    std::string cTgl;
    int cTgl_Len = 0;
    unsigned char charToggle = '0';
    int charVal;
    std::string loopCharStrng;
    bool validLen = false;
    bool inArray = false;

    // Display FUNCTION MESSAGE; Ask for single charcater option selection input...
    std::cout << functionMsg;

    // Perform 1st logic check...
    while (!validLen || !inArray) {
        std::cout << "\nPlease enter a single, valid charcater in this set... [ ";
        //Print Valid Set...
        for (int a = 0; a < validArrayLen; a++) {
            charVal = *(orgPntr + a);
            loopCharStrng = static_cast<char>(charVal);
            std::cout << loopCharStrng + " ";
        }
        std::cout << "]";
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Enter Value == ";
        std::cin >> cTgl;
        cTgl_Len = cTgl.length();

        if (cTgl_Len == 1) {
            validLen = true;

            // Perform 2nd logic check...
            for (int a = 0; a < validArrayLen; a++) {
                char loopChar2 = *(orgPntr + a);
                if (cTgl[0] == loopChar2) {
                    std::cout << "\nSUCCESS --> Value Found in Valid Options Array... ";
                    inArray = true;
                    charToggle = static_cast<char>(cTgl[0]);
                    break;
                }
                else {
                    inArray = false;
                    charToggle = '0';
                }
            }
            if (!inArray)
                std::cout << "\nYou did not enter a valid value in the defined option set... ";
        }
        else
            std::cout << "\nYou entered more than 1 character...";
    }

    return charToggle;
}

// Function for printing debug output... take in string, and pad a set number of characters; (string, length, L/R) --> L == Left Justify (string|padSpaces) ; R == Right Justify (padSpaces|string)...
// =====================================================================================
std::string padOutput(std::string data, int outFieldLen, char justifySide) {
    int inStrngLen = data.length();
    int padSpaceCnt = outFieldLen - inStrngLen;
    std::string paddedData = "";
    std::string spacesStrng = "";

    for (int a = 0; a < padSpaceCnt; a++) {
        spacesStrng = spacesStrng + " ";
    }

    if (justifySide == 'L')
        paddedData = data + spacesStrng;
    else if (justifySide == 'R')
        paddedData = spacesStrng + data;
    else
        std::cout << "\n --> Inside Function : Line 120 : padOutput --> ERROR; Function was not initialied to tell whether to Left/Right justify the output data; CHECK YOUR CALL TO THIS FUNCTION !!!";

    return paddedData;
}

// Easier to use this function when outputting char-value conversions
// =====================================================================================
std::string outputStrngFromASCIIval(int asciiVal) {
    std::string asciiOut;
    asciiOut = asciiOut + static_cast<char>(asciiVal);
    return asciiOut;
}

// Logic check to ensure user is inputting valid Windows filepaths; MODIFY for Mac/Linux...etc...
// =====================================================================================
bool isValidPathFormat(const std::string& path) {
    // Basic regex for Windows paths (can be adapted for Linux/macOS)
    // This example allows drive letters, backslashes, and common filename characters.
    std::regex path_regex(R"(^[a-zA-Z]:\\(?:[^\\/:*?"<>|\r\n]+\\)*[^\\/:*?"<>|\r\n]*$)");
    return std::regex_match(path, path_regex);
}

// Isn't actually used for the command line in this program... it's to filter padded spaces when grabbing blocks of 8 chars in decryption...
// =====================================================================================
std::string eatTrailingSpaces(std::string inStrng) {
    std::string outStrng;
    int lineLength = inStrng.length();

    char currChar = inStrng[lineLength - 1];

    int subtractSpcs = 0;
    while (currChar == ' ') {
        subtractSpcs++;
        currChar = inStrng[lineLength - 1 - subtractSpcs];
    }

    outStrng = inStrng.substr(0, lineLength - subtractSpcs);

    return outStrng;
}

// ============== ROOT THEORY --> DYNAMIC ARRAYS AND RELATIONAL FUNCTIONS ==============================================================================================
// =====================================================================================================================================================================

// Print 64-Bit Numeric Representation...
// =====================================================================================
void prnt64bitBool(bool* pntrVar, int rows, int cols) { // int maxX, int maxY --> NOT NEEDED
    // Displaying the 2D array...
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::string strngCnv = std::to_string(*(pntrVar + i * cols + j));;
            std::string padSpc = "";
            int strngLen = strngCnv.length();
            int fieldTotal = 5;
            int padTtl = fieldTotal - strngLen;
            for (int i = 0; i < padTtl; i++)
                padSpc = padSpc + " ";
            std::cout << padSpc + strngCnv << " ";
        }
        // Consider making a change to remove the line-feeds; Must add those to debug outputs elsewhere...
        std::cout << std::endl;
        std::cout << std::endl;
    }
}

// Print any 2D Integer Matrix...
// =====================================================================================
void print2D_intTblLyr(int* pntrVar, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::string strngCnv = std::to_string(*(pntrVar + i * cols + j));;
            std::string padSpc = "";
            int strngLen = strngCnv.length();
            int fieldTotal = 5;
            int padTtl = fieldTotal - strngLen;
            for (int i = 0; i < padTtl; i++)
                padSpc = padSpc + " ";
            std::cout << padSpc + strngCnv << " ";
        }
    }
}

// Print a single line of a CSV file; Translating the input array into a Comma-Separated line of text...
// =====================================================================================
std::string printIntArrayToCSV(int* pntrVar, int arrayLen) {
    std::string convertedLine = "";  // RETURN VARIABLE
    for (int i = 0; i < arrayLen; i++) {
        std::string arrayVal = std::to_string(*(pntrVar + i));;

        // Add commas from all but the last value in the array...
        if (i < arrayLen - 1)
            convertedLine = convertedLine + arrayVal + ", ";
        else
            convertedLine = convertedLine + arrayVal + "\n";
    }
    return convertedLine;
}

// Print 2D Integer Matrix with ASCII chars; Need 2 versions; 1 - Which takes in an integer array for debug...
// =====================================================================================
void print2D_intsWcharsMatrix(int* pntrVar, int ttlRows, int ttlCols) {
    for (int currRow = 0; currRow < ttlRows; currRow++) {
        for (int currCol = 0; currCol < ttlCols; currCol++) {
            char currChar = *(pntrVar + currRow * ttlCols + currCol);
            std::string intStrng = padOutput(std::to_string(currChar), 5, 'R');
            std::string charStrng = padOutput(outputStrngFromASCIIval(currChar), 5, 'L');

            if (currCol == ttlCols - 1)
                std::cout << intStrng + " / " + charStrng << std::endl;
            else
                std::cout << intStrng + " / " + charStrng + " | ";
        }
        std::cout << std::endl;
    }
}

// Print 2D Character Matrix; Need 2 versions; 1 - Which takes in a character array for debug...
// =====================================================================================
void print2D_charMatrix(char* pntrVar, int ttlRows, int ttlCols) {
    for (int currRow = 0; currRow < ttlRows; currRow++) {
        for (int currCol = 0; currCol < ttlCols; currCol++) {
            char currChar = *(pntrVar + currRow * ttlCols + currCol);
            std::string intStrng = padOutput(std::to_string(currChar), 5, 'R');
            std::string charStrng = padOutput(outputStrngFromASCIIval(currChar), 5, 'L');

            if (currCol == ttlCols - 1)
                std::cout << intStrng + " / " + charStrng << std::endl;
            else
                std::cout << intStrng + " / " + charStrng + " | ";
        }
        std::cout << std::endl;
    }
}

// Pass in a CSV line from a file, an array to map the data to, and the array length...
// =====================================================================================
void buildIntArrayFromCSV(std::string csvLineIn, int* buildArray, int arrayLen) {
    int lineLength = csvLineIn.length();
    int buildArrayPos = 0;
    int inLinePos = 0;
    int fieldLen = 0;

    std::string convVal = "";

    while (buildArrayPos < arrayLen) {

        unsigned char currChar = csvLineIn[inLinePos];

        // Knowing you won't need this for the last iteration as it assumes an integer will be there after a space...
        if (buildArrayPos == arrayLen - 1) {
            //std::cout << "\n --> INSIDE FUNCTION : buildIntArrayFromCSV : Line 238 --> Grabbing value to convert starting at position == " + std::to_string(inLinePos + 1) + " and ending at position == " + std::to_string(lineLength - inLinePos + 1);
            convVal = csvLineIn.substr(inLinePos + 1, lineLength - inLinePos + 1);
            //std::cout << "\n --> INSIDE FUNCTION : buildIntArrayFromCSV : Line 240 --> Debug stoi coversion from string == " + convVal;
            *(buildArray + buildArrayPos) = std::stoi(convVal);

            buildArrayPos++;
        }
        else if (currChar == ',') {
            //std::cout << "\n --> INSIDE FUNCTION : buildIntArrayFromCSV : Line 246 --> Grabbing value to convert starting at position == " + std::to_string(inLinePos + 1) + " and ending at position == " + std::to_string(fieldLen);
            convVal = csvLineIn.substr(inLinePos - fieldLen, fieldLen);
            //std::cout << "\n --> INSIDE FUNCTION : buildIntArrayFromCSV : Line 248 --> Debug stoi coversion from string == " + convVal;
            *(buildArray + buildArrayPos) = std::stoi(convVal);

            fieldLen = 0;       // Reset each time you find a comma; Knowing you won't need this for the last iteration as it assumes an integer will be there after a space...
            inLinePos++;
            buildArrayPos++;
        }
        else {  // (currChar != ',') 
            inLinePos++;
            fieldLen++;
        }

    }  // End of for search field or build array position X loop...
}


// ==================================== BASIC MATH =====================================================================================================================
// =====================================================================================================================================================================

// Basic exponential value calculator...
// =====================================================================================
unsigned long long expCalculator(int base, int exp) {
    unsigned long long fTotalVal = base;

    if (base == 0 && exp == 0) {
        fTotalVal = 0;
    }
    else if (base > 0 && exp == 0) {
        fTotalVal = 1;
    }
    else {
        for (int i = 1; i < exp; i++) {
            fTotalVal = fTotalVal * base;
        }
    }
    return fTotalVal;
}

// Print out miniature 64-Bit-Block with additional byte/line readout and line X line updated total summaries as you calculate a 64-bit int from a boolean 64-bit block/matrix...
// =====================================================================================
unsigned long long convert64bitBooltoInt(bool* pntrVar) {
    bool* orgPntr = pntrVar;

    unsigned long long recapCalc = 0;
    unsigned long long expReturn = 0;
    int expCntDwn = 63;
    for (int loopRow = 0; loopRow < 8; loopRow++) {
        int rowInverse = 8 - loopRow;
        unsigned int byteTotal = 0;
        unsigned long long byteLong = 0;
        std::string funcDebug = "";
        std::string funcDebug2 = "";

        // Update byteTotal Calculation...
        for (int loopCol = 8; loopCol > 0; loopCol--) {
            // Set initial variables...
            int colInverse = 8 - loopCol;
            bool flagAdd = *(pntrVar + loopRow * 8 + colInverse);
            int recapExp = 0;

            // Flag difference between last row, and all others...
            bool lastRow = (loopRow == 7);
            bool firstRow = (loopRow == 0);
            bool lastCol = (loopCol == 1);
            bool firstCol = (loopCol == 8);

            // Update byteTotal Calculation...
            if (flagAdd) {
                // I know this is right every time;  
                int byteExp = loopCol - 1;
                byteTotal = byteTotal + expCalculator(2, byteExp);

                // Already in 'Flag-Add' loop corresponding to seeing a '1', so add 1...
                if (lastRow) {
                    if (lastCol) {
                        expReturn = 1;
                    }
                    else {  // Should never be possible to hit as we're in a Boolean check for bit math...
                        recapExp = expCntDwn; // Should be counting backwards from 8; and must catch when=0...
                        expReturn = expCalculator(2, recapExp);
                    }
                }
                // For all other rows..
                else {
                    recapExp = expCntDwn;
                    expReturn = expCalculator(2, recapExp);
                }
                byteLong = byteLong + expReturn;
            }
            if (lastCol) { recapCalc = recapCalc + byteLong; };
            expCntDwn--;
            // Read Out Generation...
            // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
            if ((colInverse == 0) && (loopRow == 0))
                funcDebug = "\n\n";
            // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
            if ((colInverse == 7) && (loopRow == 7)) { // End of Matrix...
                funcDebug = funcDebug + std::to_string(*(pntrVar + loopRow * 8 + colInverse)) + " - Byte/Line Total = " + std::to_string(byteTotal) + " / " + static_cast<char>(byteTotal) + "\t";
                // Perhaps consider a simple loop here for gauging digit-length of generated value, and account for the tabs &| spaces... 
                std::string runTtlStrng = std::to_string(byteLong);
                std::string runTtlStrng2 = std::to_string(recapCalc);
                std::string padSpcStrng = "";
                int strngLeng = runTtlStrng.length();
                int strngLeng2 = runTtlStrng2.length();
                int padCnt = 25 - strngLeng;
                for (int i = 0; i < padCnt; i++) {
                    padSpcStrng = padSpcStrng + " ";
                }
                std::string prettyPrint1 = padSpcStrng + runTtlStrng;
                padSpcStrng = "";
                padCnt = 25 - strngLeng2;
                for (int i = 0; i < padCnt; i++) {
                    padSpcStrng = padSpcStrng + " ";
                }
                std::string prettyPrint2 = padSpcStrng + runTtlStrng2;
                funcDebug = funcDebug + "\t |  Value to Add : " + prettyPrint1 + "\t |  New Updated Total : " + prettyPrint2 + "\n";

                if (debugKeySeeding || debugByteLineReadout) { std::cout << funcDebug; }

            }
            else if (colInverse == 7) { // End of Row...
                funcDebug = funcDebug + std::to_string(*(pntrVar + loopRow * 8 + colInverse)) + " - Byte/Line Total = " + std::to_string(byteTotal) + " / " + static_cast<char>(byteTotal) + "\t";
                // Perhaps consider a simple loop here for gauging digit-length of generated value, and account for the tabs &| spaces... 
                std::string runTtlStrng = std::to_string(byteLong);
                std::string runTtlStrng2 = std::to_string(recapCalc);
                std::string padSpcStrng = "";
                int strngLeng = runTtlStrng.length();
                int strngLeng2 = runTtlStrng2.length();
                int padCnt = 25 - strngLeng;
                for (int i = 0; i < padCnt; i++) {
                    padSpcStrng = padSpcStrng + " ";
                }
                std::string prettyPrint1 = padSpcStrng + runTtlStrng;
                padSpcStrng = "";
                padCnt = 25 - strngLeng2;
                for (int i = 0; i < padCnt; i++) {
                    padSpcStrng = padSpcStrng + " ";
                }
                std::string prettyPrint2 = padSpcStrng + runTtlStrng2;
                funcDebug = funcDebug + "\t |  Value to Add : " + prettyPrint1 + "\t |  New Updated Total : " + prettyPrint2 + "\n";

                if (debugKeySeeding || debugByteLineReadout) { std::cout << funcDebug; }

            }
            else {
                funcDebug = funcDebug + std::to_string(*(pntrVar + loopRow * 8 + colInverse)) + " ";
            }
        }   // Read-Out Generation works as expected...^^
    }       // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-

    return recapCalc;
}


// ================================== BASIC FUNCTIONS ==================================================================================================================
// =====================================================================================================================================================================

// 8-Bit / Single-Byte Binary String Generator...
// =====================================================================================
std::string binary8bit(int valueIn) {
    // This should always only be called with an int; Must check bounds first...
    if (valueIn > 255) {
        std::cout << "\n -- binary8bit -::|::- Invalid Input / Value greater that 255... ";
        return 0;
    }
    std::string stringOut = "";
    bool boolSeqarray[8] = { false };
    int stepPos = 0;
    int remVal = valueIn;
    int preCalc;

    // Now I just need to adjust this so it accounts for even division by 2 on each iteration...
    for (int i = 7; i >= 0; i--) {
        float divisor = expCalculator(2, i) * 1.00;
        float dblVal = remVal / divisor;
        bool flagBit = (1.0 <= dblVal);
        bool flagCeil = (2.0 >= dblVal);

        if (flagBit) {
            if (flagCeil) {
                stringOut = stringOut + "1";
                preCalc = remVal;
                int modRem = expCalculator(2, i);
                remVal = remVal % (modRem);     // Offset the remaining value when division is possible...
            }
            else {
                std::cout << "\n    binary8bit == ERROR --> THIS SHOULD NEVER RUN; OR ONLY RUN IF ( dblVal>2.0 )";
            }
        }
        else {
            stringOut = stringOut + "0";
        }
        stepPos++;
    }
    return stringOut;
}

// Take in a variable length string which recognies bracketed values, and build a boolean grid representation...
// =====================================================================================
void buildBoolGridFrom8chars(std::string inStrng, bool* pntrVar) {
    if (debugPrimaryInternals || debugByteLineReadout) {
        std::cout << "\n --> STARTING FUNCTION : Line 361 : buildBoolGridFrom8chars !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    bool* orgPntr = pntrVar;
    int row = 0;
    int intVal;

    int loopCntr = 0;
    int strngLen8 = inStrng.length();
    unsigned char currCharSrch;

    std::string currCharStrng = "";
    std::string outputStrng = "";

    while (row < strngLen8) {
        loopCntr++;

        currCharSrch = inStrng[row];
        currCharStrng = inStrng[row];
        int intVal = currCharSrch;

        if (debugByteLineReadout) { std::cout << "\n --> INSIDE FUNCTION : Line 383 : buildBoolGridFrom8chars --> Loop to build encrypted value-position # " + std::to_string(loopCntr) + "\t |  From intVal == " + std::to_string(intVal) + "\t |  Which translates to currCharStrng == " + currCharStrng; }

        // SPEED-OP !!! --> Take in an Letter and build a row of boolean grid representation; Taking in a Pointer to flip bits; 
        // THUS Bypassing the need to use a string variable... Something like this is used in bool64bitMask_EN2, only entire matrix is passed...
        // ROOT-THEORY-FUNCTION --> Passing an array to loop until a matrix is built is part of a relational DB system !!!
        // =====================================================================================
        // Now write the value row to boolean grid... this should always work out to be 8 chars, based on earlier math above...
        // intVal is set; now write to row, which is tracked with cntRows...
        std::string flagStrng = binary8bit(intVal);
        for (int col = 0; col < 8; col++) {
            pntrVar = orgPntr + row * 8 + col;
            if (flagStrng[col] == '1') {
                //std::cout << "\n --> Found '1' at position : " + std::to_string(col);
                *(pntrVar) = true;
            }
            else
                *(pntrVar) = false;
        }
        row++;
        if (oldPASSEDdebug) { std::cout << "\n --> GET PAST --> Line 402 : Ready to process next value? - Check Break Loop; (row), updated; Checking next string8 position == " + std::to_string(row); }
    }
    if (debugByteLineReadout || debugPrimaryInternals) { std::cout << std::endl; } // Needed to pad extra line feed after outputing read-out...
}

// Take in a variable length string which recognies bracketed values, and build a boolean grid representation...
// =====================================================================================
void buildBoolGridFromString1(std::string inStrng, bool* pntrVar) {
    if (debugByteLineReadout) {
        std::cout << "\n --> STARTING FUNCTION : Line 405 : buildBoolGridFromString1 !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    bool* orgPntr = pntrVar;
    int a = 0;
    int intVal;
    int cntRows = -1;
    int loopCntr = 0;
    int foundCappedVals = 0;
    int strngLen = inStrng.length();
    int trackOffset = 0;
    int fndValLengthAdjLast;
    int fndValLengthAdjTotal = 0;
    unsigned char currCharSrch;
    unsigned char capCharSrch;
    std::string currCharStrng = "";
    std::string outputStrng = "";

    while (a < strngLen) {
        loopCntr++;
        if (debugStringBuild) { std::cout << "\n\n\n --> INSIDE FUNCTION : Line 426 : buildBoolGridFromString1 --> Loop to find encrypted value-position # " + std::to_string(loopCntr); }
        if (debugStringBuild) { std::cout << "\n --> INSIDE FUNCTION : Line 427 : buildBoolGridFromString1 --> Processing input string position / a == " + std::to_string(a); }
        int intVal = -1; // Is not used in processing, only to convert value to boolean array...

        fndValLengthAdjLast = 0;

        std::string intStrng = "";  // Set for tracking current value to transplant...

        int startPos = 0;
        int snglCharsFnd = 0;

        currCharSrch = inStrng[a];
        currCharStrng = inStrng[a];
        startPos = a;

        if (debugStringBuild) { std::cout << "\n --> INSIDE FUNCTION : Line 441 : buildBoolGridFromString1 :\t currCharStrng == " + currCharStrng; }

        unsigned char capCharSrch;
        unsigned char nextCharSrch;
        std::string capCharStrng;
        std::string nextCharStrng;
        bool capsuleVal = false;
        bool isValidNum = false;

        if (currCharSrch == '(') {
            // Encryption will ensure that all original '(' characters are encoded as (40) coming out of bitMaskTwistCharsEN, or encapsulated ASCII values to prevent processing errors...
            int iterCnt = 1;
            if (debugStringBuild) { std::cout << "\n --> INSIDE FUNCTION : Line 453 : buildBoolGridFromString1 : Found '(' at location == " + std::to_string(a); }

            // Write to check very next ( 1 2 3 )
            while (!capsuleVal && iterCnt <= 3) {
                if (a + iterCnt > strngLen) {
                    nextCharSrch = inStrng[strngLen - 1];
                    nextCharStrng = inStrng[strngLen - 1];
                }
                else {
                    nextCharSrch = inStrng[a + iterCnt];
                    nextCharStrng = inStrng[a + iterCnt];
                }

                // Logic that makes sure we have math that runs until the end of the string only and then stays set to the last character.
                if (a + iterCnt + 1 > strngLen) {
                    capCharSrch = inStrng[strngLen - 1];
                    capCharStrng = inStrng[strngLen - 1];
                }
                else {
                    capCharSrch = inStrng[a + iterCnt + 1];
                    capCharStrng = inStrng[a + iterCnt + 1];
                }
                if (debugStringBuild) { std::cout << "\n --> INSIDE FUNCTION : Line 475 : buildBoolGridFromString1 :\t nextCharSrch == " + nextCharStrng + "\t | capCharSrch == " + capCharStrng; }


                // NEED TO ADD CHECK --> isValidNum (asciiVal > 47 $$ asciiVal < 58 )  // 3 Valid nums needed  // 
                if (47 < nextCharSrch < 58) {
                    isValidNum = true;
                    fndValLengthAdjLast++;
                }
                else {
                    isValidNum = false;
                }

                if (capCharSrch == ')' && isValidNum) {
                    if (debugStringBuild) { std::cout << "\n --> INSIDE FUNCTION : Line 488 : buildBoolGridFromString1 : Found capped value / ')' at location == " + std::to_string(a + iterCnt + 1); }
                    foundCappedVals++;
                    capsuleVal = true;

                    // This is grabbing correctly...
                    intStrng = inStrng.substr(startPos + 1, fndValLengthAdjLast);

                    fndValLengthAdjTotal = fndValLengthAdjTotal + fndValLengthAdjLast;
                    //break;
                }
                iterCnt++;
            }
        }


        if (capsuleVal) {
            if (debugByteLineReadout) { std::cout << "\n --> INSIDE FUNCTION : Line 504 : buildBoolGridFromString1 : Debug STOI conversion -->   \t |  intVal conversion to integer from intStrng == " + intStrng; }
            intVal = std::stoi(intStrng);
            cntRows++;
            //The other version in MAIN calculates blocks found for sets of 8 to start a new string, this one needs the cnt of steps/positions built so far... in this case, the cntRows variable used for building rows/lines of the permutations matrix...
            a = a + fndValLengthAdjLast + 2;
        }
        else {
            //currCharSrch = inStrng[a + trackOffset];
            intVal = currCharSrch;
            if (debugByteLineReadout) { std::cout << "\n --> INSIDE FUNCTION : Line 513 : buildBoolGridFromString1 : Ready to process intVal? -->\t |  intVal == " + std::to_string(intVal) + "\t |  and variable currCharSrch == " + std::to_string(currCharSrch) + " / " + static_cast<char>(currCharSrch); }
            snglCharsFnd++;
            cntRows++;
            a++;
        }

        if (oldPASSEDdebug) { std::cout << "\n --> GET PAST --> Line 519 : Ready to process intVal? -::|::- intVal == " + std::to_string(intVal); }

        // SPEED-OP !!! --> Take in an Letter and build a row of boolean grid representation; Taking in a Pointer to flip bits; 
        // THUS Bypassing the need to use a string variable... Something like this is used in bool64bitMask_DE2, only entire matrix is passed...
        // ROOT-THEORY-FUNCTION --> Passing an array to loop until a matrix is built is part of a relational DB system !!!
        // =====================================================================================
        // Now write the value row to boolean grid... this should always work out to be 8 chars, based on earlier math above...
        // intVal is set; now write to row, which is tracked with cntRows...
        std::string flagStrng = binary8bit(intVal);
        for (int col = 0; col < 8; col++) {
            pntrVar = orgPntr + cntRows * 8 + col;
            if (flagStrng[col] == '1')
                *(pntrVar) = true;
            else
                *(pntrVar) = false;
        }
        if (oldPASSEDdebug) { std::cout << "\n --> GET PAST --> Line 437 : Ready to process next value? :: trackOffset == " + std::to_string(trackOffset) + "\t and new 'a' == " + std::to_string(a); }
    }
}

// ==================================== Fast64 MATH ====================================================================================================================
// =====================================================================================================================================================================

// Hexadecimal Converter --> Simple function for calcualting a 64-bit integer from a standardized notation (0x) + 16 chars Hexadecimal...
// =====================================================================================
unsigned long long calcHexVal(std::string inputSeq) {
    if (debugPrimaryInternals) {
        std::cout << "\n --> STARTING FUNCTION : Line 415 : calcHexVal !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    int inStrngLen = inputSeq.length();
    std::string hexSeq = inputSeq.substr(0, 2);
    bool chkValid = (hexSeq == "0x") && (inStrngLen == 18);

    unsigned long long fTotalVal = 0;
    unsigned long long addedVal = 0;

    // I think I can code this several ways because of the consistent structure... And this may be an example where proper 'threading' may enhance speed considerably...
    // I'm generally guessing it makes sense to start with the smallest values and data types for the first iterations, and then redefine the data hand-offs by loop stage...
    int itrCntr = 0;
    if (chkValid) {
        for (int loopCntr = 8; loopCntr > 0; loopCntr--) {
            int grabPos = loopCntr * 2;
            int hexGrp = (9 - loopCntr);
            hexSeq = inputSeq.substr(grabPos, 2);

            for (int innrLoop = 0; innrLoop < 2; innrLoop++) {
                std::string hexCharStrng = "";
                bool evenFlag = innrLoop == 0;
                int startPos = 0;
                int expCalc = 0;

                if (evenFlag && hexGrp == 1) {
                    itrCntr = 1;
                    startPos = 16;
                    expCalc = 1;
                }
                else if (!evenFlag && (hexGrp == 1)) {
                    itrCntr = 2;
                    startPos = 17;
                    expCalc = 0;
                }
                else if (evenFlag && (hexGrp >= 2)) {
                    itrCntr++;
                    startPos = 18 - (itrCntr + 1);
                    expCalc = ((innrLoop + 2) * hexGrp) - 1;
                }
                else if (!evenFlag && (hexGrp >= 2)) {
                    itrCntr++;
                    startPos = 18 - (itrCntr - 1);
                    expCalc = ((innrLoop + 1) * hexGrp) - 2;
                }
                else if (evenFlag && (hexGrp == 8)) {
                    itrCntr++;
                    startPos = 2;
                    expCalc = ((innrLoop + 2) * hexGrp) - 1;
                }
                else if (!evenFlag && (hexGrp == 8)) {
                    itrCntr++;
                    startPos = 3;
                    expCalc = ((innrLoop + 1) * hexGrp) - 2;
                }

                hexCharStrng = inputSeq.substr(startPos, 1);
                char hexChar = static_cast<char>(hexSeq[innrLoop]);
                char upperCase = std::toupper(hexChar);
                // This needs to be coded differently for error-trapping...
                bool validNum = (48 <= hexChar && hexChar <= 57);
                bool validHex = (65 <= upperCase && upperCase <= 70);
                int hexVal = 0;
                // This needs logic to skip this conversion if the character isn't numeric...
                if (validNum) {
                    hexVal = std::stoi(hexCharStrng);
                }
                else if (validHex) {
                    upperCase = std::toupper(hexChar);
                }
                else if (!validHex) {
                    upperCase = std::toupper(hexChar);
                    std::cout << "\n    -::|::- TERMINATING HEX CONVERSION FUNCTION --> BAD INPUT! ";
                    break;
                }

                unsigned long long firstCalc;
                firstCalc = expCalculator(16, expCalc);

                if (upperCase == 'A') {
                    addedVal = firstCalc * 10;
                    fTotalVal = fTotalVal + addedVal;
                }
                else if (upperCase == 'B') {
                    addedVal = firstCalc * 11;
                    fTotalVal = fTotalVal + addedVal;
                }
                else if (upperCase == 'C') {
                    addedVal = firstCalc * 12;
                    fTotalVal = fTotalVal + addedVal;
                }
                else if (upperCase == 'D') {
                    addedVal = firstCalc * 13;
                    fTotalVal = fTotalVal + addedVal;
                }
                else if (upperCase == 'E') {
                    addedVal = firstCalc * 14;
                    fTotalVal = fTotalVal + addedVal;
                }
                else if (upperCase == 'F') {
                    addedVal = firstCalc * 15;
                    fTotalVal = fTotalVal + addedVal;
                }
                else {
                    addedVal = firstCalc * hexVal;
                    fTotalVal = fTotalVal + addedVal;
                }
            }
        }
    }
    else {
        std::cout << "Calculating the Hex-Value failed! Bad Input! \n";
    }
    return fTotalVal;
}

// Hexadecimal Converter --> Also returns a 64-bit Boolean grid representation of the value; Used in initial seeding...
// =====================================================================================
unsigned long long fast64buildBoolInt(std::string fast64seedOut, bool* blankMatrixIn) {
    if (debugKeySeeding) {
        std::cout << "\n --> STARTING FUNCTION : Line 568 : fast64buildBoolInt !!!";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }

    bool* pntrVar1A = new bool[8 * 8];
    pntrVar1A = blankMatrixIn;

    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    // Seed out your similar Read-In strategy... Only Read-In by byte and translate accordingly...
    int inStrngLen = fast64seedOut.length();
    std::string hexSeq = fast64seedOut.substr(0, 2);
    bool chkValid = (hexSeq == "0x") && (inStrngLen == 18);

    int itrCntr = 1;
    if (chkValid) {
        for (int loopCntr = 0; loopCntr < 8; loopCntr++) {
            int grabPos = 2 + (loopCntr * 2);
            int hexGrp = (1 + loopCntr);
            hexSeq = fast64seedOut.substr(grabPos, 2);

            // This step should only be calculating 1-byte / 0-255 values...
            unsigned int iterVal = 0;
            unsigned int firstCalc = 0;

            for (int innrLoop = 0; innrLoop < 2; innrLoop++) {
                std::string hexCharStrng = "";
                bool evenFlag = innrLoop == 0;
                int startPos = 0;
                int expCalc = 0;

                if (evenFlag) {
                    itrCntr++;
                    startPos = itrCntr;  // Should start at 2...
                    expCalc = 1;
                }
                else if (!evenFlag) {
                    itrCntr++;
                    startPos = itrCntr;
                    expCalc = 0;
                }


                hexCharStrng = fast64seedOut.substr(startPos, 1);
                char hexChar = static_cast<char>(hexSeq[innrLoop]);
                char upperCase = std::toupper(hexChar);
                // This needs to be coded differently for error-trapping...
                bool validNum = (48 <= hexChar && hexChar <= 57);
                bool validHex = (65 <= upperCase && upperCase <= 70);
                int hexVal = 0;
                // This needs logic to skip this conversion if the character isn't numeric...
                if (validNum) {
                    hexVal = std::stoi(hexCharStrng);
                }
                else if (validHex) {
                    upperCase = std::toupper(hexChar);
                }
                else if (!validHex) {
                    upperCase = std::toupper(hexChar);
                    std::cout << "\n --> INSIDE FUNCTION : Line 600 : fast64buildBoolInt -::|::-->\t string hexCharStrng = " + hexCharStrng + "\t |  int hexVal=std::stoi(hexCharStrng) = NULL ";
                    std::cout << "\n --> INSIDE FUNCTION : Line 601 : fast64buildBoolInt -::|::--> TERMINATING HEX CONVERSION FUNCTION --> BAD INPUT! ";
                    break;
                }


                firstCalc = expCalculator(16, expCalc);
                unsigned int secondCalc;


                if (upperCase == 'A') {
                    secondCalc = firstCalc * 10;
                    iterVal = iterVal + secondCalc;
                }
                else if (upperCase == 'B') {
                    secondCalc = firstCalc * 11;
                    iterVal = iterVal + secondCalc;
                }
                else if (upperCase == 'C') {
                    secondCalc = firstCalc * 12;
                    iterVal = iterVal + secondCalc;
                }
                else if (upperCase == 'D') {
                    secondCalc = firstCalc * 13;
                    iterVal = iterVal + secondCalc;
                }
                else if (upperCase == 'E') {
                    secondCalc = firstCalc * 14;
                    iterVal = iterVal + secondCalc;
                }
                else if (upperCase == 'F') {
                    secondCalc = firstCalc * 15;
                    iterVal = iterVal + secondCalc;
                }
                else {
                    secondCalc = firstCalc * hexVal;
                    iterVal = iterVal + secondCalc;
                }
                // Here is where the BOOLEAN MATRIX is translated...
                // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
                if (!evenFlag) {
                    if (oldPASSEDdebug) { std::cout << "\n --> INSIDE FUNCTION : Line 667 : fast64buildBoolInt --> Converting value == " + std::to_string(iterVal) + " to binary..."; }
                    std::string convertedBool = binary8bit(iterVal);
                    if (oldPASSEDdebug) { std::cout << "\n    convertedBool --> " + convertedBool; }
                    // Convert Boolean string into 64-bit block...
                    for (int col = 0; col < 8; col++) {
                        char snglChar = static_cast<char>(convertedBool[col]);
                        bool flipBit = (snglChar == 49);  // '1' == 49
                        if (flipBit)
                            *(pntrVar1A + loopCntr * 8 + col) = true;
                        else
                            *(pntrVar1A + loopCntr * 8 + col) = false;  // Must keep because you are re-using the pointer Matrix... must re-calibarte false values or extra 1's will carry over...
                    }
                }
            }
        }
    }
    else {
        std::cout << "\n --> ERROR : fast64buildBoolInt --> READ-IN Failed !!! Bad Input !!!";
    }
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-

    // This function only calculated totals for each 2 characters, or values between 0-255, calculate final value now...
    unsigned long long recapCalc;
    // Print out debugs if necessary and re-calculte the HexaDecimal value...
    // -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-
    if (debugKeySeeding) {
        std::cout << "\n --> INSIDE FUNCTION : Line 666 : fast64buildBoolInt -::|::--> Check recap calc using function convert64bitBooltoInt...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    recapCalc = convert64bitBooltoInt(pntrVar1A);

    if (debugKeySeeding) {
        std::cout << "\n --> INSIDE FUNCTION : Line 671 : fast64buildBoolInt -::|::--> Check recap calc from various channels...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
        std::cout << "\n\t\t\t      Original Simulated Seed :: " + fast64seedOut;
        std::cout << "\n\t   Converted Value From convert64bitBooltoInt :: " + std::to_string(recapCalc);
    }

    //delete pntrVar1A;
    //delete pntrVar2A;

    unsigned long long testOut = recapCalc;
    return testOut;
}

