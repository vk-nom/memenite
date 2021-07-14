#pragma once
#include <Windows.h>

uintptr_t Uworld;
uintptr_t FreeFn;
uintptr_t GetNameByIndex;
uintptr_t LineOfS;
uintptr_t BoneMatrix;
uintptr_t ProjectWorldToScreen;

//Read Addresses
uintptr_t PlayerController;
uintptr_t LocalPawn;

namespace signatures {
	const char* Uworld_Sig = "48 8B 05 ? ? ? ? 4D 8B C2"; //uworld

	const char* Gobject_Sig = "48 8B 05 ? ? ? ? 48 8B 0C C8 48 8B 04 D1";

	const char* Free_Sig = "48 85 C9 0F 84 ? ? ? ? 53 48 83 EC 20 48 89 7C 24 30 48 8B D9 48 8B 3D ? ? ? ? 48 85 FF 0F 84 ? ? ? ? 48 8B 07 4C 8B 40 30 48 8D 05 ? ? ? ? 4C 3B C0"; //Free

	const char* ProjectWorldToScreen_Sig = "E8 ? ? ? ? 41 88 07 48 83 C4 30"; //ProjectWorldToScreen

	const char* LineOfSightTo_Sig = "E8 ? ? ? ? 48 8B 0D ? ? ? ? 33 D2 40 8A F8"; //LineOfSight

	const char* GetNameByIndex_Sig = "48 89 5C 24 ? 48 89 74 24 ? 55 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 33 F6 48 8B F2 44 39 71 04 0F 85 ? ? ? ? 8B 19 0F B7 FB E8 ? ? ? ? 8B CB 48 8D 54 24"; //GetNameByIndex

	const char* BoneMatrix_Sig = "E8 ? ? ? ? 48 8B 47 30 F3 0F 10 45"; //BoneMatrix

	const char* Spread_Sig = "E8 ? ? ? ? 48 8D 4B 28 E8 ? ? ? ? 48 8B C8"; //Spread

	const char* SpreadCaller_sig = "0F 57 D2 48 8D 4C 24 ? 41 0F 28 CC E8 ? ? ? ? 48 8B 4D B0 0F 28 F0 48 85 C9"; //SpreadCaller

	const char* DiscordPresentScene_sig = "56 57 53 48 83 EC 30 44 89 C6"; //Discord PresentScene
}

namespace offsets {
	uintptr_t OwningGameInstance = 0x180;
	uintptr_t LocalPlayers = 0x38;
	uintptr_t PlayerController = 0x30;
	uintptr_t PlayerCameraManager = 0x2B8;
	uintptr_t AcknowledgedPawn = 0x2A0;

	uintptr_t Levels = 0x138;
	uintptr_t PersistentLevel = 0x30;
	uintptr_t AActors = 0x98;
	uintptr_t ActorCount = 0xA0;

	uintptr_t ComponentVelocity = 0x140;
	uintptr_t RootComponent = 0x130;
	uintptr_t FireStartLoc = 0x878;
	uintptr_t RelativeLocation = 0x11c;
	uintptr_t RelativeRotation = 0x128;
	uintptr_t CurrentWeapon = 0x600;
	uintptr_t PlayerState = 0x240;
	uintptr_t Mesh = 0x280;
	uintptr_t TeamIndex = 0xED0;


	//Exploits
	/*
	uintptr_t bDisableEquipAnimation = 0x2B3;
	uintptr_t bADSWhileNotOnGround = 0x3AB1;
	uintptr_t ReviveFromDBNOTime = 0x33B8;
	uintptr_t CustomTimeDilation = 0x98;
	uintptr_t LastFireTime = 0x9BC;
	uintptr_t LastFireTimeVerified = 0x9C0;
	*/

}
