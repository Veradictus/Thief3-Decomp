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

// FUNCTION: 0x10B4C060 ?FUN_10b4c060@Class_10E81548@@UAEXPAVAGarrett@@@Z
void Class_10E81548::FUN_10b4c060(AGarrett* Garrett)
{
    FUN_10b3ae90(Garrett);
    FUN_10b3b130(Garrett);
    Garrett->m_physicsObjectPadding->Virtual17();
    Garrett->bUpdatePhysHeight = 1;
}
