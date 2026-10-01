// Game/Unsorted_10A589C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A58BE0_Member {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
};

class Class_10E69050 {
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10a58be0();

    char Unknown04[0x10];
    Class_10A58BE0_Member** Unknown14;
    int Unknown18;
};

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

class Class_10E68D80
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
    virtual void Virtual49();
    virtual void Virtual50();
    virtual Class_1090A780 FUN_10a59320(int Index);

    char Unknown04[0x1B8];
    Class_1090A780 Unknown1BC[15];
};

// FUNCTION: 0x10A58BE0 ?FUN_10a58be0@Class_10E69050@@UAEXXZ
void Class_10E69050::FUN_10a58be0()
{
    Unknown14[Unknown18]->Virtual2();
}

// FUNCTION: 0x10A59320 ?FUN_10a59320@Class_10E68D80@@UAE?AVClass_1090A780@@H@Z
Class_1090A780 Class_10E68D80::FUN_10a59320(int Index)
{
    return Unknown1BC[Index];
}
