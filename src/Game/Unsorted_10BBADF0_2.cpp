// Game/Unsorted_10BBADF0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BFF460
{
public:
    bool FUN_10bff460();
};

class Class_10BBB410
{
public:
    Class_10BFF460* FUN_10bbb410();
    void FUN_10bbb330();

    char Unknown00[0x210];
    Class_10BFF460* Unknown210;
};

// FUNCTION: 0x10BBB410 ?FUN_10bbb410@Class_10BBB410@@QAEPAVClass_10BFF460@@XZ
Class_10BFF460* Class_10BBB410::FUN_10bbb410()
{
    if (Unknown210)
    {
        if (Unknown210->FUN_10bff460() != 1)
            FUN_10bbb330();
    }
    return Unknown210;
}
