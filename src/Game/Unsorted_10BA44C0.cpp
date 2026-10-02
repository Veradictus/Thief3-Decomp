// Game/Unsorted_10BA44C0.cpp: functions matched byte for byte, assembled by tools/agent/integrate.py.
// Declarations above the functions belong in include/ once they settle.

class Class_10BA4500
{
public:
    Class_10BA4500* FUN_10ba4500();

    void** Unknown00;
};

// Ion Storm's placement new (0x10905C10).
void* operator new(unsigned int Size, const int& Tag, int A, int B, int C, int D);

class Class_10E8C688
{
public:
    virtual Class_10BA4500* FUN_10ba44c0();
};

// FUNCTION: 0x10BA44C0 ?FUN_10ba44c0@Class_10E8C688@@UAEPAVClass_10BA4500@@XZ
Class_10BA4500* Class_10E8C688::FUN_10ba44c0()
{
    Class_10BA4500* Object = (Class_10BA4500*)operator new(sizeof(Class_10BA4500), 0, 0, 0, 0, 0);
    if (Object)
        return Object->FUN_10ba4500();
    return 0;
}
