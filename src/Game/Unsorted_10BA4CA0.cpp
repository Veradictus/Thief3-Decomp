// Game/Unsorted_10BA4CA0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4CE0
{
public:
    Class_10BA4CE0* FUN_10ba4ce0();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C6E0
{
public:
    virtual Class_10BA4CE0* FUN_10ba4ca0();
};

// FUNCTION: 0x10BA4CA0 ?FUN_10ba4ca0@Class_10E8C6E0@@UAEPAVClass_10BA4CE0@@XZ
Class_10BA4CE0* Class_10E8C6E0::FUN_10ba4ca0()
{
    Class_10BA4CE0* Object = (Class_10BA4CE0*)operator new(sizeof(Class_10BA4CE0), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4ce0();
    return 0;
}
