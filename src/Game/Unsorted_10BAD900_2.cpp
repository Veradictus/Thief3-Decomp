// Game/Unsorted_10BAD900_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern void* DAT_10e8d7b0[];

struct Struct_10BAD900
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E8D7B0
{
public:
    Class_10E8D7B0* FUN_10bad900(Struct_10BAD900* A, Struct_10BAD900* B, int* C);

    void** Unknown00;
    int Unknown04;
    Struct_10BAD900 Unknown08;
    Struct_10BAD900 Unknown14;
    int Unknown20;
};

// FUNCTION: 0x10BAD900 ?FUN_10bad900@Class_10E8D7B0@@QAEPAV1@PAUStruct_10BAD900@@0PAH@Z
Class_10E8D7B0* Class_10E8D7B0::FUN_10bad900(Struct_10BAD900* A, Struct_10BAD900* B, int* C)
{
    Unknown04 = 0;
    Unknown00 = DAT_10e8d7b0;
    Unknown08 = *A;
    Unknown14 = *B;
    Unknown20 = *C;
    return this;
}
