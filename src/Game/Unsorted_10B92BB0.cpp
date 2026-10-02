// Game/Unsorted_10B92BB0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E89A7C
{
public:
    Class_10E89A7C(int Value) : Unknown04(Value) {}

    virtual void Virtual0();
    virtual Class_10E89A7C* FUN_10b92bb0();

    int Unknown04;
};

// FUNCTION: 0x10B92BB0 ?FUN_10b92bb0@Class_10E89A7C@@UAEPAV1@XZ
Class_10E89A7C* Class_10E89A7C::FUN_10b92bb0()
{
    return new(0, 0, 0, 0, 0) Class_10E89A7C(Unknown04);
}
