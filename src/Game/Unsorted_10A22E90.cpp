// Game/Unsorted_10A22E90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E6561C
{
public:
    Class_10E6561C();

    void** Unknown00;
    char Unknown04[0x80];
};

extern Class_10E6561C* DAT_10f39f08;

// FUNCTION: 0x10A22E90 ?FUN_10a22e90@@YAPAVClass_10E6561C@@XZ
Class_10E6561C* FUN_10a22e90()
{
    if (!DAT_10f39f08)
        DAT_10f39f08 = new(0, 0, 0, 0, 0) Class_10E6561C;
    return DAT_10f39f08;
}
