// Game/Unsorted_109E3510.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E5B2AC;

class Class_10F46DA0
{
public:
    virtual void Virtual0();
    virtual void Virtual1(Class_10E5B2AC* A, int B, int C, int D);
};

extern Class_10F46DA0* DAT_10f46da0;

class Class_10E5B2AC
{
public:
    virtual void FUN_109e3510(int Msg, int A, int B, int C);

    void FUN_109e32b0();
    void FUN_109e3320(int A, int B, int C);
    void FUN_109e3420(int A, int B, int C);
};

extern void* DAT_10e5b2c0[];

extern void* DAT_10e5b2b8[];

class Class_10E67BD8
{
public:
    Class_10E67BD8();

    void* vtable;
};

class Class_10E5B2C0 : public Class_10E67BD8
{
public:
    char Unknown04[0x114];
    void** Unknown118;

    Class_10E5B2C0* FUN_109e3630();
};

// FUNCTION: 0x109E3510 ?FUN_109e3510@Class_10E5B2AC@@UAEXHHHH@Z
void Class_10E5B2AC::FUN_109e3510(int Msg, int A, int B, int C)
{
    switch (Msg)
    {
    case 5:
        FUN_109e3320(A, B, C);
        break;
    case 0x24:
    case 0x25:
        FUN_109e3420(A, B, C);
        break;
    }
}

// FUNCTION: 0x109E3630 ?FUN_109e3630@Class_10E5B2C0@@QAEPAV1@XZ
Class_10E5B2C0* Class_10E5B2C0::FUN_109e3630()
{
    this->Class_10E67BD8::Class_10E67BD8();
    vtable = DAT_10e5b2c0;
    Unknown118 = DAT_10e5b2b8;
    return this;
}
