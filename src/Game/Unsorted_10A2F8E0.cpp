// Game/Unsorted_10A2F8E0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E662F0
{
public:
    Class_10E662F0(int A, int B) : Unknown04(A), Unknown08(B) {}

    virtual ~Class_10E662F0();
    virtual Class_10E662F0* FUN_10a2f9b0();

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A2F9B0 ?FUN_10a2f9b0@Class_10E662F0@@UAEPAV1@XZ
Class_10E662F0* Class_10E662F0::FUN_10a2f9b0()
{
    return new(0, 0, 0, 0, 0) Class_10E662F0(Unknown04, Unknown08);
}
