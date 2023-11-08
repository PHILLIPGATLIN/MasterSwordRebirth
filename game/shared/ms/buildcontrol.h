//When defined, DEV_BUILD indicates that this is
//a MSDev version of MS.  Certain features are allowed in this mode
//New: This is now defined in the project instead of a file
//#define DEV_BUILD

//When defined, the client and server dlls will maintain txt logfiles
#define KEEP_LOG

//Causes DbgInputs() to be called for each DLL input function in the client and server dlls
#define TRACK_INPUTS

//In the release build, whether certain errors treated as fatal (release) or not (debug)
#define RELEASE_LOCKDOWN

#ifdef RELEASE_LOCKDOWN
#define SCRIPT_LOCKDOWN //Automatic, with lockdown mode
#endif
