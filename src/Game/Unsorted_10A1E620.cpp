// Game/Unsorted_10A1E620.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

#include "Core/Core.h"

void FUN_10a1e620(void* Object);

void FUN_10a1eaa0(void* Object);

class Class_10A1ED10
{
public:
    char Unknown00[0x288];
    void* Unknown288;
};

class Class_10963CE0
{
public:
    void FUN_10963ce0(FRotator R);

    FLOAT M[4][4];
};

struct Struct_10A1E690
{
    FLOAT M[3][3];
};

// FUNCTION: 0x10A1E690 ?FUN_10a1e690@@YAXPAUStruct_10A1E690@@PBVFRotator@@@Z
void FUN_10a1e690(Struct_10A1E690* Out, const FRotator* R)
{
    Class_10963CE0 Matrix;
    Matrix.FUN_10963ce0(*R);
    Out->M[0][0] = Matrix.M[0][0];
    Out->M[0][1] = Matrix.M[0][1];
    Out->M[0][2] = Matrix.M[0][2];
    Out->M[1][0] = Matrix.M[1][0];
    Out->M[1][1] = Matrix.M[1][1];
    Out->M[1][2] = Matrix.M[1][2];
    Out->M[2][0] = Matrix.M[2][0];
    Out->M[2][1] = Matrix.M[2][1];
    Out->M[2][2] = Matrix.M[2][2];
}

// FUNCTION: 0x10A1ED10 ?FUN_10a1ed10@@YAXPAVClass_10A1ED10@@@Z
void FUN_10a1ed10(Class_10A1ED10* Owner)
{
    void* Object = Owner->Unknown288;
    if (Object)
    {
        FUN_10a1e620(Object);
        FUN_10a1eaa0(Object);
    }
}
