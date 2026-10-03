// Game/Unsorted_10BA90A0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <math.h>

extern "C" void* memmove(void* Dest, const void* Src, unsigned Count);

class Class_10BFBD70
{
public:
    void FUN_10bfbd70(int NewCount);
    void FUN_10ba91a0(const int* Item);

    int Unknown00;
    int Unknown04;
    int* Unknown08;
};

struct Struct_10BA91E0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

float FUN_10ba91e0(const Struct_10BA91E0* A, const Struct_10BA91E0* B);

// FUNCTION: 0x10BA91A0 ?FUN_10ba91a0@Class_10BFBD70@@QAEXPBH@Z
void Class_10BFBD70::FUN_10ba91a0(const int* Item)
{
    FUN_10bfbd70(Unknown00 + 1);
    int Count = Unknown00 - 1;
    if (Count)
        memmove(Unknown08 + 1, Unknown08, Count * sizeof(int));
    Unknown08[0] = *Item;
}

// FUNCTION: 0x10BA91E0 ?FUN_10ba91e0@@YAMPBUStruct_10BA91E0@@0@Z
float FUN_10ba91e0(const Struct_10BA91E0* A, const Struct_10BA91E0* B)
{
    float X = B->Unknown00 - A->Unknown00;
    float Y = B->Unknown04 - A->Unknown04;
    float Z = B->Unknown08 - A->Unknown08;
    return sqrtf(X * X + Y * Y + Z * Z);
}
