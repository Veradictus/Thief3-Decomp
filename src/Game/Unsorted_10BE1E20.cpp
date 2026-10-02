// Game/Unsorted_10BE1E20.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10978090
{
public:
    int FUN_10978090();
};

class Class_10C08E80 : public Class_10978090
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

// The flags of the object Unknown24 refers to, 0 when it refers to none.
inline int GetFlags()
{
    if (!DAT_10ff667c->Unknown24->FUN_10978090())
        return 0;
    return ((Class_10978090*)DAT_10ff667c->Unknown24->FUN_10978090())->FUN_10978090();
}

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
    virtual void FUN_10be1e60(int A, int B, int C, int D, int E);
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
    virtual void FUN_10be1e20();
    virtual void Virtual39();
    virtual void Virtual40();
};

// FUNCTION: 0x10BE1E20 ?FUN_10be1e20@Class_10E95AC8@@UAEXXZ
void Class_10E95AC8::FUN_10be1e20()
{
    if (GetFlags() & 4)
        DAT_10ff667c->Unknown24->FUN_10c08e80();
}

// FUNCTION: 0x10BE1E60 ?FUN_10be1e60@Class_10E95AC8@@UAEXHHHHH@Z
void Class_10E95AC8::FUN_10be1e60(int A, int B, int C, int D, int E)
{
    if (GetFlags() & 4)
        DAT_10ff667c->Unknown24->FUN_10c08e80();
}
