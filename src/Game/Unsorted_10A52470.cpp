// Game/Unsorted_10A52470.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10A52EE0
{
public:
    int FUN_10a52ee0(int Index);

    char Unknown00[0xB8];
    int UnknownB8;
    char UnknownBC[4];
    int* UnknownC0;
};

// FUNCTION: 0x10A52EE0 ?FUN_10a52ee0@Class_10A52EE0@@QAEHH@Z
int Class_10A52EE0::FUN_10a52ee0(int Index)
{
    if (Index >= 0 && Index < UnknownB8)
        return UnknownC0[Index];
    return 0;
}
