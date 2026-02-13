// Dual_Layer_mergedApp_v1.0.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// =====================================================================================
#include <iostream> // Necessary for console output...
#include <fstream>  // File access library..
#include <string>   // Basic string operation functions
#include <numeric>  // Basic math functions
#include <random>   // More advanced random number generators
#include <limits>   // Learn how to utilize this library to optimize your code.
#include <vector>   // Useful for generating sequential and randomized arrays.
#include <chrono>   // Time functions 1...

#include "basicFunctions.h"

#include "runEncryption.h"
#include "runDecryption.h"

// =====================================================================================


// =====================================================================================================================================================================
// =====================================================================================================================================================================


// =====================================================================================================================================================================
// =====================================================================================================================================================================
int main()
{
    char mainToggle = 'Y';

    while (mainToggle == 'Y') {
        std::cout << "\n\n\n You're running Helm Cyber-Force Dual-Layer En-cryption/De-cryption...\n";
        std::cout << " -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
        std::cout << "\t\t ||   Option 'A' --> En-crypt a file.   || \n";
        std::cout << "\t\t ||   Option 'B' --> De-crypt a file.   || \n";
        std::cout << " -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
        std::string repeatMenu = " Please enter either 'A' to run En-cryption; Or enter 'B' to run De-cryption...\n";
        
        char optionsArray[2] = { 'A', 'B' };
        mainToggle = validToggleChar(optionsArray, repeatMenu, 2);


        // Program execution branch; validToggleChar always outputs a valid option; It will loop until a valid option is selected...
        if (mainToggle == 'A') {
            runEncryption();
        }
        else if (mainToggle == 'B') {
            runDecryption();
        }

        std::cout << "\n\n\n -~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~-~- \n";
        std::string runAgainMsg = "\tRun another Encryption/Decryption process ???\n";
        mainToggle = checkBreak(runAgainMsg);
    }

    std::cout << "\n\n======================= YOU'VE REACHED THE END OF THE PROGRAM =======================\n";
    std::cout << "============================== PROGRAM WILL NOW CLOSE ===============================\n";
}

// =====================================================================================================================================================================
// =====================================================================================================================================================================
// 
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
