// Game/Unsorted_10C3EAC0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

class Class_10C3EA90
{
public:
    ~Class_10C3EA90() { FUN_10c3ea90(); }
    void FUN_10c3ea90();

    char Unknown00[0x1C];
    int Unknown1C;
};

extern Class_10C3EA90* DAT_10ff70a4;

FVector FUN_10c3ebc0(int p1);

class Class_10E9B570
{
public:
    virtual void Virtual0();
    virtual FVector FUN_10c3ed70();

    int Unknown04;
};

// FUNCTION: 0x10C3EB80 ?FUN_10c3eb80@@YAXXZ
void FUN_10c3eb80()
{
    --DAT_10ff70a4->Unknown1C;
    if (DAT_10ff70a4->Unknown1C == 0)
    {
        delete DAT_10ff70a4;
        DAT_10ff70a4 = 0;
    }
}

// FUNCTION: 0x10C3ED70 ?FUN_10c3ed70@Class_10E9B570@@UAE?AVFVector@@XZ
FVector Class_10E9B570::FUN_10c3ed70()
{
    return FUN_10c3ebc0(Unknown04);
}
