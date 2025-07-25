/**
 * @file pch.h
 * @author Sina Karvandi (sina@hyperdbg.org)
 * @brief header file corresponding to the pre-compiled header
 * @details
 * @version 0.1
 * @date 2020-04-11
 *
 * @copyright This project is released under the GNU Public License v3.
 *
 */
#pragma once

//
// Environment headers
//
#include "platform/user/header/Environment.h"

//
// Windows SDK headers
//
#define WIN32_LEAN_AND_MEAN

//
// IA32-doc has structures for the entire intel SDM.
//

#define USE_LIB_IA32
#if defined(USE_LIB_IA32)
#    pragma warning(push, 0)
// #    pragma warning(disable : 4201) // suppress nameless struct/union warning
#    include <ia32-doc/out/ia32.h>
#    pragma warning(pop)
typedef RFLAGS * PRFLAGS;
#endif // USE_LIB_IA32

//
// Native API header files for the Process Hacker project.
//
// #define USE__NATIVE_PHNT_HEADERS
#define USE_NATIVE_SDK_HEADERS
#define _AMD64_

#if defined(USE__NATIVE_PHNT_HEADERS)

//
// Dirty fix: the "PCWCHAR" in undefined in "ntrtl.h" so I deifined it here.
//
typedef const wchar_t *LPCWCHAR, *PCWCHAR;

#    define PHNT_MODE               PHNT_MODE_USER
#    define PHNT_VERSION            PHNT_WIN11 // Windows 11
#    define PHNT_PATCH_FOR_HYPERDBG TRUE

#    include <phnt/phnt_windows.h>
#    include <phnt/phnt.h>

#elif defined(USE_NATIVE_SDK_HEADERS)

#    include <winternl.h>
#    include <Windows.h>
#    include <winioctl.h>
#    include <platform/user/header/Windows.h>

#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <strsafe.h>
#include <shlobj.h>
#include <tchar.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <VersionHelpers.h>
#include <tchar.h>
#include <psapi.h>
#include <time.h>
#include <conio.h>
#include <intrin.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

//
// STL headers
//
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <bitset>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <fstream>
#include <map>
#include <numeric>
#include <list>
#include <locale>
#include <memory>
#include <cctype>
#include <cstring>
#include <unordered_set>
#include <regex>

//
// Scope definitions
//
#define SCRIPT_ENGINE_USER_MODE
#define HYPERDBG_USER_MODE
#define HYPERDBG_LIBHYPERDBG

//
// Zydis Debug Disable Flag
//
#ifndef NDEBUG
#    define NDEBUG
#endif // !NDEBUG

//
// Keystone
//
#include "keystone/keystone.h"

//
// HyperDbg defined headers
//
#include "config/Configuration.h"
#include "config/Definition.h"
#include "SDK/HyperDbgSdk.h"

//
// Script-engine
//
#include "../script-eval/header/ScriptEngineHeader.h"

//
// Imports/Exports
//
#include "SDK/imports/user/HyperDbgScriptImports.h"
#include "SDK/imports/user/HyperDbgLibImports.h"

//
// PCI IDs
//
#include "pci-id.h"

//
// General
//
#include "header/libhyperdbg.h"
#include "header/export.h"
#include "header/inipp.h"
#include "header/commands.h"
#include "header/common.h"
#include "header/symbol.h"
#include "header/debugger.h"
#include "header/script-engine.h"
#include "header/help.h"
#include "header/install.h"
#include "header/list.h"
#include "header/tests.h"
#include "header/transparency.h"
#include "header/communication.h"
#include "header/namedpipe.h"
#include "header/forwarding.h"
#include "header/kd.h"
#include "header/pe-parser.h"
#include "header/ud.h"
#include "header/objects.h"
#include "header/steppings.h"
#include "header/rev-ctrl.h"
#include "header/assembler.h"

//
// hwdbg
//
#include "header/hwdbg-interpreter.h"
#include "header/hwdbg-scripts.h"

//
// Libraries
//

#ifdef ENV_WINDOWS

#    pragma comment(lib, "ntdll.lib")

//
// For path combine
//
#    pragma comment(lib, "Shlwapi.lib")

//
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
// for tcpclient.cpp and tcpserver.cpp
//
#    pragma comment(lib, "Ws2_32.lib")
#    pragma comment(lib, "Mswsock.lib")
#    pragma comment(lib, "AdvApi32.lib")

//
// For GetModuleFileNameExA on script-engine for user-mode
// Kernel32.lib is not needed, but seems that it's the library
// for Windows 7
//
#    pragma comment(lib, "Psapi.lib")
#    pragma comment(lib, "Kernel32.lib")

#endif // ENV_WINDOWS
