#include "runEncryption.h"


//bool debugPrimaryInternals = false;
//bool debugKeySeeding = false;


void runEncryption() {
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
    std::cout << " --> runEncryption : Line 18 : (-Step 1-) --:|:--> Configuring input file & path...\n";;
    std::cout << "\tPlease enter a valid Windows filepath to a .txt or .csv file TO ENCRYPT...\n\t";
    std::cin >> inFilePath;
    std::cout << "\n --> runEncryption : Line 24 : (-Step 1-) --:|:--> Attempting to Open Data-File TO ENCRYPT @: " + inFilePath;
    // Open the input file TO ENCRYPT using ifstream...
    std::ifstream fileIn(inFilePath);

    while (!fileIn.is_open()) {
        std::cerr << "\n\tFailed to open file @: " << inFilePath;  // Print error message and repeat loop...
        while (!isValidPathFormat(inFilePath)) {
            std::cerr << "\n\tInput does not follow WINDOWS standards @: " << inFilePath << std::endl;;  // Print error message and repeat loop...

            std::cout << "\n\tPlease enter a valid Windows filepath to a .txt or .csv file TO ENCRYPT...\n\t";
            std::cin >> inFilePath;
        }

        std::ifstream fileIn(inFilePath);
        if (fileIn.is_open())
            std::cout << "\n\tSUCCESS --> Source-File TO ENCRYPT opened successfully @: " << inFilePath;
    }
    // Need a final check to alert user of successful input when entered correctly right away (NO LOOP NEEDED)...
    if (fileIn.is_open())
        std::cout << "\n\tSUCCESS --> Source-File TO ENCRYPT opened successfully @: " << inFilePath;

    std::cout << "\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
    std::cout << " --> runEncryption : Line 46 : (-Step 1-) --:|:--> Configuring output file & path...\n";;
    std::cout << "\tPlease enter a valid Windows filepath to a .txt file AS YOUR OUTPUT ENCRYPTED FILE...\n\t";
    std::cin >> outFilePath;
    std::cout << "\n --> runEncryption : Line 49 : (-Step 1-) --:|:--> Attempting to Create Output-File of Encrypted-Data @: " + inFilePath;
    // Create a new file to write the ecnrypted data to...
    std::ofstream outputFile(outFilePath);  // Open/create a file for writing encrypted data-copy to...

    while (!outputFile.is_open()) {
        std::cerr << "\n\tFailed to open file @: " << outFilePath;  // Print error message and repeat loop...
        while (!isValidPathFormat(outFilePath)) {
            std::cerr << "\n\tInput does not follow WINDOWS standards @: " << outFilePath << std::endl;;  // Print error message and repeat loop...

            std::cout << "\n\tPlease enter a valid Windows filepath to a .txt file AS YOUR OUTPUT ENCRYPTED FILE...\n\t";
            std::cin >> outFilePath;
        }

        std::ofstream outputFile(outFilePath);
        if (outputFile.is_open())
            std::cout << "\n\tSUCCESS --> Output-File for Encrypted-Data created successfully @: " << outFilePath;
    }
    // Need a final check to alert user of successful input when entered correctly right away (NO LOOP NEEDED)...
    if (outputFile.is_open())
        std::cout << "\n\tSUCCESS --> Output-File for Encrypted-Data created successfully @: " << outFilePath << std::endl;
    std::cout << " -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n\n";
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 1 -::|::-  Initial Seeding & Timestamp Functions  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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

    // Value overflow test; KEEP in code body until all testing is over to keep mechanical theory in mind...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    unsigned long long int valueFromLimits = ULLONG_MAX;
    unsigned long long int testMax = 18446744073709551615;
    unsigned long long int testOverflow = 18446744073709551615 + 1;
    std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- ";
    std::cout << std::endl;
    std::cout << "\n  Output of limits constant from <limits> header file : " + std::to_string(valueFromLimits);
    std::cout << "\n  unsigned long long int set to theoretical max value : " + std::to_string(testMax);
    std::cout << "\n     unsigned long long int, test overflow maxVal + 1 : " + std::to_string(testOverflow);
    std::cout << std::endl;
    std::cout << std::endl;

    // This needs to be adjusted to randomly select this final character... or further alter this stage with the XOR design variants you're trying to consider later...
    // Consider the portions of the 'passedSub' variants above...
    // Consider adding extra Hexadecimal characters; Sandwhiched between and swapped for positions in the string built so far...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string fast64seed = "0xa" + passedSub.substr((subStrngSize / 2), (subStrngSize / 2) - 1) + passedSub2 + passedSub.substr(0, subStrngSize / 2);

    // Run initial calculation or first-layer analysis of generated Hex-Value...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    unsigned long long logSeedVal;
    logSeedVal = calcHexVal(fast64seed);
    std::cout << "\n    Original Simulated Seed: " + fast64seed;
    std::cout << "\n    Overall Converted Value: " + std::to_string(logSeedVal);
    std::cout << std::endl;
    std::cout << std::endl;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Mersenne Twister Engine (32) should NOT be used for generating more than 624 unique values...
    // There is a known way to reverse engineer the sequence if these values can be intercepted...
    // Consider GitHub code for :: L'Ecuyer MRG32k3a ; Well19937a ; Melg19997/Melg19937-64
    std::mt19937_64 engine(logSeedVal);

    // Now use this as an initial seed for furter randomizing the seed...
    // I'm using this with randSeq9 in this version because only limited cases have collapsed to narrow ranges of output, SOMETHING TO WATCH...
    // SOMETHING TO WATCH --> Consider whether it may be better to use ONLY boolBitMask1 for 64-bit block permutations/rotations ONLY... VS bitMaskTwistCharsEN...
    // Debating on whether to replace this code with a version that only generates a single value, as we may just run 64-bit block permutations on the initial seed with boolBitMask1...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::uniform_int_distribution<int> randSeq9(1, 7);
    int* randSeqArray9 = new int[9];
    // The above code sets up the function to be called in this next loop...
    for (int i = 0; i < 9; ++i) {
        randSeqArray9[i] = randSeq9(engine);
    }
    // Prefer to denote pointers with this convention for learning purposes...
    int* pntrVar6A = new int[9];
    pntrVar6A = &randSeqArray9[0];

    // Must print to confirm this works as expected; NO LONGER NEEDED...
    //string testOutput = "Confirm Array Values --:|:-->\n";
    //for (int i = 0; i < 9; i++) {
    //    testOutput = testOutput + std::to_string(randSeqArray9[i]) + " "; }
    //std::cout << testOutput;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Perform operations to initiailize the primary seed...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\n --> runEncryption --> Line 213 : (-Step-XXX-) --:|:-- Create [8]x[8] Boolean Matrix --> Special block for internal initial seeding !!!\n"; }
    bool bool2d64bitInMainSeed[8][8] = { false };
    bool* pntrVar7A = &bool2d64bitInMainSeed[0][0];

    // Build a 64-Bit Boolean grid while also converting an output 64-bit unsigned int...
    if (debugKeySeeding) {
        std::cout << "\n\n --> runEncryption : Line 219 : -::|::--> Convert initial fast64seed to a 64-bit block for further permutations...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    unsigned long long int primarySeed = fast64buildBoolInt(fast64seed, &bool2d64bitInMainSeed[0][0]);

    // Twist and randomize the seed, thus building off of the initial seeding equations...
    // This version has only had weird moments where it collapses grids to limited values... or some ranges may have bugs...
    bitMaskTwistCharsEN(&bool2d64bitInMainSeed[0][0], &randSeqArray9[0]);
    // Utilize boolBitMask1 to perfom simpler permutations if some condition is met... May Fix some ranges may have bugs...
    //bool64bitMask_EN1();

    if (debugKeySeeding) {
        std::cout << "\n\n --> runEncryption : Line 231 : -::|::--> Check output from performing Bit-Masking operation on initial seed...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
    }
    //Ouput Final-Twisted Internal-Service-Seed; used to generate a Security Key which is then factored into a seed...
    unsigned long long int hexMaskedSeed = convert64bitBooltoInt(&bool2d64bitInMainSeed[0][0]);

    std::cout << "\n                   Primary/Initial Seed: " + std::to_string(primarySeed);
    std::cout << "\n    Final-Twisted Internal-Service Seed: " + std::to_string(hexMaskedSeed);
    std::cout << std::endl;
    std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
    std::cout << std::endl;
    std::cout << std::endl;

    if (debugKeySeeding) {
        std::cout << "\n\n --> runEncryption : Line 238 : -::|::--> NOTE TO SELF !!! --> Watch how the above continues to generate; Test somehow if possible to ensure security of initial seed used to build the SecurityKey...\n";
    }

    // You first build out the simulated Internal Service Seed, then combine it with the simulated DEV-OS-APP verification API...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 2 -::|::-  Generate Security Key && Run Cyber-Force Simulated API  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // SIMULATE A DATABASE by using this file structure for the parseHexValFromKey functionality...
    std::string simActiveSecTablesFilePath = "C:/Users/BrandonHelm/Documents/testPRGRMoutput/_activeSecurityTables.txt";
    std::string simDEVOSAPPsecTablesFilePath = "C:/Users/BrandonHelm/Documents/testPRGRMoutput/_DEVOSAPP_activeSecurity.txt";

    // 128 bit (16-Character) ------> [2]x[8] Matrix Built...
    // 256 bit (32-Character) ------> [4]x[8] Matrix Built...
    // 512 bit (64-Character) ------> [8]x[8] Matrix Built...
    // 1024 bit (128-Character) ----> 2 - [8]x[8] Matrices Built... BUILD THIS VERSION !!!
    // 2048 bit (256-Character) ----> 4 - [8]x[8] Matrices Built...

    //char secKeyMatrix1[2][8];     // TEST BOUNDS --> 128-bit setting
    //char secKeyMatrix1[8][8];     // TEST BOUNDS --> 512-bit setting; TEST VERSION...
    char secKeyMatrix1[16][8];      // TEST BOUNDS --> 1024-bit setting; PROD VERSION...
    //char secKeyMatrix1[32][8];    // TEST BOUNDS --> 2048-bit setting
    char* pntrVar8A = &secKeyMatrix1[0][0];

    //string securityKey = genSecurityKey(hexMaskedSeed, pntrVar8A, 128);       // TEST BOUNDS --> 128-bit setting
    //string securityKey = genSecurityKey(hexMaskedSeed, pntrVar8A, 512);       // TEST BOUNDS --> 512-bit setting; TEST VERSION...
    std::string securityKey = genSecurityKey(hexMaskedSeed, pntrVar8A, 1024);        // TEST BOUNDS --> 1024-bit setting; PROD VERSION...
    //string securityKey = genSecurityKey(hexMaskedSeed, pntrVar8A, 2048);      // TEST BOUNDS --> 2048-bit setting

    if (debugKeySeeding) {
        std::cout << "\n\n --> MAIN PROGRAM : Line 1702 : -::|::--> Check output from genSecurityKey64 string...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        std::cout << securityKey;
        std::cout << "\n --> MAIN PROGRAM : Line 1705 : -::|::--> Check output from genSecurityKey64 matrix representation...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        //print2D_charMatrix(pntrVar8A, 2, 8);      // TEST BOUNDS --> 128-bit setting
        //print2D_charMatrix(pntrVar8A, 8, 8);      // TEST BOUNDS --> 512-bit setting; TEST VERSION...
        print2D_charMatrix(pntrVar8A, 16, 8);     // TEST BOUNDS --> 1024-bit setting; PROD VERSION...
        //print2D_charMatrix(pntrVar8A, 32, 8);     // TEST BOUNDS --> 2048-bit setting
    }
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Key Parsing randomiation requires "Active-Security Tables"; and a major part of those drive how these keys are parsed...
    // First, I'll SIMULATE integarting a DATABASE by just using a CSV file for passing these arrays between encrytpion/decryption executions...
    // These table updates should be going out through the primary network; The Cyber-Force API and platform would cover this...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // Needs to be passed to customAZhexConverter, and output to a file a a CSV line that can be imported in De-Cryption...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::uniform_int_distribution<int> validHexBounds(65, 70);
    int* alphaHexXrefs = new int[26];
    // The above code sets up the function to be called in this next loop...
    for (int i = 0; i < 26; ++i) {
        alphaHexXrefs[i] = validHexBounds(engine);
    }

    if (debugKeySeeding) {
        std::cout << "\n Debug Generation of Active-Security-xRef-Tables --> alphaHexXrefs...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        print2D_intTblLyr(alphaHexXrefs, 1, 26);
        std::cout << std::endl;
    }

    // Needs to be passed to customAZhexConverter, and output to a file a a CSV line that can be imported in De-Cryption...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::uniform_int_distribution<int> stdBase10bounds(0, 9);
    int* base10xRefs = new int[10];
    // The above code sets up the function to be called in this next loop...
    for (int i = 0; i < 10; ++i) {
        base10xRefs[i] = stdBase10bounds(engine);
    }

    if (debugKeySeeding) {
        std::cout << "\n Debug Generation of Active-Security-xRef-Tables --> base10xRefs...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        print2D_intTblLyr(base10xRefs, 1, 10);
        std::cout << std::endl;
    }

    // Needs to be passed to scaleStep6, and output to a file a a CSV line that can be imported in De-Cryption...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::uniform_int_distribution<int> scaleStepBounds(2, 8);  // Day of week is already pointing initial position to a value of 0-6, careful how many can be added as we step to grab 16 characters...
    //std::uniform_int_distribution<int> scaleStepBounds(2, 7);
    int* scaleStepXrefs = new int[16];
    // The above code sets up the function to be called in this next loop...
    for (int i = 0; i < 16; ++i) {
        scaleStepXrefs[i] = scaleStepBounds(engine);
    }

    if (debugKeySeeding) {
        std::cout << "\n Debug Generation of Active-Security-xRef-Tables --> scaleStepXrefs...";
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        print2D_intTblLyr(scaleStepXrefs, 1, 16);
        std::cout << std::endl;
    }


    // ACTIVE SECURITY TABLES...
    // Key Parsing randomiation requires "Active-Security Tables"; and a major part of those drive how these keys are parsed...
    // First, I'll SIMULATE integarting a DATABASE by just using a CSV file for passing these arrays between encrytpion/decryption executions...
    // These table updates should e going out through the primary network, but the Cyber-Force API and platform could cover this...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // So for now, open, create/overwrite a file of critical security tables...
    std::ofstream secTablesFile(simActiveSecTablesFilePath);
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Write/Out filePath...
    std::cout << "\n --> MAIN PROGRAM : Line 1758 : (-Step 0.1-) --:|:--> Creating simulated database Active-Security-xRef-Tables file @:" + simActiveSecTablesFilePath;
    if (!secTablesFile.is_open()) {
        // print error message and return
        std::cerr << "\n\tFailed to open file @: " << simActiveSecTablesFilePath;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        exit(1);
    }
    else
        std::cout << "\n\tCreating output Active Security xRefs file @: " << simActiveSecTablesFilePath;
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Quickly write the critical 3 arrays to the file...
    if (secTablesFile.is_open()) {    // Basic error trap for writing the file...
        secTablesFile << printIntArrayToCSV(alphaHexXrefs, 26);
        secTablesFile << printIntArrayToCSV(base10xRefs, 10);
        secTablesFile << printIntArrayToCSV(scaleStepXrefs, 16);
    }
    else {
        std::cout << "\n\tFailed to create the Active Security xRefs file." << std::endl;  // Display an error message if file creation failed
    }
    // And close the file right away...
    secTablesFile.close();
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    // Now parse this generated 1024-bit key into a unique 64-bit integer...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //int secKeySeedInternal = parseIntFromKey(securityKey);
    std::string hexValStrng = parseHexValFromKey(securityKey, alphaHexXrefs, base10xRefs, scaleStepXrefs);
    unsigned long long int parsedSecKeySeed = calcHexVal(hexValStrng);
    if (debugKeySeeding) {
        std::cout << "\n\n --> MAIN PROGRAM : Line 1721 : -::|::--> Check output from parseHexValFromKey; Check HexaDecimal string generated == " + hexValStrng;
        std::cout << "\n --> MAIN PROGRAM : Line 1722 : -::|::-- > HexaDecimal value converts to == " + std::to_string(parsedSecKeySeed);
        std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
        // Pass the 64-bit matrix used earlier for outputting seeding steps; A printout of convert64bitBooltoInt is included in fast64buildBoolInt...
        fast64buildBoolInt(hexValStrng, pntrVar7A);
    }



    // Finally, consider how keys could be stacked in commercial/prod environments to enable a Cyber-Force...
    // CALIBRATE-ENCRYPTION-SEED --:|:--> Simulate an API to authenticate other system resources from the requesting device...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // It doesn't matter if this is ever intercepted as there are too many other masked pieces...
    // Additionally this is designed to rotate as an Active-Device-ID...
    // In theory; in a perfect world ONLY Cyber-Force authenticates genuine Manufacturer-ID information for critical security reasons...
    uint_fast64_t brandonHelmsDevice = 0x5555555555555555;

    // Simulate this API with a file call; KEEP IN MIND !!! --> You would normally pass the 2 critical security keys for OS & APP layers, Device Security Key is also a good idea
    unsigned long long int secKeySeedMaster = cyberForceSecKeyComb(parsedSecKeySeed, brandonHelmsDevice, simDEVOSAPPsecTablesFilePath);


    // Plug in test cases for debug... Pass set seed variable...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //hexMaskedSeed = parsedSecKeySeed;             // PROD --> Primary setting to wire SEED parsed from Security Key into the encryption program...
    hexMaskedSeed = secKeySeedMaster;         // PROD --> Primary setting which includes simulated Cyber-Force API...
    //hexMaskedSeed = 18192021222324;           // MAIN Test Case from development...


    // Finally you can use all this effort to create a genuinely well constructed random seed...
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // Mersenne Twister Engine (32) should NOT be used for generating more than 624 unique values...
    // There is a known way to reverse engineer the sequence if these values can be intercepted...
    // Consider GitHub code for :: L'Ecuyer MRG32k3a ; Well19937a ; Melg19997/Melg19937-64
    std::mt19937_64 engine2(hexMaskedSeed);

    std::cout << "\n\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
    std::cout << "\n Program seeded with Cyber-Force Simulated API & Internal Service Layer...";
    std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
    std::cout << "\n\t\t      Final Combination Lock-Seed: " + std::to_string(hexMaskedSeed);
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
    initializeCypher(stdSeqArray, cypherArray, hexMaskedSeed);


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // STEP 4 -::|::-  Run Dual-Layer Encryption  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    if (debugPrimaryInternals) { std::cout << "\n --> runEncryption : Line 433 : (-Step XXX-) --:|:--> Create [8]x[8] Boolean Matrix --> Final Conversions Matrix, used in MAIN processing !!!\n"; }
    bool bool2d64bitInMain[8][8] = { false };
    bool* pntrVar5A = &bool2d64bitInMain[0][0];


    // We will output the security seed/key at the top of the encrypted file until a commercial version is developed...
    outputFile << "Encrypted File-Key --> " + securityKey << std::endl;                      // PROD BRANCH; Outputs Security Key to top of encrypted file...
    //outputFile << "Encrypted Seed --> " + std::to_string(hexMaskedSeed) << endl;      // DEV BRANC; Outputs primary seed to top of encrypted file...



    // Primary command-line program notification...
    std::cout << "\n\n --> MAIN PROGRAM : Line 1813 : (-Step 2.1-) --:|:--> Running Dual-Layer Encryption...";



    // Read the input file line by line and FIRST run CYPHER; then SECOND run bitMask permutations... 
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::string lineIn;
    int lineCntr = 0;
    while (getline(fileIn, lineIn)) {
        lineCntr++;

        if (debugPrimaryInternals) {
            std::cout << "\n --> RUNNING ENCRYPTION -::|::--> Read-Back INPUT line...\n";
            std::cout << lineIn << std::endl;
        }

        // Get length of line, use this data when looping to grab and convert all characters for CYPHER and BIT-MASKING...
        int lineLength = lineIn.length();
        // Actually, BIT-MASKING will utilize some division, rounded up for the final block...

        // Layer-1 --> CYPHER Encryption...
        // For CYPHER-SWAPS, must find character in purgedASCIIstdSeqRA...
        // Can use a clever approach that always starts at the ASCII value position, and works it's way down... adjusting the bounds for the high-end of the array to prevent index errors.
        // Best to do this with the math from the beginning of the program where we get the purged count... and considering how narrow to make the IF-ELSE fall-throughs for necessary adjustments.
        // 127 and 255 are the key values to wonder about... and there is no reason to adjust this overall strategy to remove structure characters... as this is technically masked effectively in the way you're swapping CYPHERS...
        std::string cypheredStrng = "";
        std::string originalChar = "";
        std::string cypheredChar = "";
        for (int a = 0; a < lineLength; a++) {
            unsigned char currentChar = lineIn[a];  // Should be an int!
            //std::cout << "--> RUNNING ENCRYPTION -::|::--> attempting to find character == " + std::to_string(currentChar) + "\n";

            // IS IT POSSIBLE TO SPEED UP THIS LOOP WITH THE ABOVE NOTE ?
            // IF currentChar < 64, 128, 192, 256 ???
            int posFlag = 0;
            while (stdSeqArray[posFlag] != currentChar) {
                if (performanceOp) { std::cout << "\n --> MAIN PROGRAM : Line 1847 : Calculating Cypher-Swap FROM -->\t  stdSeqArray[" + std::to_string(posFlag) + "] == " + std::to_string(stdSeqArray[posFlag]) + " | \t != currentChar == " + std::to_string(currentChar); }
                posFlag++;
            }
            unsigned char cypheredChar = cypherArray[posFlag];   // This should grab the corresponding 
            cypheredStrng = cypheredStrng + static_cast<char>(cypheredChar);
            if (debugCypherSwaps) { std::cout << "\n --> MAIN PROGRAM : Line 1852 : Performing Cypher-Swap -->\t |  All characters from input file == " + std::to_string(currentChar) + "\t |  Will be translated == " + std::to_string(cypheredChar); }
        }
        if (debugPrimaryInternals) {
            std::cout << "\n --> RUNNING ENCRYPTION -::|::--> Read-Back INPUT line...\n";
            std::cout << lineIn << std::endl;
            std::cout << "\n --> RUNNING ENCRYPTION -::|::--> Read-Back CYPHERED line...\n";
            std::cout << cypheredStrng << std::endl;
        }

        if (debugCypherSwaps) {
            debugMsg = "BREAK CHECK --> Main Processing Check --:|:-- Check Cypher-Swap Output...";
            continueTgl = checkBreak(debugMsg);
            if (continueTgl == 'N') {
                exit(1);
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }

        // Layer-2 --> BIT-MASKING Encryption...  Run bitMasking, grabbing 8 characters at a time and utilizing your 64-bit block function...
        // Actually, BIT-MASKING will utilize some division, rounded up for the final block... this will determine loop bounds...
        // I think I can use a DOUBLE or FLOAT for the initial calc... and then store as an int and add 1 ONLY IF %/Modulus == 0...
        // So do both long division and modulus every time, then use IF statement accordingly...
        int blockCnt = 0;
        int blockCntTotal = 0;
        float divCalc = lineLength / 8;
        int modCalc = lineLength % 8;
        int divTruncated = divCalc;
        if (modCalc > 0)
            blockCntTotal = divTruncated + 1;
        else
            blockCntTotal = divTruncated;
        if (debugPrimaryInternals) { std::cout << "\n --> MAIN PROGRAM : Line 1883 : Calculating blocks from original input line length == " + std::to_string(lineLength) + "\t & blocks count == " + std::to_string(blockCntTotal); }
        std::string hexedStrng = "";

        int a = 0;

        while (a < lineLength) {
            blockCnt++;
            if (debugProcess8chars) {
                std::cout << "\n\n\n\n --> MAIN PROGRAM : Line 1891 --> Beginning block loop # " + std::to_string(blockCnt) + "\t from overall index position # " + std::to_string(a) + "\t of overall length == " + std::to_string(lineLength);
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
            }

            std::string toMaskStrng = "";

            if (blockCnt < blockCntTotal) {
                toMaskStrng = cypheredStrng.substr(a, 8);
            }
            else if (modCalc == 0) {
                toMaskStrng = cypheredStrng.substr(a, 8);
            }
            else { // Pad the last block generated...
                // Grab the final string to encrypt, knowing the remaining characters in the string; Because of the way this loop is built... need to subtract 8 here...
                toMaskStrng = cypheredStrng.substr(a, modCalc);
                // Map the character that space has been swapped with, so this will decrypt correctly...
                std::string spcChar = outputStrngFromASCIIval(cypherArray[0]);
                // Calculate the number of characters that have to be padded to the end...
                int padChars = 8 - modCalc;
                std::string spacesStrng = "";

                for (int b = 0; b < padChars; b++) {
                    if (debugProcess8chars) { std::cout << "\n --> MAIN PROGRAM : Line 1913 --> toMaskStrng == PADDING STRING !!!"; }
                    spacesStrng = spacesStrng + spcChar;
                }
                // Finally, build the last padded string of 8 vald characters...
                toMaskStrng = toMaskStrng + spacesStrng;
            }
            if (debugProcess8chars) {
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                std::cout << "\n --> MAIN PROGRAM : Line 1922 --> Check (toMaskStrng) before running Bit-Masking; Check padding of last block or set of 8 chars... () == (" + toMaskStrng + ")";
            }

            // Need to re-generate randSeqArray9... First time called with new hexMaskedSeed...
            for (int i = 0; i < 9; ++i) {
                randSeqArray9[i] = randSeq9(engine2);
            }
            // This sequence generates the same as long as seeded value is set correctly to the generated value from encryption; in encryptedScript.
            if (debugPrimaryInternals) {
                std::cout << "\n\n\n --> MAIN PROGRAM : Line 1929 --> Random Generation Sequence of 9 integers, toMaskStrng loop # " + std::to_string(blockCnt) + " ; While processing input file line # " + std::to_string(lineCntr);
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
                std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-";
                std::cout << "\n ~~~~~~~~~~~~~~ I Already Know These Match Generation Steps As Expected ~~~~~~~~~~~~~~";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
                print2D_intTblLyr(randSeqArray9, 1, 9);
            }

            buildBoolGridFrom8chars(toMaskStrng, pntrVar5A);
            if (debugMajorPermutations) {
                std::cout << "\n -- > MAIN PROGRAM : Line 1938 -- > Debug buildBoolGridFrom8chars...";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
                convert64bitBooltoInt(pntrVar5A);
            }

            if (debugPrimaryInternals) {
                std::cout << "\n --> MAIN PROGRAM : Line 1943 --> Running bitMaskTwistCharsEN...";
                std::cout << "\n ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
            }

            hexedStrng = hexedStrng + bitMaskTwistCharsEN(pntrVar5A, randSeqArray9);

            a = (blockCnt * 8);
        }

        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  BREAK CHECK LINES  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // In Late-Debugging, I replicate/repeat these outputs a second time, as there are also earlier run-time outputs...
        if (debugProcessLine) {
            std::cout << "\n\n\n --> RUNNING ENCRYPTION -::|::--> Read-Back INPUT line...\n";
            std::cout << lineIn << std::endl;
            std::cout << "\n --> RUNNING ENCRYPTION -::|::--> Read-Back CYPHERED line...\n";
            std::cout << cypheredStrng << std::endl;
            std::cout << "\n --> RUNNING ENCRYPTION -::|::--> Read-Back BIT-MASKED line...\n";
            std::cout << hexedStrng << std::endl;
            std::cout << "\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";
            std::cout << "\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~";

            debugMsg = "BREAK CHECK --> Check Above Final Generated Output Encrypted Line --:|:-- Check Output...";
            continueTgl = checkBreak(debugMsg);
            if (continueTgl == 'N') {
                exit(1);
            }
            std::cout << std::endl;
            std::cout << std::endl;
        }
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
        // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

        // Write converted line to output file...
        if (outputFile.is_open()) {    // Check if the file was successfully opened...
            outputFile << hexedStrng << std::endl;  // Write a line of text to the file...
        }
        else {
            std::cout << "\tFailed to create the En-Crypted file." << std::endl;  // Display an error message if file creation failed
        }
    }

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
    std::cout << "\n\n --> File Successfully Encrypted and Output to :: " + outFilePath;
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

