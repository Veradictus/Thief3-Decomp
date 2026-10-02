// Game/Unsorted_10BA4E80.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4EC0
{
public:
    Class_10BA4EC0* FUN_10ba4ec0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6F4
{
public:
    virtual Class_10BA4EC0* FUN_10ba4e80();
};

// FUNCTION: 0x10BA4E80 ?FUN_10ba4e80@Class_10E8C6F4@@UAEPAVClass_10BA4EC0@@XZ
Class_10BA4EC0* Class_10E8C6F4::FUN_10ba4e80()
{
    Class_10BA4EC0* Object = (Class_10BA4EC0*)operator new(sizeof(Class_10BA4EC0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4ec0();
    return 0;
}
