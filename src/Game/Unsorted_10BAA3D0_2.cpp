// Game/Unsorted_10BAA3D0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BAC050
{
public:
    int FUN_10baac90(int A);
    int FUN_10bac050(int A);
};

extern void* DAT_10e8d7b8[];

struct Struct_10BAD970
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10E8D7B8
{
public:
    Class_10E8D7B8* FUN_10bad970(Struct_10BAD970* A, int* B, int C);

    void** Unknown00;
    int Unknown04;
    Struct_10BAD970 Unknown08;
    int Unknown14;
    int Unknown18;
};

// FUNCTION: 0x10BAC050 ?FUN_10bac050@Class_10BAC050@@QAEHH@Z
int Class_10BAC050::FUN_10bac050(int A)
{
    int State = FUN_10baac90(A);
    if (State == 0 || State == 1)
        return 1;
    return 0;
}

// FUNCTION: 0x10BAD970 ?FUN_10bad970@Class_10E8D7B8@@QAEPAV1@PAUStruct_10BAD970@@PAHH@Z
Class_10E8D7B8* Class_10E8D7B8::FUN_10bad970(Struct_10BAD970* A, int* B, int C)
{
    Unknown04 = 0;
    Unknown00 = DAT_10e8d7b8;
    Unknown08 = *A;
    Unknown14 = *B;
    Unknown18 = C;
    return this;
}
