// Game/Unsorted_10BB5690.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Item_10953AC0
{
    int Unknown00;
    int Unknown04;
    int Unknown08;
    int Unknown0C;
};

class Class_10953AC0
{
public:
    void FUN_10953ac0(int A);
    void FUN_10bb5810(const Class_10953AC0& Other);

    int Unknown00;
    int Unknown04;
    Item_10953AC0* Unknown08;
};

// FUNCTION: 0x10BB5810 ?FUN_10bb5810@Class_10953AC0@@QAEXABV1@@Z
void Class_10953AC0::FUN_10bb5810(const Class_10953AC0& Other)
{
    FUN_10953ac0(Other.Unknown00);
    for (int i = 0; i < Unknown00; i++)
        Unknown08[i] = Other.Unknown08[i];
}
