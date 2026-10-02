// Game/Unsorted_10B4BCE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class AGarrett
{
public:
    char Unknown00[0x34C];
    int MtNextState;
    char Unknown350[0x100];
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

    void FUN_10b3ae90(AGarrett* Garrett);
    void FUN_10b3b130(AGarrett* Garrett);
};

class Class_10B3AE50 : public Class_10B3ADC0
{
public:
    void FUN_10b3ae50(AGarrett* Garrett);
};

class Class_10B3AE70 : public Class_10B3AE50
{
public:
    void FUN_10b3ae70(AGarrett* Garrett);
};

class Class_10E7E730 : public Class_10B3AE70
{
public:
    void FUN_10b3b0b0(AGarrett* Garrett);
};

class Class_10E7E808 : public Class_10E7E730
{
public:
    virtual void FUN_10b4bcb0(int A);
    virtual void FUN_10b4bce0(AGarrett* Garrett);
    virtual void FUN_10b4bd30(AGarrett* Garrett);
    virtual void Virtual4();

    char Unknown04[0xC];
    float Unknown10;
};

// FUNCTION: 0x10B4BCE0 ?FUN_10b4bce0@Class_10E7E808@@UAEXPAVAGarrett@@@Z
void Class_10E7E808::FUN_10b4bce0(AGarrett* Garrett)
{
    Unknown10 = 3.5f;
    switch (Garrett->MtNextState)
    {
    case 2:
        FUN_10b3ae50(Garrett);
        break;
    default:
        FUN_10b3ae70(Garrett);
        break;
    }
    FUN_10b3b0b0(Garrett);
    Garrett->bUpdatePhysHeight = 0;
}
