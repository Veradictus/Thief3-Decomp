// Game/Unsorted_10A2C530.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2(int A, int B, int C, int D, int E);
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* Block);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10A2C610
{
public:
    void FUN_10a2c3b0(int Count);
    void FUN_10a2c610();

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

struct Struct_10A2C580
{
    char Unknown00[8];
    void* Unknown08;
    char Unknown0C[0x71];
    char Unknown7D;
};

class Class_10A2C2F0
{
public:
    int FUN_10a2c2f0(void* A, void* B);
    bool FUN_10a2c580(void* A, void* B, void* C);
};

// FUNCTION: 0x10A2C580 ?FUN_10a2c580@Class_10A2C2F0@@QAE_NPAX00@Z
bool Class_10A2C2F0::FUN_10a2c580(void* A, void* B, void* C)
{
    Struct_10A2C580* Entry = (Struct_10A2C580*)FUN_10a2c2f0(A, C);
    if (Entry && !Entry->Unknown7D && Entry->Unknown08 == B)
        return true;
    return false;
}

// FUNCTION: 0x10A2C610 ?FUN_10a2c610@Class_10A2C610@@QAEXXZ
void Class_10A2C610::FUN_10a2c610()
{
    FUN_10a2c3b0(0);
    if (Unknown04)
    {
        FUN_10905aa0()->Virtual5(Unknown08);
        Unknown08 = 0;
        Unknown04 = 0;
    }
}
