// Game/Unsorted_10C05A80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C05A80
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

float FUN_10c05a80(const Struct_10C05A80* A, const Struct_10C05A80* B);

// FUNCTION: 0x10C05A80 ?FUN_10c05a80@@YAMPBUStruct_10C05A80@@0@Z
float FUN_10c05a80(const Struct_10C05A80* A, const Struct_10C05A80* B)
{
    float X = B->Unknown00 - A->Unknown00;
    float Y = B->Unknown04 - A->Unknown04;
    float Z = B->Unknown08 - A->Unknown08;
    return X * X + Y * Y + Z * Z;
}
