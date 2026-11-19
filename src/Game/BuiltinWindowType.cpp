// Game/BuiltinWindowType.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

// FUNCTION: 0x109E3A10 ?ResolveBuiltinWindowType@@YGHPBVFString@@@Z
int __stdcall ResolveBuiltinWindowType(const FString* Name)
{
    if (appStricmp(**Name, "Window") == 0) return 0;
    if (appStricmp(**Name, "BorderedWindow") == 0) return 13;
    if (appStricmp(**Name, "TextWindow") == 0) return 1;
    if (appStricmp(**Name, "Menu") == 0) return 2;
    if (appStricmp(**Name, "ActorWindow") == 0) return 3;
    if (appStricmp(**Name, "LightWindow") == 0) return 4;
    if (appStricmp(**Name, "IconWindow") == 0) return 5;
    if (appStricmp(**Name, "SkeletalMeshWindow") == 0) return 14;
    if (appStricmp(**Name, "YesNoWindow") == 0) return 15;
    if (appStricmp(**Name, "ButtonActorWindow") == 0) return 6;
    if (appStricmp(**Name, "ScrollBarWindow") == 0) return 7;
    if (appStricmp(**Name, "ActorBillboardTextWindow") == 0) return 8;
    if (appStricmp(**Name, "RadioWindow") == 0) return 9;
    if (appStricmp(**Name, "CheckBoxWindow") == 0) return 10;
    if (appStricmp(**Name, "MetaReaderTextWindow") == 0) return 11;
    return appStricmp(**Name, "FMVWindow") == 0 ? 12 : -1;
}
