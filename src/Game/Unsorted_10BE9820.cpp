// Game/Unsorted_10BE9820.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BC4240_Param;

class Object_10BE9860
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
    virtual void Virtual13();
    virtual void Virtual14();
    virtual void Virtual15();
    virtual void Virtual16();
    virtual void Virtual17();
    virtual Struct_10BC4240_Param* Virtual18(int A, int B);
};

class Class_10E975A0
{
public:
    virtual void Virtual0();

    void FUN_10bc4240(Struct_10BC4240_Param* A, bool B);
    void FUN_10be9860(int A);

    int Unknown04;
    Object_10BE9860* Unknown08;
    char Unknown0C[0x61];
    bool Unknown6D;
};

struct Struct_10BE9820
{
    char Unknown00[0x14];
    float Unknown14;
};

// FUNCTION: 0x10BE9820 ?FUN_10be9820@@YAHPAPAUStruct_10BE9820@@0@Z
int FUN_10be9820(Struct_10BE9820** A, Struct_10BE9820** B)
{
    if ((*A)->Unknown14 == (*B)->Unknown14)
        return 0;
    return (*A)->Unknown14 < (*B)->Unknown14 ? -1 : 1;
}

// FUNCTION: 0x10BE9860 ?FUN_10be9860@Class_10E975A0@@QAEXH@Z
void Class_10E975A0::FUN_10be9860(int A)
{
    int Id = Unknown04;
    Object_10BE9860* Obj = Unknown08;
    Unknown6D = true;
    Struct_10BC4240_Param* Param = Obj->Virtual18(Id, A);
    FUN_10bc4240(Param, false);
}
