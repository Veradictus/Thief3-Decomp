// Game/Unsorted_10B24D70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void* FUN_10b154c0();

class Class_10B16930
{
public:
    void FUN_10b16930();
    void FUN_10b16780();
};

class Class_10B25200
{
public:
    void FUN_10b25200();

    char Unknown00[0x28];
    int Unknown28;
    char Unknown2C[0x1C];
    int Unknown48;
    int Unknown4C;
};

struct Struct_10B25010
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B25010_Member
{
public:
    int Get(int Index) { return Unknown08[Index].Unknown04; }

    char Unknown00[8];
    Struct_10B25010* Unknown08;
};

class Class_10B1B8A0
{
public:
    char Unknown00[0x1C];
    Class_10B25010_Member Unknown1C;
};

Class_10B1B8A0* FUN_10b1b600();

class Class_10B255F0
{
public:
    int FUN_10b25010();

    char Unknown00[0x2C];
    int Unknown2C;
};

// FUNCTION: 0x10B25010 ?FUN_10b25010@Class_10B255F0@@QAEHXZ
int Class_10B255F0::FUN_10b25010()
{
    int Index = Unknown2C;
    if (Index == 0)
        return 0;
    return FUN_10b1b600()->Unknown1C.Get(Index);
}

// FUNCTION: 0x10B25200 ?FUN_10b25200@Class_10B25200@@QAEXXZ
void Class_10B25200::FUN_10b25200()
{
    Unknown4C = 0;
    ((Class_10B16930*)FUN_10b154c0())->FUN_10b16930();
    Unknown28 = 0;
    Unknown48 = 0;
    ((Class_10B16930*)FUN_10b154c0())->FUN_10b16780();
}
