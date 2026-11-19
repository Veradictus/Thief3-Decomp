// Game/GridCommandRemove.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Game/cString.h"
#include "Game/cIntArray.h"

struct Struct_10AA3520;

class Class_10AF3AA0;

extern Struct_10AA3520* DAT_10f35dec;

cString FUN_10af5210(const char* In);

int ParseCommand(const char** Stream, const char* Match);

void LogMessage(Class_10AF3AA0* Out, const char* Message);

struct CommandListView
{
    char Unknown00[0x1C];
    cIntArray Items;
};

struct CommandGlobalsView
{
    char Unknown00[0xA8];
    CommandListView* List;
};

// FUNCTION: 0x10C2A470 ?FUN_10c2a470@@YA_NPBDPAVClass_10AF3AA0@@HHH00@Z
bool FUN_10c2a470(const char* Stream, Class_10AF3AA0* Out, int Unused3,
    int Item, int Unused5, const char* Command, const char* Message)
{
    int Matched = ParseCommand(&Stream, *FUN_10af5210(Command));
    if (Matched)
    {
        cIntArray* List = &((CommandGlobalsView*)DAT_10f35dec)->List->Items;
        int Index = List->FindIndex(Item);
        if (Index != -1)
            List->RemoveAt(Index);
        LogMessage(Out, *FUN_10af5210(Message));
        return true;
    }
    return false;
}
