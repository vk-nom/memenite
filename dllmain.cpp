#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "siggies.h"
#include "MemoryHelper.h"
#include "headers.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>
#include "api.h"

void WINAPI main() {
    FILE* fDummy;
    AllocConsole();
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    std::cout << "\x1B[2J\x1B[H";
    std::cout << "memenite\nv1.0 pre release";

    Uworld = MemoryHelper::PatternScan(signatures::Uworld_Sig);
    Uworld = RVA(Uworld, 7);

    FreeFn = MemoryHelper::PatternScan(signatures::Free_Sig);
    std::cout << "GetPlayerName: " << Framework::Objects::FindObject("/Script/Engine.PlayerState.GetPlayerName") << "\n";
}


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        main();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

