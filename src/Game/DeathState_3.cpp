// Game/DeathState_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.
#include "Core/Core.h"
#include "Game/Class_10E90D70.h"
#include "Game/DeathState.h"

struct Struct_10BCEAB0Triple
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10BCEAB0Part
{
    FLOAT Unknown00;
    FVector Unknown04;
    Struct_10BCEAB0Triple Unknown10;
    bool Unknown1C;
    bool Unknown1D;
    int Unknown20;
};

class Class_10BCEAB0_Unknown40
{
public:
    char Unknown00[0x1C];
    int Unknown1C;
};

void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// FUNCTION: 0x10BCEAB0 ??0DeathState@@QAE@HHHHPAX_N@Z
DeathState::DeathState(int A, int B, int C, int D, void* E, bool F)
    : Class_10E90D70(A, B)
{
    Struct_10BCEAB0Part* Source = (Struct_10BCEAB0Part*)E;
    Unknown40 = (Class_10BCEAB0_Unknown40*)D;
    Unknown48 = false;
    Unknown49 = F;
    Unknown4A = false;
    Unknown4B = false;
    Unknown4C = C;
    Unknown50 = 0;
    if (Source)
    {
        int Tag = 0;
        Unknown50 = new(Tag, 0, 0, 0, 0) Struct_10BCEAB0Part;
        Unknown50->Unknown00 = Source->Unknown00;
        Unknown50->Unknown04 = Source->Unknown04;
        Unknown50->Unknown10 = Source->Unknown10;
        Unknown50->Unknown1C = Source->Unknown1C;
        Unknown50->Unknown1D = Source->Unknown1D;
        Unknown50->Unknown20 = Source->Unknown20;
    }
    if (Unknown40 && (Unknown40->Unknown1C & 0x800000))
        Unknown40 = 0;
}
