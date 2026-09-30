// Game/Unsorted_10B9EEB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern __int64 DAT_10f05c70;

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int Count);
    int FUN_10b9fa20(int* Item);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

extern void* DAT_10e8c00c[];

class Class_10E8C00C
{
public:
    Class_10E8C00C* FUN_10ba01f0(int A);

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
};

void FUN_10ad1dc0(void* Memory);

class Class_10BA1660
{
public:
    void FUN_10ba15c0(int A);
    void FUN_10ba1660();

    int Unknown00;
    int Unknown04;
    char Unknown08[4];
    int Unknown0C;
    char Unknown10[4];
    void* Unknown14;
};

// FUNCTION: 0x10B9F250 ?FUN_10b9f250@@YAHH@Z
int FUN_10b9f250(int Bit)
{
    if ((DAT_10f05c70 & (1 << Bit)) == 0)
        return 1;
    return 0;
}

// FUNCTION: 0x10B9FA20 ?FUN_10b9fa20@Class_10BFBD70@@QAEHPAH@Z
int Class_10BFBD70::FUN_10b9fa20(int* Item)
{
    int Index = Unknown00;
    FUN_10bfbd70(Index + 1);
    Unknown08[Index] = *Item;
    return Index;
}

// FUNCTION: 0x10BA01F0 ?FUN_10ba01f0@Class_10E8C00C@@QAEPAV1@H@Z
Class_10E8C00C* Class_10E8C00C::FUN_10ba01f0(int A)
{
    Unknown00 = DAT_10e8c00c;
    Unknown04 = 0;
    Unknown08 = 0;
    Unknown0C = 0;
    Unknown10 = A;
    Unknown14 = 0;
    Unknown18 = 0;
    Unknown1C = 0;
    Unknown20 = 0;
    Unknown24 = 0;
    Unknown28 = 0;
    return this;
}

// FUNCTION: 0x10BA1660 ?FUN_10ba1660@Class_10BA1660@@QAEXXZ
void Class_10BA1660::FUN_10ba1660()
{
    FUN_10ba15c0(0x40);
    FUN_10ad1dc0(Unknown14);
    Unknown04 = 0;
    Unknown0C = 0;
    Unknown14 = 0;
    Unknown00 = 0;
}
