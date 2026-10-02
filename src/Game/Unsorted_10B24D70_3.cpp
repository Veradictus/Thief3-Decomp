// Game/Unsorted_10B24D70_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void* FUN_10b154c0();

class Class_10B16930
{
public:
    void FUN_10b16780();
};

class Class_10B25200
{
public:
    void FUN_10b24d90();

    char Unknown00[0x28];
    int Unknown28;
    char Unknown2C[0x1C];
    int Unknown48;
};

// FUNCTION: 0x10B24D90 ?FUN_10b24d90@Class_10B25200@@QAEXXZ
void Class_10B25200::FUN_10b24d90()
{
    Unknown28 = 0;
    Unknown48 = 0;
    static_cast<Class_10B16930*>(FUN_10b154c0())->FUN_10b16780();
}
