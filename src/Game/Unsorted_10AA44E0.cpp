// Game/Unsorted_10AA44E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10AA44E0
{
public:
    Class_10AA44E0();
    ~Class_10AA44E0();
};

// FUNCTION: 0x10AA45F0 ?FUN_10aa45f0@@YAPAVClass_10AA44E0@@XZ
Class_10AA44E0* FUN_10aa45f0()
{
    static Class_10AA44E0 GSingleton;
    return &GSingleton;
}
