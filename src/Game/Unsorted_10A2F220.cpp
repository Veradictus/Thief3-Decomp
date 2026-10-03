// Game/Unsorted_10A2F220.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
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

class Class_10E6D208 : public Class_10E662C0
{
public:
    Class_10E6D208() : Unknown04(0) {}

    virtual Class_10E6D208* FUN_10a2f220();

    int Unknown04;
};

// FUNCTION: 0x10A2F220 ?FUN_10a2f220@Class_10E6D208@@UAEPAV1@XZ
Class_10E6D208* Class_10E6D208::FUN_10a2f220()
{
    Class_10E6D208* Copy = new(0, 0, 0, 0, 0) Class_10E6D208();
    Copy->Unknown04 = Unknown04;
    return Copy;
}
