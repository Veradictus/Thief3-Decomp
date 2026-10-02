// Game/Unsorted_10A905B0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E6C9CC
{
public:
    Class_10E6C9CC(int Value) : Unknown04(Value) {}

    virtual void Virtual0();
    virtual Class_10E6C9CC* FUN_10a905b0();

    int Unknown04;
};

// FUNCTION: 0x10A905B0 ?FUN_10a905b0@Class_10E6C9CC@@UAEPAV1@XZ
Class_10E6C9CC* Class_10E6C9CC::FUN_10a905b0()
{
    return new(0, 0, 0, 0, 0) Class_10E6C9CC(Unknown04);
}
