#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>
#include <vector>
#include <functional>
#include <iostream>
#include "MemoryHelper.h"
#include "no_spoofcall.h"
#include "siggies.h"
#include <algorithm>
#include "api.h"


inline bool ProcessEvent(uintptr_t address, void* fnobject, void* parms)
{
    UObject* addr = reinterpret_cast<UObject*>(address); if (!addr) return false;
    auto vtable = *reinterpret_cast<void***>(addr); if (!vtable) return false;
    auto processEventFn = static_cast<void(*)(void*, void*, void*)>(vtable[0x68]); if (!processEventFn) return false;
    SpoofCall(processEventFn, (void*)addr, (void*)fnobject, (void*)parms);
    return true;
}

namespace FNObjects {
    PVOID GetPlayerName;
}