// Game/Unsorted_10BA4B80_2.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10E8C86C
{
public:
    Class_10E8C86C* FUN_10ba4bc0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6D4
{
public:
    virtual Class_10E8C86C* FUN_10ba4b80();
};

// FUNCTION: 0x10BA4B80 ?FUN_10ba4b80@Class_10E8C6D4@@UAEPAVClass_10E8C86C@@XZ
Class_10E8C86C* Class_10E8C6D4::FUN_10ba4b80()
{
    Class_10E8C86C* Object = (Class_10E8C86C*)operator new(sizeof(Class_10E8C86C), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4bc0();
    return 0;
}
