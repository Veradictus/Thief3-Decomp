// Game/Unsorted_10924A00_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Entry_10925410
{
    char Unknown00[0xC];
    int Unknown0C;
    char Unknown10[0x34];
};

class Class_10925410
{
public:
    int FUN_10925410(int Index);

    char Unknown00[0xDC];
    int UnknownDC;
    char UnknownE0[4];
    Entry_10925410* UnknownE4;
};

struct Entry_10925440
{
    char Unknown00[0x34];
    int Unknown34;
    char Unknown38[0xC];
};

class Class_10925440
{
public:
    int FUN_10925440(int Index);

    char Unknown00[0xDC];
    int UnknownDC;
    char UnknownE0[4];
    Entry_10925440* UnknownE4;
};

struct Entry_10925470
{
    char Unknown00[0x34];
    int Unknown34;
    char Unknown38[0xC];
};

class Class_10925470
{
public:
    void FUN_10925470(int Index, int Value);

    char Unknown00[0xDC];
    int UnknownDC;
    char UnknownE0[4];
    Entry_10925470* UnknownE4;
};

struct Entry_109254A0
{
    char Unknown00[0x38];
    int Unknown38;
    char Unknown3C[8];
};

class Class_109254A0
{
public:
    void FUN_109254a0(int Index, int Value);

    char Unknown00[0xDC];
    int UnknownDC;
    char UnknownE0[4];
    Entry_109254A0* UnknownE4;
};

struct Entry_109254D0
{
    char Unknown00[0x3C];
    char Unknown3C;
    char Unknown3D[7];
};

class Class_109254D0
{
public:
    void FUN_109254d0(int Index, char Value);

    char Unknown00[0xDC];
    int Unknown0DC;
    int Unknown0E0;
    Entry_109254D0* Unknown0E4;
};

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

class Class_10925D50
{
public:
    void FUN_10925d50(int Value);

    char Unknown00[0x68];
    Class_10BFBD70 Unknown68;
};

// FUNCTION: 0x10925410 ?FUN_10925410@Class_10925410@@QAEHH@Z
int Class_10925410::FUN_10925410(int Index)
{
    if (Index >= 0 && Index < UnknownDC)
        return UnknownE4[Index].Unknown0C;
    return 0;
}

// FUNCTION: 0x10925440 ?FUN_10925440@Class_10925440@@QAEHH@Z
int Class_10925440::FUN_10925440(int Index)
{
    if (Index >= 0 && Index < UnknownDC)
        return UnknownE4[Index].Unknown34;
    return -1;
}

// FUNCTION: 0x10925470 ?FUN_10925470@Class_10925470@@QAEXHH@Z
void Class_10925470::FUN_10925470(int Index, int Value)
{
    if (Index >= 0 && Index < UnknownDC)
        UnknownE4[Index].Unknown34 = Value;
}

// FUNCTION: 0x109254A0 ?FUN_109254a0@Class_109254A0@@QAEXHH@Z
void Class_109254A0::FUN_109254a0(int Index, int Value)
{
    if (Index >= 0 && Index < UnknownDC)
        UnknownE4[Index].Unknown38 = Value;
}

// FUNCTION: 0x109254D0 ?FUN_109254d0@Class_109254D0@@QAEXHD@Z
void Class_109254D0::FUN_109254d0(int Index, char Value)
{
    if (Index >= 0 && Index < Unknown0DC)
        Unknown0E4[Index].Unknown3C = Value;
}

// FUNCTION: 0x10925D50 ?FUN_10925d50@Class_10925D50@@QAEXH@Z
void Class_10925D50::FUN_10925d50(int Value)
{
    Class_10BFBD70* Array = &Unknown68;
    int Index = Array->Unknown00;
    Array->FUN_10bfbd70(Index + 1);
    Array->Unknown08[Index] = Value;
}
