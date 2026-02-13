// Debug toggles...
// =====================================================================================

extern bool debugIntro;                    // Must use with debugPrimaryInternals; Break-Cheaks the read-out of each internal step...
extern bool debugPrimaryInternals;

extern bool debugKeySeeding;
extern bool debugCypherSwaps;          // SET TO TRUE TO STUDY PERFORMANCE OP...

extern bool debugStringBuild;			// Decryption Only
extern bool performanceOp;				// Encryption Only; SET TO TRUE TO OPTIMIZE ITERATIVE COMPLEXITY...

extern bool debugByteLineReadout;
extern bool debugBitMaskInternals;         // SET TO TRUE TO CLEAN UP FUNCTION NAMES ( bit-mask 1 & 2 ; )!!!  -->
extern bool debugMajorPermutations;        // Knowing Bit-Mask Functions work correctly; Debug major STEP-1 = Readout Overall BitMasked String && STEP-2 = Readout Final Cypher-Swapped String...

extern bool debugProcess8chars;
extern bool debugProcessLine;

extern bool oldPASSEDdebug;

// Extra --> For active debugging...
//bool activeDebug = true;
//bool activeDebug = false;
//bool processBreak = true;
//bool processBreak = false;