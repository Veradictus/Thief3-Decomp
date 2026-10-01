// Game/Unsorted_109514C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_1092bdb0(void* Memory);

class Class_109514C0
{
public:
    void FUN_109514c0();

    char Unknown00[0xC];
    void* Unknown0C[9];
};

// FUNCTION: 0x109514C0 ?FUN_109514c0@Class_109514C0@@QAEXXZ
void Class_109514C0::FUN_109514c0()
{
    for (int i = 0; i < 9; i++)
    {
        if (Unknown0C[i])
            FUN_1092bdb0(Unknown0C[i]);
        Unknown0C[i] = 0;
    }
}
