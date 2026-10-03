// Game/Unsorted_10BD0410.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10C1A690
{
public:
    void FUN_10c1a690();

    char Unknown00[0x10];
};

class Class_10BD0960
{
public:
    void FUN_10bd0960();

    int Unknown00;
    char Unknown04[4];
    Class_10C1A690* Unknown08;
};

// FUNCTION: 0x10BD0960 ?FUN_10bd0960@Class_10BD0960@@QAEXXZ
void Class_10BD0960::FUN_10bd0960()
{
    for (int i = 0; i < Unknown00; i++)
        Unknown08[i].FUN_10c1a690();
    Unknown00 = 0;
}
