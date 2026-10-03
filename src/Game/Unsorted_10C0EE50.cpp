// Game/Unsorted_10C0EE50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

int FUN_10af36e0(const char* A, const char* B);

extern char DAT_10f06248[8][0x28];

// FUNCTION: 0x10C0EE50 ?FUN_10c0ee50@@YAHPBD@Z
int FUN_10c0ee50(const char* Name)
{
    for (int i = 0; i < 8; i++)
    {
        if (!FUN_10af36e0(Name, DAT_10f06248[i]))
            return i;
    }
    return -1;
}
