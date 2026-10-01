// Game/Unsorted_10B491A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B19300_Param;

class Class_10B19300
{
public:
    void FUN_10b19300(Struct_10B19300_Param* A, float B);
};

Class_10B19300* FUN_10b190e0();

class Class_10E7E5C8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10b49220(Struct_10B19300_Param* A);
};

class Class_10E7E580
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual int FUN_10b491a0(int p1);
};

// FUNCTION: 0x10B491A0 ?FUN_10b491a0@Class_10E7E580@@UAEHH@Z
int Class_10E7E580::FUN_10b491a0(int p1)
{
    switch (p1)
    {
    case 1:
        return 0;
    default:
        return Virtual4();
    }
}

// FUNCTION: 0x10B49220 ?FUN_10b49220@Class_10E7E5C8@@UAEXPAUStruct_10B19300_Param@@@Z
void Class_10E7E5C8::FUN_10b49220(Struct_10B19300_Param* A)
{
    FUN_10b190e0()->FUN_10b19300(A, 1.0f);
    Virtual4();
}
