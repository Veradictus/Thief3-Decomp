// Game/Unsorted_10C3ED90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

FVector FUN_10c3ec80(int p1);

class Class_10E9B570
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual FVector FUN_10c3ed90();

    int Unknown04;
};

// FUNCTION: 0x10C3ED90 ?FUN_10c3ed90@Class_10E9B570@@UAE?AVFVector@@XZ
FVector Class_10E9B570::FUN_10c3ed90()
{
    return FUN_10c3ec80(Unknown04);
}
