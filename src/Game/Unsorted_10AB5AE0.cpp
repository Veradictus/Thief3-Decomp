// Game/Unsorted_10AB5AE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_10dd3d40();

extern void* DAT_10e6f388[];

class Class_10ABA190
{
public:
    void* Field00;
    void FUN_10aba190();
};

extern void* DAT_10e6f47c[];

void FUN_10abb760();

class Class_10ABB8F0
{
public:
    void* Field00;
    void FUN_10abb8f0();
};

extern void* DAT_10e6f4b4[];

class Class_10ABB9D0
{
public:
    void* Field00;
    void FUN_10abb9d0();
};

extern void* DAT_10f3a3e4;

class Class_10AC1490
{
public:
    char Unknown00[1536];
    void* Unknown600;
    void* FUN_10ac1490();
};

class Class_10AC14F0
{
public:
    void FUN_10ac14f0(int A, int B, int C, bool D);

    char Unknown00[0x44];
    int Unknown44;
    char Unknown48[0x5BC];
    int Unknown604;
    int Unknown608;
    int Unknown60C;
    int Unknown610;
    bool Unknown614;
    bool Unknown615;
};

struct Struct_10AC1830
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10AC1830
{
public:
    Struct_10AC1830 FUN_10ac1830();

    char Unknown00[0xE0];
    Struct_10AC1830 UnknownE0;
};

class Class_10AC2600
{
public:
    char Unknown00[0x14];
    unsigned char Field14;
    unsigned char FUN_10ac2600();
};

class Class_10AC3BF0
{
public:
    char Unknown00[0x40];
    unsigned char Field40;
    unsigned char FUN_10ac3bf0();
};

void FUN_10ac2fb0();

class Object_10AB5B20
{
public:
    virtual void Virtual0();
    virtual void Virtual1();
};

class Class_10AB5B20
{
public:
    Class_10AB5B20(const Class_10AB5B20& Other)
    {
        Unknown00 = Other.Unknown00;
        if (Unknown00)
            Unknown00->Virtual1();
    }
    ~Class_10AB5B20();

    Class_10AB5B20 FUN_10ab5b20();

    Object_10AB5B20* Unknown00;
};

// FUNCTION: 0x10AB5B20 ?FUN_10ab5b20@Class_10AB5B20@@QAE?AV1@XZ
Class_10AB5B20 Class_10AB5B20::FUN_10ab5b20()
{
    return *this;
}

// FUNCTION: 0x10ABA160 ?FUN_10aba160@@YAXXZ
void FUN_10aba160()
{
    FUN_10dd3d40();
}

// FUNCTION: 0x10ABA190 ?FUN_10aba190@Class_10ABA190@@QAEXXZ
void Class_10ABA190::FUN_10aba190()
{
    Field00 = (void*)DAT_10e6f388;
}

// FUNCTION: 0x10ABB8F0 ?FUN_10abb8f0@Class_10ABB8F0@@QAEXXZ
void Class_10ABB8F0::FUN_10abb8f0()
{
    Field00 = (void*)DAT_10e6f47c;
    FUN_10abb760();
}

// FUNCTION: 0x10ABB9D0 ?FUN_10abb9d0@Class_10ABB9D0@@QAEXXZ
void Class_10ABB9D0::FUN_10abb9d0()
{
    Field00 = (void*)DAT_10e6f4b4;
    FUN_10abb760();
}

// FUNCTION: 0x10ABC120 ?FUN_10abc120@@YAPAXXZ
void* FUN_10abc120()
{
    return DAT_10f3a3e4;
}

// FUNCTION: 0x10ABC130 ?FUN_10abc130@@YAXPAX@Z
void FUN_10abc130(void* p)
{
    DAT_10f3a3e4 = p;
}

// FUNCTION: 0x10AC1490 ?FUN_10ac1490@Class_10AC1490@@QAEPAXXZ
void* Class_10AC1490::FUN_10ac1490()
{
    return Unknown600;
}

// FUNCTION: 0x10AC14F0 ?FUN_10ac14f0@Class_10AC14F0@@QAEXHHH_N@Z
void Class_10AC14F0::FUN_10ac14f0(int A, int B, int C, bool D)
{
    Unknown608 = A;
    Unknown60C = B;
    Unknown610 = C;
    Unknown614 = D;
    Unknown615 = true;
    Unknown604 = Unknown44;
}

// FUNCTION: 0x10AC1830 ?FUN_10ac1830@Class_10AC1830@@QAE?AUStruct_10AC1830@@XZ
Struct_10AC1830 Class_10AC1830::FUN_10ac1830()
{
    return UnknownE0;
}

// FUNCTION: 0x10AC2600 ?FUN_10ac2600@Class_10AC2600@@QAEEXZ
unsigned char Class_10AC2600::FUN_10ac2600()
{
    return Field14;
}

// FUNCTION: 0x10AC3BF0 ?FUN_10ac3bf0@Class_10AC3BF0@@QAEEXZ
unsigned char Class_10AC3BF0::FUN_10ac3bf0()
{
    return Field40;
}

// FUNCTION: 0x10AC44B0 ?FUN_10ac44b0@@YAXXZ
void FUN_10ac44b0()
{
    FUN_10ac2fb0();
}
