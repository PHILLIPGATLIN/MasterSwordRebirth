/***
*
*	Copyright (c) 1996-2002, Valve LLC. All rights reserved.
*
*	This product contains software technology licensed from Id
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc.
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
/*

===== h_export.cpp ========================================================

  Entity classes exported by Halflife.

*/

#include "msdllheaders.h"
#include "global.h"
#include "logger.h"

// Holds engine functionality callbacks
enginefuncs_t g_engfuncs;
globalvars_t* gpGlobals;

#undef DLLEXPORT
#ifdef _WIN32
#define DLLEXPORT __stdcall
#else
#define DLLEXPORT __attribute__ ((visibility("default")))
#endif

#ifdef _WIN32
/*
#define DLL_PROCESS_DETACH   0
#define DLL_PROCESS_ATTACH   1
#define DLL_THREAD_ATTACH    2
#define DLL_THREAD_DETACH    3
#define DLL_PROCESS_VERIFIER 4
*/

// Required DLL entry point
BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID lpvReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH ||
		fdwReason == DLL_PROCESS_DETACH)
		DBG_INPUT;

	if (fdwReason == DLL_PROCESS_ATTACH)
		MSGlobals::DLLAttach(hinstDLL);
	else if (fdwReason == DLL_PROCESS_DETACH)
		MSGlobals::DLLDetach();

	return TRUE;
}
#endif

extern "C" void DLLEXPORT GiveFnptrsToDll(enginefuncs_t * pengfuncsFromEngine, globalvars_t * pGlobals)
{
#ifdef _WIN32
	DBG_INPUT;
#endif
	memcpy(&g_engfuncs, pengfuncsFromEngine, sizeof(enginefuncs_t));
	gpGlobals = pGlobals;
#ifndef _WIN32
	MSGlobals::DLLAttach(0);
#endif
}
