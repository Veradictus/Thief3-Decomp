// Game/Unsorted_10BECF00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BC4240_Param;

class Class_10E94578
{
public:
    virtual void Virtual0();

    void FUN_10bc5b50();
};

class Class_10E975A0 : public Class_10E94578
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
    virtual void FUN_10becfd0();

    void FUN_10bc4240(Struct_10BC4240_Param* A, bool B);
    void FUN_10bece10();

    char Unknown04[0x45];
    char Unknown49;
    char Unknown4A[2];
    Struct_10BC4240_Param* Unknown4C;
};

// FUNCTION: 0x10BECFD0 ?FUN_10becfd0@Class_10E975A0@@UAEXXZ
void Class_10E975A0::FUN_10becfd0()
{
    if (Unknown4C)
        FUN_10bc4240(Unknown4C, false);
    else if (Unknown49 == 1)
        FUN_10bc5b50();
    else
        FUN_10bece10();
}
