// Game/Unsorted_10947500.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// FUNCTION: 0x10947500 ?FUN_10947500@@YGPBDI@Z
const char* __stdcall FUN_10947500(unsigned int Type)
{
    const char* Names[2] = { "BSP Runtime", "BSP Mesh   " };
    if (Type < 2)
        return Names[Type];
    return "<undefined mem type>";
}
