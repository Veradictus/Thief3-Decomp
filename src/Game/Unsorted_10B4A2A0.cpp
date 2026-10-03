// Game/Unsorted_10B4A2A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10B1E010_Param;

FVector FUN_10b1e010(Struct_10B1E010_Param* A);

class Class_10B4A2A0
{
public:
    FVector FUN_10b4a2a0(Struct_10B1E010_Param* A);

    char Unknown00[0x10];
    int Unknown10;
};

class AGarrett
{
public:
    void FUN_10b21b90(int A);

    char Unknown00[0x450];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
    unsigned CanDoItemSearch : 1;
    unsigned CanUseItems : 1;
    unsigned bUpdatePhysHeight : 1;
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();
};

class Class_10B3AE70 : public Class_10AA82D0
{
public:
    virtual void Virtual1();

    void FUN_10b3ae70(AGarrett* Garrett);

    char Unknown04[0xC];
};

class Class_10E7E658 : public Class_10B3AE70
{
public:
    void FUN_10b3b030(AGarrett* Garrett);
};

class Class_10E7E6A0 : public Class_10E7E658
{
public:
    virtual void FUN_10b4a330(AGarrett* Garrett);

    void FUN_10b49f60();

    int Unknown10;
    char Unknown14[4];
    bool Unknown18;
    bool Unknown19;
    bool Unknown1A;
    bool Unknown1B;
    bool Unknown1C;
};

// FUNCTION: 0x10B4A2A0 ?FUN_10b4a2a0@Class_10B4A2A0@@QAE?AVFVector@@PAUStruct_10B1E010_Param@@@Z
FVector Class_10B4A2A0::FUN_10b4a2a0(Struct_10B1E010_Param* A)
{
    switch (Unknown10)
    {
    case 1:
    case 2:
        return FVector(0.0f, 0.0f, 32.0f);
    case 3:
    case 4:
        return FUN_10b1e010(A) * 17.6f;
    }
    return FVector(0.0f, 0.0f, 0.0f);
}

// FUNCTION: 0x10B4A330 ?FUN_10b4a330@Class_10E7E6A0@@UAEXPAVAGarrett@@@Z
void Class_10E7E6A0::FUN_10b4a330(AGarrett* Garrett)
{
    Unknown18 = true;
    Unknown19 = false;
    Unknown1B = false;
    Unknown1A = false;
    Unknown10 = 1;
    Unknown1C = false;
    FUN_10b49f60();
    FUN_10b3b030(Garrett);
    FUN_10b3ae70(Garrett);
    Garrett->bUpdatePhysHeight = 0;
    Garrett->FUN_10b21b90(1);
}
