// Game/Unsorted_10C12CC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

extern const char DAT_10e47660[];

class Class_10E8C4A4_Member
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
    virtual Class_109081E0 Virtual25();
};

class Class_1096C8D0;

class Class_10E8C4A4
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10c12cc0();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual Class_109081E0 FUN_10c131d0();
    virtual bool FUN_10c129b0();

    Class_1096C8D0* Unknown04;
    Class_10E8C4A4_Member* Unknown08;
};

// FUNCTION: 0x10C12CC0 ?FUN_10c12cc0@Class_10E8C4A4@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E8C4A4::FUN_10c12cc0()
{
    if (Unknown08)
        return Unknown08->Virtual25();
    return Class_109081E0(DAT_10e47660);
}
