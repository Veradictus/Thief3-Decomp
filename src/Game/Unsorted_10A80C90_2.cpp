// Game/Unsorted_10A80C90_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E6C104
{
public:
    Class_10E6C104();

    virtual void Virtual0();

    char Unknown04[8];
};

struct Struct_10A81140
{
    Struct_10A81140() : Unknown00(0), Unknown04(0) {}

    int Unknown00;
    int Unknown04;
};

class Class_10E6C128 : public Class_10E6C104
{
public:
    Class_10E6C128();

    virtual void Virtual0();

    Struct_10A81140 Unknown0C;
    char Unknown14[4];
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
};

class Class_10E6C1F0 {
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
    virtual unsigned FUN_10a81fc0();
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
    virtual unsigned Virtual22();
};

// FUNCTION: 0x10A81140 ??0Class_10E6C128@@QAE@XZ
Class_10E6C128::Class_10E6C128() : Unknown18(0), Unknown1C(0), Unknown20(0), Unknown24(0)
{
}

// FUNCTION: 0x10A81FC0 ?FUN_10a81fc0@Class_10E6C1F0@@UAEIXZ
unsigned Class_10E6C1F0::FUN_10a81fc0()
{
    return (Virtual22() >> 10) & 1;
}
