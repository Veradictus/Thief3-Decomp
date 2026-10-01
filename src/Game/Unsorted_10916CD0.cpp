// Game/Unsorted_10916CD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// FUNCTION: 0x109178D0 ?FUN_109178d0@@YAIII@Z
unsigned int FUN_109178d0(unsigned int Value, unsigned int Alignment)
{
    return (Value + Alignment - 1) / Alignment * Alignment - Value;
}
