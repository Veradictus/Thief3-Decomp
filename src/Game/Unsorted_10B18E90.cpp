// Game/Unsorted_10B18E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B19300
{
public:
    Class_10B19300();

    virtual ~Class_10B19300() {}

    char Unknown04[0x30];
};

// FUNCTION: 0x10B190E0 ?FUN_10b190e0@@YAPAVClass_10B19300@@XZ
Class_10B19300* FUN_10b190e0()
{
    static Class_10B19300 GSingleton;
    return &GSingleton;
}
