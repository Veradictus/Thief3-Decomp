// Game/Unsorted_10A87F80_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern float DAT_10eafbdc;

class Class_10A88A50
{
public:
    int FUN_10a88a50(int Index);
    int FUN_10a88a90(int Index);

    char Unknown00[4];
    float Unknown04[255];
    float Unknown400[255];
};

// FUNCTION: 0x10A88A90 ?FUN_10a88a90@Class_10A88A50@@QAEHH@Z
int Class_10A88A50::FUN_10a88a90(int Index)
{
    if (Index < 0)
        Index = 0;
    else if (Index >= 254)
        Index = 254;
    if (Unknown400[Index] > DAT_10eafbdc)
        return 1;
    return 0;
}
