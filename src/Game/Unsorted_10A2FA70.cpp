// Game/Unsorted_10A2FA70.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// Slot 0 of this vtable is the scalar deleting destructor at 0x10A15B00, which several
// vtables share; the accepted Class_10E662C0 (0x10A2F2C0) names it Virtual0.
class Class_10E662C0
{
public:
    virtual ~Class_10E662C0();
};

class Class_10E6B93C : public Class_10E662C0
{
public:
    virtual ~Class_10E6B93C();
    Class_10E6B93C(int Value) : Unknown04(Value) {}

    virtual Class_10E6B93C* FUN_10a2fa70();
    virtual int FUN_10a2f160(Class_10E6B93C* Other);

    int Unknown04;
};

// FUNCTION: 0x10A2FA70 ?FUN_10a2fa70@Class_10E6B93C@@UAEPAV1@XZ
Class_10E6B93C* Class_10E6B93C::FUN_10a2fa70()
{
    return new(0, 0, 0, 0, 0) Class_10E6B93C(Unknown04);
}
