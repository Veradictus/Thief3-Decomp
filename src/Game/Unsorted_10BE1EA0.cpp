// Game/Unsorted_10BE1EA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10BC4C10;

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

class Class_10E8BE68
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
    virtual void FUN_10bc4c10(Struct_10BC4C10* A, int B);
};

class Class_10E95AC8 : public Class_10E8BE68
{
public:
    virtual void FUN_10be1ea0(Struct_10BC4C10* A, int B);
};

// FUNCTION: 0x10BE1EA0 ?FUN_10be1ea0@Class_10E95AC8@@UAEXPAUStruct_10BC4C10@@H@Z
void Class_10E95AC8::FUN_10be1ea0(Struct_10BC4C10* A, int B)
{
    Class_10E8BE68::FUN_10bc4c10(A, B);
    if (GetFlags() & 8)
        DAT_10ff667c->Unknown24->FUN_10c08e80();
}
