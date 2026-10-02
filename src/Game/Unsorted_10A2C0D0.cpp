// Game/Unsorted_10A2C0D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10A2C130
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10A2C130
{
public:
    Class_10A2C130* FUN_10a2c130(const Struct_10A2C130& A, const Struct_10A2C130& B, const Struct_10A2C130& C);

    Struct_10A2C130 Unknown00;
    Struct_10A2C130 Unknown0C;
    Struct_10A2C130 Unknown18;
};

// FUNCTION: 0x10A2C130 ?FUN_10a2c130@Class_10A2C130@@QAEPAV1@ABUStruct_10A2C130@@00@Z
Class_10A2C130* Class_10A2C130::FUN_10a2c130(const Struct_10A2C130& A, const Struct_10A2C130& B,
                                             const Struct_10A2C130& C)
{
    Unknown00 = A;
    Unknown0C = B;
    Unknown18 = C;
    return this;
}
