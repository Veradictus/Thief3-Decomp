// Game/Unsorted_10C25EF0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B9FBE0
{
public:
    int Unknown00;
    int Unknown04;
    char* Unknown08;
};

class Class_10C064D0
{
public:
    int Unknown00;
    Class_10B9FBE0 Unknown04;
    Class_10B9FBE0 Unknown10;
};

int FUN_10b0fdb0();

void FUN_10c06790(Class_10B9FBE0* Array);

class Class_10C25EB0
{
public:
    char FUN_10c25fb0();

    Class_10C064D0* Unknown00;
    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10C25FB0 ?FUN_10c25fb0@Class_10C25EB0@@QAEDXZ
char Class_10C25EB0::FUN_10c25fb0()
{
    if (!Unknown00)
        return 0;
    int Y = Unknown08;
    int X = Unknown04;
    Class_10B9FBE0* Array = &Unknown00->Unknown04;
    FUN_10c06790(Array);
    int Index = FUN_10b0fdb0() * X + Y;
    return Array->Unknown08[Index];
}
