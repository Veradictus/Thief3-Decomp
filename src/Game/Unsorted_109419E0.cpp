// Game/Unsorted_109419E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_109415F0
{
public:
    void FUN_109415f0();

    char Unknown00[0x44];
};

class Class_1091CCB0
{
public:
    void FUN_1091c8d0(int A);

    int Unknown00;
    int Unknown04;
    void* Unknown08;
};

class Class_10941AC0
{
public:
    void FUN_10941ac0();

    bool Unknown00;
    Class_1091CCB0 Unknown04;
    char Unknown10[8];
    int Unknown18;
    int Unknown1C;
};

// FUNCTION: 0x10941AC0 ?FUN_10941ac0@Class_10941AC0@@QAEXXZ
void Class_10941AC0::FUN_10941ac0()
{
    for (int i = 0; i < Unknown04.Unknown00; i++)
        ((Class_109415F0*)Unknown04.Unknown08)[i].FUN_109415f0();
    Unknown04.FUN_1091c8d0(0);
    Unknown1C = 0;
    Unknown18 = -1;
    Unknown00 = false;
}
