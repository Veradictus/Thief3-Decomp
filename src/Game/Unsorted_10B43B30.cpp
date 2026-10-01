// Game/Unsorted_10B43B30.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e80c78[];

class Class_10B78780
{
public:
    void FUN_10b78780();

    void** Unknown00;
    char Unknown04[0x18C];
};

class Class_10B2A8A0
{
public:
    Class_10B2A8A0() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E80C78 : public Class_10B78780
{
public:
    Class_10E80C78* FUN_10b43cd0(int Value);

    int Unknown190;
    int Unknown194;
    Class_10B2A8A0 Unknown198;
    int Unknown1A4;
    int Unknown1A8;
    int Unknown1AC;
    int Unknown1B0;
    int Unknown1B4;
    int Unknown1B8;
    int Unknown1BC;
    int Unknown1C0;
};

// FUNCTION: 0x10B43CD0 ?FUN_10b43cd0@Class_10E80C78@@QAEPAV1@H@Z
Class_10E80C78* Class_10E80C78::FUN_10b43cd0(int Value)
{
    FUN_10b78780();
    Unknown00 = DAT_10e80c78;
    Unknown190 = 0;
    Unknown194 = Value;
    Unknown198.Class_10B2A8A0::Class_10B2A8A0();
    Unknown1A4 = 0;
    Unknown1A8 = 0;
    Unknown1AC = 0;
    Unknown1B0 = 0;
    Unknown1B4 = 0;
    Unknown1B8 = 0;
    Unknown1BC = 0;
    Unknown1C0 = 0;
    return this;
}
