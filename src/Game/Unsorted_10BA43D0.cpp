// Game/Unsorted_10BA43D0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4410
{
public:
    Class_10BA4410* FUN_10ba4410();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C67C
{
public:
    virtual Class_10BA4410* FUN_10ba43d0();
};

// FUNCTION: 0x10BA43D0 ?FUN_10ba43d0@Class_10E8C67C@@UAEPAVClass_10BA4410@@XZ
Class_10BA4410* Class_10E8C67C::FUN_10ba43d0()
{
    Class_10BA4410* Object = (Class_10BA4410*)operator new(sizeof(Class_10BA4410), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4410();
    return 0;
}
