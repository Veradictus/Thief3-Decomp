// Game/Unsorted_10B7AC90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109B5DB0
{
public:
    float FUN_109b5db0(int A, int B);
};

class Class_10B7AD20
{
public:
    float FUN_10b7ad20(int Index);

    int Unknown00;
    Class_109B5DB0* Unknown04;
    char Unknown08[0xC];
    int Unknown14;
    char Unknown18[0x10];
    int Unknown28;
};

extern float DAT_10eafbdc;

// FUNCTION: 0x10B7AD20 ?FUN_10b7ad20@Class_10B7AD20@@QAEMH@Z
float Class_10B7AD20::FUN_10b7ad20(int Index)
{
    if (Unknown28 > Index)
        return Unknown04->FUN_109b5db0(Unknown14, Index);
    return DAT_10eafbdc;
}
