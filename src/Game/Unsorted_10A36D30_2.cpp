// Game/Unsorted_10A36D30_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class FVector
{
public:
    float X, Y, Z;
};

class Class_10D9FEE0
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
    virtual void Virtual8();
    virtual void Virtual9();
    virtual void Virtual10();
    virtual void Virtual11();
    virtual void Virtual12();
    virtual void Virtual13(int A);

    void FUN_10d9fee0(int A, int B);
    void FUN_10da0710(const FVector& A);
};

class Class_10A370C0
{
public:
    char Unknown00[0x44];
    FVector Unknown44;
    char Unknown50[0x60];
    Class_10D9FEE0* Unknown0B0;
};

// FUNCTION: 0x10A37030 ?FUN_10a37030@@YA_NPAVClass_10A370C0@@ABVFVector@@@Z
bool FUN_10a37030(Class_10A370C0* Obj, const FVector& A)
{
    Obj->Unknown44 = A;
    if (!Obj->Unknown0B0)
        return false;
    Obj->Unknown0B0->FUN_10d9fee0(1, 1);
    Obj->Unknown0B0->FUN_10da0710(A);
    return true;
}
