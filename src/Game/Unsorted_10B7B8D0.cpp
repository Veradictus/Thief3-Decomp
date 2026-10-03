// Game/Unsorted_10B7B8D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3A460
{
public:
    Class_10B3A460* FUN_10b3a460(int Index);

    char Unknown00;
};

Class_10B3A460* FUN_10b3abf0();

class Class_10B7AD70
{
public:
    void FUN_10b7b8a0();
    bool FUN_10b7b8d0(int A);

    char Unknown00[8];
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    bool Unknown18;
};

// FUNCTION: 0x10B7B8D0 ?FUN_10b7b8d0@Class_10B7AD70@@QAE_NH@Z
bool Class_10B7AD70::FUN_10b7b8d0(int A)
{
    if (Unknown18)
    {
        Class_10B3A460* Entry = FUN_10b3abf0()->FUN_10b3a460(Unknown08);
        if (Unknown14 == A && !Entry->Unknown00)
        {
            FUN_10b7b8a0();
            return true;
        }
    }
    return false;
}
