// Game/Unsorted_10BE1D90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C08E80
{
public:
    void FUN_10c08e80();
};

class Class_10FF667C
{
public:
    char Unknown00[0x24];
    Class_10C08E80* Unknown24;
};

extern Class_10FF667C* DAT_10ff667c;

class Class_10E95AC8
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
    virtual void FUN_10be1ef0();
};

class Class_10E95780
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
    virtual void FUN_10be2de0(unsigned char p1);

    void FUN_10be2a70();

    char Unknown04[0x45];
    unsigned char Unknown49;
};

extern void* DAT_10e95be8[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E95BE8 : public Class_10E90D70
{
public:
    Class_10E95BE8* FUN_10be2df0(int A, int B, int C);

    int Unknown40;
    int Unknown44;
};

// FUNCTION: 0x10BE1EF0 ?FUN_10be1ef0@Class_10E95AC8@@UAEXXZ
void Class_10E95AC8::FUN_10be1ef0()
{
    DAT_10ff667c->Unknown24->FUN_10c08e80();
}

// FUNCTION: 0x10BE2DE0 ?FUN_10be2de0@Class_10E95780@@UAEXE@Z
void Class_10E95780::FUN_10be2de0(unsigned char p1)
{
    Unknown49 = p1;
    FUN_10be2a70();
}

// FUNCTION: 0x10BE2DF0 ?FUN_10be2df0@Class_10E95BE8@@QAEPAV1@HHH@Z
Class_10E95BE8* Class_10E95BE8::FUN_10be2df0(int A, int B, int C)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown00 = DAT_10e95be8;
    Unknown40 = C;
    Unknown44 = 0;
    return this;
}
