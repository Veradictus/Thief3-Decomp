// Game/Unsorted_10BE8C30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAAB60
{
public:
    void FUN_10baab60();
};

struct Struct_10BE8F70_Unknown04
{
    char Unknown00[8];
    Class_10BAAB60* Unknown08;
};

class Class_10BE8F70
{
public:
    void FUN_10be8f70();
    void FUN_10be8ee0();

    char Unknown00[4];
    Struct_10BE8F70_Unknown04* Unknown04;
};

class Class_10bf7f90
{
public:
    void FUN_10bf7f90(int A, int B);
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    int FUN_10bc4160();
};

class Class_10E91CB8 : public Class_10BC4160
{
public:
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
    virtual void FUN_10be90c0(int A);
};

// FUNCTION: 0x10BE8F70 ?FUN_10be8f70@Class_10BE8F70@@QAEXXZ
void Class_10BE8F70::FUN_10be8f70()
{
    Unknown04->Unknown08->FUN_10baab60();
    FUN_10be8ee0();
}

// FUNCTION: 0x10BE90C0 ?FUN_10be90c0@Class_10E91CB8@@UAEXH@Z
void Class_10E91CB8::FUN_10be90c0(int A)
{
    ((Class_10bf7f90*)FUN_10bc4160())->FUN_10bf7f90(0, 1);
}
