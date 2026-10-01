// Game/Unsorted_10A49020.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

int FUN_10a48b30(int A, int B);

void FUN_10a4a100(int A, int B, int C, int D);

struct Struct_10A4C4A0_Pair
{
    int Unknown00;
    int Unknown04;
};

struct Struct_10A4C4A0
{
    int Unknown00;
    int Unknown04;
    Struct_10A4C4A0_Pair Unknown08;
};

class Class_10A4C4A0
{
public:
    Struct_10A4C4A0* FUN_10a4c0d0(int A, int B);
    void FUN_10a4c4a0(int A, int B, Struct_10A4C4A0_Pair* C);
};

// FUNCTION: 0x10A4A160 ?FUN_10a4a160@@YAXHHHH@Z
void FUN_10a4a160(int A, int B, int C, int D)
{
    int Value = FUN_10a48b30(A, B);
    FUN_10a4a100(A, Value, C, D);
}

// FUNCTION: 0x10A4C4A0 ?FUN_10a4c4a0@Class_10A4C4A0@@QAEXHHPAUStruct_10A4C4A0_Pair@@@Z
void Class_10A4C4A0::FUN_10a4c4a0(int A, int B, Struct_10A4C4A0_Pair* C)
{
    Struct_10A4C4A0* Node = FUN_10a4c0d0(1, 0);
    if (Node)
    {
        Node->Unknown00 = A;
        Node->Unknown04 = B;
        Node->Unknown08 = *C;
    }
}
