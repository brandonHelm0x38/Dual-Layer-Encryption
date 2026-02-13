#include "runDecryption.h"


//bool debugPrimaryInternals = false;
//bool debugKeySeeding = false;


void runDecryption() {
    // Basic operation/debug variables...
    std::string debugMsg;
    char continueTgl;

    // Get/check valid filepaths...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 0 -::|::-  Get Filepath Input From User  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string inFilePath;
    std::string outFilePath;

    std::cout << "\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
    std::cout << " --> runEncryption : Line 21 : (-Step 1-) --:|:--> Configuring input file & path...\n";;
    std::cout << "\tPlease enter a valid Windows filepath to a .txt or .csv file TO DECRYPT...\n\t";
    std::cin >> inFilePath;
    std::cout << "\n --> runEncryption : Line 24 : (-Step 1-) --:|:--> Attempting to Open Data-File TO DECRYPT @: " + inFilePath;
    // Open the input file TO ENCRYPT using ifstream...
    std::ifstream fileIn(inFilePath);

    while (!fileIn.is_open()) {
        std::cerr << "\n\tFailed to open file @: " << inFilePath;  // Print error message and repeat loop...
        while (!isValidPathFormat(inFilePath)) {
            std::cerr << "\n\tInput does not follow WINDOWS standards @: " << inFilePath << std::endl;;  // Print error message and repeat loop...

            std::cout << "\n\tPlease enter a valid Windows filepath to a .txt or .csv file TO DECRYPT...\n\t";
            std::cin >> inFilePath;
        }

        std::ifstream fileIn(inFilePath);
        if (fileIn.is_open())
            std::cout << "\n\tSUCCESS --> Encrypted-File opened successfully @: " << inFilePath;
    }
    // Need a final check to alert user of successful input when entered correctly right away (NO LOOP NEEDED)...
    if (fileIn.is_open())
        std::cout << "\n\tSUCCESS --> Encrypted-File opened successfully @: " << inFilePath;

    std::cout << "\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
    std::cout << " --> runEncryption : Line 44 : (-Step 1-) --:|:--> Configuring output file & path...\n";;
    std::cout << "\tPlease enter a valid Windows filepath to a .txt file AS YOUR OUTPUT DECRPTED FILE...\n\t";
    std::cin >> outFilePath;
    std::cout << "\n --> runEncryption : Line 47 : (-Step 1-) --:|:--> Attempting to Create Output-File of Decrypted-Data @: " + inFilePath;
    // Create a new file to write the ecnrypted data to...
    std::ofstream outputFile(outFilePath);  // Open/create a file for writing encrypted data-copy to...

    while (!outputFile.is_open()) {
        std::cerr << "\n\tFailed to open file @: " << outFilePath;  // Print error message and repeat loop...
        while (!isValidPathFormat(outFilePath)) {
            std::cerr << "\n\tInput does not follow WINDOWS standards @: " << outFilePath << std::endl;;  // Print error message and repeat loop...

            std::cout << "\n\tPlease enter a valid Windows filepath to a .txt file AS YOUR OUTPUT DECRYPTED FILE...\n\t";
            std::cin >> outFilePath;
        }

        std::ofstream outputFile(outFilePath);
        if (outputFile.is_open())
            std::cout << "\n\tSUCCESS --> Output-File for Decrypted-Data created successfully @: " << outFilePath;
    }
    // Need a final check to alert user of successful input when entered correctly right away (NO LOOP NEEDED)...
    if (outputFile.is_open())
        std::cout << "\n\tSUCCESS --> Output-File for Decrypted-Data created successfully @: " << outFilePath << std::endl;
    std::cout << " -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n\n";
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 1 -::|::-  Runtime Calculations and Timestamp Functions  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Runtime Analysis...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto start = std::chrono::high_resolution_clock::now();     // Ued in final Run-Time seconds calculation...
    auto initCallTS = start.time_since_epoch();
    auto highResTimeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(initCallTS).count();            // I'm not sure whats being calculated here, but its 15 digits/characters long...
    // Need a second set for building initial seeding relevant to security key generation...
    auto const start2 = std::chrono::system_clock::now();
    auto initCallTS2 = start2.time_since_epoch();
    auto stdTimeStamp = std::chrono::duration_cast<std::chrono::nanoseconds>(initCallTS2).count();          // I'm not sure whats being calculated here, but its 19 digits/characters long...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // DateTime Conversions and test...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    time_t unixEpochSeconds;
    wchar_t DateTimeStamp[26];
    errno_t error;

    time(&unixEpochSeconds);

    error = _wctime_s(DateTimeStamp, 26, &unixEpochSeconds);
    if (error != 0)
    {
        printf("Invalid Arguments for _wctime_s. Error Code: %d\n", error);
    }
    wprintf_s(L"The time is %s\n", DateTimeStamp);

    std::cout << "\n   unixEpochSeconds: " + std::to_string(unixEpochSeconds);

    // Unique value seeding...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout << "\n   highResTimeStamp: " + std::to_string(highResTimeStamp);
    std::cout << "\n       stdTimeStamp: " + std::to_string(stdTimeStamp);
    std::string highResTimeStampString = std::to_string(highResTimeStamp);
    std::string stdTimeStampString = std::to_string(stdTimeStamp);
    int stringLen = highResTimeStampString.length();
    int string2Len = stdTimeStampString.length();
    int subStrngSize = 8;
    std::string passedSub = highResTimeStampString.substr(stringLen - (subStrngSize + 3), subStrngSize);
    std::string passedSub2 = stdTimeStampString.substr(string2Len - (subStrngSize + 3), subStrngSize);
    std::cout << "\n  Passed Substring1: " + passedSub;
    std::cout << "\n  Passed Substring2: " + passedSub2;
    std::cout << std::endl;
    std::cout << std::endl;

    float yearsSinceUnixEpoch = unixEpochSeconds / (3600.00 * 24 * 365.25);
    float daysSinceUnixEpoch = unixEpochSeconds / (3600.00 * 24);
    float hoursSinceUnixEpoch = unixEpochSeconds / (3600.00);
    std::cout << "\n\tYears Passed Since Unix Epoch == " + std::to_string(yearsSinceUnixEpoch);
    std::cout << "\n\t Days Passed Since Unix Epoch == " + std::to_string(daysSinceUnixEpoch);
    std::cout << "\n\tHours Passed Since Unix Epoch == " + std::to_string(hoursSinceUnixEpoch);
    std::cout << std::endl;
    std::cout << "\n\t2025 - 1970 == " + std::to_string(2025 - 1970);
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "\n   Mirror functionality; Pass original timestamp substring into function again...";
    std::cout << "\n   Mirror timestamp: " + stdTimeStampString.substr(0, 10);  // Could pass the original timestamp into this function... doesn't need to call system time again...
    std::cout << "\n   unixEpochSeconds: " + std::to_string(unixEpochSeconds);
    std::cout << "\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- ";
    std::cout << std::endl;
    std::cout << std::endl;

    debugMsg = "BREAK CHECK --> Check output of Timestamp Seeding Functions ??? --:|:--> Continue?? ...";
    continueTgl = checkBreak(debugMsg);
    if (continueTgl == 'N') {
        exit(1);
    }

    // You first build out the simulated Internal Service Seed, then combine it with the simulated DEV-OS-APP verification API...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 2 -::|::-  Generate Security Key && Run Cyber-Force Simulated API  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SIMULATE A DATABASE by using this file structure for the parseHexValFromKey functionality...
    std::string simActiveSecTablesFilePath = "C:/Users/BrandonHelm/Documents/testPRGRMoutput/_activeSecurityTables.txt";
    std::string simDEVOSAPPsecTablesFilePath = "C:/Users/BrandonHelm/Documents/testPRGRMoutput/_DEVOSAPP_activeSecurity.txt";

 
    std::cout << "\n\n --> Running DUAL LAYER DE-CRYPTION (-Step 2.1-) Importing Security Key...\n";


    // CALIBRATE-DECRYPTION-SEED --:|:--> Import the security key from the file...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string securityKeyLine;
    getline(fileIn, securityKeyLine);
    std::string securityKey = securityKeyLine.substr(23, 128);
    if (debugKeySeeding) {
        std::cout << "\n --> runDecryption : Line 162 : Check Security Key Read-In...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        std::cout << securityKey << std::endl;
    }

    // CALIBRATE-DECRYPTION-SEED --:|:--> Import the Active-Security-xRef-Tables for Security-Key parsing randomization...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout << "\n --> Running DUAL LAYER DE-CRYPTION (-Step 2.2-) Importing Active-Security-xRef-Tables...\n";

    // Open the file using ifstream...
    std::ifstream secTablesFileIn(simActiveSecTablesFilePath);
    // Confirm file opening for input file --> Ouput file will be created/opened later...
    std::cout << "\n --> runDecryption : Line 174 : (-Step 2.2-) --:|:--> Importing Active-Security-xRef-Tables from file @: " + simActiveSecTablesFilePath;
    if (!secTablesFileIn.is_open()) {
        // print error message and return
        std::cerr << "\n\tFailed to open file @: " << simActiveSecTablesFilePath;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        exit(1);
    }
    else
        std::cout << "\n\tActive-Security-xRef-Tables file opened successfully from @: " << simActiveSecTablesFilePath;

    // CALIBRATE-DECRYPTION-SEED --:|:--> Import the security key from the file...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int* alphaHexXrefs = new int[26];   // Line 1 from Active Security Tables file; Replace with Cyber-Force DataBase API...
    int* base10xRefs = new int[10];     // Line 2 from Active Security Tables file; Replace with Cyber-Force DataBase API...
    int* scaleStepXrefs = new int[16];  // Line 3 from Active Security Tables file; Replace with Cyber-Force DataBase API...

    std::string alphaHexXrefs_Strng = "";
    getline(secTablesFileIn, alphaHexXrefs_Strng);
    buildIntArrayFromCSV(alphaHexXrefs_Strng, alphaHexXrefs, 26);

    std::string base10xRefs_Strng = "";
    getline(secTablesFileIn, base10xRefs_Strng);
    buildIntArrayFromCSV(base10xRefs_Strng, base10xRefs, 10);

    std::string scaleStepXrefs_Strng = "";
    getline(secTablesFileIn, scaleStepXrefs_Strng);
    buildIntArrayFromCSV(scaleStepXrefs_Strng, scaleStepXrefs, 16);


    // Finally, parse the Security Key and generate a HexaDecimal seed value...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string keySeedHexVal = parseHexValFromKey(securityKey, alphaHexXrefs, base10xRefs, scaleStepXrefs);

    //uint_fast64_t securityKeySeed1 = keySeedHexVal;
    unsigned long long int internalKeySeed = calcHexVal(keySeedHexVal);


    // Finally, consider how keys could be stacked in commercial/prod environments to enable a Cyber-Force...
    // CALIBRATE-ENCRYPTION-SEED --:|:--> Simulate an API to authenticate other system resources from the requesting device...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // It doesn't matter if this is ever intercepted as there are too many other masked pieces...
    // Additionally this is designed to rotate as an Active-Device-ID...
    // In theory; in a perfect world ONLY Cyber-Force authenticates genuine Manufacturer-ID information for critical security reasons...
    uint_fast64_t brandonHelmsDevice = 0x5555555555555555;

    // Simulate this API with a file call; KEEP IN MIND !!! --> You would normally pass the 2 critical security keys for OS & APP layers, Device Security Key is also a good idea
    unsigned long long int secKeySeedMaster = cyberForceSecKeyComb(internalKeySeed, brandonHelmsDevice, simDEVOSAPPsecTablesFilePath);


    // Plug in test cases for debug... Pass set seed variable...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    unsigned long long int finalSeed;
    //finalSeed = parsedSecKeySeed;             // PROD --> Primary setting to wire SEED parsed from Security Key into the encryption program...
    finalSeed = secKeySeedMaster;         // PROD --> Primary setting which includes simulated Cyber-Force API...
    //finalSeed = 18192021222324;           // MAIN Test Case from development...


    // Finally you can use all this effort to create a genuinely well constructed random seed...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Mersenne Twister Engine (32) should NOT be used for generating more than 624 unique values...
    // There is a known way to reverse engineer the sequence if these values can be intercepted...
    // Consider GitHub code for :: L'Ecuyer MRG32k3a ; Well19937a ; Melg19997/Melg19937-64
    std::mt19937_64 engine2(finalSeed);

    std::cout << "\n\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
    std::cout << "\n Program seeded with Cyber-Force Simulated API & Internal Service Layer...";
    std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
    std::cout << "\n\t\t      Final Combination Lock-Seed: " + std::to_string(finalSeed);
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    debugMsg = "BREAK CHECK --> Check/Note Final Combination Lock-Seed --:|:-- Continue?? ...";
    continueTgl = checkBreak(debugMsg);
    if (continueTgl == 'N') {
        exit(1);
    }
    std::cout << std::endl;
    std::cout << std::endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 3 -::|::-  Initialize/generate Cypher xRef  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int validChars = 256 - 38;
    int* stdSeqArray = new int[validChars];
    int* cypherArray = new int[validChars];
    initializeCypher(stdSeqArray, cypherArray, finalSeed);


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 4 -::|::-  Run Dual-Layer Decryption  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\n --> MAIN PROGRAM : Line 1376 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Used in bitMaskTwistCharsDE !!!"; }
    bool bool2d64bitInMain[8][8] = { false };
    bool* pntrVar5A = &bool2d64bitInMain[0][0];
    if (debugPrimaryInternals) { std::cout << "\n --> MAIN PROGRAM : Line 1379 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Used in debug final readout !!!"; }
    bool finalDebugMirror[8][8] = { false };
    bool* pntrOutMirror = &finalDebugMirror[0][0];

    // Initialize variable and range for iterative random number generation...
    int* randSeqArray9 = new int[9];
    std::uniform_int_distribution<int> randSeq9(1, 7);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Primary command-line program notification...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::cout << "\n\n --> MAIN PROGRAM : Line 1425 : (-Step 2.1-) --:|:--> Running DUAL-LAYER De-CRYPTION...";


    // Read the input file Line-X-Line and FIRST run CYPHER; then SECOND run BIT-MASK permutations... 
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string lineIn;
    int lineCntr = 0;
    while (getline(fileIn, lineIn)) {
        lineCntr++;
        int lineLength = lineIn.length();

        if (debugPrimaryInternals) {
            std::cout << "\n --> RUNNING DE-CRYPTION -::|::--> Processing input-file-line == " + std::to_string(lineCntr) + "\t Read-Back INPUT line...\n";
            std::cout << lineIn << std::endl;
        }

        // Initial Variables for Dual-Layer DE-CRYPTION...
        std::string deMaskedStrng = "";
        int a = 0;
        int blockCnt = 0;
        int fndValLengthAdjBlock;
        int fndValLengthAdjLast;
        int trackOffset = 0;
        std::string toDeMaskStrng = "";


        while (a < lineLength) {
            blockCnt++;
            if (debugProcess8chars) {
                std::cout << "\n\n\n\n\n --> MAIN PROGRAM : Line 1453 -->\t |  Processing input-file-line == " + std::to_string(lineCntr) + "\t |  Line-block# == " + std::to_string(blockCnt) + "\t |  From overall line-index position # " + std::to_string(a) + "     |  Of overall line-length == " + std::to_string(lineLength);
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
            }
            toDeMaskStrng = "";
            int foundCappedVals = 0;
            int b = 0;
            bool capsuleFoundInBlock = false;
            fndValLengthAdjBlock = 0;
            std::string intStrng = "";

            while (b < 8) {
                fndValLengthAdjLast = 0;
                unsigned char capCharSrch;
                unsigned char nextCharSrch;
                std::string capCharStrng = "";
                std::string nextCharStrng = "";
                std::string currCharStrng = "";

                unsigned char currCharSrch = 0;
                bool capsuleVal = false;
                bool isValidNum = false;
                int iterCnt = 0;

                if (capsuleFoundInBlock) {
                    currCharSrch = lineIn[a + b + fndValLengthAdjBlock];
                    currCharStrng = lineIn[a + b + fndValLengthAdjBlock];
                }
                else {
                    currCharSrch = lineIn[a + b];
                    currCharStrng = lineIn[a + b];
                }


                std::string intStrng = "";
                if (debugStringBuild) { std::cout << "\n\n\n --> MAIN PROGRAM --> Line 1488 --> Looping to grab 8 valid values...\t | loop# == " + std::to_string(b + 1) + "\t | processing currCharSrch == " + currCharStrng; }

                // You don't have to worry about errors with this loop based on the reality the ecnryption script is encoding original '(' from data... those not generated when making encapsulated values...
                // Will also be encoded as encapsulated values to prevent this loop accidentally starting when alpha/symbol or other non-numerics might be mistakenly put inside brackets based on the way it is written now.
                if (currCharSrch == '(') {
                    if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1493 : Found '(' at location : " + std::to_string(a + b + fndValLengthAdjBlock); }

                    // Want to start at 2 to prevent flagging an () / empty bracket, which could cypher out by chance...
                    int iterCnt = 1;
                    // Technically, any incoming raw data should be re-arranged by the first cypher... which makes the alogithm capable of encypting raw data-capsules... though this script may error

                    while (!capsuleVal && iterCnt <= 3) {
                        // Logic that makes sure we have math that runs until the end of the string only and then stays set to the last character.
                        if (a + b + iterCnt + fndValLengthAdjBlock > lineLength) {
                            nextCharSrch = lineIn[lineLength - 1];
                            nextCharStrng = lineIn[lineLength - 1];
                        }
                        else {
                            nextCharSrch = lineIn[a + b + iterCnt + fndValLengthAdjBlock];
                            nextCharStrng = lineIn[a + b + iterCnt + fndValLengthAdjBlock];
                        }
                        // Logic that makes sure we have math that runs until the end of the string only and then stays set to the last character.
                        if (a + b + iterCnt + fndValLengthAdjBlock + 1 > lineLength) {
                            capCharSrch = lineIn[lineLength - 1];
                            capCharStrng = lineIn[lineLength - 1];
                        }
                        else {
                            capCharSrch = lineIn[a + b + iterCnt + fndValLengthAdjBlock + 1];
                            capCharStrng = lineIn[a + b + iterCnt + fndValLengthAdjBlock + 1];
                        }

                        if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1519 : Processing chars from encrypted file --> \t nextCharSrch == " + nextCharStrng + "\t | capCharSrch == " + capCharStrng; }

                        // NEED TO ADD CHECK --> isValidNum (asciiVal > 47 $$ asciiVal < 59 )  // 3 Valid nums needed  // 
                        if (47 < nextCharSrch < 59) {
                            isValidNum = true;
                            fndValLengthAdjLast++;
                            if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1525 : Building (intStrng) From -->\t lineLength == " + std::to_string(lineIn.length()) + "\t | grabbing position == " + std::to_string(a + b + iterCnt + fndValLengthAdjBlock); }
                        }
                        else {
                            isValidNum = false;
                            //break;
                        }

                        if (capCharSrch == ')' && isValidNum) {
                            capsuleVal = true;
                            capsuleFoundInBlock = true;
                            foundCappedVals++;

                            if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1537 : Found capped value / ')' at location : " + std::to_string(a + b + (iterCnt + 1) + fndValLengthAdjBlock); }  // -foundCappedVals ???

                            //Calculate this after the above debugStringBuild output as you would otherwise need to know the block adjustment before this calculation for later use in the program.
                            fndValLengthAdjBlock = fndValLengthAdjBlock + fndValLengthAdjLast + 1;

                            // This should theoretically prevent extra string processing after a capsule value is found...
                            break;
                        }
                        iterCnt++;
                    }
                }

                // Change bottom logic to grab valid chunk of current string to build aka toDeMaskStrng...
                if (capsuleVal && isValidNum) {
                    int startPos = a + b + fndValLengthAdjBlock - fndValLengthAdjLast;

                    //if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1553 -->\t  !!!!! -- debugStringBuild -- !!!  -- RUNTIME BREAK-CHECK -- !!!!!"; }
                    if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1554 : Building (intStrng) From -->\t |  startPos == " + std::to_string(startPos) + "\t |  fndValLengthAdjLast == " + std::to_string(fndValLengthAdjLast); }
                    intStrng = lineIn.substr(startPos, fndValLengthAdjLast);

                    unsigned char intStrngChar1 = intStrng[0];
                    int pos1val = intStrngChar1;
                    toDeMaskStrng = toDeMaskStrng + "(" + intStrng + ")";

                    if (debugByteLineReadout) { std::cout << "\n --> MAIN PROGRAM : Line 1561 : Building encrypted string -->\t |  position == " + std::to_string(b + 1) + "\t |  FROM variable intStrng == " + intStrng + "  \t\t |  toDeMaskString now == " + toDeMaskStrng; }
                    b++;
                }
                else { // The string being built as toDeMaskStrng has no capped values...
                    toDeMaskStrng = toDeMaskStrng + lineIn[a + b + fndValLengthAdjBlock];

                    currCharSrch = lineIn[a + b + fndValLengthAdjBlock];
                    if (debugStringBuild) { std::cout << "\n --> MAIN PROGRAM : Line 1568 : fndValLengthAdjBlock == " + std::to_string(fndValLengthAdjBlock); }
                    if (debugByteLineReadout) { std::cout << "\n --> MAIN PROGRAM : Line 1569 : Building encrypted string -->\t |  position == " + std::to_string(b + 1) + "\t |  FROM variable currCharSrch == " + std::to_string(currCharSrch) + " / " + outputStrngFromASCIIval(currCharSrch) + "\t |  toDeMaskString now == " + toDeMaskStrng; }
                    b++;
                }
                //std::cout << "\n --> Looped through inner (cntRows < 8) loop : |" + std::to_string(b) + "| times;\t\t   Last loop will double up this value if capsuleVal found at position 7 !!!";
            }

            // DO NOT CHANGE THIS !!! It has calculated successfully fo multiple capped values... It is for stepping through the overall string of the file-line being read-in.
            trackOffset = trackOffset + fndValLengthAdjBlock;
            // This calculation outputs how long the generated string should be... It needs the above and below calculations placed acorddingly... trackOffset
            if (debugProcess8chars) {
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                std::cout << "\n --> MAIN PROGRAM --> Line 1580 : To De-Mask string starts at position == " + std::to_string(a) + "\t and extends to a length == " + std::to_string(8 + fndValLengthAdjBlock) + " characters.\n";
            }
            // DO NOT CHANGE THIS !!! It has calculated successfully fo multiple capped values... It is for stepping through the overall string of the file-line being read-in.
            a = trackOffset + (blockCnt * 8);
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if (debugProcess8chars) {
                debugMsg = "BREAK CHECK --> Test Output --:|:-- toDeMaskStrng == " + toDeMaskStrng;
                continueTgl = checkBreak(debugMsg);
                if (continueTgl == 'N') {
                    exit(1);
                }
            }
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            // Need to re-generate randSeqArray9...
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            for (int i = 0; i < 9; ++i) {
                randSeqArray9[i] = randSeq9(engine2);
            }
            // This sequence generates the same as long as seeded value is set correctly to the generated value from encryption; in encryptedScript.
            if (debugPrimaryInternals) {
                std::cout << "\n --> MAIN PROGRAM : Line 1605 --> Random Generation Sequence of 9 integers, toDeMaskStrng loop # " + std::to_string(blockCnt) + " ; While processing input file line # " + std::to_string(lineCntr);
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
                std::cout << "\n ~~~~~~~~~~~~~~ I Already Know These Match Generation Steps As Expected ~~~~~~~~~~~~~~";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                print2D_intTblLyr(randSeqArray9, 1, 9);
            }

            // Now that you've looped to grab the next set of 8 encrypted values from the input-file, prepare data for boolean operations...
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            buildBoolGridFromString1(toDeMaskStrng, pntrVar5A);
            if (debugBitMaskInternals) {
                std::cout << "\n\n\n --> MAIN PROGRAM : Line 1617 : ( Step 3.1 ) --:|:-- PRINT --> buildBoolGridFromString1 ; Output generated 64-bit matrix in 2 views...";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                prnt64bitBool(pntrVar5A, 8, 8);
                // The Command-Line debug outputs nicely with this next function as a read-out...
                convert64bitBooltoInt(pntrVar5A);
            }  // Used to ouput more detail... Builds a set of strings that prints out a smaller 64-bit block with byte/line readouts...

            // Generate the next set of 8 deMasked values; Inverse Layer-2 Bit-Mask Decryption...
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if (debugPrimaryInternals) { std::cout << "\n\n --> MAIN PROGRAM : Line 1626 : ( Step 3.2 ) --:|:-- RUN --> bitMaskTwistCharsDE..."; }
            bitMaskTwistCharsDE(pntrVar5A, randSeqArray9);
            if (debugMajorPermutations) {
                std::cout << "\n\n\n --> MAIN PROGRAM : Line 1629 : ( Step 3.2 ) --:|:-- convert64bitBooltoInt --> Check bitMaskTwistCharsDE output... ";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                // The Command-Line debug outputs nicely with this next function as a read-out...
                convert64bitBooltoInt(pntrVar5A);
            }  // Used to ouput more detail... Builds a set of strings that prints out a smaller 64-bit block with byte/line readouts...

            // Perform the final Cypher-Swap; Inverse Layer-1 Cypher-Swap...
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            std::string outputSet = buildDecrypted8chars(pntrVar5A, stdSeqArray/* ASCII Standard Array */, cypherArray /* ASCII Lookup Array */, 256-38/*purgedRAsize*/);
            if (debugPrimaryInternals) { std::cout << std::endl; } // Needed for command-line debug to look well-spaced...

            // Create a Byte-Line readout of the final decrypted set of 8 values/characters; Only useful for debugging...
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            if (debugMajorPermutations) {
                // Build another boolean grid from the output string as it did not permute the last matrix in the prior buildDecrypted8chars function...
                buildBoolGridFromString1(outputSet, pntrOutMirror);
                std::cout << "\n --> MAIN PROGRAM : Line 1645 : ( Step 3.3 ) --:|:-- convert64bitBooltoInt --> Check buildDecrypted8chars output... ";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                // The Command-Line debug outputs nicely with this next function as a read-out...
                convert64bitBooltoInt(pntrOutMirror);
            }  // Used to ouput more detail... Builds a set of strings that prints out a smaller 64-bit block with byte/line readouts...

            // Build the final demasked string...
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            deMaskedStrng = deMaskedStrng + outputSet;
            if (debugProcess8chars) {
                std::cout << "\n --> MAIN PROGRAM : Line 1656 -->\t |  Processing input-file-line == " + std::to_string(lineCntr) + "\t |  Line-block# == " + std::to_string(blockCnt) + "\t  --:|:-- buildDecrypted8chars NEXT CHUNK OUTPUT == " + outputSet;
                std::cout << "\n --> MAIN PROGRAM : Line 1657 : Added to deMaskedStrng to now TOTAL == " + deMaskedStrng;
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
            }
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

            //Clean padded spaces at the end of the line; IF a == lineLength...
            if (a == lineLength) {
                deMaskedStrng = eatTrailingSpaces(deMaskedStrng);
            }
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        } // END OF LOOP --> while (a < lineLength); --> Process blocks of 8 chars...

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        if (debugProcessLine) {  // Toggle to break program -::@::--> At the end of each line...
            std::cout << "\n --> RUNNING DE-CRYPTION -::|::--> Processing input-file-line == " + std::to_string(lineCntr) + "\t Read-Back INPUT line...\n";
            std::cout << lineIn << std::endl;
            std::cout << "\n --> RUNNING DE-CRYPTION -::|::--> Processing input-file-line == " + std::to_string(lineCntr) + "\t Read-Back DE-MASKED && DE-CYPHERED line...\n";
            std::cout << deMaskedStrng << std::endl;
            std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ CHECK SUCCESS -::|::- READ NEXT LINE TO PROCESS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
            // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            debugMsg = "BREAK CHECK --> DEBUG ABOVE --:|:-- Analayze how last line was processed <^>";
            continueTgl = checkBreak(debugMsg);
            if (continueTgl == 'N') {
                exit(1);
            }
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // Write converted line to output file... I know this general structure works...
        if (outputFile.is_open()) {    // Check if the output file is open and write the final decrypted text/data...
            outputFile << deMaskedStrng << std::endl;
        }
        else {
            std::cout << "\n\tFailed to create the output the De-Crypted file." << std::endl;  // Display an error message if file creation failed
        }

    } //  END OF LOOP -->  while (getline(fileIn, lineIn)); --> Process each line...

    // Close the file...
    fileIn.close();
    // Close the file...
    outputFile.close();


    // Runtime Analysis...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto end = std::chrono::high_resolution_clock::now();
    //std::chrono::time_point<std::chrono::high_resolution_clock> end = std::chrono::high_resolution_clock::now();
    auto dt = 1.e-9 * std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "\n\n --> File Successfully Decrypted and Output to :: " + outFilePath;
    std::cout << "\n --> Analayze Run-Time Execution Time == " + std::to_string(dt) + " Seconds !!!\n\n";

    debugMsg = "BREAK CHECK --> End Program --:|:-- Check RunTime...";
    continueTgl = checkBreak(debugMsg);
    if (continueTgl == 'N') {
        exit(1);
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}


// OVERALL THEORY DEEP DIVE - In theory, any request for validation/encryption is going to come from an app... at a specific time;
// And when you're logged into an app... the app already has your identity, and information about the device you're using.
// Using math unique to the device, identity involved when applicable, timestamp, and app utilized; You can recreate any RSA data...
// I have to wonder ways of using 'Active Device-ID', which will rotate on every call, as the main primary mask of the remaining data.
// Cyber-Force would not be in sole control of the remaining library/access strategies needed to circumvent how this protocol would be sent and updated.
// 
// Any device in the advanced world we want to build... will go through a 'Modular Verification' boot-up process, and have both a 'Registered-DeviceID' -  maintained by the OS in non-volatile memory; though this will change/rotate on boot-up processes...
// And an 'Active-DeviceID' maintained by a separate library/resource access protocol set that rotates on every main call to connected apps/cloud-resources.
// Truthfully, we want some over-arching theory that forces a kind of 2-part verification automatically with the OS team, and Cyber-Force maintaining a special chip, or partitioning and resource access strategy.
// Really, we want this Cyber-Force strategy to be capable of maintaining a separate algorithm set, but they also need manufacturers to collaborate on modular verification strategies for trusted boards/architecture.
// When firmware is present, I think it's possible to verify code bases work together as expected... and then you can work to make updates to that firmware as need based on trusted architecture data-flows.
// 
// The way this information, and tables of security tags related to software/apps used to interact with the overall IAM grid... gets used is case dependent.
// We're going to get to a point where every OS team has a subsidiary or partnership that maintains either a direct contract with Anti-Virus software, or an internal program...
// Most often these are configurations that will come with an identity product... So that separation of powers exists in architectural design, apart from the manufacturer of the device.

// CONCLUSION --> I'm going to focus on the repeatable ActiveDeviceID/ActiveSecurityKey(Hidden) related to the optimized security chip for modular verification and compartmentalization of security.
// The 'Registered-DeviceID' will be generated through either the OS or registered ID-Product App; Both will be calculated using similar tactics, but separate channels.
// The 'Active-DeviceID' will be passed in the transaction, and will be used to first lookup an active security key used for masking the remaining data in the protocol.
// When the protocol finishes, the ActiveDeviceID and volatile memory component containing the ActiveSecurityKey will be updated.
// While the protocol is executing, it will be working with the main chip/ram architecture and special partition/resource access of otherwise hidden system components... 
// Including passing either combined or separate APP/OS generated security keys, as well as registered device/product IDs... noting that registered device should be sufficient for the OS.
// In this way, algorithms driving the local generation of new values will always stay secure.
// This is due in part because of the ways updates will flow to devices in separate protocols, and be encrypted through the OS teams in conjunction with Cyber-Force through different channels.



// Still undecided if it's better to read the entire file in as one sequence of information, or line by line and segment the encryption in layers, while also re-arranging the order of the segments.

// We're reading in the FileName, and doing some string math to deduce the FileType... then removing structure characters and effectively encyphering that part of the data...

// Need to add \n to the end of every line as you read each in... and account for multi-character read-in in the generated structure character index restoration tracking arrays that will be used to decrypt the file.



// How are you going to know the size of the structure character arrays?  You have to loop through and count all of these to assign an array size.
// I think I should create a function that takes in a string of structure characters.  I'm kind of intending this be driven by file types or some passed paramter from the file.
// If I know the structure characters when this code runs... as in my example for CSV, I'm just going to count all spaces and structure characters...
// Create a corresponding array the same length as the string... and use this for storing the length of each new array for preserving structure.


//int* intASCIIarray = new int[totalASCIIchars];          //Integer configurations for selecting which letter position; Pairs with boolean array for selecting which name.
//char* charASCIIarray = new char[totalASCIIchars];       //The initial merged ASCII-Key input portion of the algorithm.


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Determine how many chunks to break the overall dataset into, by selecting one character...
// Or set of characters to model a mathematical relationship with the overall size of the dataset processed.


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Loop through and encypher each chunk of the file into an array; Noting that you want to find some way to use the original key to rotate cypher starting points.
// In this way, each chunk will be encyphered slightly differently.
// While you do this, remove the special characters that denote structure, but preserve their positions through building 2 arrays...
// One array logs the position of each special charcter; You need one array for each special character that denotes structure or spacing.
// The second array denotes the length of the value stored; Again you need a second array for each special character that denotes structure or spacing.


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Finally, build out the encyphered file; Appending each structuring character array, and spaces array separately.
// You will send the partnered arrays as a transmitted key file.  This is what I would call a "Public Key".
// Keeping in mind that complex data compartmentalization will allow us to flow the repeatable seed values which drive the primary key generation at both endpoints securely.


// =====================================================================================================================================================================
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ UNUSED CODE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

