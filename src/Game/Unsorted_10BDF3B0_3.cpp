// Game/Unsorted_10BDF3B0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10bf7f90
{
public:
    void FUN_10bf7f90(int A, int B);
};

class Class_10BC4160
{
public:
    virtual void Virtual0();

    int FUN_10bc4160();
};

double FUN_10c00480();

class Class_10E95170 : public Class_10BC4160
{
public:
    virtual void FUN_10bdf410();

    char Unknown04[0x3C];
    int Unknown40;
    float Unknown44;
};

// FUNCTION: 0x10BDF410 ?FUN_10bdf410@Class_10E95170@@UAEXXZ
void Class_10E95170::FUN_10bdf410()
{
    ((Class_10bf7f90*)FUN_10bc4160())->FUN_10bf7f90(0, 1);
    Unknown40 = 1;
    Unknown44 = (float)(FUN_10c00480() + 1.0);
}
