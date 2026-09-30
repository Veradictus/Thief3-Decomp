// Game/Unsorted_10C3D570.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109BBBA0
{
public:
    void FUN_109bbba0(int A);
};

class Class_10E9B168
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
    virtual void FUN_10c3d570();

    char Unknown04[0x14];
    char Unknown18;
    char Unknown19[0x3B];
    int Unknown54;
    char Unknown58[0xC];
    Class_109BBBA0* Unknown64;
};

class Class_10E9B370
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
    virtual void FUN_10c3d5e0();

    char Unknown04[0x14];
    bool Unknown18;
    char Unknown19[0x27];
    int Unknown40;
    char Unknown44[0xC];
    Class_109BBBA0* Unknown50;
};

class Class_10E9B240
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
    virtual void FUN_10c3d890();

    char Unknown04[0x14];
    bool Unknown18;
    char Unknown19[0x47];
    int Unknown60;
    char Unknown64[0xC];
    Class_109BBBA0* Unknown70;
};

// FUNCTION: 0x10C3D570 ?FUN_10c3d570@Class_10E9B168@@UAEXXZ
void Class_10E9B168::FUN_10c3d570()
{
    if (Unknown54 >= 0)
    {
        Unknown64->FUN_109bbba0(Unknown54);
        Unknown54 = -1;
    }
    Unknown18 = 0;
}

// FUNCTION: 0x10C3D5E0 ?FUN_10c3d5e0@Class_10E9B370@@UAEXXZ
void Class_10E9B370::FUN_10c3d5e0()
{
    if (Unknown40 >= 0)
    {
        Unknown50->FUN_109bbba0(Unknown40);
        Unknown40 = -1;
    }
    Unknown18 = false;
}

// FUNCTION: 0x10C3D890 ?FUN_10c3d890@Class_10E9B240@@UAEXXZ
void Class_10E9B240::FUN_10c3d890()
{
    if (Unknown60 >= 0)
    {
        Unknown70->FUN_109bbba0(Unknown60);
        Unknown60 = -1;
    }
    Unknown18 = false;
}
