// Game/Unsorted_10933670.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10932ED0
{
    float Unknown00;
    float Unknown04;
    float Unknown08;
};

class Class_10E49EB8
{
public:
    virtual void Virtual0();
    virtual int FUN_10933910(int A, int B, Struct_10932ED0* C, int D);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    Struct_10932ED0 Unknown10;
    char Unknown1C[0x18];
    int Unknown34;
    float Unknown38;
};

// FUNCTION: 0x10933910 ?FUN_10933910@Class_10E49EB8@@UAEHHHPAUStruct_10932ED0@@H@Z
int Class_10E49EB8::FUN_10933910(int A, int B, Struct_10932ED0* C, int D)
{
    Unknown04 = A;
    Unknown08 = B;
    Unknown10 = *C;
    Unknown38 = Unknown10.Unknown00;
    Unknown0C = D;
    Unknown34 = 0;
    return 0;
}
