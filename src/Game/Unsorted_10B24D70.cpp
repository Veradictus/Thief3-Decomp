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

// FUNCTION: 0x10B25200 ?FUN_10b25200@Class_10B25200@@QAEXXZ
void Class_10B25200::FUN_10b25200()
{
    Unknown4C = 0;
    ((Class_10B16930*)FUN_10b154c0())->FUN_10b16930();
    Unknown28 = 0;
    Unknown48 = 0;
    ((Class_10B16930*)FUN_10b154c0())->FUN_10b16780();
}
