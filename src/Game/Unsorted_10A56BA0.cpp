// Game/Unsorted_10A56BA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A626F0
{
public:
    void FUN_10a64d70();
    void FUN_10a56ba0(int p1);

    char Unknown00[0x154];
    int Unknown154;
};

// FUNCTION: 0x10A56BA0 ?FUN_10a56ba0@Class_10A626F0@@QAEXH@Z
void Class_10A626F0::FUN_10a56ba0(int p1)
{
    if (Unknown154 != p1)
    {
        Unknown154 = p1;
        FUN_10a64d70();
    }
}
