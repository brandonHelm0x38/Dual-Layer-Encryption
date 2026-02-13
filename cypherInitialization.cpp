#include "cypherInitialization.h"

//bool debugIntro = true;
//bool debugPrimaryInternals = true;
//
//bool oldPASSEDdebug = false;

// There are currently 38 characters that are being purged... so initialize 2 arrays to modify of length 256-38...
// =====================================================================================
void initializeCypher(int* stdSeqRA_purged, int* cypherRA_purged, unsigned long long seedVal) {
    std::mt19937_64 numGenerator(seedVal);
    //int seedVal = seedValIn;

    std::string testOutput = "";
    std::string debugMsg = "";
    int continueTgl = 0;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 3 -::|::- Generate unique arrangement of ASCII characters to use as a cypher ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Consider whether information transfer and machine code strategies can be compartmentalized more effectively by allowing regions to collaborate on the order of the first 128 ASCII characters... 
    // Saving the second for machine code and firmware specific strategies by region may be useful, especially for tracking Supply-Chain security.
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.0-) --:|:--> Generate the ordered sequential array of all ASCII values...\n"; }
    int totalASCIIchars = 256;
    std::vector<int> stdASCIIseq(totalASCIIchars);          // Create a vector of the desired size...
    std::iota(stdASCIIseq.begin(), stdASCIIseq.end(), 1);   // Fill with values starting from 1...
    // The above code sets up the function to be called in a later loop...
    // Now create and populate a sequential array...
    int* stdSeqArray = new int[totalASCIIchars];            // This will hold the standard sequential ASCII array, and is used for 2 purposes... confirming all ASCII values have been asigned, and cypher conversions.
    for (int i = 0; i < totalASCIIchars; i++) {
        stdSeqArray[i] = (stdASCIIseq[i] - 1);
    }
    // Must print to confirm this works as expected...
    if (debugPrimaryInternals) {
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < totalASCIIchars; i++) {
            testOutput = testOutput + std::to_string(stdSeqArray[i]) + "/" + static_cast<char>(stdSeqArray[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.0-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.1-) --:|:--> Purge un-useable chars from sequential look-up array; Needed for Cypher-level character swap, dual-encryption strategy...\n"; }
    int purgeTheseArray[38] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, /* 40 ( , 91 [ , 123 { */ 127, 129, /*143,*/ 144, 157, 160, 255 };
    int purgedCount = sizeof(purgeTheseArray) / sizeof(*purgeTheseArray);
    int purgedRAsize = totalASCIIchars /* 256 */ - purgedCount;
    //int* purgedASCIIstdSeqRA = new int[purgedRAsize];

    for (int a = 0; a < purgedCount; a++) {
        int flaggedVal = purgeTheseArray[a];
        // Set flagged Val/Pos to 0; To remove 0's next...
        stdSeqArray[flaggedVal] = 0;
    }
    // Rebuild a new availASCIIcharsRA...
    int rebuildASCIIpos = 0;
    for (int a = 0; a < totalASCIIchars; a++) {
        if (stdSeqArray[a] != 0) {
            stdSeqRA_purged[rebuildASCIIpos] = stdSeqArray[a];
            rebuildASCIIpos++;
        }
    }

    // Must print to confirm this works as expected...
    if (debugPrimaryInternals) {
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < purgedRAsize; i++) {
            testOutput = testOutput + std::to_string(stdSeqRA_purged[i]) + "/" + static_cast<char>(stdSeqRA_purged[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.1-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    bool boolASCIIarray[256] = { false };
    if (debugPrimaryInternals) {
        std::cout << "\nRUN --> (-Step 3.2-) --:|:--> Initialize an all false boolean array to flag generated values...";
        debugMsg = "BREAK CHECK --> (-Step 3.2-) --:|:--> Boolean array generated...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.3-) --:|:--> Generate the randomized array of ASCII values...\n"; }
    // This set of code is brought in from C++'s powerful randomization library.
    // If we create a list of 256*n uniquely generated numbers... We can likely collapse these values into one set of unique values; Without knowing details about how this is generated... I won't be able to recreate the same cypher.
    // Some statistical analysis of various run-times with variants of the original array created, whether 2,3, or 4* the needed 256 will be an interesting question.
    std::uniform_int_distribution<int> randSeq(1, totalASCIIchars);
    int scaleGenerationVar = 2;     //4000 * 256 will generate about a million random characters in about 1 minute... DO NOT DO THIS!!!
    //mt19937 should not be used for generating more than 624 unique numbers; A known vulnerability exists!!!
    //Awkwardly, this makes this approach to generating a unique cypher array, perfectly right-sized the way it is written with a scaleVariable of 2.
    int* randSeqArray = new int[totalASCIIchars * scaleGenerationVar];              // This will hold the random re-ordering of cypher variables...
    // The above code sets up the function to be called in a later loop...
    for (int i = 0; i < totalASCIIchars * scaleGenerationVar; ++i) {
        //randSeqArray[i] = randSeq(seedVal);
        randSeqArray[i] = randSeq(numGenerator);
    }

    // Must print to confirm this works as expected...
    if (debugPrimaryInternals) {
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < totalASCIIchars * scaleGenerationVar; i++) {
            testOutput = testOutput + std::to_string(randSeqArray[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.3-) --:|:--> Randomly generated values for a list " + std::to_string(scaleGenerationVar) + "x longer than the standard ASCII list of 256 characters.";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.4-) --:|:--> Detect duplicates and collapse as many random values as possible into a final cypher array...\n"; }
    // Now collapse the randomized array and only populate unique values in the random-Sequence array...
    // An outer loop will process the entire array, while an inner-loop keeps track of the position of the final generated array.  You will also need a 3rd inner loop for running through both the boolean, and sequential arrays...
    // At this stage I'm trying to think of how I can keep the overall length of 256 ASCII characters... 
    // But cleverly structure the placement, and/or arrangment of the characters which will be used to restore structure of the overall file...

    // It's possible to minimze the looping by dividing the overall length of 256 by either 64 or 32 (then round), and having main branches for starting the corresponding searching of the sequential and boolean flag arrays...
    float arraySplit = 64;        // Curious how runtime changes with 32.
    int totalSections = totalASCIIchars / arraySplit;  // Should equal 4.
    int sectSelected;
    int lowerBounds;
    int upperBounds;
    int searchPos;
    int genKeyPos = 0;
    int nextRand;
    bool boolFlag;
    char asciiChar;


    int* altrdASCIIarray = new int[totalASCIIchars];                                    // The final altered sequence ASCII-Key portion of the algorithm.
    for (int mainCntr = 0; mainCntr < totalASCIIchars * scaleGenerationVar; mainCntr++) {   // I suspect ++mainCntr & mainCntr++ have to operate the same...
        nextRand = randSeqArray[mainCntr];
        if (oldPASSEDdebug) {
            std::cout << "\n--> Inside loop for mainCntr = " + std::to_string(mainCntr);
            std::cout << "\n--> The currently selected value is = " + std::to_string(nextRand);
        }
        // First set of calculations set up to determine lower search bounds...
        sectSelected = (nextRand / arraySplit);
        lowerBounds = (sectSelected * arraySplit);          // This math should automatically start us in the right spot with C++ arrays starting at 0;
        if (lowerBounds == 256) {
            lowerBounds = sectSelected * (arraySplit - 1);  // This should reset the lower starting point to the correct value of 64 * 3 / or 32 * 7 if the arraySplit value is changed.
        }
        // Second set of calculations set up to determine upper search bounds...
        sectSelected = sectSelected + 1;
        if (sectSelected == 5) {
            sectSelected = 4;
        }
        upperBounds = arraySplit * sectSelected;
        if (oldPASSEDdebug) {
            std::cout << "\n--> The section to search is calculated to be = " + std::to_string(sectSelected);
            std::cout << "\n--> The lower bounds of the search is calculated to be = " + std::to_string(lowerBounds);
            std::cout << "\n--> The upper bounds of the search is calculated to be = " + std::to_string(upperBounds);
        }

        searchPos = lowerBounds;
        // This is where the array splitting comes into play to optimize the searching...
        for (searchPos; searchPos < upperBounds; searchPos++) {
            if (oldPASSEDdebug) { std::cout << "\n--> Iteration " + std::to_string(searchPos) + " Looping between " + std::to_string(lowerBounds) + " and " + std::to_string(upperBounds); }
            if (searchPos == nextRand) {
                if (boolASCIIarray[searchPos] == false) {
                    boolASCIIarray[searchPos] = true;
                    altrdASCIIarray[genKeyPos] = nextRand;
                    if (oldPASSEDdebug) { std::cout << "\n--> The value of = " + std::to_string(nextRand) + " was added to the " + std::to_string(genKeyPos) + " position of the final cypher array."; }
                    genKeyPos++;
                }
                else if (oldPASSEDdebug) { std::cout << "\n--> A duplicate of = " + std::to_string(nextRand) + " was already generated in the final cypher array."; }
                break;      // Break out of the "For" loop whenever a value is added to the generated Cypher array.
            }
        }
        if (oldPASSEDdebug) {
            std::cout << std::endl;
            std::cout << std::endl;
        }
    }

    if (debugPrimaryInternals) {
        std::cout << "RUN --> (-Step 3.4-) --:|:--> Build out the partially generated cypher array; Which should contain " + std::to_string(genKeyPos - 1) + " total values...\n";
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < totalASCIIchars; i++) {
            testOutput = testOutput + std::to_string(altrdASCIIarray[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.4-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.5-) --:|:--> Run math on the remaining characters left to randomize, and create a new dynamic array of these characters...\n"; }
    int remainingChars = totalASCIIchars - genKeyPos;
    if (debugPrimaryInternals) { std::cout << "RUN --> (-Step 3.5-) --:|:--> There were " + std::to_string(genKeyPos) + " values generated in the prior loop, leaving " + std::to_string(remainingChars) + " yet to sort...\n"; }
    int cntRemaining = 0;
    int* remainingASCIIarray = new int[remainingChars];
    std::vector<bool> remainingASCIIbool(remainingChars, false);
    for (int i = 0; i < totalASCIIchars; i++) {
        if (boolASCIIarray[i] == false) {
            remainingASCIIarray[cntRemaining] = i;
            cntRemaining++;
        }
    }

    if (debugPrimaryInternals) {
        testOutput = "Confirm Array of Remaining Values --:|:-->\n";  // Reset...
        for (int i = 0; i < remainingChars; i++) {
            if (i == remainingChars-1)
                testOutput = testOutput + std::to_string(remainingASCIIbool[i]);
            else
                testOutput = testOutput + std::to_string(remainingASCIIarray[i]) + " | ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.5-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.6-) --:|:--> Create a simple bounded random number generator array for looping through and randomly continuing the final cypher array...\n"; }
    std::uniform_int_distribution<int> randSeq2(1, remainingChars);
    int* randSeqArray2 = new int[remainingChars * scaleGenerationVar];// This will hold the random re-ordering of cypher variables...
    // The above code sets up the function to be called in the below loop...
    for (int i = 0; i < remainingChars * scaleGenerationVar; ++i) {
        //randSeqArray2[i] = randSeq2(seedVal);
        randSeqArray2[i] = randSeq2(numGenerator);
    }

    if (debugPrimaryInternals) {
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < remainingChars * scaleGenerationVar; i++) {
            testOutput = testOutput + std::to_string(randSeqArray2[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.6-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // Looping through like this... We'll always grab 3 values, current/previous/next ... except for the outter bounds.
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.7-) --:|:--> Looping through like this... We'll always grab 3 values, current/previous/next ... Except for the outter bounds...\n"; }
    int lastPos;
    bool lastPosFlag = false;
    int currentPos;
    bool currentPosFlag = false;
    int nextPos;
    bool nextPosFlag = false;
    // Loop through array 2x the length of the remaining unused values...
    for (int mainCntr = 0; mainCntr < remainingChars * scaleGenerationVar; mainCntr++) {
        // Loop through both boolean and remaining values array, grabbing the randomly generated position, and checking the corresponding value hasn't been flagged...
        currentPos = randSeqArray2[mainCntr] - 1;
        if (currentPos <= 0) {
            if (currentPos == -1) { currentPos = 0; };
            currentPosFlag = remainingASCIIbool[currentPos];
            nextPosFlag = remainingASCIIbool[currentPos + 1];
            if (!currentPosFlag) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos];
                remainingASCIIbool[currentPos] = true;
                genKeyPos++;
            }
            else if (!nextPosFlag) {    // This should only run if 0 is randomly generated twice.
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos + 1];
                remainingASCIIbool[currentPos + 1] = true;
                genKeyPos++;
            }
        }
        else if (currentPos == remainingChars - 1) {
            lastPosFlag = remainingASCIIbool[currentPos - 1];
            currentPosFlag = remainingASCIIbool[currentPos];
            if (!currentPosFlag) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos];
                remainingASCIIbool[currentPos] = true;
                genKeyPos++;
            }
            else if (!lastPosFlag) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos - 1];
                remainingASCIIbool[currentPos - 1] = true;
                genKeyPos++;
            }
        }
        else {
            // This is where I try to off-set for repeated/missed values...
            lastPosFlag = remainingASCIIbool[currentPos - 1];
            currentPosFlag = remainingASCIIbool[currentPos];
            nextPosFlag = remainingASCIIbool[currentPos + 1];
            if (!currentPosFlag) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos];
                remainingASCIIbool[currentPos] = true;
                genKeyPos++;
            }
            else if (!lastPosFlag) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos - 1];
                remainingASCIIbool[currentPos - 1] = true;
                genKeyPos++;
            }
            else if (!nextPosFlag) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[currentPos + 1];
                remainingASCIIbool[currentPos + 1] = true;
                genKeyPos++;
            }
        }
    }

    // Must print to confirm this works as expected...
    if (debugPrimaryInternals) {
        std::cout << "RUN --> (-Step 3.7-) --:|:--> Build out the partially generated cypher array; Which should contain " + std::to_string(genKeyPos) + " total values...\n";
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < totalASCIIchars; i++) {
            testOutput = testOutput + std::to_string(altrdASCIIarray[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.7-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // Simply loop through the remainingASCIIbool[i] array, and add any values that haven't been flagged into the final cypher array...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.8-) --:|:--> Add any remaining values sequentially...\n"; }
    int lastLoopCntr = totalASCIIchars - genKeyPos;
    bool flagAdd = false;
    for (int i = 0; i < lastLoopCntr; i++) {
        for (int innrCntr = 0; innrCntr < remainingChars; innrCntr++) {
            flagAdd = remainingASCIIbool[innrCntr];
            if (!flagAdd) {
                altrdASCIIarray[genKeyPos] = remainingASCIIarray[innrCntr];
                remainingASCIIbool[innrCntr] = true;
                genKeyPos++;
            }
        }
    }
    // Print the randomized Cypher-Array... needing only to purge unuseable characters...
    if (debugPrimaryInternals) {
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < totalASCIIchars; i++) {
            testOutput = testOutput + std::to_string(altrdASCIIarray[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.8-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\nRUN --> (-Step 3.9-) --:|:--> Purge un-useable chars from altered sequence look-up array; Needed for Cypher-level character swap, dual-encryption strategy...\n"; }
    //int purgeTheseArray[12] = { 0, 8, 9, 10, 11, 12, 13, 17/*XON*/, 19/*XOFF*/, 27, /*32-Is space,*/ 127, 255};
    //purgedCount = sizeof(purgeTheseArray) / sizeof(*purgeTheseArray);
    //purgedRAsize = totalASCIIchars /* 256 */ - purgedCount;
    //int* purgedASCIIaltrdSeqRA = new int[purgedRAsize];

    for (int a = 0; a < purgedCount; a++) {
        int flaggedVal = purgeTheseArray[a];
        // Set flagged Val/Pos to 0; To remove 0's next...
        int posFlag = 1;  // You know 0 exists first, so start at 1...
        while (altrdASCIIarray[posFlag] != flaggedVal) {
            posFlag++;
        }
        altrdASCIIarray[posFlag] = 0;
    }
    // Rebuild a new availASCIIcharsRA; Removing everything flagged and set to 0 in prior step...
    rebuildASCIIpos = 0;
    for (int a = 0; a < totalASCIIchars; a++) {
        if (altrdASCIIarray[a] != 0) {
            cypherRA_purged[rebuildASCIIpos] = altrdASCIIarray[a];
            rebuildASCIIpos++;
        }
    }
    // Must print to confirm this works as expected...
    if (debugPrimaryInternals) {
        testOutput = "Confirm Array Values --:|:-->\n";  // Reset...
        for (int i = 0; i < purgedRAsize; i++) {
            testOutput = testOutput + std::to_string(cypherRA_purged[i]) + "/" + static_cast<char>(cypherRA_purged[i]) + " ";
        }
        std::cout << testOutput;
        std::cout << std::endl;
        debugMsg = "BREAK CHECK --> (-Step 3.9-) --:|:--> Check Output...";
        if (debugIntro) { continueTgl = checkBreak(debugMsg); }
        if (continueTgl == 'N') {
            exit(1);
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }
}