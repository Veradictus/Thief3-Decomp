// Game/Unsorted_10BE1A70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BB8360
{
public:
    void FUN_10bb8360(int p1, float p2, int p3);
};

class Class_10E95898
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
    virtual void FUN_10be1c40(int p1);

    Class_10BB8360* Unknown04;
    char Unknown08[0x3C];
    int Unknown44;
};

class Object_10BE1AD0
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
    virtual bool Virtual9();
};

class Class_10BAA3A0
{
public:
    void* FUN_10baa3a0();
};

struct Struct_10BE1AD0
{
    char Unknown00[8];
    Class_10BAA3A0* Unknown08;
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
    virtual void FUN_10be1b00(int A, int B, int C, int D, int E);
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
    virtual void FUN_10be1ad0();

    void FUN_10be1a70();

    Struct_10BE1AD0* Unknown04;
};

// FUNCTION: 0x10BE1AD0 ?FUN_10be1ad0@Class_10E95780@@UAEXXZ
void Class_10E95780::FUN_10be1ad0()
{
    Object_10BE1AD0* Object = static_cast<Object_10BE1AD0*>(Unknown04->Unknown08->FUN_10baa3a0());
    if (Object && !Object->Virtual9())
        FUN_10be1a70();
}

// FUNCTION: 0x10BE1B00 ?FUN_10be1b00@Class_10E95780@@UAEXHHHHH@Z
void Class_10E95780::FUN_10be1b00(int A, int B, int C, int D, int E)
{
    Object_10BE1AD0* Object = static_cast<Object_10BE1AD0*>(Unknown04->Unknown08->FUN_10baa3a0());
    if (Object && !Object->Virtual9())
        FUN_10be1a70();
}

// FUNCTION: 0x10BE1C40 ?FUN_10be1c40@Class_10E95898@@UAEXH@Z
void Class_10E95898::FUN_10be1c40(int p1)
{
    int Value = Unknown44;
    if (Value)
        Unknown04->FUN_10bb8360(Value, 10.0f, 0);
}
