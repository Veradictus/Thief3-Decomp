// Game/Unsorted_109E1E80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern bool DAT_10f35b48;

void FUN_109dfe80();

void FUN_109e1e80(float A, bool B);

extern bool DAT_10f35b24;

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void* Virtual2(unsigned int A, int B, int C, int D, int E);
};

Class_10905A90_Member* FUN_10905aa0();

// FUNCTION: 0x109E1F90 ?FUN_109e1f90@@YAXM@Z
void FUN_109e1f90(float A)
{
    FUN_109dfe80();
    bool Flag = false;
    if (DAT_10f35b48)
    {
        Flag = true;
        DAT_10f35b48 = false;
    }
    FUN_109e1e80(A, Flag);
}

// FUNCTION: 0x109E2930 ?FUN_109e2930@@YAXXZ
void FUN_109e2930()
{
    FUN_109dfe80();
    bool Flag = false;
    if (DAT_10f35b48)
    {
        Flag = true;
        DAT_10f35b48 = false;
    }
    FUN_109e1e80(1.0f, Flag);
    DAT_10f35b24 = false;
}

// FUNCTION: 0x109E2970 ?FUN_109e2970@@YGPAXI@Z
void* __stdcall FUN_109e2970(unsigned int A)
{
    return FUN_10905aa0()->Virtual2(A, 0, 0, 0, 0);
}
