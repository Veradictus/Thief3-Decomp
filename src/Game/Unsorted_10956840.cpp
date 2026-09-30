// Game/Unsorted_10956840.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

void FUN_1092bdb0(void* Memory);

class Class_10956F20
{
public:
    void FUN_10956f20(int Index);

    char Unknown00[0x29C];
    void* Unknown29C[1];
};

// FUNCTION: 0x10956F20 ?FUN_10956f20@Class_10956F20@@QAEXH@Z
void Class_10956F20::FUN_10956f20(int Index)
{
    if (Unknown29C[Index])
    {
        FUN_1092bdb0(Unknown29C[Index]);
        Unknown29C[Index] = 0;
    }
}
