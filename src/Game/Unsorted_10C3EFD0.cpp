// Game/Unsorted_10C3EFD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E9B5C0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void FUN_10c3f100(unsigned char param);
    char Unknown04[0x24];
    unsigned char Unknown28;
    unsigned char Unknown29;
};

class Class_10C3F110
{
public:
    char Unknown00[0x2C];
    int Unknown2C[1];

    int FUN_10c3f110(int p1);
};

// FUNCTION: 0x10C3F100 ?FUN_10c3f100@Class_10E9B5C0@@UAEXE@Z
void Class_10E9B5C0::FUN_10c3f100(unsigned char param)
{
    Unknown28 = param;
    Unknown29 = 1;
}

// FUNCTION: 0x10C3F110 ?FUN_10c3f110@Class_10C3F110@@QAEHH@Z
int Class_10C3F110::FUN_10c3f110(int p1)
{
    return Unknown2C[p1];
}
