// Game/Unsorted_10A12F60_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A80E60
{
public:
    void FUN_10a80e60(int Param);
};

class Class_10E5D548
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
    virtual void Virtual18();
    virtual void Virtual19();
    virtual void Virtual20();
    virtual void Virtual21();
    virtual void Virtual22();
    virtual void Virtual23();
    virtual void Virtual24();
    virtual void Virtual25();
    virtual void Virtual26();
    virtual void Virtual27();
    virtual void Virtual28();
    virtual void FUN_10a13480(int Param);

    char Unknown04[4];
    int Unknown08;
    char Unknown0C[4];
    Class_10A80E60** Unknown10;
};

// FUNCTION: 0x10A13480 ?FUN_10a13480@Class_10E5D548@@UAEXH@Z
void Class_10E5D548::FUN_10a13480(int Param)
{
    for (int i = 0; i < Unknown08; i++)
        Unknown10[i]->FUN_10a80e60(Param);
}
