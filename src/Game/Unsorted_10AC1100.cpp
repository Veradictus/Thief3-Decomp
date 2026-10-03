// Game/Unsorted_10AC1100.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10AC1100
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

struct Struct_10AC1100_Frame
{
    char Unknown00[8];
    Struct_10AC1100 Unknown08;
    Struct_10AC1100 Unknown14;
    Struct_10AC1100 Unknown20;
    char Unknown2C[0x10];
};

class Class_10AC1100
{
public:
    Class_10AC1100* FUN_10ac1100(const Struct_10AC1100& A, const Struct_10AC1100& B, const Struct_10AC1100& C);

    Struct_10AC1100_Frame Unknown00[4];
};

// FUNCTION: 0x10AC1100 ?FUN_10ac1100@Class_10AC1100@@QAEPAV1@ABUStruct_10AC1100@@00@Z
Class_10AC1100* Class_10AC1100::FUN_10ac1100(const Struct_10AC1100& A, const Struct_10AC1100& B,
                                             const Struct_10AC1100& C)
{
    Unknown00[0].Unknown08 = A;
    Unknown00[0].Unknown14 = B;
    Unknown00[0].Unknown20 = C;
    Unknown00[1] = Unknown00[0];
    Unknown00[2] = Unknown00[0];
    Unknown00[3] = Unknown00[0];
    return this;
}
