// Game/Unsorted_10BDBA70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e94100[];

class Class_10E90D70
{
public:
    Class_10E90D70(int A, int B);

    void** Unknown00;
    int Unknown04[15];
};

class Class_10E94100 : public Class_10E90D70
{
public:
    Class_10E94100* FUN_10bdbd10(int A, int B);

    int Unknown40;
    int Unknown44;
    int Unknown48[3];
};

extern void* DAT_10e94a00[];

class Class_10E94A00 : public Class_10E90D70
{
public:
    Class_10E94A00* FUN_10bdbb80(int A, int B, int C, int D);

    int Unknown40;
    int Unknown44[3];
    float Unknown50;
    int Unknown54;
};

extern void* DAT_10e94b20[];

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}

    void* Data;
    int ArrayNum;
    int ArrayMax;
};

class FVector
{
public:
    float X, Y, Z;
};

class Class_10E94B20 : public Class_10E90D70
{
public:
    Class_10E94B20* FUN_10bdbbc0(int A, int B, int C, const FVector& D, int E, bool F);

    int Unknown40;
    FArray Unknown44;
    float Unknown50;
    bool Unknown54;
    bool Unknown55;
    FVector Unknown58;
    int Unknown64;
};

extern void* DAT_10e94c58[];

class Class_10E94C58 : public Class_10E90D70
{
public:
    Class_10E94C58* FUN_10bdbc70(int A, int B, int C, int D);

    int Unknown40;
    int Unknown44[3];
    float Unknown50;
    int Unknown54;
    bool Unknown58;
};

// FUNCTION: 0x10BDBB80 ?FUN_10bdbb80@Class_10E94A00@@QAEPAV1@HHHH@Z
Class_10E94A00* Class_10E94A00::FUN_10bdbb80(int A, int B, int C, int D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = C;
    for (int i = 0; i < 3; i++)
        Unknown44[i] = 0;
    Unknown54 = D;
    Unknown50 = -1.0f;
    Unknown00 = DAT_10e94a00;
    return this;
}

// FUNCTION: 0x10BDBBC0 ?FUN_10bdbbc0@Class_10E94B20@@QAEPAV1@HHHABVFVector@@H_N@Z
Class_10E94B20* Class_10E94B20::FUN_10bdbbc0(int A, int B, int C, const FVector& D, int E, bool F)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = C;
    Unknown44.FArray::FArray();
    Unknown54 = false;
    Unknown55 = F;
    Unknown50 = -1.0f;
    Unknown00 = DAT_10e94b20;
    Unknown58 = D;
    Unknown64 = E;
    return this;
}

// FUNCTION: 0x10BDBC70 ?FUN_10bdbc70@Class_10E94C58@@QAEPAV1@HHHH@Z
Class_10E94C58* Class_10E94C58::FUN_10bdbc70(int A, int B, int C, int D)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = C;
    for (int i = 0; i < 3; i++)
        Unknown44[i] = 0;
    Unknown50 = -1.0f;
    Unknown00 = DAT_10e94c58;
    Unknown54 = D;
    Unknown58 = false;
    return this;
}

// FUNCTION: 0x10BDBD10 ?FUN_10bdbd10@Class_10E94100@@QAEPAV1@HH@Z
Class_10E94100* Class_10E94100::FUN_10bdbd10(int A, int B)
{
    this->Class_10E90D70::Class_10E90D70(A, B);
    Unknown40 = 0;
    Unknown44 = 0;
    Unknown00 = DAT_10e94100;
    for (int i = 0; i < 3; i++)
        Unknown48[i] = 0;
    return this;
}
