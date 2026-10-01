// Game/Unsorted_10B4E680.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7EA48
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual int FUN_10b4e680(int p1);
};

class Class_10E7EA90
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();
    virtual void Virtual3();
    virtual int Virtual4();
    virtual void Virtual5();
    virtual void Virtual6();
    virtual void Virtual7();
    virtual int FUN_10b4eb40(int p1);
};

class Object_10B3ADC0;

class Class_10AC92F0
{
public:
    void FUN_10ac92f0();
};

class Class_10F3A3D8
{
public:
    char Unknown00[0x13C];
    Class_10AC92F0* Unknown13C;
};

extern Class_10F3A3D8* DAT_10f3a3d8;

class Class_10B3ADC0
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void Virtual2();

    void FUN_10b3adc0(Object_10B3ADC0* A);
    void FUN_10b3ae90(Object_10B3ADC0* A);
};

class Class_10E7EAD8 : public Class_10B3ADC0
{
public:
    virtual void FUN_10b4ec00(Object_10B3ADC0* A);
};

// FUNCTION: 0x10B4E680 ?FUN_10b4e680@Class_10E7EA48@@UAEHH@Z
int Class_10E7EA48::FUN_10b4e680(int p1)
{
    if (p1 != 3)
        return Virtual4();
    return 0x14;
}

// FUNCTION: 0x10B4EB40 ?FUN_10b4eb40@Class_10E7EA90@@UAEHH@Z
int Class_10E7EA90::FUN_10b4eb40(int p1)
{
    switch (p1)
    {
    case 1:
        return 0x13;
    default:
        return Virtual4();
    }
}

// FUNCTION: 0x10B4EC00 ?FUN_10b4ec00@Class_10E7EAD8@@UAEXPAVObject_10B3ADC0@@@Z
void Class_10E7EAD8::FUN_10b4ec00(Object_10B3ADC0* A)
{
    FUN_10b3ae90(A);
    FUN_10b3adc0(A);
    DAT_10f3a3d8->Unknown13C->FUN_10ac92f0();
}
