// Game/Unsorted_10BCBDF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AAF570_Field10
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
    virtual void Virtual29();
    virtual void Virtual30();
    virtual void Virtual31();
    virtual void Virtual32();
    virtual void Virtual33();
    virtual void Virtual34();
    virtual void Virtual35();
    virtual void Virtual36();
    virtual void Virtual37();
    virtual void Virtual38();
    virtual void Virtual39();
    virtual void Virtual40();
    virtual void Virtual41();
    virtual void Virtual42();
    virtual void Virtual43();
    virtual void Virtual44();
    virtual void Virtual45();
    virtual void Virtual46();
    virtual void Virtual47();
    virtual void Virtual48();
    virtual void Virtual49(int A);
};

class Class_10AAF570
{
public:
    int FUN_10aaf570();
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    int FUN_10bc4160();
};

class Class_10E92730 : public Class_10BC4160
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
    virtual void FUN_10bcbea0();
};

class Class_10BB7E30
{
public:
    void FUN_10bb7e30();
};

class Class_10E94578
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
    virtual void FUN_10bcac50(int A, int B, int C, int D, int E);

    void FUN_10bc5b50();
};

class Class_10E92230 : public Class_10E94578
{
public:
    virtual void FUN_10bcbdf0(int A, int B, int C, int D, int E);

    Class_10BB7E30* Unknown04;
};

// FUNCTION: 0x10BCBDF0 ?FUN_10bcbdf0@Class_10E92230@@UAEXHHHHH@Z
void Class_10E92230::FUN_10bcbdf0(int A, int B, int C, int D, int E)
{
    Unknown04->FUN_10bb7e30();
    Class_10E94578::FUN_10bcac50(A, B, C, D, E);
    FUN_10bc5b50();
}

// FUNCTION: 0x10BCBEA0 ?FUN_10bcbea0@Class_10E92730@@UAEXXZ
void Class_10E92730::FUN_10bcbea0()
{
    Class_10AAF570* Owner = (Class_10AAF570*)FUN_10bc4160();
    ((Class_10AAF570_Field10*)Owner->FUN_10aaf570())->Virtual49(0);
}
