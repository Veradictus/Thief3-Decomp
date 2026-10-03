// Game/Unsorted_10B1ABD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B1B8A0
{
public:
    Class_10B1B8A0();
    ~Class_10B1B8A0();
};

// FUNCTION: 0x10B1B600 ?FUN_10b1b600@@YAPAVClass_10B1B8A0@@XZ
Class_10B1B8A0* FUN_10b1b600()
{
    static Class_10B1B8A0 GSingleton;
    return &GSingleton;
}
