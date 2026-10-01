// Game/Unsorted_10B4DB70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10B4DB70
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
};

class Class_10B4DB70
{
public:
    Class_10B4DB70* FUN_10b4db70(const Struct_10B4DB70& A, const Struct_10B4DB70& B);

    Struct_10B4DB70 Unknown00;
    Struct_10B4DB70 Unknown0C;
};

// FUNCTION: 0x10B4DB70 ?FUN_10b4db70@Class_10B4DB70@@QAEPAV1@ABUStruct_10B4DB70@@0@Z
Class_10B4DB70* Class_10B4DB70::FUN_10b4db70(const Struct_10B4DB70& A, const Struct_10B4DB70& B)
{
    Unknown00 = A;
    Unknown0C = B;
    return this;
}
