// Game/Unsorted_10BA3C90.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

// Ion Storm's placement new and its delete (0x10905C10; the delete folded into ::operator delete).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

void operator delete(void* Ptr, const int& Tag, int A, int B, int C, int D);

extern void* DAT_10e8c3f0[];

class Class_10e984f4
{
public:
    Class_10e984f4* FUN_10c12a90();

    void* Unknown00;
    int Unknown04;
};

class Class_10E8C3F0 : public Class_10e984f4
{
public:
    Class_10E8C3F0()
    {
        FUN_10c12a90();
        Unknown00 = DAT_10e8c3f0;
    }
};

class Class_10E8C5DC
{
public:
    virtual Class_10E8C3F0* FUN_10ba3c90(int A, int B);
};

// FUNCTION: 0x10BA3C90 ?FUN_10ba3c90@Class_10E8C5DC@@UAEPAVClass_10E8C3F0@@HH@Z
Class_10E8C3F0* Class_10E8C5DC::FUN_10ba3c90(int A, int B)
{
    return new(0, 0, 0, 0, 0) Class_10E8C3F0;
}
