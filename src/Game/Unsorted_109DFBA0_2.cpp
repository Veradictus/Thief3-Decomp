// Game/Unsorted_109DFBA0_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10f35b54;

extern bool DAT_10f35b1c;

extern int DAT_10effbf8;

extern bool DAT_10f35b24;

extern bool DAT_10f35b58;

void FUN_109dffa0();

void FUN_109e0090();

// FUNCTION: 0x109E0430 ?FUN_109e0430@@YAXXZ
void FUN_109e0430()
{
    if (DAT_10f35b54 == 0)
        FUN_109dffa0();
    if (!DAT_10f35b1c)
    {
        FUN_109e0090();
        return;
    }
    DAT_10effbf8++;
    DAT_10f35b24 = true;
    DAT_10f35b58 = false;
    if (DAT_10effbf8 >= DAT_10f35b54)
        DAT_10effbf8 = DAT_10f35b54 - 1;
}
