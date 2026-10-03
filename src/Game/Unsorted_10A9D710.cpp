// Game/Unsorted_10A9D710.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// A growable array of pointers: a count, the capacity in bytes and the items.
class Class_10BFBD70
{
public:
    ~Class_10BFBD70();

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10A7F5A0
{
public:
    Class_10BFBD70 FUN_10a7f5a0(int A, int B);
};

class Class_10A9DBE0_Param2
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual int Virtual8();
};

class Class_10A9DBE0_Param3
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual int Virtual3();
    virtual Class_10A7F5A0* Virtual4(int A);
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual float Virtual8(int A);
};

void* FUN_10a030c0();

int FUN_10977fa0(int A);

class Class_10E6D260
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual int FUN_10a9dbe0(int A, Class_10A9DBE0_Param2* B, Class_10A9DBE0_Param3* C);

    void FUN_10a9d5b0(int Id, float Value);
};

// FUNCTION: 0x10A9DBE0 ?FUN_10a9dbe0@Class_10E6D260@@UAEHHPAVClass_10A9DBE0_Param2@@PAVClass_10A9DBE0_Param3@@@Z
int Class_10E6D260::FUN_10a9dbe0(int A, Class_10A9DBE0_Param2* B, Class_10A9DBE0_Param3* C)
{
    if (B && B->Virtual8() && C && C->Virtual3() >= 2 && FUN_10a030c0())
    {
        Class_10BFBD70 Found = C->Virtual4(0)->FUN_10a7f5a0(B->Virtual8(), 0);
        float Value = C->Virtual8(1);
        for (int i = 0; i < Found.Unknown00; i++)
            FUN_10a9d5b0(FUN_10977fa0(Found.Unknown08[i]), Value);
        return 1;
    }
    return 0;
}
