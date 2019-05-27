// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>
#include <windowsx.h>

// C RunTime Header Files
//#include <stdlib.h>
//#include <malloc.h>
//#include <memory.h>
//#include <tchar.h>

// reference additional headers your program requires here
#include <ShellAPI.h>
#include <commctrl.h> 
#include <assert.h>

#include "../bridge/bridge.h"

//#define TITLE_TEXT TEXT("Cliente Arkanoid/Breakout") -> definido nas string tables;

#define MAX_LOADSTRING 100