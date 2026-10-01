// Game/Unsorted_10C0BDE0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

struct Struct_10C0C8E0
{
    char Unknown00[0x2C];
    int Unknown2C;
    int Unknown30;
};

class Class_10C0C8E0
{
public:
    void FUN_10c0c8e0(const Struct_10C0C8E0* In);
    void FUN_10c0c200(int A, int B);
};

struct Struct_10C0BFC0
{
    char Unknown00[0x38];
    FVector Unknown38;
    char Unknown44[0x18];
    float Unknown5C;
};

double FUN_10c00480();

class Class_10C0C090
{
public:
    Struct_10C0BFC0* FUN_10c0bfc0(int A, int B);
    void FUN_10c0c090(int A, int B, FVector* Pos, int D);
};

void* operator new(unsigned int);

struct Struct_10C0C0D0A
{
    int Unknown00;
    int Unknown04;
};

struct Struct_10C0C0D0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    Struct_10C0C0D0A Unknown0C;
    bool Unknown14;
    bool Unknown15;
};

struct Item_10C0C150
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10C0C150
{
public:
    int FUN_10c0c150(const Item_10C0C150* Item);
    void FUN_10c0be50(int NewCount);

    int Unknown00;
    int Unknown04;
    Item_10C0C150* Unknown08;
};

// FUNCTION: 0x10C0C090 ?FUN_10c0c090@Class_10C0C090@@QAEXHHPAVFVector@@H@Z
void Class_10C0C090::FUN_10c0c090(int A, int B, FVector* Pos, int D)
{
    Struct_10C0BFC0* Obj = FUN_10c0bfc0(A, B);
    Obj->Unknown5C = FUN_10c00480();
    Obj->Unknown38 = *Pos;
}

// FUNCTION: 0x10C0C0D0 ?FUN_10c0c0d0@@YGPAUStruct_10C0C0D0@@HHHPBUStruct_10C0C0D0A@@_N@Z
Struct_10C0C0D0* __stdcall FUN_10c0c0d0(int A, int B, int C, const Struct_10C0C0D0A* D, bool E)
{
    Struct_10C0C0D0* Node = new Struct_10C0C0D0;
    if (Node)
    {
        Node->Unknown00 = A;
        Node->Unknown04 = B;
        Node->Unknown08 = C;
        Node->Unknown0C = *D;
        Node->Unknown14 = E;
        Node->Unknown15 = false;
    }
    return Node;
}

// FUNCTION: 0x10C0C150 ?FUN_10c0c150@Class_10C0C150@@QAEHPBUItem_10C0C150@@@Z
int Class_10C0C150::FUN_10c0c150(const Item_10C0C150* Item)
{
    int Index = Unknown00;
    FUN_10c0be50(Index + 1);
    Unknown08[Index] = *Item;
    return Index;
}

// FUNCTION: 0x10C0C8E0 ?FUN_10c0c8e0@Class_10C0C8E0@@QAEXPBUStruct_10C0C8E0@@@Z
void Class_10C0C8E0::FUN_10c0c8e0(const Struct_10C0C8E0* In)
{
    FUN_10c0c200(In->Unknown30, In->Unknown2C);
}
