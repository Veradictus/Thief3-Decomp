// Game/Unsorted_10B18B60.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

struct Static_10B18D00
{
    int Unknown00;
    Static_10B18D00() {}
};

// FUNCTION: 0x10B18D00 ?FUN_10b18d00@@YAPAUStatic_10B18D00@@XZ
Static_10B18D00* FUN_10b18d00()
{
    static Static_10B18D00 Instance;
    return &Instance;
}
