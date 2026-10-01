// Game/Unsorted_109421E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10942BB0
{
public:
    void FUN_10942bb0(int Flag, unsigned int Value);

    char Unknown00[0x158];
    unsigned int Unknown158Bits0To18 : 19;
    unsigned int Unknown158Bits19To31 : 13;
};

class Class_10942BF0
{
public:
    int FUN_10942bf0(int Flag);

    char Unknown00[0x158];
    int Unknown158;
};

class Class_109435A0
{
public:
    int FUN_109435a0(const short* Item);
    void FUN_10942c60(int NewCount);

    int Unknown00;
    int Unknown04;
    short* Unknown08;
};

extern "C" void* memcpy(void* Dest, const void* Src, unsigned Count);

// FUNCTION: 0x10942760 ?FUN_10942760@@YGXPAXHHPBDPAH@Z
void __stdcall FUN_10942760(void* Dest, int Size, int Count, const char* Source, int* Position)
{
    memcpy(Dest, Source + *Position, Size * Count);
    *Position += Size * Count;
}

// FUNCTION: 0x10942BB0 ?FUN_10942bb0@Class_10942BB0@@QAEXHI@Z
void Class_10942BB0::FUN_10942bb0(int Flag, unsigned int Value)
{
    if (Flag == 0)
        Unknown158Bits19To31 = Value;
    else
        Unknown158Bits0To18 = Value;
}

// FUNCTION: 0x10942BF0 ?FUN_10942bf0@Class_10942BF0@@QAEHH@Z
int Class_10942BF0::FUN_10942bf0(int Flag)
{
    if (Flag == 0)
        return (Unknown158 >> 0x13) & 0x1fff;
    return Unknown158 & 0x7ffff;
}

// FUNCTION: 0x109435A0 ?FUN_109435a0@Class_109435A0@@QAEHPBF@Z
int Class_109435A0::FUN_109435a0(const short* Item)
{
    int Index = Unknown00;
    FUN_10942c60(Index + 1);
    Unknown08[Index] = *Item;
    return Index;
}
