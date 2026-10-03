// Game/Unsorted_10C26030.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Struct_10C26030
{
    int Unknown00;
    int Unknown04;
    float* Unknown08;
};

class Class_10C064D0
{
public:
    int Unknown00;
    char Unknown04[0x18];
    Struct_10C26030 Unknown1C;
};

int FUN_10b0fdb0();

void FUN_10c25f40(Struct_10C26030* Array);

class Class_10C25EB0
{
public:
    void FUN_10c26030(float Value);

    Class_10C064D0* Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10C26030 ?FUN_10c26030@Class_10C25EB0@@QAEXM@Z
void Class_10C25EB0::FUN_10c26030(float Value)
{
    if (Unknown00)
    {
        int Y = Unknown08;
        int X = Unknown04;
        Struct_10C26030* Array = &Unknown00->Unknown1C;
        FUN_10c25f40(Array);
        int Index = FUN_10b0fdb0() * X + Y;
        Array->Unknown08[Index] = Value;
    }
}
