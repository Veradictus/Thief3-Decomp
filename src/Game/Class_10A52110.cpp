// Game/Class_10A52110.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A52110
{
public:
    bool FUN_10a52110();

    char Unknown00[0x10C];
    void* Unknown10C;
    int Unknown110;
    int Unknown114;
};

// FUNCTION: 0x10A52110 ?FUN_10a52110@Class_10A52110@@QAE_NXZ
bool Class_10A52110::FUN_10a52110()
{
    bool HasData = Unknown10C != 0;
    if (HasData)
    {
        Unknown10C = 0;
        Unknown110 = 0;
        Unknown114 = 0;
    }
    return HasData;
}
