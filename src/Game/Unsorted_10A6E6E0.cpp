// Game/Unsorted_10A6E6E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void* operator new(unsigned int);

struct Struct_10A6E9F0A
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10A6E9F0
{
    int Unknown00;
    int Unknown04;
    Struct_10A6E9F0A Unknown08;
};

// FUNCTION: 0x10A6E9F0 ?FUN_10a6e9f0@@YGPAUStruct_10A6E9F0@@HHPBUStruct_10A6E9F0A@@@Z
Struct_10A6E9F0* __stdcall FUN_10a6e9f0(int A, int B, const Struct_10A6E9F0A* C)
{
    Struct_10A6E9F0* Node = new Struct_10A6E9F0;
    if (Node)
    {
        Node->Unknown00 = A;
        Node->Unknown04 = B;
        Node->Unknown08 = *C;
    }
    return Node;
}
