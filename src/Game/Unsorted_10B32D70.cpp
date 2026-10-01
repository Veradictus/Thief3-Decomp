// Game/Unsorted_10B32D70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B33D70
{
public:
    void FUN_10b33d70();
    void FUN_10b332d0();
    void FUN_10b33000();

    char Unknown00[0x18C];
    int Unknown18C;
    int Unknown190;
};

extern void* DAT_10e7bf50[];

class Class_10E81130
{
public:
    Class_10E81130* FUN_10b46080();

    void** Unknown00;
    char Unknown04[0x160];
};

class Class_10BFBD70
{
public:
    Class_10BFBD70() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10B330D0
{
public:
    Class_10B330D0() : Unknown00(0), Unknown04(0), Unknown08(0) {}

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10E7BF50 : public Class_10E81130
{
public:
    Class_10E7BF50* FUN_10b33da0();

    int Unknown164;
    int Unknown168;
    int Unknown16C;
    Class_10BFBD70 Unknown170;
    float Unknown17C;
    int Unknown180;
    int Unknown184;
    int Unknown188;
    int Unknown18C;
    Class_10B330D0 Unknown190;
    int Unknown19C;
    int Unknown1A0;
    bool Unknown1A4;
};

// FUNCTION: 0x10B33D70 ?FUN_10b33d70@Class_10B33D70@@QAEXXZ
void Class_10B33D70::FUN_10b33d70()
{
    if (Unknown18C < Unknown190 - 1)
    {
        Unknown18C++;
        FUN_10b332d0();
        FUN_10b33000();
    }
}

// FUNCTION: 0x10B33DA0 ?FUN_10b33da0@Class_10E7BF50@@QAEPAV1@XZ
Class_10E7BF50* Class_10E7BF50::FUN_10b33da0()
{
    FUN_10b46080();
    Unknown00 = DAT_10e7bf50;
    Unknown164 = 0;
    Unknown168 = 0;
    Unknown16C = 0;
    Unknown170.Class_10BFBD70::Class_10BFBD70();
    Unknown17C = 0.65f;
    Unknown180 = 0;
    Unknown184 = 0;
    Unknown188 = 0;
    Unknown190.Class_10B330D0::Class_10B330D0();
    Unknown19C = 0;
    Unknown1A0 = 0;
    Unknown1A4 = false;
    return this;
}
