// Game/Unsorted_10A2F3E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// Slot 0 of this vtable is a scalar deleting destructor, like the other classes
// cloned in this range (0x10A2F1D0, 0x10A2F300).
class Class_10E5D5E0
{
public:
    Class_10E5D5E0() : Unknown04(0) {}

    virtual void Virtual0();

    int Unknown04;
};

class Class_10E6BB18 : public Class_10E5D5E0
{
public:
    Class_10E6BB18() : Unknown08(0) {}

    virtual Class_10E6BB18* FUN_10a2f3e0();

    int Unknown08;
};

// FUNCTION: 0x10A2F3E0 ?FUN_10a2f3e0@Class_10E6BB18@@UAEPAV1@XZ
Class_10E6BB18* Class_10E6BB18::FUN_10a2f3e0()
{
    Class_10E6BB18* Copy = new(0, 0, 0, 0, 0) Class_10E6BB18();
    Copy->Unknown08 = Unknown08;
    Copy->Unknown04 = Unknown04;
    return Copy;
}
