// Game/Unsorted_10C16910.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern int DAT_10ff708c;


// FUNCTION: 0x10C1A130 ?FUN_10c1a130@@YAXXZ
void FUN_10c1a130()
{
    --*(int*)DAT_10ff708c;
    if (*(int*)DAT_10ff708c == 0)
    {
        ::operator delete((void*)DAT_10ff708c);
        DAT_10ff708c = 0;
    }
}
