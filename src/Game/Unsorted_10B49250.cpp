// Game/Unsorted_10B49250.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett
{
public:
    void FUN_10b21b90(int A);

    char Unknown00[0x450];
    unsigned bInBowDraw : 1;
    unsigned isCrouching : 1;
    unsigned CanDoItemSearch : 1;
    unsigned CanUseItems : 1;
    unsigned bUpdatePhysHeight : 1;
};

class Class_10B396A0
{
public:
    void FUN_10b396a0();
};

class Class_10AA82D0
{
public:
    virtual void Virtual0();

    int FUN_10aa82d0();
};

class Class_10B3ADC0 : public Class_10AA82D0
{
public:
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_10b3ae90(AGarrett* Garrett);
    void FUN_10b3b130(AGarrett* Garrett);
};

class Class_10E7E610 : public Class_10B3ADC0
{
public:
    virtual void FUN_10b49360(AGarrett* Garrett);
};

// FUNCTION: 0x10B49360 ?FUN_10b49360@Class_10E7E610@@UAEXPAVAGarrett@@@Z
void Class_10E7E610::FUN_10b49360(AGarrett* Garrett)
{
    FUN_10b3ae90(Garrett);
    FUN_10b3b130(Garrett);
    ((Class_10B396A0*)FUN_10aa82d0())->FUN_10b396a0();
    Garrett->bUpdatePhysHeight = 1;
    Garrett->FUN_10b21b90(0);
}
