// Game/Unsorted_10BDAF60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFF240
{
public:
    void FUN_10bff240(unsigned char A);
};

class Class_10BFF460 : public Class_10BFF240
{
public:
    bool FUN_10bff460();
    bool FUN_10bff330();
};

class Class_10BBB410
{
public:
    Class_10BFF460* FUN_10bbb410();
};

class Class_10E94698
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
    virtual void FUN_10bdaf60();

    Class_10BBB410* Unknown04;
};

// FUNCTION: 0x10BDAF60 ?FUN_10bdaf60@Class_10E94698@@UAEXXZ
void Class_10E94698::FUN_10bdaf60()
{
    Class_10BFF460* Obj = Unknown04->FUN_10bbb410();
    if (Obj && Obj->FUN_10bff460() && !Obj->FUN_10bff330())
        Obj->FUN_10bff240(1);
}
