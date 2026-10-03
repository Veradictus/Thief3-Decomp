// Game/Class_Field04_9.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B26930
{
public:
    void FUN_10b26930(int A);
};

class Class_10B7AD70 : public Class_10B26930
{
public:
    void FUN_10b7b8a0();
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10B21560
{
public:
    unsigned char FUN_10b21560();
};

struct Struct_10AA3520
{
    char Unknown00[8];
    Class_10B21560* Unknown08;
};

extern Struct_10AA3520* DAT_10f35dec;

class Class_Field04
{
public:
    void FUN_10b47310(int A);
    void FUN_10b476d0();

    char Unknown00[8];
    Class_10B7AD70* Unknown08[2];
    int Unknown10;
    int Unknown14;
    float Unknown18;
    char Unknown1C[0x1C];
    int Unknown38;
    int Unknown3C;
    float Unknown40;
    int Unknown44;
    unsigned char Unknown48;
    char Unknown49[3];
    Class_10BFBD70 Unknown4C;
};

// FUNCTION: 0x10B47310 ?FUN_10b47310@Class_Field04@@QAEXH@Z
void Class_Field04::FUN_10b47310(int A)
{
    Unknown10 = A;
    for (int i = 0; i < 2; i++)
        Unknown08[i]->FUN_10b26930(A);
    Unknown48 = DAT_10f35dec->Unknown08->FUN_10b21560();
}

// FUNCTION: 0x10B476D0 ?FUN_10b476d0@Class_Field04@@QAEXXZ
void Class_Field04::FUN_10b476d0()
{
    Unknown4C.FUN_10bfbd70(0);
    for (int i = 0; i < 2; i++)
        Unknown08[i]->FUN_10b7b8a0();
    Unknown14 = 0x101;
    Unknown18 = -1.0f;
    Unknown38 = 0x101;
    Unknown3C = 0;
    Unknown44 = 0;
    Unknown40 = -1.0f;
}
