// Game/Unsorted_10A7DE40.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E6BF5C
{
public:
    Class_10E6BF5C() : Unknown04(false), Unknown08(0) {}

    virtual void Virtual0();

    bool Unknown04;
    int Unknown08;
};

extern Class_10E6BF5C* DAT_10f3a17c;

// FUNCTION: 0x10A7EA80 ?FUN_10a7ea80@@YAPAVClass_10E6BF5C@@XZ
Class_10E6BF5C* FUN_10a7ea80()
{
    if (DAT_10f3a17c == 0)
        DAT_10f3a17c = new(0, 0, 0, 0, 0) Class_10E6BF5C;
    return DAT_10f3a17c;
}
