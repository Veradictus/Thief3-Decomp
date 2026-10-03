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

struct Struct_10AB0400
{
    Struct_10AB0400* Unknown00;
    Struct_10AB0400* Unknown04;
};

class Class_10AB0400
{
public:
    void FUN_10a6e990();

    char Unknown00[4];
    Struct_10AB0400* Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A6E990 ?FUN_10a6e990@Class_10AB0400@@QAEXXZ
void Class_10AB0400::FUN_10a6e990()
{
    Struct_10AB0400* Node = Unknown04->Unknown00;
    Unknown04->Unknown00 = Unknown04;
    Unknown04->Unknown04 = Unknown04;
    Unknown08 = 0;
    while (Node != Unknown04)
    {
        Struct_10AB0400* Next = Node->Unknown00;
        delete Node;
        Node = Next;
    }
}

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
