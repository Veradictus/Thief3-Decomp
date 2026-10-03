// Game/Unsorted_10B19820.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10B199A0
{
    FStringNoInit Unknown00;
    int Unknown0C;
};

class Class_10AF4BB0
{
public:
    void FUN_10af3bd0(int A, int B, int C);

    void* Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B199A0 : public Class_10AF4BB0
{
public:
    void FUN_10b199a0(int Index, int Count);
};

class Class_1098E330
{
public:
    int FUN_1098e330(int Id, int* Out);
};

struct Struct_10B198A0
{
    char Unknown00[0xE8];
    Class_1098E330* UnknownE8;
    int UnknownEC;
};

Struct_10B198A0* FUN_10b198a0(int A);

struct Item_10B19940
{
    FString Unknown00;
    int Unknown0C;
    int Unknown10;
    unsigned char Unknown14;
    unsigned int Unknown18 : 1;
};

class Class_10B19940
{
public:
    int FUN_10af4cc0(int A, int B);
    int FUN_10b19940(const Item_10B19940& Item);

    Item_10B19940* Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10B19940 ?FUN_10b19940@Class_10B19940@@QAEHABUItem_10B19940@@@Z
int Class_10B19940::FUN_10b19940(const Item_10B19940& Item)
{
    int Index = FUN_10af4cc0(sizeof(Item_10B19940), 1);
    Unknown00[Index] = Item;
    return Index;
}

// FUNCTION: 0x10B199A0 ?FUN_10b199a0@Class_10B199A0@@QAEXHH@Z
void Class_10B199A0::FUN_10b199a0(int Index, int Count)
{
    for (int i = Index; i < Index + Count; i++)
        ((Struct_10B199A0*)Unknown00)[i].Unknown00.~FStringNoInit();
    FUN_10af3bd0(Index, Count, 0x10);
}

// FUNCTION: 0x10B19BE0 ?FUN_10b19be0@@YGHH@Z
int __stdcall FUN_10b19be0(int A)
{
    if (A)
    {
        Struct_10B198A0* Owner = FUN_10b198a0(A);
        Class_1098E330* Props = !Owner->UnknownEC ? 0 : Owner->UnknownE8;
        int Value = 0;
        Props->FUN_1098e330(0x200062, &Value);
        if (Value)
            return Value;
    }
    return 1;
}
