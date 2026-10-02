// Game/Unsorted_10B4BEC0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Object_10B4C060
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
};

class AGarrett
{
public:
    char Unknown00[0xB0];
    Object_10B4C060* m_physicsObjectPadding;
    char Unknown0B4[0x39C];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
    unsigned CanDoItemSearch : 1;
    unsigned CanUseItems : 1;
    unsigned bUpdatePhysHeight : 1;
};

class Class_10B3ADC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_10b3ae90(AGarrett* Garrett);
    void FUN_10b3b130(AGarrett* Garrett);
};

class Class_10E81548 : public Class_10B3ADC0
{
public:
    virtual void FUN_10b4c060(AGarrett* Garrett);
};

struct Struct_10B4BEC0_Vec
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10B4BEC0
{
    char Unknown00[0x38];
    Struct_10B4BEC0_Vec Unknown38;
    char Unknown44[0x3BC];
    Struct_10B4BEC0_Vec Unknown400;
};

class Class_10B39700
{
public:
    void FUN_10b39700();
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10E7E778 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual void Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void FUN_10b4bec0(Struct_10B4BEC0* A);
};

// FUNCTION: 0x10B4BEC0 ?FUN_10b4bec0@Class_10E7E778@@UAEXPAUStruct_10B4BEC0@@@Z
void Class_10E7E778::FUN_10b4bec0(Struct_10B4BEC0* A)
{
    A->Unknown400 = A->Unknown38;
    ((Class_10B39700*)FUN_10aa82d0())->FUN_10b39700();
    Virtual4();
}

// FUNCTION: 0x10B4C060 ?FUN_10b4c060@Class_10E81548@@UAEXPAVAGarrett@@@Z
void Class_10E81548::FUN_10b4c060(AGarrett* Garrett)
{
    FUN_10b3ae90(Garrett);
    FUN_10b3b130(Garrett);
    Garrett->m_physicsObjectPadding->Virtual17();
    Garrett->bUpdatePhysHeight = 1;
}
