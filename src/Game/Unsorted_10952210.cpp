// Game/Unsorted_10952210.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

extern unsigned int DAT_10f3424c;

// FUNCTION: 0x10953A90 ?FUN_10953a90@@YAXHHH@Z
void FUN_10953a90(int Red, int Green, int Blue)
{
    DAT_10f3424c = (0xff << 24) | ((Red & 0xff) << 16) | ((Green & 0xff) << 8) | (Blue & 0xff);
}
