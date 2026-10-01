// Game/Unsorted_10A56AB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A626F0
{
public:
    void FUN_10a64d70();
    void FUN_10a56ab0(int p1);

    char Unknown00[0x17C];
    int Unknown17C;
};

// FUNCTION: 0x10A56AB0 ?FUN_10a56ab0@Class_10A626F0@@QAEXH@Z
void Class_10A626F0::FUN_10a56ab0(int p1)
{
    if (Unknown17C != p1)
    {
        Unknown17C = p1;
        FUN_10a64d70();
    }
}
