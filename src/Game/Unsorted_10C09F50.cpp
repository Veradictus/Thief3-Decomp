// Game/Unsorted_10C09F50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C0A6B0
{
    char Unknown00[8];
    int Unknown08;
    char Unknown0C[4];
    int* Unknown10;
};

class Class_10C0A6B0
{
public:
    void FUN_10c0a6b0(Struct_10C0A6B0* A, int Item);
    void FUN_10c0a0b0(Struct_10C0A6B0* A, int Index);
};

// FUNCTION: 0x10C0A6B0 ?FUN_10c0a6b0@Class_10C0A6B0@@QAEXPAUStruct_10C0A6B0@@H@Z
void Class_10C0A6B0::FUN_10c0a6b0(Struct_10C0A6B0* A, int Item)
{
    for (int i = A->Unknown08 - 1; i >= 0; i--)
    {
        if (A->Unknown10[i] == Item)
        {
            FUN_10c0a0b0(A, i);
            return;
        }
    }
}
