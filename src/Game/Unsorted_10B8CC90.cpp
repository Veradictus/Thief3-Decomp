// Game/Unsorted_10B8CC90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10D9E5E0_Param
{
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
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual void Virtual18(float A);
};

class Class_10D9B090
{
public:
    void FUN_10d9e490(Struct_10D9E5E0_Param* A);
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10B8C810
{
public:
    void FUN_10b8c810();
    void FUN_10b8cc90();

    char Unknown00[0x19];
    bool Unknown19;
    char Unknown1A[6];
    Struct_10D9E5E0_Param* Unknown20;
    bool Unknown24;
};

// FUNCTION: 0x10B8CC90 ?FUN_10b8cc90@Class_10B8C810@@QAEXXZ
void Class_10B8C810::FUN_10b8cc90()
{
    if (!Unknown24 && !Unknown19)
    {
        FUN_10b8c810();
        FUN_10d9dcb0()->FUN_10d9e490(Unknown20);
        Unknown24 = true;
        Unknown20->Virtual18(-1.0f);
    }
}
