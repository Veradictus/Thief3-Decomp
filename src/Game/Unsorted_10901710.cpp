// Game/Unsorted_10901710.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern const char DAT_10e4761c[];

extern int DAT_10f3a39c;

int FUN_10ab5070(const char* Name);

void FUN_10ab47d0();

extern int DAT_10f3a3a8;

int FUN_10ab5210(const char* Name);

void FUN_10ab4b00();

// FUNCTION: 0x10901710 ?FUN_10901710@@YAHXZ
int FUN_10901710()
{
    if (DAT_10f3a39c == 0)
    {
        DAT_10f3a39c = FUN_10ab5070(DAT_10e4761c);
        FUN_10ab47d0();
    }
    return DAT_10f3a39c;
}

// FUNCTION: 0x10901740 ?FUN_10901740@@YAHXZ
int FUN_10901740()
{
    if (DAT_10f3a3a8 == 0)
    {
        DAT_10f3a3a8 = FUN_10ab5210(DAT_10e4761c);
        FUN_10ab4b00();
    }
    return DAT_10f3a3a8;
}
