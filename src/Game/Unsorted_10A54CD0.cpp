// Game/Unsorted_10A54CD0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// Slot 0 of this vtable is the scalar deleting destructor at 0x10A15B00, which several
// vtables share; the accepted Class_10E662C0 (0x10A2F2C0) names it Virtual0.
class Class_10E662C0
{
public:
    virtual void Virtual0();
};

class Class_10E682E0 : public Class_10E662C0
{
public:
    Class_10E682E0(int Value) : Unknown04(Value) {}

    virtual Class_10E682E0* FUN_10a54ce0();

    int Unknown04;
};

// FUNCTION: 0x10A54CE0 ?FUN_10a54ce0@Class_10E682E0@@UAEPAV1@XZ
Class_10E682E0* Class_10E682E0::FUN_10a54ce0()
{
    return new(0, 0, 0, 0, 0) Class_10E682E0(Unknown04);
}
