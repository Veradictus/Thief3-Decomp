// Game/Unsorted_10C0B3D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B87900
{
public:
    bool FUN_10b87900();
};

class Class_10C0B6B0_Unknown0B0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual Class_10B87900* Virtual6();
};

struct Struct_10C0B6B0_Unknown0C0
{
    char Unknown00[0xB0];
    Class_10C0B6B0_Unknown0B0* Unknown0B0;
};

struct Struct_10C0B6B0
{
    char Unknown00[0xC0];
    Struct_10C0B6B0_Unknown0C0* Unknown0C0;
};

class Class_10E97C18
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
    virtual bool FUN_10c0b6b0(Struct_10C0B6B0* A);
};

// FUNCTION: 0x10C0B6B0 ?FUN_10c0b6b0@Class_10E97C18@@UAE_NPAUStruct_10C0B6B0@@@Z
bool Class_10E97C18::FUN_10c0b6b0(Struct_10C0B6B0* A)
{
    Struct_10C0B6B0_Unknown0C0* Owner = A->Unknown0C0;
    if (!Owner)
        return false;
    Class_10C0B6B0_Unknown0B0* Source = Owner->Unknown0B0;
    if (Source)
    {
        Class_10B87900* Target = Source->Virtual6();
        if (Target && Target->FUN_10b87900())
            return false;
    }
    return true;
}
