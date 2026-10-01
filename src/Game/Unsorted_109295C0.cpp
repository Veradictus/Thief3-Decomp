// Game/Unsorted_109295C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10905A90_Member
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5(void* A);
};

Class_10905A90_Member* FUN_10905aa0();

class Class_10929710
{
public:
    void FUN_10929710();

    char Unknown00[0xC];
    char* Unknown0C;
};

typedef unsigned short WORD;

typedef unsigned long DWORD;

struct Struct_10929D60
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49B48
{
public:
    virtual void Virtual0(int A, int B, int C, DWORD* Out);
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void FUN_10929d60(int A, int B, int C, Struct_10929D60* Out);
};

// FUNCTION: 0x10929710 ?FUN_10929710@Class_10929710@@QAEXXZ
void Class_10929710::FUN_10929710()
{
    if (Unknown0C)
    {
        char* Block = Unknown0C - 4;
        FUN_10905aa0()->Virtual5(Block);
        Unknown0C = 0;
    }
}

// FUNCTION: 0x10929D60 ?FUN_10929d60@Class_10E49B48@@UAEXHHHPAUStruct_10929D60@@@Z
void Class_10E49B48::FUN_10929d60(int A, int B, int C, Struct_10929D60* Out)
{
    DWORD Packed;
    Virtual0(A, B, C, &Packed);
    const float Scale = 1.0f / 32767.0f;
    Out->Unknown00 = (WORD)(Packed >> 16) * Scale;
    Out->Unknown04 = (WORD)Packed * Scale;
    Out->Unknown08 = Scale;
}
