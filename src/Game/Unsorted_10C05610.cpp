// Game/Unsorted_10C05610.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include <math.h>

struct Struct_10C05A50
{
    float Unknown00;
    float Unknown04;
};

float FUN_10c05a20(const Struct_10C05A50* A, const Struct_10C05A50* B);

// FUNCTION: 0x10C05A20 ?FUN_10c05a20@@YAMPBUStruct_10C05A50@@0@Z
float FUN_10c05a20(const Struct_10C05A50* A, const Struct_10C05A50* B)
{
    float X = B->Unknown00 - A->Unknown00;
    float Y = B->Unknown04 - A->Unknown04;
    return sqrtf(X * X + Y * Y);
}
