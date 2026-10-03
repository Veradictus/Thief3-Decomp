// Game/Unsorted_10919B40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10919b40
{
    char Unknown00[8];
    float Unknown08;
};

// FUNCTION: 0x10919B40 ?FUN_10919b40@@YAHPAUStruct_10919b40@@0@Z
int FUN_10919b40(Struct_10919b40* A, Struct_10919b40* B)
{
    if (A->Unknown08 > B->Unknown08)
        return -1;
    if (A->Unknown08 < B->Unknown08)
        return 1;
    return 0;
}
