// Game/Unsorted_10A89070_4.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109081E0
{
public:
    Class_109081E0(const char* In);
    ~Class_109081E0();

    char* Unknown00;
};

class Class_10A891F0_Member
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

class Class_10E6C4A8
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual Class_109081E0 FUN_10a891f0();

    Class_10A891F0_Member* Unknown04;
};

// FUNCTION: 0x10A891F0 ?FUN_10a891f0@Class_10E6C4A8@@UAE?AVClass_109081E0@@XZ
Class_109081E0 Class_10E6C4A8::FUN_10a891f0()
{
    Class_10A891F0_Member* Inner = Unknown04;
    if (Inner)
        return Inner->Virtual25();
    return Class_109081E0("Class");
}
