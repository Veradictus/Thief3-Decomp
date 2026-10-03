// Game/Unsorted_10A4D410.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A4DDA0 {
public:
    void FUN_10a4dda0();

    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);
};

class Class_10A4E2A0
{
public:
    void FUN_10a4e2a0(int A, Class_10BFBD70* B);
};

class Class_10A4EAE0
{
public:
    void FUN_10a4eae0(int A, Class_10BFBD70* B);

    char Unknown00[0x1C];
    Class_10A4E2A0 Unknown1C;
};

struct Struct_10A4DD60
{
    char Unknown00[0x328];
    int Unknown328[6];
};

class Class_10A4DD60
{
public:
    int FUN_10a4dd60(int Index);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10A4DD60** Unknown0C;
    char Unknown10[0x330];
    int Unknown340[6];
};

// FUNCTION: 0x10A4DD60 ?FUN_10a4dd60@Class_10A4DD60@@QAEHH@Z
int Class_10A4DD60::FUN_10a4dd60(int Index)
{
    for (int i = 0; i < Unknown04; i++)
    {
        int Value = Unknown0C[i]->Unknown328[Index];
        if (Value != 0x40)
            return Value;
    }
    return Unknown340[Index];
}

// FUNCTION: 0x10A4DDA0 ?FUN_10a4dda0@Class_10A4DDA0@@QAEXXZ
void Class_10A4DDA0::FUN_10a4dda0()
{
    Unknown00 = 0;
    Unknown04 = 0;
    Unknown08 = 0;
}

// FUNCTION: 0x10A4EAE0 ?FUN_10a4eae0@Class_10A4EAE0@@QAEXHPAVClass_10BFBD70@@@Z
void Class_10A4EAE0::FUN_10a4eae0(int A, Class_10BFBD70* B)
{
    B->FUN_10bfbd70(0);
    Unknown1C.FUN_10a4e2a0(A, B);
}
