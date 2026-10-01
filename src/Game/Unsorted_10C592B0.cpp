// Game/Unsorted_10C592B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C5A1C0
{
public:
    void FUN_10c592b0(int A);
    void FUN_10c5a1c0();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

class Class_10C591A0
{
public:
    bool FUN_10c591a0(int* A);
};

class Class_10E9C7DC
{
public:
    virtual void FUN_10c59ec0(int A);

    char Unknown04[0xD4];
    Class_10C591A0 Unknown0D8;
};

// FUNCTION: 0x10C59EC0 ?FUN_10c59ec0@Class_10E9C7DC@@UAEXH@Z
void Class_10E9C7DC::FUN_10c59ec0(int A)
{
    int Key = A;
    Unknown0D8.FUN_10c591a0(&Key);
}

// FUNCTION: 0x10C5A1C0 ?FUN_10c5a1c0@Class_10C5A1C0@@QAEXXZ
void Class_10C5A1C0::FUN_10c5a1c0()
{
    FUN_10c592b0(0x40);
    ::operator delete(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
