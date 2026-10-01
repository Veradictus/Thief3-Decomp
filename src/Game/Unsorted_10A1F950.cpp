// Game/Unsorted_10A1F950.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <vector>

class Class_10A1F9C0
{
public:
    int FUN_10a1f9c0();

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

class Class_10A1F9D0
{
public:
    int FUN_10a1f8a0(int A);
    int FUN_10a1f9d0(int A);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

struct Struct_10A1FA70
{
    int Unknown00;
    int Unknown04;
};

class Class_10A1FA70
{
public:
    void FUN_10a1fa70(int Index, int* A, int* B);

    char Unknown00[0x70];
    std::vector<Struct_10A1FA70> Unknown70;
};

class Class_10A1FB50
{
public:
    int FUN_10a1fad0(int A);
    int FUN_10a1fb50(int A);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    int* Unknown0C;
};

extern void* DAT_10e6561c[];

class Class_10E6561C
{
public:
    Class_10E6561C* FUN_10a22e20();

    void** Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
    int Unknown24;
    int Unknown28;
    int Unknown2C;
    int Unknown30;
    int Unknown34;
    int Unknown38;
    int Unknown3C;
    int Unknown40;
    int Unknown44;
    int Unknown48;
    int Unknown4C;
    int Unknown50;
    int Unknown54;
    int Unknown58;
    int Unknown5C;
    int Unknown60;
    int Unknown64;
    int Unknown68;
    int Unknown6C;
    int Unknown70;
    int Unknown74;
    int Unknown78;
    int Unknown7C;
    int Unknown80;
};

// FUNCTION: 0x10A1F9C0 ?FUN_10a1f9c0@Class_10A1F9C0@@QAEHXZ
int Class_10A1F9C0::FUN_10a1f9c0()
{
    if (Unknown04 <= 0)
        return 0;
    return *Unknown0C;
}

// FUNCTION: 0x10A1F9D0 ?FUN_10a1f9d0@Class_10A1F9D0@@QAEHH@Z
int Class_10A1F9D0::FUN_10a1f9d0(int A)
{
    int Index = FUN_10a1f8a0(A);
    if (Index >= 0 && Index < Unknown04)
        return Unknown0C[Index];
    return 0;
}

// FUNCTION: 0x10A1FA70 ?FUN_10a1fa70@Class_10A1FA70@@QAEXHPAH0@Z
void Class_10A1FA70::FUN_10a1fa70(int Index, int* A, int* B)
{
    if (Index < Unknown70.size())
    {
        *A = Unknown70[Index].Unknown00;
        *B = Unknown70[Index].Unknown04;
    }
    else
    {
        *A = -1;
        *B = -1;
    }
}

// FUNCTION: 0x10A1FB50 ?FUN_10a1fb50@Class_10A1FB50@@QAEHH@Z
int Class_10A1FB50::FUN_10a1fb50(int A)
{
    int Index = FUN_10a1fad0(A);
    if (Index >= 0 && Index < Unknown04)
        return Unknown0C[Index];
    return 0;
}

// FUNCTION: 0x10A22E20 ?FUN_10a22e20@Class_10E6561C@@QAEPAV1@XZ
Class_10E6561C* Class_10E6561C::FUN_10a22e20()
{
    Unknown00 = DAT_10e6561c;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = 0;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown28 = 0;
    Unknown2C = 0;
    Unknown30 = 0;
    Unknown34 = 0;
    Unknown38 = 0;
    Unknown3C = 0;
    Unknown40 = 0;
    Unknown44 = 0;
    Unknown48 = 0;
    Unknown4C = 0;
    Unknown50 = 0;
    Unknown54 = 0;
    Unknown58 = 0;
    Unknown5C = 0;
    Unknown60 = 0;
    Unknown6C = 0;
    Unknown70 = 0;
    Unknown74 = 0;
    Unknown78 = 0;
    Unknown7C = 0;
    Unknown80 = 0;
    return this;
}
