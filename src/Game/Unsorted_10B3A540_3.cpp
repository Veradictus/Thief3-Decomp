// Game/Unsorted_10B3A540_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10B3A460
{
};

class Class_10B3A520 : public Class_10B3A460
{
public:
    Class_10B3A520();
    ~Class_10B3A520();
};

// FUNCTION: 0x10B3ABF0 ?FUN_10b3abf0@@YAPAVClass_10B3A460@@XZ
Class_10B3A460* FUN_10b3abf0()
{
    static Class_10B3A520 GSingleton;
    return &GSingleton;
}
