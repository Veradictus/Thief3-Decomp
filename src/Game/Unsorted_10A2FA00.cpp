// Game/Unsorted_10A2FA00.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E66300
{
public:
    Class_10E66300(int A, int B) : Unknown04(A), Unknown08(B) {}

    virtual void Virtual0();
    virtual Class_10E66300* FUN_10a2fa00();

    int Unknown04;
    int Unknown08;
};

// FUNCTION: 0x10A2FA00 ?FUN_10a2fa00@Class_10E66300@@UAEPAV1@XZ
Class_10E66300* Class_10E66300::FUN_10a2fa00()
{
    return new(0, 0, 0, 0, 0) Class_10E66300(Unknown04, Unknown08);
}
