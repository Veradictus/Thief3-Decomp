// Game/Unsorted_1094EAF0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E4AB88_UnknownFC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6(int Param);
};

struct Struct_10E4AB88_UnknownFC
{
    Class_10E4AB88_UnknownFC* Unknown00;
};

class Class_10E4AB88
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
    virtual void FUN_1094eea0(int Param);

    char Unknown04[0xF0];
    int UnknownF4;
    char UnknownF8[4];
    Struct_10E4AB88_UnknownFC** UnknownFC;
};

// FUNCTION: 0x1094EEA0 ?FUN_1094eea0@Class_10E4AB88@@UAEXH@Z
void Class_10E4AB88::FUN_1094eea0(int Param)
{
    for (int i = 0; i < UnknownF4; i++)
    {
        Class_10E4AB88_UnknownFC* Member = UnknownFC[i]->Unknown00;
        if (Member)
            Member->Virtual6(Param);
    }
}
