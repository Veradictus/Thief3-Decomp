// Game/Unsorted_10B25240.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7AAAC
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10b26910(int p1);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

extern void* DAT_10e7aa60[];

class Class_10B255F0
{
public:
    Class_10B255F0()
    {
        Unknown00 = DAT_10e7aa60;
        Unknown04 = 0;
        Unknown2C = 0;
        Unknown14 = 1;
        Unknown10 = 1;
        Unknown38 = 1;
        Unknown18 = 1;
        Unknown1C = false;
        Unknown3C = false;
        Unknown20 = -1.0f;
        Unknown40 = -1.0f;
        Unknown24 = 0;
        Unknown44 = 0;
        Unknown34 = 0;
        Unknown0C = 0;
        Unknown4C = 0;
        Unknown50 = false;
        Unknown51 = false;
        Unknown52 = false;
    }

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    bool Unknown1C;
    float Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    int Unknown34;
    int Unknown38;
    bool Unknown3C;
    float Unknown40;
    int Unknown44;
    int Unknown48;
    int Unknown4C;
    bool Unknown50;
    bool Unknown51;
    bool Unknown52;
};

class Class_10B25D60
{
public:
    int FUN_10b253e0(int* A);
    int FUN_10b254f0(int* A);
    void FUN_10b25d60();

    char Unknown00[4];
    int Unknown04;
    char Unknown08[8];
    int Unknown10;
};

class Class_10B25D90
{
public:
    int FUN_10b25240(int* A);
    int FUN_10b25310(int* A);
    void FUN_10b25d90();

    char Unknown00[4];
    int Unknown04;
    char Unknown08[8];
    int Unknown10;
};

// FUNCTION: 0x10B25CD0 ?FUN_10b25cd0@@YAPAVClass_10B255F0@@XZ
Class_10B255F0* FUN_10b25cd0()
{
    static Class_10B255F0 Instance;
    return &Instance;
}

// FUNCTION: 0x10B25D60 ?FUN_10b25d60@Class_10B25D60@@QAEXXZ
void Class_10B25D60::FUN_10b25d60()
{
    if (Unknown10)
        Unknown04 = FUN_10b253e0(&Unknown10);
    else
        Unknown04 = FUN_10b254f0(&Unknown10);
}

// FUNCTION: 0x10B25D90 ?FUN_10b25d90@Class_10B25D90@@QAEXXZ
void Class_10B25D90::FUN_10b25d90()
{
    if (Unknown10)
        Unknown04 = FUN_10b25240(&Unknown10);
    else
        Unknown04 = FUN_10b25310(&Unknown10);
}

// FUNCTION: 0x10B26910 ?FUN_10b26910@Class_10E7AAAC@@UAEXH@Z
void Class_10E7AAAC::FUN_10b26910(int p1)
{
    Unknown10 = 0;
    Unknown0C = 0;
    Unknown08 = 0;
    Unknown04 = 0;
    Unknown20 = 0;
    Unknown1C = 0;
    Unknown18 = 0;
    Unknown14 = 0;
}
