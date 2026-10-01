// Game/Unsorted_10A11EC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B06220
{
public:
    int FUN_10b06220();
    void FUN_10ada010(int Id);
};

class Class_10E5D464
{
public:
    virtual void FUN_10a11ec0(int Type, int A, int B, int C);
    virtual void Virtual1(int A, int B, int C);
};

// FUNCTION: 0x10A11EC0 ?FUN_10a11ec0@Class_10E5D464@@UAEXHHHH@Z
void Class_10E5D464::FUN_10a11ec0(int Type, int A, int B, int C)
{
    if (Type > 0 && Type <= 2)
        Virtual1(A, B, C);
}

// FUNCTION: 0x10A11EF0 ?FUN_10a11ef0@@YGXPAVClass_10B06220@@@Z
void __stdcall FUN_10a11ef0(Class_10B06220* Obj)
{
    if (Obj->FUN_10b06220() == 0)
        Obj->FUN_10ada010(0x4002002b);
}
