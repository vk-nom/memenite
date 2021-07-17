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

    //dumping things
    FreeFn = MemoryHelper::PatternScan(signatures::Free_Sig);
    Uworld = MemoryHelper::PatternScan(signatures::Uworld_Sig);
    Uworld = RVA(Uworld, 7);

    //opening console (in a way fn wont output gay shit
    FILE* fDummy;
    AllocConsole();
    //static_cast<VOID>(freopen("CONIN$", "r", stdin));
    static_cast<VOID>(freopen("CONOUT$", "w", stdout));
    //static_cast<VOID>(freopen("CONOUT$", "w", stderr));

    //trying to define playername (horrible and doesnt work)
    //UObject playerName = Framework::Objects::FindObject("/Script/Engine.PlayerState.GetPlayerName");
    //Framework::Objects::GetUObjectName("/Script/Engine.PlayerState.GetPlayerName");
    //const char* playername = Framework::Objects::FindObject("/Script/Engine.PlayerState.GetPlayerName");

    //new and works
    int i = 0;
    uintptr_t World = read<uintptr_t>(Uworld);
    uintptr_t PersistentLevel = read<uintptr_t>(World + offsets::PersistentLevel);
    uintptr_t AActors = read<uintptr_t>(PersistentLevel + offsets::AActors);
    auto CurrentPawn = read<uintptr_t>(AActors + i * sizeof(uintptr_t));

    uintptr_t PlayerState = read<uintptr_t>(CurrentPawn + offsets::PlayerState);


    Framework::Structs::FString PlayerName;
    ProcessEvent(PlayerState, FNObjects::GetPlayerName, &PlayerName);



    //outputting to the console
    FNObjects::GetPlayerName = Framework::Objects::FindObject("/Script/Engine.PlayerState.GetPlayerName");
    printf("memenite\nv1.0 pre release\n");
    wprintf(PlayerName.c_str());
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

