// Game/Unsorted_10CBCF70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10CBCFD0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
    float Unknown0C;
    float Unknown10;
};

void FUN_10cbcfd0(Struct_10CBCFD0* Params);

extern void* DAT_10ffab68[];

// FUNCTION: 0x10CBCF90 ?FUN_10cbcf90@@YAPAXXZ
void* FUN_10cbcf90()
{
    return (void*)DAT_10ffab68;
}

// FUNCTION: 0x10CBCFD0 ?FUN_10cbcfd0@@YAXPAUStruct_10CBCFD0@@@Z
void FUN_10cbcfd0(Struct_10CBCFD0* Params)
{
    if (Params)
    {
        Params->Unknown00 = -1.0f;
        Params->Unknown04 = 0.01f;
        Params->Unknown08 = 0.005f;
        Params->Unknown0C = 0.1f;
        Params->Unknown10 = 0.2f;
    }
}
