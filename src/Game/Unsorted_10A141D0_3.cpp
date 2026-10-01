// Game/Unsorted_10A141D0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A15800
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int p1);
};

extern Class_10A15800* DAT_10f39878;

class Class_10A15C30
{
public:
    bool FUN_10a15c30(int* A);
};

class Class_10E5D688
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual bool FUN_10a16640(int A);

    char Unknown04[0x30];
    Class_10A15C30 Unknown34;
};

// FUNCTION: 0x10A15800 ?FUN_10a15800@@YAXXZ
void FUN_10a15800()
{
    if (DAT_10f39878)
    {
        DAT_10f39878->Virtual1(1);
        DAT_10f39878 = 0;
    }
}

// FUNCTION: 0x10A16640 ?FUN_10a16640@Class_10E5D688@@UAE_NH@Z
bool Class_10E5D688::FUN_10a16640(int A)
{
    int Key = A;
    return Unknown34.FUN_10a15c30(&Key) == 1;
}
