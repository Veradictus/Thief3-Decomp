// Game/Unsorted_10C09090.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_1090A780
{
public:
    Class_1090A780(const Class_1090A780& Other);
    ~Class_1090A780();

    char* Unknown00;
};

extern Class_1090A780 DAT_10ff7060;

class Class_10C12DA0
{
public:
    Class_1090A780 FUN_10c12da0();
};

extern Class_1090A780 DAT_10ff7064;

class Class_10C13100
{
public:
    Class_1090A780 FUN_10c13100();
};

class Class_10C13130
{
public:
    Class_1090A780 FUN_10c13130();

    char Unknown00[0xC];
    Class_1090A780 Unknown0C;
};

extern void* DAT_10e98c80[];

class Class_10C15BB0
{
public:
    void* Field00;
    void FUN_10c15bb0();
};

class Class_10C15D50
{
public:
    char Unknown00[0x401c];
    void* Field401c;
    void* FUN_10c15d50();
};

extern void* DAT_10e98c84[];

class Class_10C15DB0
{
public:
    void* Field00;
    void FUN_10c15db0();
};

class Class_10C160D0
{
public:
    bool FUN_10c160d0(int Id, int* Out);
};

class Class_10C16220
{
public:
    int FUN_10c16220(int Id);

    char Unknown00[4];
    Class_10C160D0 Unknown04;
};

double FUN_10c00480();

class Class_10C168F0
{
public:
    void FUN_10c168f0(int A, float B);

    char Unknown00[0xAC];
    int Unknown0AC;
    float Unknown0B0;
};

// FUNCTION: 0x10C12DA0 ?FUN_10c12da0@Class_10C12DA0@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10C12DA0::FUN_10c12da0()
{
    return Class_1090A780(DAT_10ff7060);
}

// FUNCTION: 0x10C13100 ?FUN_10c13100@Class_10C13100@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10C13100::FUN_10c13100()
{
    return Class_1090A780(DAT_10ff7064);
}

// FUNCTION: 0x10C13130 ?FUN_10c13130@Class_10C13130@@QAE?AVClass_1090A780@@XZ
Class_1090A780 Class_10C13130::FUN_10c13130()
{
    return Class_1090A780(Unknown0C);
}

// FUNCTION: 0x10C13CC0 ?FUN_10c13cc0@@YAHXZ
int FUN_10c13cc0()
{
    return 0x27;
}

// FUNCTION: 0x10C15BB0 ?FUN_10c15bb0@Class_10C15BB0@@QAEXXZ
void Class_10C15BB0::FUN_10c15bb0()
{
    Field00 = DAT_10e98c80;
}

// FUNCTION: 0x10C15D50 ?FUN_10c15d50@Class_10C15D50@@QAEPAXXZ
void* Class_10C15D50::FUN_10c15d50()
{
    return Field401c;
}

// FUNCTION: 0x10C15DB0 ?FUN_10c15db0@Class_10C15DB0@@QAEXXZ
void Class_10C15DB0::FUN_10c15db0()
{
    Field00 = (void*)DAT_10e98c84;
}

// FUNCTION: 0x10C16220 ?FUN_10c16220@Class_10C16220@@QAEHH@Z
int Class_10C16220::FUN_10c16220(int Id)
{
    int Value = 0;
    Unknown04.FUN_10c160d0(Id, &Value);
    return Value;
}

// FUNCTION: 0x10C168F0 ?FUN_10c168f0@Class_10C168F0@@QAEXHM@Z
void Class_10C168F0::FUN_10c168f0(int A, float B)
{
    Unknown0AC = A;
    Unknown0B0 = FUN_10c00480() + B;
}
