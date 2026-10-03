// Game/Unsorted_10954000.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10955750
{
public:
    bool FUN_10955540(int I, int A);
    bool FUN_10955750(int A);

    char Unknown00[0x10];
    int Unknown10;
};

// FUNCTION: 0x10955750 ?FUN_10955750@Class_10955750@@QAE_NH@Z
bool Class_10955750::FUN_10955750(int A)
{
    for (int i = 0; i < Unknown10; i++)
    {
        if (!FUN_10955540(i, A))
            return false;
    }
    return true;
}
