// Game/Unsorted_10A15820.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10A15800
{
public:
    virtual void Virtual0();
    virtual void Virtual1(int p1);
};

extern Class_10A15800* DAT_10f39878;

// FUNCTION: 0x10A15850 ?FUN_10a15850@@YAPAVClass_10A15800@@XZ
Class_10A15800* FUN_10a15850()
{
    if (!DAT_10f39878)
        DAT_10f39878 = new (0, 0, 0, 0, 0) Class_10A15800;
    return DAT_10f39878;
}
