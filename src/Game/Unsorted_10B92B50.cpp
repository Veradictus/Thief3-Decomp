// Game/Unsorted_10B92B50.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E89A6C
{
public:
    Class_10E89A6C(int Value) : Unknown04(Value) {}

    virtual void Virtual0();
    virtual Class_10E89A6C* FUN_10b92b50();

    int Unknown04;
};

// FUNCTION: 0x10B92B50 ?FUN_10b92b50@Class_10E89A6C@@UAEPAV1@XZ
Class_10E89A6C* Class_10E89A6C::FUN_10b92b50()
{
    return new(0, 0, 0, 0, 0) Class_10E89A6C(Unknown04);
}
