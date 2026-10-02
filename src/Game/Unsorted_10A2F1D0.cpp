// Game/Unsorted_10A2F1D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E5D5E0
{
public:
    Class_10E5D5E0() : Unknown04(0) {}

    virtual void Virtual0();
    virtual Class_10E5D5E0* FUN_10a2f1d0();

    int Unknown04;
};

class Class_10E662C0
{
public:
    Class_10E662C0(int Value) : Unknown04(Value) {}

    virtual void Virtual0();
    virtual Class_10E662C0* FUN_10a2f2c0();

    int Unknown04;
};

// FUNCTION: 0x10A2F1D0 ?FUN_10a2f1d0@Class_10E5D5E0@@UAEPAV1@XZ
Class_10E5D5E0* Class_10E5D5E0::FUN_10a2f1d0()
{
    Class_10E5D5E0* Copy = new(0, 0, 0, 0, 0) Class_10E5D5E0();
    Copy->Unknown04 = Unknown04;
    return Copy;
}

// FUNCTION: 0x10A2F2C0 ?FUN_10a2f2c0@Class_10E662C0@@UAEPAV1@XZ
Class_10E662C0* Class_10E662C0::FUN_10a2f2c0()
{
    return new(0, 0, 0, 0, 0) Class_10E662C0(Unknown04);
}
