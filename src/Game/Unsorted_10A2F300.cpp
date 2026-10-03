// Game/Unsorted_10A2F300.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

// Slot 0 of this vtable is the scalar deleting destructor at 0x10A15B00, which several
// vtables share; the accepted Class_10E662C0 (0x10A2F2C0) names it Virtual0.
class Class_10E662C0
{
public:
    Class_10E662C0(int Value) : Unknown04(Value) {}

    virtual void Virtual0();

    int Unknown04;
};

class Class_10E662D0 : public Class_10E662C0
{
public:
    Class_10E662D0() : Class_10E662C0(0), Unknown08(0) {}

    virtual Class_10E662D0* FUN_10a2f300();
    virtual int FUN_10a2ed70(Class_10E662D0* Other);

    int Unknown08;
};

// Slot 0 of this vtable is the scalar deleting destructor at 0x10A15B00, which several
// vtables share; the accepted Class_10E5D5E0 (0x10A2F1D0) owns its name.
class Class_10E5D5E0
{
public:
    Class_10E5D5E0() : Unknown04(0) {}

    virtual void Virtual0();

    int Unknown04;
};

class Class_10E662E0 : public Class_10E5D5E0
{
public:
    Class_10E662E0() : Unknown08(-1), Unknown0C(-1), Unknown10(0) {}

    virtual Class_10E662E0* FUN_10a2f360();

    int Unknown08;
    int Unknown0C;
    int Unknown10;
};

// FUNCTION: 0x10A2F300 ?FUN_10a2f300@Class_10E662D0@@UAEPAV1@XZ
Class_10E662D0* Class_10E662D0::FUN_10a2f300()
{
    Class_10E662D0* Copy = new(0, 0, 0, 0, 0) Class_10E662D0();
    Copy->Unknown04 = Unknown04;
    Copy->Unknown08 = Unknown08;
    return Copy;
}

// FUNCTION: 0x10A2F360 ?FUN_10a2f360@Class_10E662E0@@UAEPAV1@XZ
Class_10E662E0* Class_10E662E0::FUN_10a2f360()
{
    Class_10E662E0* Copy = new(0, 0, 0, 0, 0) Class_10E662E0();
    Copy->Unknown04 = Unknown04;
    Copy->Unknown08 = Unknown08;
    Copy->Unknown0C = Unknown0C;
    return Copy;
}
