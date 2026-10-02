// Game/Unsorted_10B25DC0_3.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E7AAAC
{
public:
    Class_10E7AAAC();

    virtual void Virtual0();
    virtual void Virtual1();
    virtual void FUN_10b26910(int p1);

    int Unknown04;
    int Unknown08;
    int Unknown0C;
    int Unknown10;
    int Unknown14;
    int Unknown18;
    int Unknown1C;
    int Unknown20;
};

// FUNCTION: 0x10B266E0 ?FUN_10b266e0@@YAPAVClass_10E7AAAC@@XZ
Class_10E7AAAC* FUN_10b266e0()
{
    static Class_10E7AAAC GSingleton;
    return &GSingleton;
}
