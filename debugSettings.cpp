#include "debugSettings.h"

// Debug toggles...
// =====================================================================================
//bool debugIntro = true;                     // Must use with debugPrimaryInternals; Break-Cheaks the read-out of each internal step...
bool debugIntro = false;                    // Must use with debugPrimaryInternals; Break-Cheaks the read-out of each internal step...
//bool debugPrimaryInternals = true;
bool debugPrimaryInternals = false;

//bool debugKeySeeding = true;
bool debugKeySeeding = false;
//bool debugCypherSwaps = true;           // SET TO TRUE TO STUDY PERFORMANCE OP...
bool debugCypherSwaps = false;          // SET TO TRUE TO STUDY PERFORMANCE OP...

//bool debugStringBuild = true;			// Decryption Only
bool debugStringBuild = false;			// Decryption Only
//bool performanceOp = true;			// Encryption Only; SET TO TRUE TO OPTIMIZE ITERATIVE COMPLEXITY...
bool performanceOp = false;				// Encryption Only; SET TO TRUE TO OPTIMIZE ITERATIVE COMPLEXITY...

//bool debugByteLineReadout = true;
bool debugByteLineReadout = false;
//bool debugBitMaskInternals = true;          // SET TO TRUE TO CLEAN UP FUNCTION NAMES ( bit-mask 1 & 2 ; )!!!  --> Could change to debugBitMaskInternals
bool debugBitMaskInternals = false;         // SET TO TRUE TO CLEAN UP FUNCTION NAMES ( bit-mask 1 & 2 ; )!!!  -->
//bool debugMajorPermutations = true;         // Knowing Bit-Mask Functions work correctly; Debug major STEP-1 = Readout Overall BitMasked String && STEP-2 = Readout Final Cypher-Swapped String...
bool debugMajorPermutations = false;        // Knowing Bit-Mask Functions work correctly; Debug major STEP-1 = Readout Overall BitMasked String && STEP-2 = Readout Final Cypher-Swapped String...

//bool debugProcess8chars = true;
bool debugProcess8chars = false;
//bool debugProcessLine = true;
bool debugProcessLine = false;

//bool oldPASSEDdebug = true;
bool oldPASSEDdebug = false;

// Extra --> For active debugging...
//bool activeDebug = true;
//bool activeDebug = false;
//bool processBreak = true;
//bool processBreak = false;
// =====================================================================================