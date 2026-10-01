// Game/Unsorted_10B8A850.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10CAFD00
{
public:
    void FUN_10cafd00(int A);
    void FUN_10cb1b90(int A);
};

class Class_10D9B090
{
public:
    char Unknown00[4];
    Class_10CAFD00* Unknown04;
};

Class_10D9B090* FUN_10d9dcb0();

class Class_10B8A850
{
public:
    void FUN_10b8a850();

    char Unknown00[0x10];
    int Unknown10;
    char Unknown14[0x3C];
    int Unknown50;
};

// FUNCTION: 0x10B8A850 ?FUN_10b8a850@Class_10B8A850@@QAEXXZ
void Class_10B8A850::FUN_10b8a850()
{
    Class_10D9B090* Mgr = FUN_10d9dcb0();
    Mgr->Unknown04->FUN_10cafd00(Unknown50);
    int Arg = Unknown10;
    Mgr = FUN_10d9dcb0();
    Mgr->Unknown04->FUN_10cb1b90(Arg);
}
