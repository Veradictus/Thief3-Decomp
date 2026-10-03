// Game/Unsorted_10C27100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e99314[];

class Class_10E93B5C
{
public:
    Class_10E93B5C(const Class_10E93B5C& Other);

    char Unknown00[0x34];
};

class Class_10E99314
{
public:
    Class_10E99314* FUN_10c27320(int A, const Class_10E93B5C& B, int C);

    void** Unknown00;
    int Unknown04;
    Class_10E93B5C Unknown08;
    int Unknown3C;
    int Unknown40;
    bool Unknown44;
    bool Unknown45;
    int Unknown48;
};

class Class_10C39220
{
public:
    virtual ~Class_10C39220();

    int FUN_10c3c2c0(int A);
};

class Class_10C27100
{
public:
    void FUN_10c27100();

    char Unknown00[0x44];
    bool Unknown44;
    bool Unknown45;
    char Unknown46[2];
    Class_10C39220* Unknown48;
};

// FUNCTION: 0x10C27100 ?FUN_10c27100@Class_10C27100@@QAEXXZ
void Class_10C27100::FUN_10c27100()
{
    if (Unknown48 && !Unknown48->FUN_10c3c2c0(0))
    {
        if (Unknown48)
        {
            delete Unknown48;
            Unknown48 = 0;
        }
        Unknown44 = false;
        Unknown45 = true;
    }
}

// FUNCTION: 0x10C27320 ?FUN_10c27320@Class_10E99314@@QAEPAV1@HABVClass_10E93B5C@@H@Z
Class_10E99314* Class_10E99314::FUN_10c27320(int A, const Class_10E93B5C& B, int C)
{
    Unknown00 = DAT_10e99314;
    Unknown04 = A;
    Unknown08.Class_10E93B5C::Class_10E93B5C(B);
    Unknown3C = 0;
    Unknown45 = false;
    Unknown48 = 0;
    Unknown40 = C;
    Unknown44 = true;
    return this;
}
