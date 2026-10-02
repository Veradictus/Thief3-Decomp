// Game/Unsorted_10C0BDE0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C0BFC0
{
    char Unknown00[0x2C];
    int Unknown2C;
    int Unknown30;
};

class Class_10C0C090
{
public:
    Struct_10C0BFC0* FUN_10c0bfc0(int A, int B);

    char Unknown00[4];
    int Unknown04;
    char Unknown08[4];
    Struct_10C0BFC0** Unknown0C;
};

// FUNCTION: 0x10C0BFC0 ?FUN_10c0bfc0@Class_10C0C090@@QAEPAUStruct_10C0BFC0@@HH@Z
Struct_10C0BFC0* Class_10C0C090::FUN_10c0bfc0(int A, int B)
{
    for (int i = 0; i < Unknown04; i++)
    {
        if (Unknown0C[i] && Unknown0C[i]->Unknown30 == A && Unknown0C[i]->Unknown2C == B)
            return Unknown0C[i];
    }
    return 0;
}
